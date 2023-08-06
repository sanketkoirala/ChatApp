
#include <stdbool.h>

bool sendUdpData(const char ipv4Address[], int port, const char str[]);
bool openUdpListenerPort(int port);
bool receiveUdpData(char str[], int str_length, int timeout_us);
void closeUdpListenerPort(void);
