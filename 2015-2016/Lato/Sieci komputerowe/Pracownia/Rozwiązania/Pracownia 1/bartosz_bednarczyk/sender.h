// Bartosz Bednarczyk (273 479)

#ifndef SENDER_INCLUDED
#define SENDER_INCLUDED 1

#include "utils.h"

class Sender
{
  public:
    Sender(int *aSock, int programID);
    void sendPacket(int TTL, char* ip_addr, int num);

  private:
    int *aSocket;
    int PID;
    icmphdr createHeader(int num);
};

#endif
