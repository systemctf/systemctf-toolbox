#include <Python.h>
#include <sys/sysinfo.h>
#include "utils.h"
#include "juggfind.h"

#define PY_SSIZE_T_CLEAN

extern int hash_func;
extern int rndm_string_len;
extern char *result_hash;
extern int chain_len;

// Define method juggfind.juggfind(<hash_func>, <chain_len> [random_str_len])
//  - hash_function : string that represent the hash function wanted
//    - Available hash functions : refer to AVAILABLE_FUNCTIONS array
//
//  - chain_len : hash chain length
//    - exemple : "sha1" 2 -> test with SHA1(SHA1(random_string))
//
//  - random_string_length : the length of the candidate string generate
static PyObject *method_juggfind(PyObject *self, PyObject *args) {
  int nb_thrd = get_nprocs();
  int argc = PyTuple_Size(args);
  int try = 0;
  pthread_t *thrds;
  const char *func;

  // Parsing the method arguments
  if(argc == 3 && PyArg_ParseTuple(args, "sii", &func, &chain_len, &try)){
    if(try > 0){
      rndm_string_len = try;
    }
    else{
      PyErr_SetString(
        PyExc_ValueError,
        "The chosen length for random string must be positive"
      );
      return NULL;
    }
  }
  else if(argc != 2 || !PyArg_ParseTuple(args, "si", &func, &chain_len)){
    PyErr_SetString(
      PyExc_ValueError,
      "juggfind parameters : <hash_func> <chain_length> [random_str_len]"
    );
    return NULL;
  }

  // The chain is negative or null
  if(chain_len < 0){
    PyErr_SetString(
      PyExc_ValueError,
      "The chosen hash chain length must be positive"
    );
    return NULL;
  }

  // Is the hash function available ?
  if((hash_func = function_index(func)) == -1){
    PyErr_SetString(
      PyExc_ValueError,
      "The desired hash function selected does not exist"
    );
    return NULL;
  }

  // Allocate threads memory
  thrds = malloc(sizeof(pthread_t) * nb_thrd);
  if(thrds == NULL){
    PyErr_SetString(
      PyExc_MemoryError,
      "Memory allocation failed"
    );
    return NULL;
  }
  
  result_hash = malloc(33);
  juggfind(nb_thrd, thrds);

  if(result_hash != NULL){
    return Py_BuildValue("(s)", result_hash);
  }else{
    PyErr_SetString(
      PyExc_SystemError,
      "Something went wrong with the result crafting"
    );
    return NULL;
  }
}

// Define the methods name
static PyMethodDef JuggfindMethods[] = {
  {
    "juggfind",
    method_juggfind,
    METH_VARARGS,
    "Python interface for the type juggling attack hash finder"
  },
  {NULL, NULL, 0, NULL}
};

// Define the module name and description
static struct PyModuleDef juggfindmodule = {
    PyModuleDef_HEAD_INIT,
    "juggfind",
    "Python interface for the type juggling attack hash finder",
    -1,
    JuggfindMethods
};

// Initialize the module
PyMODINIT_FUNC PyInit_juggfind(void) {
  return PyModule_Create(&juggfindmodule);
}