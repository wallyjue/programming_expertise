#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#define BUF_SIZE 128


enum{
  UTC=0,
  localTZ
};

#define ISO8601_FORMAT  "%Y-%m-%dT%T"
void util_convert_to_iso8601(time_t timer, char* output_str, int TZType)
{
  struct tm* tm_info;
  struct timeval tv;
  char buffer[BUF_SIZE];
  char temp[BUF_SIZE];
  char tztemp[BUF_SIZE];
  memset( tztemp,0,sizeof(char)*BUF_SIZE);
  if(TZType == UTC){
    tm_info = gmtime(&timer);
  }else{
    tm_info = localtime(&timer);
  }
  gettimeofday(&tv,NULL);

  strftime(buffer, BUF_SIZE, ISO8601_FORMAT, tm_info);
  if(TZType == UTC){
    snprintf(temp,BUF_SIZE,".%3d000", (int)tv.tv_usec/1000);
  }else{
    strftime(tztemp, BUF_SIZE, "%Z", tm_info);
    snprintf(temp,BUF_SIZE,".%3d", (int)tv.tv_usec/1000);
  }
  strcat(buffer,temp);
  if(strlen(tztemp) > 0 ){
    strcat(buffer,tztemp);
  }
  printf("output:%s\n", buffer);
}

int main()
{
    time_t timer;
    char buffer[BUF_SIZE];
    struct tm* tm_info;
    struct tm* gmtm_info;

    time(&timer);
//  timer = (time_t)1386990566;
    tm_info = localtime(&timer);
    gmtm_info = gmtime(&timer);

  util_convert_to_iso8601(timer, NULL, UTC);
  util_convert_to_iso8601(timer, NULL, localTZ);
//    strftime(buffer, BUF_SIZE, "gmtime    %Y:%m:%d %H:%M:%S %Z", gmtm_info);
//    puts(buffer);
    memset( buffer, BUF_SIZE, sizeof(char));
    strftime(buffer, BUF_SIZE, "localtime %Y:%m:%d %H:%M:%S %Z", tm_info);
    puts(buffer);

    return 0;
}
