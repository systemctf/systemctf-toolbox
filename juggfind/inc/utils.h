#ifndef UTILS_H_
#define UTILS_H_

#include <Python.h>

// Parse the arguments of the python method
int parse_args(PyObject *args, const char *func, int *rndm_string_len);

// Resolve the hash function index, if it exists
int function_index(const char *func);

#endif