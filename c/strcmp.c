#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO_ERROR (0)


int main(int argc, char** argv)
{
  int ret = 1;
  ret = atoi("invalid_password");
  printf("ret:%d\n", ret);
  ret = 1;

  ret = atoi(" ");
  printf("ret:%d\n", ret);
  ret = 1;

  ret = atoi(NO_ERROR);
  printf("ret:%d\n", ret);
  ret = 1;



  ret = atoi("0");
  printf("ret:%d\n", ret);
  return 0;
}

