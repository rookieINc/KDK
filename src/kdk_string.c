
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
    str[i] = END_TAG;
    
    return ;
}

kdk_void
str_trim_tail(kdk_char32 *str)
{
    if(str == KDK_NULL) return ;

    kdk_char32 *tail = str + strlen(str) - 1;

    while(*(tail--) == ' ');

    if(++tail == str + strlen(str) - 1) return ;

    tail[1] = END_TAG;

    return ;
}

kdk_void
str_trim(kdk_char32 *str)
{
    str_trim_head(str);
    str_trim_tail(str);

    return ;
}

kdk_void
kdk_string_low(kdk_char32 *str)
{
    int i;
    if(str == NULL) return ;
    
    for(i = 0; i < strlen(str); i++)
    {
        if(isupper(str[i]))
            str[i] = tolower(str[i]);
    }

    return ;
}

kdk_void
kdk_string_up(kdk_char32 *str)
{
    int i;
    if(str == NULL) return ;
    
    for(i = 0; i < strlen(str); i++)
    {
        if(islower(str[i]))
            str[i] = toupper(str[i]);
    }

    return ;
}

kdk_uint32
kdk_string_merge(kdk_char32 *ret, kdk_char32 *str1, kdk_char32 *str_split, kdk_char32 *str2, kdk_char32 low_or_up)
{
    void        (*func)();
    kdk_char32  str1_cpy[1024] = {'\0'};
    kdk_char32  str2_cpy[1024] = {'\0'};

    if(ret == NULL) return KDK_NULLPTR;

    strncpy(str1_cpy, str1, sizeof(str1_cpy) - 1);
    strncpy(str2_cpy, str2, sizeof(str2_cpy) - 1);

    str_trim(str1_cpy);
    str_trim(str_split);
    str_trim(str2_cpy);

    if(low_or_up == 'L' || low_or_up == 'l')
        func = kdk_string_low;
    else if(low_or_up == 'U' || low_or_up == 'u')
        func = kdk_string_up;
    else
       return KDK_INVAL;

    (*func)(str1_cpy);
    (*func)(str2_cpy);

    sprintf(ret, "%s%s%s", str1_cpy, str_split, str2_cpy);
    
    return KDK_SUCCESS;
}
