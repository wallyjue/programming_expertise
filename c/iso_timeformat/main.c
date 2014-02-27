#include <string.h>
#include <stdio.h>
#include <time.h>
void convert_iso8601(const char *time_string, int ts_len, struct tm *tm_data)
{
  tzset();

  char temp[64];
  memset(temp, 0, sizeof(temp));
  strncpy(temp, time_string, ts_len);

  struct tm ctime;
  memset(&ctime, 0, sizeof(struct tm));
  strptime(temp, "%FT%T%z", &ctime);

  long ts = mktime(&ctime) - timezone;
  localtime_r(&ts, tm_data);
}

int main()
{
 char date[] =  "2013-11-13T11:57:01.213000";
//  char date[] = "2006-03-28T16:49:29.000Z";
  struct tm tm;
  memset(&tm, 0, sizeof(struct tm));
  convert_iso8601(date, sizeof(date), &tm);

  char buf[128];
  strftime(buf, sizeof(buf), "Date: %a, %d %b %Y %H:%M:%S %Z", &tm);
  printf("%s\n", buf);
}
