#include <Python.h>
#include "hash_thread.h"

// Launch threads to find the correct hash
void juggfind(int nb_thrd, pthread_t *thrds){
  int i;
  
  // Random seed initialization
  srand(time(0));
  
  // The threads start and we  waits for them to finish
  for(i = 0; i < nb_thrd; i++) pthread_create(&thrds[i], NULL, ht_run, NULL);
  for(i = 0; i < nb_thrd; i++) pthread_join(thrds[i], NULL);
}