#include "string.h"
#include "stdlib.h"
#include "stdio.h"
 
int get_value_by_key(char* input,char* key, char *value, size_t value_size)
{
  int nel = 0, len = strlen(input)+1;
  char *q, *name, *qvalue, *qry_str = (char*)malloc(len*sizeof(char));
  strncpy( qry_str, input, len*sizeof(char));
  q = qry_str;
  while (strsep(&q, "&")){
    nel++;
  }
  for (q = qry_str; q < (qry_str + len);) {
    qvalue = name = q;
    for (q += strlen(q); q < (qry_str + len) && !*q; q++);
    name = strsep(&qvalue, "=");
    if(strcmp(key,name) == 0){
      strncpy(value, qvalue, value_size);
    }
  }
  free(qry_str);
  return 0;
}

int main()
{
  int len, nel;
  char query[] = "user_command=appleboy&test=1&test2=2";
  char value[32], key[32];
  snprintf(key,32,"user_command");
  get_value_by_key(query, "user_command", value, 32);
  printf("value:%s\n", value);
  snprintf(key,32,"test");
  get_value_by_key(query, key, value, 32);
  printf("value:%s\n", value);
  snprintf(key,32,"test2");
  get_value_by_key(query, key, value, 32);
  printf("value:%s\n", value);
  return 0;
}
