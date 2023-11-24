#ifndef HASH_H_
#define HASH_H_

// Hash a string according to its length, put the result in hash parameter
void do_hash(char *string, unsigned char *hash, int hash_func, int string_len);

// Verify if a hash is fitting the juggling attack
int hash_ok(unsigned char *hash, int hash_length);

#endif