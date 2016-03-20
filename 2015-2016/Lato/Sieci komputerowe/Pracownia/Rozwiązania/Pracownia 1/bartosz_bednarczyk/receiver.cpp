// Bartosz Bednarczyk (273 479)

#include "utils.h"
#include "receiver.h"
#include <iostream>

MyPacket Receiver::getPacket() {
  struct sockaddr_in sender;
  socklen_t sender_len = sizeof(sender);
  u_int8_t buffer[IP_MAXPACKET+1];
  u_int8_t* buffptr = buffer;
  ssize_t packet_len = recvfrom (*aSocket, buffer, IP_MAXPACKET, MSG_DONTWAIT, (struct sockaddr*)&sender, &sender_len);
  
  if (packet_len < 0) {
    return MyPacket();  // if recvfrom failed return empty packet
  }

  char sender_ip_str[20];
  inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str));

  struct iphdr* ip_hdr = (struct iphdr*) buffer;
  buffptr += 4 * ip_hdr->ihl + 8;
  struct ip* rec_pck = (struct ip*) buffptr;
  buffptr += (rec_pck->ip_hl * 4);
  struct icmp* receivedICMP = (struct icmp*) buffptr;
  
  u_int8_t* icmp_packet = buffer + 4 * ip_hdr->ihl;
  struct icmphdr* icmp_header = (struct icmphdr*) icmp_packet;

  if (icmp_header->type == ICMP_TIME_EXCEEDED) {
    int seq = receivedICMP->icmp_seq, id = receivedICMP->icmp_id, ttl = seq / 3 + 1;
    return MyPacket(id, ttl, seq, string(sender_ip_str));
  }
  else if(icmp_header->type == ICMP_ECHOREPLY) {
    int seq = icmp_header->un.echo.sequence, id = icmp_header->un.echo.id, ttl = seq / 3 + 1;
    return MyPacket(id, ttl, seq, string(sender_ip_str));
  }
  
  return MyPacket();
}

Receiver::Receiver(int *aSock, int programID) {
  aSocket = aSock;
  PID = programID;
}
