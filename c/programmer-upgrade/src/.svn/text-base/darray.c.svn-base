
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "darray.h"

void print_content_char(DArray* darray, void* data)
{
	printf("%s %d\n", (char*)data, data);
}

Ret darray_for_each( DArray* darray, DArrayVisitFunc function, void* data)
{
	if( darray == NULL)
		return RET_FAIL;
	
	size_t array_size = 0;
	for( array_size = 0; array_size < darray->size ; array_size++)
	{
		function( darray, darray->element + array_size);
	}
	return RET_OK;
}

Ret darray_append( DArray* thiz, size_t index, void* data)
{
	if( thiz == NULL )
	{
		return RET_FAIL;
	}	
	
	void* buffer = (void*) malloc( index * sizeof(void*) + (thiz->size) * sizeof(void*));
	memcpy( buffer, thiz->element, thiz->size);
	memcpy( buffer + sizeof(size_t)*(thiz->size), data, index*sizeof(size_t));
	thiz->size += index;
	free( data);
	data = NULL;
	free( thiz->element );
	thiz->element = NULL;
	thiz->element = buffer;

	return RET_OK;
}

Ret darray_destory( DArray* thiz)
{
	if( thiz == NULL)
		return RET_FAIL;
		
	thiz->size = 0;
	if( thiz->element != NULL)
	{
		free( thiz->element );
		thiz->element = NULL;
	}
	free( thiz );
	thiz = NULL;
	return RET_OK;
}

DArray* darray_create( DArrayDestoryFunc darray_destroy, void* ctx)
{
	DArray* darray = (DArray*) malloc( sizeof( DArray ));
	darray->size = (size_t)0;
	return darray;
}


