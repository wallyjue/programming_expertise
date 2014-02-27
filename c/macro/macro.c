#include <stdio.h>
#include <string.h>

#ifdef DEBUG
#define E(code, s) { code, (s " [" #code "]") }
#else
#define E(code, s) { code, s }
#endif

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

typedef struct error_set{
  int code;
  const char *msg;
}error_set;

typedef enum _errno
{
    OAUTH_ERR_INVALID_REQ = 1012001,            // Missing OAuth parameters
    OAUTH_ERR_INVALID_CLI = 1010002,            // Invalid client id or secret
    OAUTH_ERR_INVALID_USER = 1012005,           // Invalid user email
    OAUTH_ERR_INVALID_PASS,                     // Invalid password
    OAUTH_ERR_INVALID_GRANT = 1012001,          // Wrong grant type {grant_type}
    OAUTH_ERR_SERVER = 1019999,                 // Authorization Failed
/* end of generic error */

}ea_errno;

error_set oauth_errorstr[] = {
  E(OAUTH_ERR_INVALID_REQ, "invalid_request"),
  E(OAUTH_ERR_INVALID_CLI, "invalid_client"),
  E(OAUTH_ERR_INVALID_USER, "invalid_user"),
  E(OAUTH_ERR_INVALID_PASS, "invalid_password"),
  E(OAUTH_ERR_INVALID_GRANT, "invalid_grant"),
  E(OAUTH_ERR_SERVER, "server_error")
};

int main(){
  int c = 0;
  for( c = 0; c < ARRAY_SIZE(oauth_errorstr); c++)
  {
    printf("c:%d code:%d msg:%s\n", c, oauth_errorstr[c].code,oauth_errorstr[c].msg);
  }
  return 0;
}



