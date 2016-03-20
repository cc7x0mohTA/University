// Bartosz Bednarczyk (273 479)

#include "sender.h"

icmphdr Sender::createHeader(int num) {
  icmphdr icmp_header;
  icmp_header.type = ICMP_ECHO;
  icmp_header.code = 0;
  icmp_header.un.echo.id = (PID);
  icmp_header.un.echo.sequence = (num);
  icmp_header.checksum = 0;
  icmp_header.checksum = compute_icmp_checksum((u_int16_t*)&icmp_header, sizeof(icmp_header));
  return icmp_header;
}

Sender::Sender(int *aSock, int programID) {
  aSocket = aSock;
  PID = programID;
}

void Sender::sendPacket(int TTL, char* ip_addr, int num) {
  sockaddr_in recipient;
  bzero (&recipient, sizeof(recipient));
  recipient.sin_family = AF_INET;
  inet_pton(AF_INET, ip_addr, &(recipient.sin_addr));
  icmphdr icmp_header = createHeader(num);
  setsockopt (*aSocket, IPPROTO_IP, IP_TTL, &TTL, sizeof(int));
  ssize_t bytes_sent = sendto (*aSocket, &icmp_header, sizeof(icmp_header), 0, (struct sockaddr*) &recipient, sizeof(recipient));
  assert(bytes_sent > 0);
}
