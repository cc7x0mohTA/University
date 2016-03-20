// Bartosz Bednarczyk (273 479)

#ifndef RECIEVER_INCLUDED
#define RECIEVER_INCLUDED 1

#include "utils.h"
#include "mypacket.h"

class Receiver
{
  public:
    MyPacket getPacket();
    Receiver(int *aSock, int programID);

  private:
    int *aSocket;
    int PID;
};

#endif
