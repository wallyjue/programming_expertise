#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>

#define REG127 "^127\\.0\\.0\\.."
#define REG192 "^192\\.168\\.."
#define REG10 "^10\\.0\\.."
#define REG172 "^172\\.1[6-9]\\.."
#define REG0 "^0\\.."
#define REG169 "^169\\.254\\.."
#define REG_MULTICAST1 "^22[4-9]\\.."
#define REG_MULTICAST2 "^23[0-9]\\.."

#define REG_IPV4 "^[0-9]\\{1,3\\}\\.[0-9]\\{1,3\\}\\.[0-9]\\{1,3\\}\\.[0-9]\\{1,3\\}"
//#define REG_IPV4 "^[0-9]\\{1,3\\}"
char* reg_rules[] = { REG127, REG192, REG10, REG172, REG0, REG169,REG_MULTICAST1,REG_MULTICAST2};
enum
{
  reg127,
  reg192,
  reg10,
  reg172,
  reg0,
  reg169,
  reg_multicast1,
  reg_multicast2,
  num_reg_rules
};

int is_ipv4(char* ip)
{
  int ret = -1;
  regex_t regex_struct;
  regcomp( &regex_struct, REG_IPV4, 0);
  ret = regexec(&regex_struct, ip, 0, NULL, 0);
  regfree(&regex_struct);
  if( ret == REG_NOMATCH ){
    ret = 0;
  }else if( ret == 0){
    ret = 1;
  }
  return ret;
}

int is_public_ip(char* input_ip)
{
  regex_t reg;
  int ret = 0, i = 0;
  for( i = 0; i < num_reg_rules; i++){
    ret = regcomp( &reg, reg_rules[i], 0);
    ret = regexec(&reg, input_ip, 0, NULL, 0);
    if( ret == REG_NOMATCH ){
      ret = 1;
    }else if( ret == 0){
      ret = 0;
      goto exit;
    }else{
      /*
        error occurs.
      */
      return -2;
      goto exit;
    }
    regfree(&reg);
  }
exit:
  regfree(&reg);
  return ret;
}

char* ip_for_test[] = 
{
  "0.0.0.0",
  "127.0.0.1",
  "10.0.1.2",
  "172.13.1.3",
  "192.168.68.123",
  "169.254.1.2",
  "2001:0db2:85a3:08d3:1319:8a2e:0370:7344"
};

int main()
{
  int reti, i = 0;
  for( i = 0; i < 7; i++){
    reti = is_public_ip(ip_for_test[i]);
    printf("ip:%16s reti:%1d 1:is public 0:not public\n", ip_for_test[i], reti);
    reti = is_ipv4(ip_for_test[i]);
    printf("ip:%16s reti:%1d 1:is ipv4 0:not\n", ip_for_test[i], reti);
  }
  return 0;
}

