#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

struct string {
  char *ptr;
  size_t len;
};

typedef struct string ST;

void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s) {
  size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}

char* urlencode(char* originalText) {
    // allocate memory for the worst possible case (all characters need to be encoded)
    char *encodedText = (char *)malloc(sizeof(char)*strlen(originalText)*2);
    int pos = 0;
    for (size_t i = 0; i < strlen(originalText); i++) {
        if (originalText[i] == '&') {
            encodedText[pos++] = '\\';
        }
        encodedText[pos++] = originalText[i];
    }
    encodedText[pos] = '\0';
    return encodedText;
}

char * getvalue( char * json, char * key, int occ, char * loc ) {
  char * start = strstr(json, key) + strlen(key);
  while (occ > 1) {
    char * t = strstr(start, key) + strlen(key);
    occ--;
    if ( t ) start = t;
    else break;
  }

  int k = 0;
  for (int i = 0; start[i] != ',' && start[i] != '}'; i++) {
    switch (start[i]) {
      case ' ':
      case '\"':
      case '{':
      case ':':
        //printf("skipped : %c\n", start[i]);
        continue;
        break;
    }
    //printf("%c", start[i]);
    loc[k++] = start[i];
  }
  loc[k] = '\0';
  return loc;
}

ST geocode(char * lat, char * lon) {
    char * buff = (char *) malloc(1024);
    struct string s;
    CURL *hnd = curl_easy_init();
    sprintf(buff, "https://google-maps-geocoding.p.rapidapi.com/geocode/json?latlng=%s%%2C%s&language=en", lat, lon);
    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_URL, buff);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "X-RapidAPI-Key: 15be109401msh039dc334993a18cp1b9113jsn7f88dd5900bf");
    headers = curl_slist_append(headers, "X-RapidAPI-Host: google-maps-geocoding.p.rapidapi.com");
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

    CURLcode response = curl_easy_perform(hnd);
    init_string(&s);
    if(response != CURLE_OK) {
        fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(response));
        strcpy(s.ptr, curl_easy_strerror(response));
        return s;
    } /*else {
        printf("Data : \n%s", s.ptr);
    }*/
    curl_easy_cleanup(hnd);
    return s;
}
ST getreq(char * ur) {
    CURL *curl;
    CURLcode response;
    struct string s;
    init_string(&s);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, ur);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);  
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

        response = curl_easy_perform(curl);

        if(response != CURLE_OK) {
            fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(response));
            strcpy(s.ptr, curl_easy_strerror(response));
            return s;
        } /*else {
            printf("Data : \n%s", s.ptr);
        }*/
        curl_easy_cleanup(curl);
    }
    return s;
}

int main () {
  char * buff = (char *) malloc(1024);
  //ST weatheratip = getreq("https://api.openweathermap.org/data/2.5/weather?lat=12.9634&lon=77.5855&appid=b1741d4b9a702da375fddc8571ba4eaa");
  ST ip = getreq("http://ip-api.com/json");
  char * lat = (char *) malloc(12);
  char * lon = (char *) malloc(12);
  lat = getvalue(ip.ptr, "\"lat\"", 1, lat);
  lon = getvalue(ip.ptr, "\"lon\"", 1, lon);
  sprintf(buff, "https://api.openweathermap.org/data/2.5/weather?lat=%s&lon=%s&appid=b1741d4b9a702da375fddc8571ba4eaa", lat, lon);
  ST weatheratip = getreq(buff);
  char * desc = (char *) malloc(15);
  char * temp = (char *) malloc(15);
  char * pressure = (char *) malloc(15);
  char * addr = (char *) malloc(100);
  desc = getvalue(weatheratip.ptr, "\"description\"", 1, desc);
  temp = getvalue(weatheratip.ptr, "\"temp\"", 1, temp);
  pressure = getvalue(weatheratip.ptr, "\"pressure\"", 1, pressure);
  ST address = geocode(lat, lon);
  addr = getvalue(address.ptr, "\"formatted_address\"", 1, addr);

  printf("\nWeather : %s\nTemperature: %s\nPressure : %s\nAddress : %s\n\n", desc, temp, pressure, addr);

  free(ip.ptr);
  free(weatheratip.ptr);
  
  //out = getvalue( json, s, o, out);
  //printf("\n value : %s\n", out);
  return 0;
}
