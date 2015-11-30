#include "kdk.h"

#ifndef __KDK_MEM_POOL_H__
#define __KDK_MEM_POOL_H__

#define ALIGNNUM            8
#define ISNOTCLEAR          0
#define ISCLEAR             1
#define EIGHT_ALIGN(x)      x
#define ALIGN(x)            EIGHT_ALIGN(x)
#define MEMPOOLALIGNSIZE    ALIGN(sizeof(kdk_mem_pool_t))
#define MEMCELLALIGNSIZE    ALIGN(sizeof(kdk_mem_cell_t))

typedef struct  kdk_mem_cell_s
{
    kdk_uint32              mem_cell_size;
    kdk_uint32              mem_cell_free; 
    void                   *mem_cell_offset;
    struct kdk_mem_cell_s  *mem_cell_next;
}kdk_mem_cell_t;

typedef struct kdk_mem_pool_s
{
    kdk_uint32          mem_pool_realloc_size; 
    kdk_uint32          mem_pool_clear; //Zeta 1:is clear 0:is not clear
    kdk_mem_cell_t     *mem_pool_cell_offset;
    kdk_mem_cell_t     *mem_pool_cell_list;
}kdk_mem_pool_t;

kdk_mem_pool_t *   kdk_mem_pool_create(kdk_uint32 size, kdk_uint32 realloc_size);
void *          kdk_mem_pool_malloc(kdk_mem_pool_t *head, kdk_uint32 malloc_size);
kdk_uint32      kdk_mem_pool_print(kdk_mem_pool_t *head);
kdk_uint32      kdk_mem_pool_clear(kdk_mem_pool_t *head);
void            kdk_mem_pool_destroy(kdk_mem_pool_t *head);

#endif
