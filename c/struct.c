#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _key_pair{
  char key[64+1];
  char value[512+1];
}key_pair_st;
#define NUM_KEY_PAIR(T) (sizeof(T)/sizeof(key_pair_st))
typedef struct base{
  char* name;
  int year;
  int month;
}BASE;
/*
BASE content = {
  .name = "wally",
  .year = 1985,
};
*/
#define PAIR_GET_KEY(NF, ID)          NF[ID].key
#define PAIR_GET_VALUE(NF, ID)        NF[ID].value
enum qid_register_info
{
  qid_register_device_id = 0,
  qid_register_user_id,
  qid_register_device_name,
  qid_register_description,
  qid_register_device_info,

  qid_register_device_type,
  qid_register_model_name,
  qid_register_hw_serial_number,
  qid_register_fw_serial_number,
  qid_register_mac_address,

  qid_register_host_name,
  qid_register_firmware_version,
  qid_register_client_agent_version,
  qid_register_lan_ip,
  qid_register_lan_gateway,

  qid_register_wan_ip,
  qid_register_create_date,
  qid_register_update_date,
  qid_register_status,
  qid_register_published_access_code,

  num_qid_register
};


int main(int argc, char** argv)
{
  BASE new_base;
  memset( &new_base, 0 , sizeof(BASE));
  char* str = "string_for test";
  new_base.name = str;
  //strcpy( new_base.name, str);
  printf("name:%s\n", new_base.name);
  int i;
  key_pair_st register_reqst_fields2 [] =                     // HTTP fields of register request
  {
   {"device_id", "\0"},
   {"user_id", "\0"},
   {"device_name", "\0"},
   {"description", "\0"},
   {"device_info", "\0"},

   {"device_type", "\0"},
   {"model_name", "\0"},
   {"hw_serial_number", "\0"},
   {"fw_serial_number", "\0"},
   {"mac_address", "\0"},

   {"host_name", "\0"},
   {"firmware_version", "\0"},
   {"client_agent_version", "\0"},
   {"lan_ip", "\0"},
   {"lan_gateway", "\0"},

   {"wan_ip", "\0"},
   {"create_date", "\0"},
   {"update_date", "\0"},
   {"status", "\0"},
   {"published_access_code", "\0"},

   {"\0", "\0"}
  };
  for(i = 0; i < num_qid_register; i++)
  {
    printf("i:%d key:%s value:%s\n", i, PAIR_GET_KEY(register_reqst_fields2, i), PAIR_GET_VALUE(register_reqst_fields2, i));
  }
  printf("time(0):%d\n", time(0));
//  printf("sizeof:%d\n", NUM_KEY_PAIR(respn_fields));
  return 0;
}
