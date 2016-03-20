// Bartosz Bednarczyk (273 479)

#include "utils.h"

bool isInputValid(int &argc, char* argv[]) {
  regex ipRegex("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
  return (argc == 2 && argv[1] != nullptr && regex_match(string(argv[1]), ipRegex));
}

// compute_icmp_checksum by Marcin Bienkowski

u_int16_t compute_icmp_checksum (const void *buff, int length) {
  assert(length % 2 == 0);
  u_int32_t sum;
  const u_int16_t* ptr = (const u_int16_t*) buff;
  for (sum = 0; length > 0; length -= 2) sum += *ptr++;
  sum = (sum >> 16) + (sum & 0xffff);
  return (u_int16_t)(~(sum + (sum >> 16)));
}

int getElapsedTime(chrono::steady_clock::time_point &start) {
  chrono::steady_clock::time_point end = chrono::steady_clock::now();
  typedef std::chrono::duration<int,std::milli> millisecs_t;
  millisecs_t duration( chrono::duration_cast<millisecs_t>(end-start) );
  return (int) duration.count();
}
