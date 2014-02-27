#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _qnap_notify_share
{
  int num;
  char* receivers[];
}qnap_notify_share;


void main()
{
  qnap_notify_share* notify_info;
  notify_info = (qnap_notify_share*) calloc(1, sizeof(qnap_notify_share));
  notify_info->receivers[0] = (char*) calloc( 2, sizeof(char)*64);
  sprintf(notify_info->receivers[0],"array 0");
  printf("0:%s\n",notify_info->receivers[0]);
  printf("1:%s\n",notify_info->receivers[1]);
}
