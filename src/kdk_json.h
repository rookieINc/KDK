
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName    : kdk_json.h
 * Author      : rookieINc
 * Version     : v0.1.0
 * Date        : 2016-03-31 15:36
 * Description : kdk_json.h
 * History     : 
 ***********************************************************/


#ifndef _KDK_JSON_H_INCLUDED_
#define _KDK_JSON_H_INCLUDED_

#include "kdk_base.h"
#include "cJSON.h"


typedef struct cJSON        kdk_json_t;

typedef struct cJSON_Hooks  kdk_json_hooks_t;

#define kdk_json_init_hooks                 cJSON_InitHooks
#define kdk_json_parse                      cJSON_Parse
#define kdk_json_print                      cJSON_Print
#define kdk_json_print_unformat             cJSON_PrintUnformatted
#define kdk_json_print_buffer               cJSON_PrintBuffered
#define kdk_json_delete                     cJSON_Delete
#define kdk_json_get_array_size             cJSON_GetArraySize
#define kdk_json_get_array_item             cJSON_GetArrayItem
#define kdk_json_get_object_item            cJSON_GetObjectItem
#define kdk_json_get_error_ptr              cJSON_GetErrorPtr
#define kdk_json_create_null                cJSON_CreateNull
#define kdk_json_create_true                cJSON_CreateTrue
#define kdk_json_create_false               cJSON_CreateFalse
#define kdk_json_create_bool                cJSON_CreateBool
#define kdk_json_create_number              cJSON_CreateNumber
#define kdk_json_create_string              cJSON_CreateString
#define kdk_json_create_array               cJSON_CreateArray
#define kdk_json_create_object              cJSON_CreateObject
#define kdk_json_create_int_array           cJSON_CreateIntArray
#define kdk_json_create_float_array         cJSON_CreateFloatArray
#define kdk_json_create_double_array        cJSON_CreateDougleArray
#define kdk_json_create_string_array        cJSON_CreateStringArray
#define kdk_json_add_item_to_array          cJSON_AddItemToArray
#define kdk_json_add_item_to_object         cJSON_AddItemToObject
#define kdk_json_add_item_to_object_cs      cJSON_AddItemToObjectCS
#define kdk_json_add_item_refer_to_array    cJSON_AddItemReferenceToArray
#define kdk_json_add_item_refer_to_object   cJSON_AddItemReferenceToObject
#define kdk_json_detach_item_from_array     cJSON_DetachItemFromArray
#define kdk_json_delete_item_from_array     cJSON_DeleteItemFromArray
#define kdk_json_detach_item_from_object    cJSON_DetachItemFromObject
#define kdk_json_delete_item_from_object    cJSON_DeleteItemFromObject
#define kdk_json_insert_item_in_array       cJSON_InsertItemInArray
#define kdk_json_replace_item_in_array      cJSON_ReplaceItemInArray
#define kdk_json_replace_item_object        cJSON_ReplaceItemInObject
#define kdk_json_duplicate                  cJSON_Duplicate
#define kdk_json_parse_with_opts            cJSON_ParseWithOpts
#define kdk_json_minify                     cJSON_Minify
#define kdk_json_add_null_to_object         cJSON_AddNullToObject
#define kdk_json_add_true_to_object         cJSON_AddTrueToObject
#define kdk_json_add_false_to_object        cJSON_AddFalseToObject
#define kdk_json_add_bool_to_object         cJSON_AddBoolToObject
#define kdk_json_add_number_to_object       cJSON_AddNumberToObject
#define kdk_json_add_string_to_object       cJSON_AddStringToObject
#define kdk_json_set_int_value              cJSON_SetIntValue
#define kdk_json_set_number_value           cJSON_SetNumberValue


#endif  /* _KDK_JSON_H_INCLUDED_ */
