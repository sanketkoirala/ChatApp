#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>

#include "udp3.h"



int listen_sockfd;
struct in_addr listen_remote_ip;



// Sends UDP package containing a string to ipv4Address::port
// returns true if successful
bool sendUdpData(const char ipv4Address[], int port, const char str[])
{
    struct sockaddr_in remote_addr;
    struct in_addr remote_ip;

    int sockfd;
    int count;
    int result;
    bool ok;

    ok = (sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) != -1;
    if (ok)
    {
        inet_aton(ipv4Address, &remote_ip);

        remote_addr.sin_family = AF_INET;
        remote_addr.sin_port = htons(port);
        remote_addr.sin_addr = remote_ip;
        memset(&(remote_addr.sin_zero), 0, 8);

        count = sendto(sockfd, str, strlen(str)+1, 0, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr));
        ok = count > 0;
        close(sockfd);
    }
    return ok;
}

// Opens listener port that accepts only data from any address
bool openUdpListenerPort(int listenPort)
{
    struct sockaddr_in local_addr;
    int opt = 1;
    int result;
    bool ok = true;

    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(listenPort);
    local_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(local_addr.sin_zero), 0, 8);
    ok = (listen_sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) != -1;
    if (ok)
        ok = setsockopt(listen_sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) != -1;
    if (ok)
        ok = bind(listen_sockfd, (struct sockaddr *)&local_addr, sizeof(struct sockaddr)) != -1;
    return ok;
}

// get data from port and return sender address
// function returns true if data was received before the timeout period elapses
bool receiveUdpData(char str[], int str_length, int timeout_ms)
{
    bool success;

    // Listener
    struct sockaddr_in sender_addr;
    int sender_add_length = sizeof(struct sockaddr);

    // Look for data
    struct pollfd pfd;
    pfd.fd = listen_sockfd;
    pfd.events = POLLIN;
    poll(&pfd, listen_sockfd, timeout_ms);
    success = pfd.revents == POLLIN;
    if (success)
    {
        recvfrom(listen_sockfd, str, str_length, 0, (struct sockaddr *)&sender_addr, &sender_add_length);
    }
    return success;
}

// Closes listener port
void closeUdpListenerPort()
{
    close(listen_sockfd);
}
