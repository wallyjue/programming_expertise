#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <CUnit/CUnit.h>
#include <CUnit/Automated.h>
#include <CUnit/TestDB.h>
#include "dlist.h"
#include "darray.h"

static int TestInit(void) {return 0;}
static int TestClean(void) {return 0;}

void testAssertTrue(void)
{
  CU_ASSERT_TRUE(CU_TRUE);
  CU_ASSERT_TRUE(!CU_FALSE);

  CU_ASSERT_TRUE(!CU_TRUE);
  CU_ASSERT_TRUE(CU_FALSE);
}
int main(int argc, char** argv)
{
	CU_pSuite pSuite;

    CU_initialize_registry();

    pSuite = CU_add_suite("TestHello", TestInit, TestClean);
    CU_add_test(pSuite, "testAssertTrue", testAssertTrue);

    CU_console_run_tests();
    CU_cleanup_registry();	
	
	DArray* darray = (DArray*) malloc( sizeof( DArray ));
    memset( darray, 0x00 ,sizeof(DArray));
	char* name = (char*) malloc( sizeof(char)*100);
	
	sprintf( name, "kakasi");
	darray_append( darray, sizeof(char)*strlen(name), name);
	
	darray_for_each( darray, print_content_char, NULL );
	
	darray_destory( darray );
	return 0;
}
