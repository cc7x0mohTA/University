// Bartosz Bednarczyk

#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdint.h>

// Mierzenie czasu:

typedef struct timer {
  struct timeval tv_start, tv_sum;
} timer_t;

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

// Przechodzenie po tablicy:

int32_t **Array;
struct timeval tval_before, tval_after, tval_result;
int numberOfRows, numberOfColumns, numberOfTimes, i, j, counter = 0;
char direction;

void initializeArray() {
	Array = malloc(numberOfRows * sizeof(int32_t *));

	for(i = 0; i < numberOfRows; i++)
    Array[i] = malloc(numberOfColumns * sizeof(int32_t));
}

void resetArray() {
	for(i = 0; i < numberOfRows; i++)
  {
    for(j = 0; j < numberOfColumns; j++) Array[i][j] = i+j;
  }

	counter = 0;
}

void measureByRows() {
	resetArray();
  gettimeofday(&tval_before, NULL);

  for(i = 0; i < numberOfRows; i++) {
    for(j = 0; j < numberOfColumns; j++) {
    	Array[i][j] = 1;
    }
    counter++;
  }

  gettimeofday(&tval_after, NULL);
  timersub(&tval_after, &tval_before, &tval_result);
  printf("%ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
}

void measureByColumns() {
	resetArray();
  gettimeofday(&tval_before, NULL);

  for(j = 0; j < numberOfColumns; j++) {
    for(i = 0; i < numberOfRows; i++) {
    	Array[i][j] = 1;
    }
    counter++;
  }

  gettimeofday(&tval_after, NULL);
  timersub(&tval_after, &tval_before, &tval_result);
  printf("%ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
}

void parseInput(char **argv) {
	direction = (char)(argv[1][0]);
  numberOfRows = atoi(argv[2]);
  numberOfColumns = atoi(argv[3]);
  numberOfTimes = atoi(argv[4]);
}

int main(int argc, char **argv)
{
	if(argc < 4) {
		printf("Niepoprawna liczba argumentow. Wlacz jeszcze raz\n");
		return 0;
	}

	parseInput(argv);
  initializeArray();
  
  while(numberOfTimes--) {
  	if(direction == 'r') measureByRows();
  	else measureByColumns();
  }

  return EXIT_SUCCESS;
}
