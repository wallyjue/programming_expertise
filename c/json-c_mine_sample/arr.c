#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json.h>
typedef struct _key_pair{
  char key[64+1];
  char value[512+1];
}key_pair_st;
#define NUM_KEY_PAIR(T) (sizeof(T)/sizeof(key_pair_st))
key_pair_st reg_fields[] =
{
 {"code",    "\0" },
 {"message", "\0" },
 {"device_id", "\0"},
 {"result", "\0"}
};



int main()
{





    json_object* my_array, *root, *entry;
    
    my_array = json_object_new_array();
    root = json_object_new_object();
    entry = json_object_new_object();
    json_object_object_add( entry,"key", json_object_new_string("value"));
    json_object_object_add( entry,"bool1", json_object_new_boolean(1234));
    json_object_object_add( entry,"bool2", json_object_new_boolean(0));
    json_object_object_add( entry,"bool3", json_object_new_boolean(-1));
    json_object_object_add( entry,"bool4", json_object_new_boolean(1234));
    json_object_array_add(my_array,entry);
	//json_object_array_add(my_array, json_object_new_int(2));
	//json_object_array_add(my_array, json_object_new_int(3));
    //json_object_object_add(root, "array", my_array);
    printf("%s\n",json_object_to_json_string(my_array));
    json_object_put(root);

    return 0;
}
