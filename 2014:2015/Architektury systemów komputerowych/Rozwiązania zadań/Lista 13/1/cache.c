/*
 * Computer Architecture Course @ii.uni.wroc.pl
 *
 * Template for programming assignment: "cache memory".
 *
 * Author: Krystian Bacławski <cahirwpz@cs.uni.wroc.pl>
 */

#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

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

  printf("Allocated array of %d bytes at %p.\n", array.size, array.data);
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
 * Parse program parameters from command line.
 */

static struct {
  int size;
} config;

static void usage(char *program) {
  printf("Usage: %s [options]\n"
         "\n"
         "Options:\n"
         " -s array-size (in 32-bit words)\n",
         program);
  exit(EXIT_FAILURE);
}

static void parse_args(int argc, char **argv) {
  int c;

  while ((c = getopt(argc, argv, "s:")) != -1) {
    switch (c) {
      case 's':
        config.size = strtol(optarg, NULL, 10);
        break;
      case '?':
      default:
        usage(argv[0]);
    }
  }

  argc -= optind;
  argv += optind;
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
  else
    printf("Allocated poison buffer of %d bytes at %p.\n", array.size, array.data);
}

void poison_cache() {
  for (int i = 0; i < poison.size; i++)
    poison.data[i] = 0;
}

/*
 * Program entry point.
 */

void measure(int N, int M, char C)
{
  int32_t **T; int i, j;
  struct timeval tval_before, tval_after, tval_result;
  T = malloc(N * sizeof(int32_t *));

  for(i = 0; i < N; i++)
    T[i] = malloc(M * sizeof(int32_t));

  for(i =0; i < N; i++)
  {
    for(j = 0; j < M; j++) T[i][j] = i+j;
  }

  gettimeofday(&tval_before, NULL);


  if(C == 'w')  // wiersze
  {
    for(i = 0; i < N; i++)
    {
      for(j = 0; j < M; j++)
      {
        T[i][j] = 1;
      }

      printf("\n");
    }
  }
  else if(C == 'k') // kolumny
  {
    for(i = 0; i < M; i++)
    {
      for(j = 0; j < N; j++)
      {
        T[j][i] = 1;
      }

      printf("\n");
    }
  }

  gettimeofday(&tval_after, NULL);
  timersub(&tval_after, &tval_before, &tval_result);
  printf("Time elapsed: %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);

}

int main(int argc, char **argv)
{
  // używamy wpisując np. "w 50 41"

  char znak = (char)(argv[1][0]);
  int a = atoi(argv[2]);
  int b = atoi(argv[3]);

  measure(a, b, znak);

  return EXIT_SUCCESS;
}
