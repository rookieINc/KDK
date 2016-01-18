
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName    : kdk_daemon.c
 * Author      : rookieINc
 * Version     : v0.1.0
 * Date        : 2016-01-14 01:53
 * Description : kdk_daemon.c
 * History     : 
 ***********************************************************/


#include "kdk_daemon.h"

kdk_uint32
daemonize(kdk_uint32 flags)
{
    kdk_uint32  max_fd, fd;

    switch(fork())
    {
        case KDK_SUCCESS: 
            break;
        case KDK_LINUXERR:
            return KDK_FAILURE;
        default:
            _exit(KDK_FAILURE);
    }

    if(setsid() == KDK_LINUXERR)
        return KDK_FAILURE;

    switch(fork())
    {
        case KDK_SUCCESS:
            break;
        case KDK_LINUXERR:
            return KDK_FAILURE; 
        default:
            _exit(KDK_FAILURE);
    }

    if(!(flags & DAEMON_NO_MASK))
        umask(0);

    if(!(flags & DAEMON_NO_CHDIR))
        chdir("/");

    if(!(flags & DAEMON_NO_CLOSE_FILES))
    {
        max_fd = sysconf(_SC_OPEN_MAX);
        if(max_fd == KDK_LINUXERR)
            max_fd = DAEMON_MAX_CLOSE;

        for(fd = 0; fd < max_fd; fd++)
            close(fd);
    }

    if(!(flags & DAEMON_NO_REOPEN_STD_FDS))
    {
        close(STDIN_FILENO);

        fd = open(DAEMON_NULL, O_RDWR);

        if(fd != STDIN_FILENO)
            return KDK_FAILURE;
        if(dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO)
            return KDK_FAILURE;
        if(dup2(STDIN_FILENO, STDERR_FILENO) != STDOUT_FILENO)
            return KDK_FAILURE;
    }

    return KDK_SUCCESS;
}
