// Bartosz Bednarczyk (273 479)

#ifndef MYPACKET_INCLUDED
#define MYPACKET_INCLUDED 1
#include "utils.h"

class MyPacket {
  public:
    MyPacket();
    MyPacket(int id, int ttl = -1, int sequence_number = -1, string ip = "", int age = -1);

    // getters

    bool isValid();
    bool isSpam();
    int getID();
    int getTTL();
    int getSequenceNumber();
    string getIP();
    int getAge();

    // setters

    void setAge(int age);

    // other
    
    void print();

  private:

    bool valid;
    string ip;
    int ttl, sequence_number, id, age;
};

#endif
