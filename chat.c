#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "kbhit.h"
#include "udp3.h"

#define LOCAL_PORT  5000
#define REMOTE_PORT 5000


int main(int argc, char* argv[])
{
    char* remoteIp;
    char str[100], str2[100];
    bool quit = false;


    bool goodArguments = (argc == 2);
    if (goodArguments)
    {
        remoteIp = argv[1];
    }
    else
    {
        printf("usage: chat IPV4_ADDRESS\n");
        printf("  where:\n");
        printf("  IPV4_ADDRESS is address of the remote machine\n");
        exit(EXIT_FAILURE);
    }


    if (!openUdpListenerPort(LOCAL_PORT))
    {
        printf("Cannot be opened");
        exit(0);
    }

    printf("Sent\t\t\t\t\t\tReceived\n");

    while(!quit)
    {
        if (kbhit())
        {
            fgets(str, 100, stdin);
            sendUdpData(remoteIp, REMOTE_PORT, str);
            if (strncmp(str, "QUIT",4)==0) {
                quit = true;
            }
        }

        if (receiveUdpData(str2, sizeof(str2), 1))
        {
            printf("\t\t\t\t\t%s", str2);
            if(strncmp(str2, "QUIT", 4) == 0)
            {
                quit = true;
            }
        }
    }
    closeUdpListenerPort();
    return EXIT_SUCCESS;
}
