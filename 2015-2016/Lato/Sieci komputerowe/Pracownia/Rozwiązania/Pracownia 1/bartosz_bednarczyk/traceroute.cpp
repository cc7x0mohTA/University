// Bartosz Bednarczyk (273 479)
// Project 1 - Own traceroute

#include "utils.h"
#include "receiver.h"
#include "sender.h"
#include "mypacket.h"

int main(int argc, char* argv[])
{
  if(!isInputValid(argc, argv)) {
    printf("Invalid input.\n");
    return -1;
  }

  int programID = getpid(), numberOfPackets = 0;
  int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  
  if (sockfd < 0) {
    printf("Error caused by socket creation.\n");
    return -1;
  }

  for(int TTL = 1; TTL <= 30; TTL++) {
    printf("%d.\t", TTL);
    Receiver r(&sockfd, programID);
    Sender s(&sockfd, programID);
    for(int i = 1; i <= 3; i++) {
      s.sendPacket(TTL, argv[1], numberOfPackets++);
    }
    
    vector<MyPacket> data_vec;
    chrono::steady_clock::time_point start = chrono::steady_clock::now();

    while( getElapsedTime(start) < 1500 ) {
      MyPacket data = r.getPacket();

      if(data.isValid() && !data.isSpam() && data.getID() == programID && data.getTTL() == TTL) {
        data.setAge(getElapsedTime(start));
        data_vec.push_back(data);
      }
    }

    if(data_vec.size() == 3) {
      printf("%s\t%dms\n", data_vec[0].getIP().c_str(), ( data_vec[0].getAge() + data_vec[1].getAge() + data_vec[2].getAge() )/3 );
      if(data_vec[0].getIP() == string(argv[1])) break;
    }
    else if(data_vec.size() == 0) printf("*\n");
    else printf("%s\t???\n", data_vec[0].getIP().c_str());
  }

  close(sockfd);
  return 0;
} 
