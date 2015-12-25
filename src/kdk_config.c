
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName    : kdk_config.c
 * Author      : rookieINc
 * Version     : v0.1.0
 * Date        : 2015-12-22 21:30
 * Description : kdk_config.c
 * History     : 
 ***********************************************************/


#include "kdk_config.h"

kdk_void 
kdk_config_destroy(kdk_config_t *config)
{
    if(config == KDK_NULL)
        return ;

    if(config->config_file_handle != KDK_NULL)
        fclose(config->config_file_handle);

    config->config_file_handle = KDK_NULL;

    if(config->mem_pool != KDK_NULL && config->mem_pool_type == OWN_MEM_POOL)
        kdk_mem_pool_destroy(config->mem_pool);

    return ;
}

kdk_config_t * 
kdk_config_create(kdk_mem_pool_t *mem_pool, kdk_uint32 mem_pool_size, kdk_char32 *config_file)
{
    kdk_uint32        mem_pool_type = OTHER_MEM_POOL;
    kdk_config_t     *config;

    if(config_file == KDK_NULL)
        return KDK_NULL;

    if(mem_pool == KDK_NULL)
    {
        mem_pool = kdk_mem_pool_create(mem_pool_size, mem_pool_size);
        if(mem_pool == KDK_NULL)
            return KDK_NULL;
        mem_pool_type = OWN_MEM_POOL;
    }

    config = (kdk_config_t *)kdk_mem_pool_malloc(mem_pool, sizeof(kdk_config_t));
    if(config == KDK_NULL)
    {
        if(mem_pool_type == OWN_MEM_POOL)
            kdk_mem_pool_destroy(mem_pool);
        return KDK_NULL;
    }

    config->mem_pool_type = mem_pool_type;
    config->mem_pool = mem_pool;
    config->config_file_handle = fopen(config_file, "r");
    if(config->config_file_handle == KDK_NULL)
    {
        kdk_config_destroy(config);
        return KDK_NULL;
    }

    config->config_table = kdk_hash_table_create(config->mem_pool, mem_pool_size, 103);
    if(config->config_table == KDK_NULL)
    {
        kdk_config_destroy(config);
        return KDK_NULL;
    }

    return config;
}

kdk_uint32 
kdk_config_get_value(kdk_config_t *config, kdk_char32 *section, kdk_char32 *key, kdk_char32 *value)
{
    kdk_uint32     hash_key_len = CONFIG_SECTION_LEN + CONFIG_KEY_LEN;
    kdk_char32     hash_key[CONFIG_SECTION_LEN + CONFIG_KEY_LEN] = {0};
    kdk_char32    *ret_value;

    if(config == KDK_NULL || section == KDK_NULL || key == KDK_NULL || value == KDK_NULL)
        return KDK_INARG;

    if(strlen(section) + strlen(key) >= hash_key_len)    
        return KDK_OVERFLOW;

    snprintf(hash_key, hash_key_len, "%*s%*s", CONFIG_SECTION_LEN, section, CONFIG_KEY_LEN, key);

    ret_value = (kdk_char32 *)kdk_hash_table_get_value(config->config_table, hash_key);
    if(ret_value == KDK_NULL)
        return KDK_NULLPTR;
    else if(ret_value == KDK_NULLFOUND)
        return KDK_NOTFOUND;

    strncpy(value, ret_value, strlen(ret_value));
    
    return KDK_SUCCESS;  
}

kdk_uint32 
kdk_config_set_value(kdk_config_t *config, kdk_char32 *section, kdk_char32 *key, kdk_char32 *value)
{
    kdk_uint32      hash_key_len = CONFIG_SECTION_LEN + CONFIG_KEY_LEN;
    kdk_char32      hash_key[CONFIG_SECTION_LEN + CONFIG_KEY_LEN] = {0};
    kdk_uint32      ret_code;

    if(config == KDK_NULL || section == KDK_NULL || key == KDK_NULL || value == KDK_NULL)
        return KDK_NULLPTR;

    if(strlen(section) + strlen(key) >= hash_key_len)    
        return KDK_OVERFLOW;
 
    snprintf(hash_key, hash_key_len, "%*s%*s", CONFIG_SECTION_LEN, section, CONFIG_KEY_LEN, key);

    ret_code = kdk_hash_table_set_value(config->config_table, (kdk_char32 *)hash_key, (void *)value, strlen(value));
    if(ret_code)
        return KDK_NULLPTR;

    return KDK_SUCCESS;  
}

kdk_uint32
kdk_config_parse_section(kdk_char32 *str, kdk_char32 *section)
{
    kdk_char32    *offset;
    kdk_uint32   i;

    if(str == KDK_NULL || section == KDK_NULL)
        return KDK_NULLPTR;

    offset = strchr(str, ']');  
    if(offset == KDK_NULL)
        return KDK_INVAL;
    
    *offset = END_TAG;

    if(offset - str > CONFIG_SECTION_LEN)
        return KDK_OVERFLOW;

    strncpy(section, str + 1, strlen(str + 1) + 1);

    for(i = 0; i < strlen(section); i++)
    {
/*
        if(isvarset(section[i]) == 0)
        {
            return KDK_INVAL;
        }
*/
    }

    return KDK_SUCCESS;
}

kdk_uint32
kdk_config_parse_key_value(kdk_char32 *str, kdk_char32 *key, kdk_char32 *value)
{
    kdk_uint32  i;

    if(str == KDK_NULL || key == KDK_NULL || value == KDK_NULL)
        return KDK_NULLPTR;

    sscanf(str, "%41[^=]=%41s", key, value);

    for(i = 0; i < strlen(key); i++)
    {
/*
        if(isvarset(key[i]) == 0)
            return KDK_INVAL;
*/
    }

    if(strlen(value) == 0)
        return KDK_INVAL;

    return KDK_SUCCESS;
}

kdk_uint32
kdk_config_parse_comment(kdk_char32 *str)
{
    if(str == KDK_NULL)
        return KDK_NULLPTR;

    return KDK_SUCCESS;
}

kdk_uint32
kdk_config_parse_line(kdk_config_t *config, kdk_char32 *str, kdk_char32 *section)
{
    kdk_char32      key[CONFIG_KEY_LEN] = {0};
    kdk_char32      value[CONFIG_VALUE_LEN] = {0};
    kdk_uint32      case_num = 0;
    kdk_uint32      ret_code = 0;

/*
    if(isspace(str[0]) || str[0] == '#')
        case_num = FLAG_COMMENT;
    else if(str[0] == '[')
        case_num = FLAG_SECTION;
    else if(isvarset(str[0]))
        case_num = FLAG_KEYVALUE;
*/
    if(isspace(str[0]) || str[0] == '#')
        case_num = FLAG_COMMENT;
    else if(str[0] == '[')
        case_num = FLAG_SECTION;
    else
        case_num = FLAG_KEYVALUE;

    switch(case_num)
    {
        case    FLAG_COMMENT:
            ret_code = kdk_config_parse_comment(str);
fprintf(stderr, "[%s]:[%s]\n", "comment", str);
            break;
        case    FLAG_SECTION:
            ret_code = kdk_config_parse_section(str, section);
fprintf(stderr, "[%s]:[%s]\n", "section", section);
            break;
        case    FLAG_KEYVALUE:
            if(strlen(section) == 0)
                return KDK_INVAL;
            
            ret_code = kdk_config_parse_key_value(str, key, value);
            if(ret_code)
                return ret_code;

            ret_code = kdk_config_set_value(config, section, key, value);
fprintf(stderr, "[%s]:[%s][%s]\n", "keyvlue", key, value);
            break;
        default:
fprintf(stderr, "dafault\n");
            ret_code = KDK_INVAL;
            break;
    }

    return ret_code;
}

kdk_uint32 
kdk_config_parse(kdk_config_t *config)
{
    kdk_char32    section[CONFIG_SECTION_LEN] = {0};
    kdk_char32    line[CONFIG_LINE_LEN] = {0};;
    kdk_uint32    ret_code;

    while(fgets(line, CONFIG_LINE_LEN, config->config_file_handle) != KDK_NULL) 
    {
        ret_code = kdk_config_parse_line(config, line, section); 
        if(ret_code)
            return ret_code;
        memset(line, 0, sizeof(line));
    }

    return KDK_SUCCESS;
}
