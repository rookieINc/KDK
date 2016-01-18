
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName    : kdk_daemon.h
 * Author      : rookieINc
 * Version     : v0.1.0
 * Date        : 2016-01-14 02:29
 * Description : kdk_daemon.h
 * History     : 
 ***********************************************************/


#ifndef _KDK_DAEMON_H_INCLUDED_
#define _KDK_DAEMON_H_INCLUDED_

#include "kdk_base.h"
#include <fcntl.h>
#include <sys/stat.h>

#define DAEMON_NO_MASK             010
#define DAEMON_NO_CHDIR             01
#define DAEMON_NO_CLOSE_FILES       02
#define DAEMON_NO_REOPEN_STD_FDS    04
#define DAEMON_MAX_CLOSE          8192

#define DAEMON_NULL                 "/dev/null"

kdk_uint32
daemonize(kdk_uint32 flags);

#endif /* _KDK_DAEMON_H_INCLUDED_ */
