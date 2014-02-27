#include <stdio.h>
#include <getopt.h>
char *l_opt_arg;
char* const short_options = "n:h";
struct option long_options[] = {
   { "name",     0,   NULL,    'n'     },
   { "help",  0,   NULL,    'h'     },
   {      0,     0,     0,     0},
};

#define USAGE "usage: ./qpkg_get -n \"QPKG_NAME\"\n"
#define QPKG_JSON_V1 "{\"statusCode\": \"%d\",\"message\": \"REQUEST successfully\", \"result\":[{\"qpkgId\": \"%s\", \"sum\":{\"download\": %d, \"update\": %d, \"install\": %d}}]"

int main(int argc, char *argv[])
{
   int c;
   while((c = getopt_long (argc, argv, short_options, long_options, NULL)) != -1)
   {
     switch (c)
     {
       case 'n':
         struct qcloud_st *ctx;
         qnap_app_info app;
         qpkg_info info;
         char output_buf[512];

         memset(&info, 0x0, sizeof(qpkg_info));
         memset(&app, 0x0, sizeof(qnap_app_info));

         ctx = qcloud_init_ctx( &app);
         ret = qcloud_get_qpkg_info(ctx, optarg, &info);
         if(ret == 0){
           sprintf(output_buf, QPKG_JSON_V1, ret, info.qpkg_id, info.counter.downloaded, info.counter.updated, info.counter.installed);
           printf("%s\n", output_buf);
         }
         qcloud_cleanup_ctx( ctx);
         break;
       default:
       case 'h':
         printf(USAGE);
         goto exit;
         break;
     }
   }
  printf(USAGE);
exit:
  return 0;
}
