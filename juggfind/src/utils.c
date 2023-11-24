#include <Python.h>
#include "utils.h"

// Available hash functions in the program
const char *AVAILABLE_FUNCTIONS[] = {
  "md2","md4","md5",
  "mdc2",
  "sha1","sha224","sha256","sha384","sha512",
  "rmd160",
  "whirlpool",
  NULL
};

// Hash length
const int HASH_LENGTH[] = {
  16, 16, 16, 16, 20, 28, 32, 48, 64, 20, 64
};

// Parse the arguments of the python method
int parse_args(PyObject *args, const char *func, int *rndm_string_len){
  int argc = PyTuple_Size(args);
  int try = 0;

  if(argc == 2 && PyArg_ParseTuple(args, "si", &func, &try)){
    if(try > 0){
      return try;
    }
    return 0;
  }
  if(argc == 1 && PyArg_ParseTuple(args, "s", &func)){
    return 1;
  }

  return 0;
}

// Resolve the hash function index, if it exists
int function_index(const char *func){
  for(int i = 0; AVAILABLE_FUNCTIONS[i] != NULL; i++){
    if(!strcmp(func, (char *)AVAILABLE_FUNCTIONS[i])){
      return i;
    }
  }
  return -1;
}