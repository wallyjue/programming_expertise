#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TMP_BUFF_LEN 20
#define NO_ERROR 0
int util_read_file_to_string(char* filename,char** output, size_t* string_size)
{
  int ret = 0;
  FILE* f = NULL;
  f = fopen( filename, "rb");
  *output = (char*) calloc(sizeof(char), TMP_BUFF_LEN);
  *string_size = 0;
  char buf[TMP_BUFF_LEN+1];
  while(0 != (ret = fread(buf, 1, TMP_BUFF_LEN, f)) )
  {
    *output = realloc( *output, *string_size + ret +1);
    strncat( *output, buf, ret);
    *string_size += ret;
  }
  if( feof(f) ){
    ret = NO_ERROR;
  }else{
    ret = ferror(f);
  }
  fclose(f);
  return ret;
}


int main()
{
  char* buf = NULL;
  size_t len;
  util_read_file_to_string("file_for_test.txt", &buf, &len);

  free( buf);
  return 0;
}
