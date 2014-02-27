#include <stdio.h>
#include <stdlib.h>

int main()
{
  int a = 0;
  int p = 10;
  a = sizeof(int) * p;
  printf("a:%d\n",a);
  return 0;
}


