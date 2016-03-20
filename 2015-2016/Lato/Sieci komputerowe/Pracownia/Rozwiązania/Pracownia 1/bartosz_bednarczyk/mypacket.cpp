// Bartosz Bednarczyk (273 479)

#include "mypacket.h"
#include "utils.h"

MyPacket::MyPacket() {
  valid = false;
  ip = "";
  ttl = sequence_number = id = age = 0;
}

MyPacket::MyPacket(int id, int ttl, int sequence_number, string ip, int age) {
  this->id = id;
  this->ttl = ttl;
  this->sequence_number = sequence_number;
  this->ip = ip;
  this->valid = true;
  this->age = age;
}

bool MyPacket::isValid() {
  return valid;
}

int MyPacket::getID() {
  return id;
}

int MyPacket::getTTL() {
  return ttl;
}

int MyPacket::getAge() {
  return age;
}

void MyPacket::setAge(int age) {
  this->age = age;
}

string MyPacket::getIP() {
  return ip;
}

int MyPacket::getSequenceNumber() {
  return sequence_number;
}

bool MyPacket::isSpam() {
  return (id < 0);
}

void MyPacket::print() {
  if(isValid()) printf("ERROR\n");
  printf("ID %d : TTL %d : SEQ : %d IP %s\n", id, ttl, sequence_number, ip.c_str());
}
