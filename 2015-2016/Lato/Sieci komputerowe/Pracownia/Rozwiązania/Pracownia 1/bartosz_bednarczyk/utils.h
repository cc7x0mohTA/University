// Bartosz Bednarczyk (273 479)

#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED 1

#include <iostream>
#include <regex>
#include <cassert>
#include <tuple>

#include <chrono>
#include <ctime>

// web tools headers
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

bool isInputValid(int &argc, char* argv[]);
u_int16_t compute_icmp_checksum (const void *buff, int length);
int getElapsedTime(chrono::steady_clock::time_point &start);

#endif
