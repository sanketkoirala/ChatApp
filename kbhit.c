#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>


#include "kbhit.h"


// returns true if keyboard has been hit and the key is in input buffer
bool kbhit(void)
{
    bool success;
    // Look for data

    fd_set fd;
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fd);
    FD_SET(0, &fd);
    select(1, &fd, NULL, NULL, &tv);
    success = FD_ISSET(0, &fd);
    return success;
}


