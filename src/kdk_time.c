
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName    : kdk_time.c
 * Author      : rookieINc
 * Version     : v0.1.0
 * Date        : 2016-03-14 17:11
 * Description : kdk_time.c
 * History     : 
 ***********************************************************/


#include "kdk_time.h"

kdk_void
kdk_time_get_date_time(kdk_time_t *date_time)
{
    kdk_time     timer;
    kdk_tm_t    *lt;

    memset(date_time, 0, sizeof(kdk_time_t));
    time(&timer);

    lt = (kdk_tm_t *)localtime(&timer);

    date_time->y   = lt->tm_year+1900;
    date_time->mon = lt->tm_mon+1;
    date_time->d   = lt->tm_mday;
    date_time->h   = lt->tm_hour;
    date_time->min = lt->tm_min;
    date_time->s   = lt->tm_sec;

    sprintf(date_time->hms1, "%02d%02d%02d",             date_time->h,   date_time->min, date_time->s);
    sprintf(date_time->hms2, "%02d:%02d:%02d",           date_time->h,   date_time->min, date_time->s);
    sprintf(date_time->hms3, "%02d:%02d:%02d",       date_time->h,   date_time->min, date_time->s);
    sprintf(date_time->ymd1, "%04d%02d%02d",             date_time->y,   date_time->mon, date_time->d);
    sprintf(date_time->ymd2, "%04d/%02d/%02d",           date_time->y,   date_time->mon, date_time->d);
    sprintf(date_time->ymd3, "%04d:%02d:%02d",       date_time->y,   date_time->mon, date_time->d);
    sprintf(date_time->mdy1, "%02d%02d%04d",             date_time->mon, date_time->d,   date_time->y);
    sprintf(date_time->mdy2, "%02d/%02d/%04d",           date_time->mon, date_time->d,   date_time->y);
    sprintf(date_time->time, "%04d%02d%02d%02d%02d%02d", date_time->y,   date_time->mon, date_time->d, date_time->h, date_time->min, date_time->s);

    return ;
}

kdk_void
kdk_time_get_current_date(kdk_char32 *current_date)
{
    kdk_time_t  date_time;

    memset(&date_time, 0, sizeof(kdk_time_t));
    kdk_time_get_date_time(&date_time);

    strncpy(current_date, date_time.ymd1, 8);

    return ;
}

kdk_void
kdk_time_get_next_date(const kdk_char32 *date, kdk_char32 *next_date)
{
    kdk_char32    tmp_buf[11];
    kdk_tm_t      tmstu, *ptime;
    kdk_time      timeb, timen;

    memset(tmp_buf, 0, sizeof(tmp_buf));
    memset(&tmstu, 0, sizeof(tmstu));

    strncpy(tmp_buf, date, 4);
    strcat(tmp_buf, "/");
    strncpy(tmp_buf + 4 + 1, date + 4, 2);
    strcat(tmp_buf, "/");
    strncpy(tmp_buf + 7 + 1, date + 6, 2);

    strptime((kdk_char32 *)tmp_buf, (kdk_char32 *)DEF_TIME_FMT,(kdk_tm_t *)&tmstu);
    timeb = mktime(&tmstu) ;
    timen = timeb + 24 * 60 * 60;

    ptime = localtime(&timen) ;

    sprintf(next_date, "%04d%02d%02d", ptime->tm_year + 1900, ptime->tm_mon + 1, ptime->tm_mday);

    return ;
}

kdk_void
kdk_time_get_next_prev_date(const kdk_char32 *date, kdk_char32 *prev_date)
{
    kdk_char32    tmp_buf[11];
    kdk_tm_t      tmstu, *ptime;
    kdk_time      timeb, timen;

    memset(tmp_buf, 0, sizeof(tmp_buf));
    memset(&tmstu, 0, sizeof(tmstu));

    strncpy(tmp_buf, date, 4);
    strcat(tmp_buf, "/");
    strncpy(tmp_buf + 4 + 1, date + 4, 2);
    strcat(tmp_buf,"/");
    strncpy(tmp_buf + 7 + 1, date + 6, 2);

    strptime((kdk_char32 *)tmp_buf, (kdk_char32 *)DEF_TIME_FMT, (kdk_tm_t *)&tmstu);
    timeb = mktime(&tmstu);
    timen = timeb - 24 * 60 * 60;

    ptime = localtime(&timen) ;

    sprintf(prev_date, "%04d%02d%02d", ptime->tm_year + 1900, ptime->tm_mon + 1, ptime->tm_mday);

    return ;
}
