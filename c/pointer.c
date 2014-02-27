#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct test{
  int variable;
  char str[128];
}test;


void pointer(test* input)
{
  printf("input[0]:%d\n", input[0].variable);
  input[0].variable = 100;
}

int main()
{
  test body[16];// = (test*)malloc( 1, sizeof(test));
  body[0].variable = 0;
  int cnt = 0;
  /*
  for( cnt = 0; cnt < 16; cnt++)
  {
    body[cnt] = (test*) calloc( 1, sizeof( test));
    body[cnt]->variable = cnt;
  }
*/
  pointer( (test*)&body);
  printf("input[0]:%d\n", body[0].variable);
  /*
  for( cnt = 0; cnt < 16; cnt++)
  {
    free( body[cnt] );
  }
*/
  return 0;

}

