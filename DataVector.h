//
//  DataVector.h
//  jgb
//
// Copyright (C) Robert Gledhill (2015, 2023) 
//

#ifndef __jgb__DataVector__
#define __jgb__DataVector__

#include <stdio.h>

enum DataVectorType
{
  RAW_ORIGINAL_MEMORY = 1,
  ZEROES = 2,
  RANDOM_INTEGERS = 3,
  DV_LAST_TYPE,
  DV_DELETED
};

struct DataVector
{
  enum DataVectorType m_type;     // What sort of data
  int m_ts;       // Timestamp associated with data
  int m_globalID; // Single, global id number for keeping track
  int m_size;     // How many floats are stored here
  float* m_data;
};

// Functions associated with DataVector
struct DataVector* DataVector_new_raw(int size);
struct DataVector* DataVector_new_blank(int ts, int size);
struct DataVector* DataVector_new_randomInt(int ts, int size);
void DataVector_printData(struct DataVector*);
void DataVector_printLong(struct DataVector*);
void DataVector_delete(struct DataVector*);

#endif /* defined(__jgb__DataVector__) */
