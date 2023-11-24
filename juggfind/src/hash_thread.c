#include <Python.h>
#include "hash.h"

static const char CHARSET[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const int CHARSET_LEN = 62;

int finished = 0;
int rndm_string_len = 7;
int hash_length = 16;
int hash_func = -1;
int chain_len;
char *result_hash = NULL;

// Lock to write the result (if 2 threads find in the same time)
pthread_mutex_t mutex_result = PTHREAD_MUTEX_INITIALIZER;

// Generate a random string in place of an existing one
void randomize_string(char *string){
  for(int i = 0; i < rndm_string_len; i++){
    string[i] = CHARSET[rand()%CHARSET_LEN];
  }
}

// Hash finding thread routine
void *ht_run(void *args){
  int i;
  char rndm_string[rndm_string_len];
  unsigned char hash[hash_length];

  while(!finished){                       // Searching the good candidate
    randomize_string(rndm_string);          // Generate a random string
    do_hash(                                // Hash the string
      rndm_string,
      hash,
      hash_func,
      rndm_string_len
    );

    if(hash_ok(hash, hash_length)){         // Is the hash ok for the attack ?
      pthread_mutex_lock(&mutex_result);    // Take the lock
      finished++;

      // Writing the result
      for (i=0; i < hash_length; i++) sprintf(result_hash+2*i, "%02x", hash[i]);
      pthread_mutex_unlock(&mutex_result);  // Leave the lock
    }
  }

  return NULL;
}