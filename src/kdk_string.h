
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName    : kdk_string.h
 * Author      : rookieINc
 * Version     : v0.1.0
 * Date        : 2015-12-01 14:28
 * Description : kdk_string.h
 * History     :     
 ***********************************************************/


#ifndef _KDK_STRING_H_INCLUDED_
#define _KDK_STRING_H_INCLUDED_

#include "kdk_base.h"

kdk_void 
str_trim_head(kdk_char32 *str);

kdk_void
str_trim_tail(kdk_char32 *str);

kdk_void
str_trim(kdk_char32 *str);

kdk_void
kdk_string_low(kdk_char32 *str);

kdk_void
kdk_string_up(kdk_char32 *str);

kdk_uint32
kdk_string_merge(kdk_char32 *ret, kdk_char32 *str1, kdk_char32 *str_split, kdk_char32 *str2, kdk_char32 low_or_up);

#endif /* _KDK_STRING_H_INCLUDED_ */
