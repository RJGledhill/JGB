//
//  DataVector.c
//  jgb
//
// Copyright (C) Robert Gledhill (2015, 2023) 
//
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DataVector.h"

static int GlobalIDCount = 0;

//-------------------------------------------------------------------------------
struct DataVector* DataVector_new_raw(int size)
{
  struct DataVector* v = (struct DataVector*) malloc(sizeof(struct DataVector));
  float* d = (float*) malloc (sizeof(float) * size);
  v->m_data = d;
  v->m_globalID = GlobalIDCount;
  v->m_type = RAW_ORIGINAL_MEMORY;
  v->m_ts = 0;
  GlobalIDCount++;
  v->m_size = size;
  return v;
}


//-------------------------------------------------------------------------------
struct DataVector* DataVector_new_blank(int ts, int size)
{
  struct DataVector* v = DataVector_new_raw(size);
  v->m_type = ZEROES;
  v->m_ts = ts;
  for (int i = 0; i < size; i++)
    v->m_data[i] = 0.0;
  return v;
}


//-------------------------------------------------------------------------------
struct DataVector* DataVector_new_randomInt(int ts, int size)
{
  struct DataVector* v = DataVector_new_raw(size);
  v->m_type = RANDOM_INTEGERS;
  v->m_ts = ts;
  for (int i = 0; i < size; i++)
    v->m_data[i] = (float) ((rand() & 15) - 8);
  return v;
}


//-------------------------------------------------------------------------------
void DataVector_printData(struct DataVector* v)
{
  fprintf(stdout, "[ ");
  for (int i = 0; i < v->m_size; i++)
    fprintf(stdout, "%.2f ", v->m_data[i]);
  fprintf(stdout, "]");
}


//-------------------------------------------------------------------------------
void DataVector_printLong(struct DataVector* v)
{
  fprintf(stdout, "V(%i %i %i %i)", v->m_globalID, v->m_ts, v->m_size, v->m_type);
  DataVector_printData(v);
  fprintf(stdout, "\n");
}


//-------------------------------------------------------------------------------
void DataVector_delete(struct DataVector* v)
{
  assert(v->m_type != DV_DELETED);
  free(v->m_data);
  v->m_data = NULL;
  v->m_type = DV_DELETED;
  v->m_size = 0;
  v->m_ts = 0;
  free(v);
}











