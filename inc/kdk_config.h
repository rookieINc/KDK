
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName    : kdk_config.h
 * Author      : rookieINc
 * Version     : v0.1.0
 * Date        : 2015-12-22 21:33
 * Description : kdk_config.h
 * History     : 
 ***********************************************************/


#ifndef _KDK_CONFIG_H_INCLUDED_
#define _KDK_CONFIG_H_INCLUDED_

#include "kdk_base.h"
#include "kdk_mem_pool.h"
#include "kdk_hash_table.h"

#define FLAG_COMMENT   1
#define FLAG_SECTION   2
#define FLAG_KEYVALUE  3

#define CONFIG_KEY_LEN      42
#define CONFIG_VALUE_LEN    42
#define CONFIG_SECTION_LEN  42
#define CONFIG_LINE_LEN     110

struct kdk_config_s
{
    kdk_uint32                  mem_pool_type;
    struct kdk_mem_pool_s      *mem_pool;
    struct kdk_hash_table_s    *coll;
    kdk_file                   *file_handle;
};

typedef struct kdk_config_s kdk_config_t;

static kdk_uint32
kdk_config_parse_section(kdk_char32 *str, kdk_char32 *section);

static kdk_uint32
kdk_config_parse_key_value(kdk_char32 *str, kdk_char32 *key, kdk_char32 *value);

static kdk_uint32
kdk_config_parse_comment(kdk_char32 *str);

static kdk_uint32
kdk_config_parse_line(kdk_config_t *config, kdk_char32 *str, kdk_char32 *section);

kdk_config_t * 
kdk_config_create(kdk_mem_pool_t *mem_pool, kdk_uint32 mem_pool_size, kdk_char32 *config_file);

kdk_uint32 
kdk_config_init(kdk_config_t *config);

kdk_uint32 
kdk_config_set_value(kdk_config_t *config, kdk_char32 *section, kdk_char32 *key, kdk_char32 *value);

kdk_uint32 
kdk_config_get_value(kdk_config_t *config, kdk_char32 *section, kdk_char32 *key, kdk_char32 *value);

kdk_void 
kdk_config_destroy(kdk_config_t *config);


#endif /* _KDK_CONFIG_H_INCLUDED_ */
