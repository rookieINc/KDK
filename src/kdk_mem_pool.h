
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName    : kdk_mem_pool.h
 * Author      : rookieINc
 * Version     : v0.1.0
 * Date        : 2015-12-01 07:28
 * Description : kdk_mem_pool.h
 * History     :     
 ***********************************************************/


#ifndef _KDK_MEM_POOL_H_INCLUDED_
#define _KDK_MEM_POOL_H_INCLUDED_

#include "kdk_base.h"
#include "kdk_malloc.h"

#define ALIGNNUM            8
#define ISNOTCLEAR          0
#define ISCLEAR             1
#define EIGHT_ALIGN(x)      x
#define ALIGN(x)            EIGHT_ALIGN(x)
#define MEMPOOLALIGNSIZE    ALIGN(sizeof(kdk_mem_pool_t))
#define MEMCELLALIGNSIZE    ALIGN(sizeof(kdk_mem_cell_t))

struct  kdk_mem_cell_s
{
    kdk_uint32              size;
    kdk_uint32              free; 
    kdk_void               *offset;
    struct kdk_mem_cell_s  *next;
};
typedef struct kdk_mem_cell_s kdk_mem_cell_t;

struct kdk_mem_pool_s
{
    kdk_uint32          realloc_size; 
    kdk_uint32          clear; //Zeta 1:is clear 0:is not clear
    kdk_mem_cell_t     *current;
    kdk_mem_cell_t     *cell_list;
};
typedef struct kdk_mem_pool_s kdk_mem_pool_t;

static kdk_mem_cell_t *
kdk_mem_cell_create(kdk_uint32 size);

static kdk_uint32 
kdk_mem_cell_clear(kdk_mem_cell_t *cell);

kdk_mem_pool_t *     
kdk_mem_pool_create(kdk_uint32 size, kdk_uint32 realloc_size);

kdk_void *          
kdk_mem_pool_malloc(kdk_mem_pool_t *head, kdk_uint32 malloc_size);

kdk_uint32          
kdk_mem_pool_print(kdk_mem_pool_t *head);

kdk_uint32          
kdk_mem_pool_clear(kdk_mem_pool_t *head);

kdk_void            
kdk_mem_pool_destroy(kdk_mem_pool_t *head);

#endif /* _KDK_MEM_POOL_H_INCLUDED_ */
