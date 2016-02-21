// Bartosz Jan Bednarczyk (273 479)
// Zadanie "Palacze"

//------------------------------------------------------------------------------

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

typedef int bool;
#define true 1
#define false 0

#define SHARED_BETWEEN_PROCESSES 1

//------------------------------------------------------------------------------

typedef struct {
  bool isTobacco, isPaper, isMatches;
  sem_t tobacco, paper, matches;
  sem_t wakeupMatches, wakeupPaper, wakeupTobacco;
  sem_t mutex, finishedSmoking;
} data;

void data_init(data* d) {
  sem_init(&d->tobacco, SHARED_BETWEEN_PROCESSES, 0);
  sem_init(&d->matches, SHARED_BETWEEN_PROCESSES, 0);
  sem_init(&d->paper, SHARED_BETWEEN_PROCESSES, 0);
  sem_init(&d->wakeupTobacco, SHARED_BETWEEN_PROCESSES, 0);
  sem_init(&d->wakeupPaper, SHARED_BETWEEN_PROCESSES, 0);
  sem_init(&d->wakeupMatches, SHARED_BETWEEN_PROCESSES, 0);

  sem_init(&d->mutex, SHARED_BETWEEN_PROCESSES, 1);
  d->isTobacco = d->isPaper = d->isMatches = false;
}

void data_destroy(data* d) {
  sem_destroy(&d->tobacco);
  sem_destroy(&d->matches);
  sem_destroy(&d->paper);
  sem_destroy(&d->wakeupTobacco);
  sem_destroy(&d->wakeupPaper);
  sem_destroy(&d->wakeupMatches);

  sem_destroy(&d->mutex);
  d->isTobacco = d->isPaper = d->isMatches = false;
}

data *shared_data;

//------------------------------------------------------------------------------

void agent() {
  while(1) {
    int random_number = rand() % 3;

    if(random_number == 0) {
      sem_post(&shared_data->tobacco);
      sem_post(&shared_data->paper);
    }
    else if(random_number == 1) {
      sem_post(&shared_data->tobacco);
      sem_post(&shared_data->matches);
    }
    else {
      sem_post(&shared_data->matches);
      sem_post(&shared_data->paper);
    }

    sem_wait(&shared_data->finishedSmoking);
  }
}

void helperTobacco() {
  while(1) {
    sem_wait(&shared_data->tobacco);
    sem_wait(&shared_data->mutex);

    if(shared_data->isPaper) sem_post(&shared_data->wakeupMatches);
    else if(shared_data->isMatches) sem_post(&shared_data->wakeupPaper);
    else shared_data->isTobacco = 1;

    sem_post(&shared_data->mutex);
  }
}

void helperPaper() {
  while(1) {
    sem_wait(&shared_data->paper);
    sem_wait(&shared_data->mutex);

    if(shared_data->isTobacco) sem_post(&shared_data->wakeupMatches);
    else if(shared_data->isMatches) sem_post(&shared_data->wakeupTobacco);
    else shared_data->isPaper = 1;

    sem_post(&shared_data->mutex);
  }
}

void helperMatches() {
  while(1) {
    sem_wait(&shared_data->matches);
    sem_wait(&shared_data->mutex);

    if(shared_data->isTobacco) sem_post(&shared_data->wakeupPaper);
    else if(shared_data->isPaper) sem_post(&shared_data->wakeupTobacco);
    else shared_data->isMatches = 1;

    sem_post(&shared_data->mutex);
  }
}

//------------------------------------------------------------------------------

void tobaccoSmoker() {
  while(1) {
    sem_wait(&shared_data->wakeupTobacco);
    shared_data->isMatches = shared_data->isPaper = false;
    printf("TYTON\n");
    sem_post(&shared_data->finishedSmoking);
  }
}


void paperSmoker() {
  while(1) {
    sem_wait(&shared_data->wakeupPaper);
    shared_data->isMatches = shared_data->isTobacco = false;
    printf("BIBULKI\n");
    sem_post(&shared_data->finishedSmoking);
  }
}

void matchesSmoker() {
  while(1) {
    sem_wait(&shared_data->wakeupMatches);
    shared_data->isTobacco = shared_data->isPaper = false;
    printf("ZAPALKI\n");
    sem_post(&shared_data->finishedSmoking);
  }
}

//------------------------------------------------------------------------------

int main() {
  int fileDescriptor = shm_open("/data", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
  ftruncate(fileDescriptor, sizeof(data));
  shared_data = mmap(NULL, sizeof(data), PROT_READ | PROT_WRITE, MAP_SHARED, fileDescriptor, 0);

  data_init(shared_data);
  pid_t pid;

  if((pid = fork()) == 0) {
    agent();
    return 0;
  }

  if((pid = fork()) == 0) {
    helperTobacco();
    return 0;
  }

  if((pid = fork()) == 0) {
    helperMatches();
    return 0;
  }

  if((pid = fork()) == 0) {
    helperPaper();
    return 0;
  }

  if((pid = fork()) == 0) {
    tobaccoSmoker();
    return 0;
  }

  if((pid = fork()) == 0) {
    paperSmoker();
    return 0;
  }

  if( (pid = fork()) == 0) {
    matchesSmoker();
    return 0;
  }

  for(int i = 0; i < 7; i++) {
    int status;
    wait(&status);
  }

  data_destroy(shared_data);
  return 0;
}