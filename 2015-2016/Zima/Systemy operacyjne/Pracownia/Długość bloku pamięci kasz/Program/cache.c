/*
 * Computer Architecture Course @ii.uni.wroc.pl
 *
 * Template for programming assignment: "cache memory".
 *
 * Author: Krystian Bacławski <cahirwpz@cs.uni.wroc.pl>
 */

// Mierzenie dlugosci cache - Bartosz Bednarczyk

#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "cache.h"


static void fail(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  fprintf(stderr, "Failure: ");
  vfprintf(stderr, fmt, ap);
  fputc('\n', stderr);
  va_end(ap);
  exit(EXIT_FAILURE);
}

/*
 * Array walker.
 */

array_t array;

static void array_init(uint32_t words) {
  array.size = words * sizeof(uint32_t);

  if (posix_memalign((void **)&array.data, getpagesize(), array.size) != 0)
    fail("Failed to allocate memory!");

  //printf("Allocated array of %d bytes at %p.\n", array.size, array.data);
}

void array_walk() {
  int32_t i, j;

  for (i = 0, j = 0; i < array.size / sizeof(uint32_t); i++) {
    if (j < 0)
      break;
    j = array.data[j];
  }
}

/*
 * Timer functions.
 */

void timer_reset(timer_t *timer) {
  memset(timer, 0, sizeof(timer_t));
}

void timer_start(timer_t *timer) {
  gettimeofday(&timer->tv_start, NULL);
}

void timer_stop(timer_t *timer) {
  struct timeval tv_end, tv_res;
  gettimeofday(&tv_end, NULL);
  timersub(&tv_end, &timer->tv_start, &tv_res);
  timeradd(&timer->tv_sum, &timer->tv_sum, &tv_res);
}

void timer_print(timer_t *timer) {
  printf("Time elapsed: %ld.%06d seconds.\n", timer->tv_sum.tv_sec, timer->tv_sum.tv_usec);
}

/*
 * Cache poisoning.
 */

static array_t poison;

static void poison_init(uint32_t pages) {
  poison.size = pages * getpagesize();

  if (posix_memalign((void **)&poison.data, getpagesize(), poison.size) != 0)
    fail("Failed to allocate poison buffer!");
  else {}
    //printf("Allocated poison buffer of %d bytes at %p.\n", array.size, array.data);
}

void poison_cache() {
  for (int i = 0; i < poison.size; i++)
    poison.data[i] = 0;
}

/*
 * Program entry point.
 */

void measure() __attribute__((weak));

void measure()
{
  struct timeval tval_before, tval_after, tval_result;

  array_init(1<<16); poison_init((1<<16)/getpagesize());

  for(int n = 1; n < 37; n++)
  {
    printf("%d", n);

    poison_cache();
    gettimeofday(&tval_before, NULL);

    for(int j = 1; j < 1000000; j++)
    {
      int counter = 0, i = 0;

      while(counter < 1700)
      {
        array.data[i] = 1;
        i+= n; counter++;
      }
    }

    gettimeofday(&tval_after, NULL);
    timersub(&tval_after, &tval_before, &tval_result);
    printf(" %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
  }

}
int main(int argc, char **argv)
{
  measure();

  free(poison.data);
  free(array.data);

  return EXIT_SUCCESS;
}
