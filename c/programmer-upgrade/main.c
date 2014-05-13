#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dlist.h"
#include "darray.h"

int main(int argc, char** argv)
{
	DArray* darray = (DArray*) malloc( sizeof( DArray ));
	char* name = (char*) malloc( sizeof(char)*100);
	
	sprintf( name, "kakasi");
	darray_append( darray, sizeof(char)*strlen(name), name);
	
	darray_for_each( darray, print_content_char, NULL );
	
	darray_destory( darray );
	return 0;
}
