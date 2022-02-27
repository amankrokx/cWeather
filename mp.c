#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
        printf("skipped : %c\n", start[i]);
        continue;
        break;
    }
    printf("%c", start[i]);
    loc[k++] = start[i];
  }
  loc[k] = '\0';
  return loc;
}

int main () {
  char json[] = "{\"coord\":{\"lon\":85.3099,\"lat\":23.3426},\"weather\":[{\"id\":721,\"main\":\"Haze\",\"description\":\"haze\",\"icon\":\"50d\"}],\"base\":\"stations\",\"main\":{\"temp\":295.12,\"feels_like\":294.42,\"temp_min\":295.12,\"temp_max\":295.12,\"pressure\":1016,\"humidity\":40},\"visibility\":4000,\"wind\":{\"speed\":2.06,\"deg\":10},\"clouds\":{\"all\":0},\"dt\":1644820306,\"sys\":{\"type\":1,\"id\":9131,\"country\":\"IN\",\"sunrise\":1644799945,\"sunset\":1644840823},\"timezone\":19800,\"id\":1258526,\"name\":\"Ranchi\",\"cod\":200}";
  puts(json);
  char s[20];
  s[0] = '\"';
  scanf("%s", s + 1);
  int t = strlen(s);
  s[t] = '\"';
  s[t+1] = '\0';
  printf(" looking for %s \n", s);

  int o;
  scanf("%d", &o);
  char * out = (char *) malloc(30);
  out = getvalue( json, s, o, out);
  printf("\n value : %s\n", out);
  return 0;
}
