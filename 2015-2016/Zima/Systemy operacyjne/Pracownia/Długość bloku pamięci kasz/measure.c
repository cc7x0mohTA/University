void measure() {
  struct timeval tval_before, tval_after, tval_result;
  array_init(1<<16); poison_init((1<<16)/getpagesize());

  for(int n = 1; n < 37; n++) {
    printf("%d", n); poison_cache();
    gettimeofday(&tval_before, NULL);

    for(int j = 1; j < 1000000; j++) {
      int counter = 0, i = 0;
      while(counter < 1700) {
        array.data[i] = 1; i+= n; counter++;
      }
    }

    gettimeofday(&tval_after, NULL);
    timersub(&tval_after, &tval_before, &tval_result);
    printf(" %ld.%06ld\n",
      (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
 }}
