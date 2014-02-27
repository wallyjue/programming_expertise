#include <stdio.h>
#include <stdlib.h>

int foo(int input)
{
  return input;
}


int main()
{
  int ret = 1;
  int input = 2;
  if( (ret = foo(input)) == 0)
  {
    printf("if ret:%d\n", ret);
  }
  

  printf("end ret:%d\n", ret);
  return 0;
}

