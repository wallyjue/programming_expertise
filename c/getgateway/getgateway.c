#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/route.h>

#define SUCCESS 0
#define FAILED -1

int getdefaultgateway(in_addr_t * addr)
{
  long d, g;
  char buf[256];
  int line = 0;
  FILE * f;
  char * p;
  f = fopen("/proc/net/route", "r");
  if(!f)
    return FAILED;
  while(fgets(buf, sizeof(buf), f)) {
    if(line > 0) {
      p = buf;
      while(*p && !isspace(*p))
        p++;
      while(*p && isspace(*p))
        p++;
      if(sscanf(p, "%lx%lx", &d, &g)==2) {
        if(d == 0) { /* default */
          printf("*addr:%x addr:%x &addr:%x\n", *addr, addr, &addr);
          *addr = g;
          fclose(f);
          return SUCCESS;
        }
      }
    }
    line++;
  }
  /* default route not found ! */
  if(f)
    fclose(f);
  return FAILED;
}


int main()
{
  struct in_addr addr;
  char* ip;

  long d, g;
  char buf[256];
  int line = 0;
  FILE * f;
  char * p;
  f = fopen("/proc/net/route", "r");
  if(!f)
    return FAILED;
  while(fgets(buf, sizeof(buf), f)) {
    if(line > 0) {
      p = buf;
      while(*p && !isspace(*p))
        p++;
      while(*p && isspace(*p))
        p++;
      if(sscanf(p, "%lx%lx", &d, &g)==2) {
        if(d == 0) { /* default */
          addr.s_addr = g;
          fclose(f);
          
        }
      }
    }
    line++;
  }


  
  //getdefaultgateway( &(addr.s_addr));
  printf("*addr:%x &addr:%x &addr.s_addr:%x\n", addr, &addr, &(addr.s_addr));
  ip = inet_ntoa( addr );
  
  printf("%s\n", ip);
  return 0;
}

