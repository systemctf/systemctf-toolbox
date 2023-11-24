#ifndef JUGGFIND_H_
#define JUGGFIND_H_

#include <pthread.h>

// Launch threads to find the correct hash
void juggfind(int nb_thrd, pthread_t *trds);

#endif