#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
//#include "QidDB.h"
#define CREATE_QID_DB           "CREATE TABLE QID (qid char(64) ,local_name char(64));"
#define INSERT_QID_DB           "INSERT INTO QID (qid, local_name) values ('%s', '%s');"
#define QUERY_QID_DB            "SELECT * FROM QID WHERE %s = '%s'"
#define DELETE_ENTRY_QID_DB     "DELETE FROM QID WHERE %s = '%s'"
#define UPDATE_QID_DB           "UPDATE QID SET %s = '%s' WHERE %s = '%s'"
#define ALTER_QID_DB            "ALTER TABLE QID ADD COLUMN %s %s"
#define MAX_SYSTEM_CMD (512)

int qid_sys_alter_db(char* db_path,char* column_name,char* column_type)
{
  sqlite3 *db;
  char *errMsg = NULL;
  char cmd[MAX_SYSTEM_CMD+1];
  snprintf(cmd, MAX_SYSTEM_CMD, ALTER_QID_DB, column_name, column_type);
  sqlite3_open(db_path, &db);
  if( sqlite3_exec( db,cmd, NULL, NULL, &errMsg) != SQLITE_OK){
    sqlite3_close(db);
    sqlite3_free(errMsg);
    return -1;
  }
  else{
    sqlite3_close(db);
    return 0;
  }
}

int qid_sys_create_sql_db(char* db_path)
{
  sqlite3 *db;
  char *errMsg = NULL;
  sqlite3_open(db_path, &db);
  if( sqlite3_exec(db,CREATE_QID_DB,NULL,NULL,&errMsg) != SQLITE_OK){
    sqlite3_close(db);
    sqlite3_free(errMsg);
    return -1;
  }
  else{
    sqlite3_close(db);
    return 0;
  }
}

int qid_sys_insert_sql_db(char* db_path, char* qid, char* local_name)
{
  sqlite3 *db;
  char *errMsg = NULL;
  char cmd[MAX_SYSTEM_CMD+1];
  snprintf(cmd, MAX_SYSTEM_CMD, INSERT_QID_DB, qid, local_name);
  sqlite3_open(db_path, &db);
  if( sqlite3_exec( db,cmd, NULL, NULL, &errMsg) != SQLITE_OK){
    sqlite3_close(db);
    sqlite3_free(errMsg);
    return -1;
  }
  else{
    sqlite3_close(db);
    return 0;
  }
}

int qid_sys_update_sql_db(char* db_path, char* wherekey, char* wherevalue
                           , char* setkey, char* setvalue)
{
  sqlite3 *db;
  char *errMsg = NULL;
  char cmd[MAX_SYSTEM_CMD+1];
  snprintf(cmd, MAX_SYSTEM_CMD, UPDATE_QID_DB, setkey, setvalue, wherekey, wherevalue);
  sqlite3_open(db_path, &db);
  if( sqlite3_exec( db,cmd, NULL, NULL, &errMsg) != SQLITE_OK){
    sqlite3_close(db);
    sqlite3_free(errMsg);
    return -1;
  }
  else{
    sqlite3_close(db);
    return 0;
  }
}

int qid_sys_delete_sql_db(char* db_path, char* wherekey, char* wherevalue)
{
  sqlite3 *db;
  char *errMsg = NULL;
  char cmd[MAX_SYSTEM_CMD+1];
  snprintf(cmd, MAX_SYSTEM_CMD, DELETE_ENTRY_QID_DB, wherekey, wherevalue);
  printf("cmd:%s\n", cmd);
  sqlite3_open(db_path, &db);
  if( sqlite3_exec( db,cmd, NULL, NULL, &errMsg) != SQLITE_OK){
    sqlite3_close(db);
    sqlite3_free(errMsg);
    return -1;
  }
  else{
    sqlite3_close(db);
    return 0;
  }
}

int query_callback(void* ret,int cnt,char** value,char** name)
{
  sprintf((char*)ret, "%s", *(value+1));
  return 0;
}

int qid_sys_query_sql_db(char* db_path, char* wherekey, char* wherevalue, char* ret)
{
  sqlite3 *db;
  char *errMsg = NULL;
  char cmd[MAX_SYSTEM_CMD+1];
  snprintf(cmd, MAX_SYSTEM_CMD, QUERY_QID_DB, wherekey, wherevalue);
  sqlite3_open(db_path, &db);
  if( sqlite3_exec( db,cmd, query_callback, ret, &errMsg) != SQLITE_OK){
    sqlite3_close(db);
    sqlite3_free(errMsg);
    return -1;
  }
  else{
     sqlite3_close(db);
    return 0;
  }
}
#define DB_PATH "sql.db"

int main()
{
   sqlite3 *db;
   char resp[256];

   qid_sys_create_sql_db(DB_PATH);
   qid_sys_insert_sql_db(DB_PATH, "wallyjue@gmail.com", "wally");
   qid_sys_query_sql_db(DB_PATH, "qid", "wallyjue@gmail.com", resp);
   printf("resp:%s\n", resp);
   qid_sys_update_sql_db(DB_PATH, "qid","wallyjue@gmail.com", "local_name", "wallychang");
   qid_sys_query_sql_db(DB_PATH, "qid", "wallyjue@gmail.com", resp);
   printf("resp:%s\n", resp);
   qid_sys_delete_sql_db(DB_PATH, "qid", "wallyjue@gmail.com");
   qid_sys_query_sql_db(DB_PATH, "qid", "wallyjue@gmail.com", resp);
   printf("resp:%s\n", resp);
   return 0;
}
