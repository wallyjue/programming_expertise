#include <stdio.h>
#include <stdint.h>
#define OFFSET(T, F)            (size_t)(&(((T *)0)->F))
#define DEALER_CONN_CB_GET(W, F)    (void *)((uint8_t *)(W)-OFFSET(DEALER_CONN_T, F))

typedef struct some_struct SOME_STRUCT_T;
struct some_struct
{
  int abc;
  int cde;
  char siz[128];
};

typedef struct _dealer_conn_st DEALER_CONN_T;
struct _dealer_conn_st
{
  int member_one;
  char string_one[64];
  int member_two;
  SOME_STRUCT_T* some;
};

int main()
{
  int addr;
  DEALER_CONN_T st;
  addr = DEALER_CONN_CB_GET( st.some, some);
  printf("st:%x addr:%x st.some:%x W:%x offset:%x\n", &st, &addr, &(st.some),(void*)(uint8_t*)&(st.some), OFFSET(DEALER_CONN_T, some));

  return 0;
}
