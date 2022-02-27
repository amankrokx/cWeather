#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    for (int i = 0; i < strlen(originalText); i++) {
        if (originalText[i] == '&') {
            encodedText[pos++] = '\\';
        }
        encodedText[pos++] = originalText[i];
    }
    encodedText[pos] = '\0';
    return encodedText;
}


int main(void) {
    CURL *curl;
    CURLcode response;
    char res[1024] = {0};
    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if(curl) {
        struct string s;
        init_string(&s);
        //char * url = urlencode("https://api.openweathermap.org/data/2.5/weather?lat=23.3426&lon=85.3099&appid=b1741d4b9a702da375fddc8571ba4eaa");
        //printf("Encoded : %s\n\n", url);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);  
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);         
        curl_easy_setopt(curl, CURLOPT_CAINFO, "cacert.pem");
        curl_easy_setopt(curl, CURLOPT_CAPATH, "cacert.pem");
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openweathermap.org/data/2.5/weather?lat=23.3426&lon=85.3099&appid=b1741d4b9a702da375fddc8571ba4eaa");
        //curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        response = curl_easy_perform(curl);

        if(response != CURLE_OK) {
            fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(response));
        } else {
            printf("Data : \n%s", s.ptr);
            free(s.ptr);
        }
        //curl_free(url);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return 0;
}
