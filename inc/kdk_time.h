
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName    : kdk_time.h
 * Author      : rookieINc
 * Version     : v0.1.0
 * Date        : 2016-03-14 17:09
 * Description : kdk_time.h
 * History     : 
 ***********************************************************/


#ifndef _KDK_TIME_H_INCLUDED_
#define _KDK_TIME_H_INCLUDED_

#include "kdk_base.h"

struct kdk_time_s
{
  kdk_short32   h;         // Ð¡Ê±
  kdk_short32   min;       // ·ÖÖÓ
  kdk_short32   s;         // Ãë
  kdk_char32    hms1[7];   // hhmmss
  kdk_char32    hms2[9];   // hh:mm:ss
  kdk_char32    hms3[13];  // hhÊ±mm·ÖssÃë
  kdk_short32   y;         // Äê
  kdk_short32   mon;       // ÔÂ
  kdk_short32   d;         // ÈÕ
  kdk_char32    ymd1[9];   // yyyymmdd
  kdk_char32    ymd2[11];  // yyyy/mm/dd
  kdk_char32    ymd3[15];  // yyyyÄêmmÔÂddÈÕ
  kdk_char32    mdy1[9];   // mmddyyyy
  kdk_char32    mdy2[11];  // mm/dd/yyyy
  kdk_char32    time[15];  // YYYYMMDDHHMMSS
};

typedef struct kdk_time_s kdk_time_t;

#define DEF_TIME_FMT   "%Y/%m/%d"

kdk_void
kdk_time_get_date_time(kdk_time_t *date_time);

kdk_void
kdk_time_get_current_date(kdk_char32 *current_date);

kdk_void
kdk_time_get_next_date(const kdk_char32 *date, kdk_char32 *next_date);

kdk_void
kdk_time_get_next_prev_date(const kdk_char32 *date, kdk_char32 *prev_date);

#endif /* _KDK_TIME_H_INCLUDED_ */
