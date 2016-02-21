#ifndef __CACHE_H__
#define __CACHE_H__

#include <stdint.h>
#include <sys/time.h>

typedef struct array {
  int32_t * volatile data;
  uint32_t size;
} array_t;

extern array_t array;

void array_walk();

typedef struct timer {
  struct timeval tv_start, tv_sum;
} timer_t;

void timer_reset(timer_t *timer);
void timer_start(timer_t *timer);
void timer_stop(timer_t *timer);
void timer_print(timer_t *timer);

void poison_cache();

#endif
