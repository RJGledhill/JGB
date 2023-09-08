//
//  pythonInterface.c
//  jgb
//
// Copyright (C) Robert Gledhill (2015, 2023) 
//
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#include <python2.7/Python.h>
#include "numpy/arrayobject.h"
#include "pythonInterface.h"


static PyObject* py_myFunction(PyObject* self, PyObject* args)
{
  char *s = "Stitches together C and Python elements!";
  return Py_BuildValue("s", s);
}


// -----------------------------------------------------------------
static PyObject* py_myOtherFunction(PyObject* self, PyObject* args)
{
  double x, y;
  PyArg_ParseTuple(args, "dd", &x, &y);
  return Py_BuildValue("d", x*y);
}


// -----------------------------------------------------------------
static PyObject* py_vectorToJGB(PyObject* self, PyObject* args)
{
  PyArrayObject* dv;
  int offset;
  int size;
  NpyIter *in_iter;
  NpyIter_IterNextFunc *in_iternext;
  PyArg_ParseTuple(args, "iiO!", &size, &offset, &PyArray_Type, &dv);
  in_iter = NpyIter_New(dv, NPY_ITER_READONLY, NPY_KEEPORDER, NPY_NO_CASTING, NULL);
  in_iternext = NpyIter_GetIterNext(in_iter, NULL);
  float ** in_dataptr = (float **) NpyIter_GetDataPtrArray(in_iter);
  printf ("%x %i %i\n", in_dataptr,size, offset);
  float* myptr = (float*) *in_dataptr;
  printf("[0] %lx %f\n",  &myptr[offset+0], myptr[offset+0]);
  printf("[1] %lx %f\n",  &myptr[offset+1], myptr[offset+1]);
  printf("[2] %lx %f\n",  &myptr[offset+2], myptr[offset+2]);
  printf ("address %% 4096 = %i\n", (int) (myptr+offset) % 4096);
  
  myptr[offset+0] = 8.2468f;
  
 /* for (int i = 0; i < size; i++)
  {
    printf ("dv[%i] = %f\n", i, *in_dataptr[offset+i] );
  }*/
  
  return Py_BuildValue("d", 1);
}

// -----------------------------------------------------------------
static PyMethodDef JGB_methods[] = {
  {"myFunction", py_myFunction, METH_VARARGS},
  {"myOtherFunction", py_myOtherFunction, METH_VARARGS},
  {"vectorToJGB", py_vectorToJGB, METH_VARARGS},
  {NULL, NULL}
};


// -----------------------------------------------------------------
void initJGB()
{
  (void) Py_InitModule("JGB", JGB_methods);
  import_array();
}


