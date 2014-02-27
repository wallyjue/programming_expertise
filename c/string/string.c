#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){

  int ret = -1;
  char a1[128] = "https://192.168.68.235/v1.1/device/1234567890";
  char a2[128] = "device";
  char* pos = NULL;
  ret = strspn( a1, a2);
  pos = strstr( a1, a2);
  printf("ret:%d pos:%s\n", ret, pos);
  return 0;
}

