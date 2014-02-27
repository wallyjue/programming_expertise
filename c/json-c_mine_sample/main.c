#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json.h>

#define PAIR_KEY_LEN 64
#define PAIR_VALUE_LEN 512
typedef struct _key_pair{
  char key[PAIR_KEY_LEN+1];
  char value[PAIR_VALUE_LEN+1];
}key_pair_st;
#define NUM_KEY_PAIR(T) (sizeof(T)/sizeof(key_pair_st))


key_pair_st oauth_fields[] =                        // parsed result of register response
{
 {"message", "\0" },
 {"code",    "\0" },
 {"access_token", "\0"},
 {"token_type", "\0"},
 {"expires_in", "\0"},
 {"refresh_token", "\0"}
};

key_pair_st respn_fields[] =                        // parsed result of resend validation email
{
   {"code",    "\0" },
   {"message", "\0" },
   {"authToken", "\0"},
   {"deviceId", "\0"}
};

int qid_httpc_json_parse(char *resp, key_pair_st *entry_list, size_t num_list);

int json_grep_value( json_object* json_obj, key_pair_st* list, size_t list_size, int index)
{
  int ret = 0;
  json_object_object_foreach( json_obj, key, value)
  {
    //printf("Key: %s value: %s\n", key, json_object_get_string( value ));
    if( json_object_get_type(value) == json_type_object){
      json_grep_value( value, list, list_size, index);
    }
    else{// if(json_object_get_type( value ) == json_type_string || ){
      if( strcmp( list[index].key, key) == 0)
      {
        strncpy( list[index].value,  json_object_get_string( value ), PAIR_VALUE_LEN);
        printf("Key at index %d is [%s], Value is [%s]\n", index, key, json_object_get_string(value));
        return 0;
      }
    }
  }
  return ret;
}


int qid_httpc_json_parse(char *resp, key_pair_st *entry_list, size_t num_list)
{
    
    json_object *new_obj;
    new_obj = json_tokener_parse(resp);
    if( new_obj == NULL)
    {
      printf("new_obj == NULL\n");
        return -1;
    }
    //printf("new_obj:%s\n",json_object_get_string( new_obj ));
    int index_cnt = 0;
    for( index_cnt = 0 ; index_cnt < num_list; index_cnt++)
    {
      json_grep_value( new_obj, entry_list, num_list, index_cnt);
    }
      

    json_object_put(new_obj);
    return 0;
}




int main(int argc, char** argv)
{

  qid_httpc_json_parse(" {\"message\": \"OK\", \"code\": 0, \"result\": {\"access_token\": \"1/fFBGRNJru1FQd44AzqT3Zg\", \"token_type\": \"Bearer\", \"expires_in\": 86400, \"refresh_token\": \"tGzv3JOkF0XG5Qx2TlKWIA\"}}",
                            oauth_fields,
                            NUM_KEY_PAIR(oauth_fields));

  json_object* req_str = json_object_new_object();
  json_object_object_add(req_str, "device_id", json_object_new_string("string"));
  json_object_object_add(req_str, "user_id", json_object_new_string("string"));

  json_object* device_info = json_object_new_object();
  json_object_object_add(device_info, "device_type", json_object_new_string("string"));
  json_object_object_add(device_info, "model_name", json_object_new_string("string"));
  
  json_object_object_add( req_str, "device_info", device_info);
  json_object_object_add( req_str, "create_date", json_object_new_string("string"));
  printf("%s\n", json_object_to_json_string(req_str));
  json_object_put(req_str);
#if 0
  qid_httpc_json_parse( " {\"return\":{\"code\":\"10131006\",\"message\":\"The email kevinchien22@qnap.com is not found.\"},\"actTime\":\"Wed, 22 May 2013 12:12:56 +0000\"}",
                            respn_fields,
                            NUM_KEY_PAIR(respn_fields));
    
  qid_httpc_json_parse("/* more difficult test case */ { \"glossary\": { \"title\": \"example glossary\", \"GlossDiv\": { \"title\": \"S\", \"GlossList\": [ { \"ID\": \"SGML\", \"SortAs\": \"SGML\", \"GlossTerm\": \"Standard Generalized Markup Language\", \"Acronym\": \"SGML\", \"Abbrev\": \"ISO 8879:1986\", \"GlossDef\": \"A meta-markup language, used to create markup languages such as DocBook.\", \"GlossSeeAlso\": [\"GML\", \"XML\", \"markup\"] } ] } } }",
                            respn_fields,
                            NUM_KEY_PAIR(respn_fields));
  qid_httpc_json_parse( " { \"code\":\"123\", \"message\":\"message_is_here\", tatus_is_here\"}",
                            respn_fields,
                            NUM_KEY_PAIR(respn_fields));
#endif
    return 0;
}
