#ifndef __IF_DARRAY_H__
#define __IF_DARRAY_H__
#define _GNU_SOURCE 
#define RET_OK 1
#define RET_FAIL 0
/*
struct _DArrayElement
{
	char* data;
};
typedef struct _DArrayElement DArrayElement;
*/
struct _DArray
{
	size_t size;
	void* element;
};
typedef struct _DArray DArray;

typedef void (*DArrayVisitFunc) (DArray*, void*);
typedef void (*DArrayCompareFunc) (DArray*, void*);
typedef void (*DArrayDestoryFunc) (DArray*);
typedef int Ret;

DArray* darray_create(DArrayDestoryFunc data_destory, void* ctx);
Ret darray_insert(DArray* thiz, size_t index, void* ctx);
Ret darray_prepend( DArray* thiz, size_t index, void* ctx);
Ret darray_append( DArray* thiz, size_t index, void* ctx);
Ret darray_delete( DArray* thiz, size_t index, void* ctx);
Ret darray_get_by_index( DArray* thiz, size_t index, void** data);
Ret darray_set_by_index( DArray* thiz, size_t index, void* data);
size_t darray_length( DArray* thiz);
int darray_find( DArray* thiz, DArrayCompareFunc cmp, void* ctx);
Ret darray_for_each( DArray* thiz, DArrayVisitFunc visit, void* ctx); 

Ret darray_destory( DArray* thiz);


void print_content_char(DArray* darray, void* data);

#endif 
