
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName    : kdk_string.c
 * Author      : rookieINc
 * Version     : v0.1.0
 * Date        : 2015-12-01 14:32
 * Description : kdk_string.c
 * History     :     
 ***********************************************************/


#include "kdk_string.h"

kdk_void 
str_trim_head(kdk_char32 *str)
{
    kdk_char32  *head = str;
    kdk_uint32   i;

    if(str == KDK_NULL) return ;
    
    while(*(head++) == ' ');

    if(--head == str) return ;

    for(i = 0; i < strlen(head); i++)
        str[i] = head[i];
    str[i] = '\0';
    
    return ;
}

kdk_void
str_trim_tail(kdk_char32 *str)
{
    if(str == KDK_NULL) return ;

    kdk_char32 *tail = str + strlen(str) - 1;

    while(*(tail--) == ' ');

    if(++tail == str + strlen(str) - 1) return ;

    tail[1] = '\0';

    return ;
}

kdk_void
str_trim(kdk_char32 *str)
{
    str_trim_head(str);
    str_trim_tail(str);

    return ;
}
