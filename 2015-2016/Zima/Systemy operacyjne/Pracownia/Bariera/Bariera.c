// Bartosz Bednarczyk

typedef struct {
  int maximumNumberOfGuests, counter;
  sem_t doorIn, doorOut, mutex;
} Barrier;

void init(Barrier* barrier, int numberOfGuests) {
  barrier->maximumNumberOfGuests = numberOfGuests;
  barrier->counter = 0;
  sem_init(&barrier->mutex, 1, 1);
  sem_init(&barrier->doorIn, 1, numberOfGuests);
  sem_init(&barrier->doorOut, 1, 0);
}

void wait(Barrier* barrier)
{
  sem_wait(&barrier->doorIn);
  sem_wait(&barrier->mutex);
  barrier->counter++;

  if(barrier->counter == barrier->maximumNumberOfGuests)
    sem_post(&barrier->doorOut);

  sem_post(&barrier->mutex);
  sem_wait(&barrier->doorOut);
  sem_wait(&barrier->mutex);
  barrier->counter--;

  if(barrier->counter > 0) sem_post(&barrier->doorOut);
  else {
    for(int i = 0; i < barrier->maximumNumberOfGuests; i++) sem_post(&barrier->doorIn);
  }

  sem_post(&barrier->mutex);
}

void destroy(Barrier* barrier) {
  sem_destroy(&barrier->mutex);
  sem_destroy(&barrier->doorIn);
  sem_destroy(&barrier->doorOut);
  barrier->counter = 0;
  barrier->maximumNumberOfGuests = 0;
}

Barrier* myBarrier;