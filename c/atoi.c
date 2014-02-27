#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
  char str[1024];
  memset( str, 0, 1024);
  printf("strlen:%d\n", strlen(str));
  return 0;
}
