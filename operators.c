//
//  operators.c
//  jgb
//
// Copyright (C) Robert Gledhill (2015, 2023) 
//

#include <stdio.h>
#include <assert.h>
#include "operators.h"
#include "DataVector.h"

void op_add(struct DataVector* source1, struct DataVector* source2, struct DataVector* dest)
{
  assert (source1->m_size == source2->m_size);
  assert (source2->m_size == dest->m_size);
  assert (source1->m_type != DV_DELETED);
  assert (source2->m_type != DV_DELETED);
  assert (dest->m_type != DV_DELETED);
  for (int i = 0; i <= source1->m_size; i++)
    dest->m_data[i] = source1->m_data[i] + source2->m_data[i];
}

void op_subtract(struct DataVector* source1, struct DataVector* source2, struct DataVector* dest)
{
  assert (source1->m_size == source2->m_size);
  assert (source2->m_size == dest->m_size);
  assert (source1->m_type != DV_DELETED);
  assert (source2->m_type != DV_DELETED);
  assert (dest->m_type != DV_DELETED);
  for (int i = 0; i <= source1->m_size; i++)
    dest->m_data[i] = source1->m_data[i] - source2->m_data[i];
}

void op_multiply(struct DataVector* source1, struct DataVector* source2, struct DataVector* dest)
{
  assert (source1->m_size == source2->m_size);
  assert (source2->m_size == dest->m_size);
  assert (source1->m_type != DV_DELETED);
  assert (source2->m_type != DV_DELETED);
  assert (dest->m_type != DV_DELETED);
  for (int i = 0; i <= source1->m_size; i++)
    dest->m_data[i] = source1->m_data[i] * source2->m_data[i];
}

void op_divide(struct DataVector* source1, struct DataVector* source2, struct DataVector* dest)
{
  assert (source1->m_size == source2->m_size);
  assert (source2->m_size == dest->m_size);
  assert (source1->m_type != DV_DELETED);
  assert (source2->m_type != DV_DELETED);
  assert (dest->m_type != DV_DELETED);
  for (int i = 0; i <= source1->m_size; i++)
    dest->m_data[i] = source1->m_data[i] / source2->m_data[i];
}

void op_inv_divide(struct DataVector* source1, struct DataVector* source2, struct DataVector* dest)
{
  assert (source1->m_size == source2->m_size);
  assert (source2->m_size == dest->m_size);
  assert (source1->m_type != DV_DELETED);
  assert (source2->m_type != DV_DELETED);
  assert (dest->m_type != DV_DELETED);
  for (int i = 0; i <= source1->m_size; i++)
    dest->m_data[i] = source2->m_data[i] / source1->m_data[i];
}

void op_inv_subtract(struct DataVector* source1, struct DataVector* source2, struct DataVector* dest)
{
  assert (source1->m_size == source2->m_size);
  assert (source2->m_size == dest->m_size);
  assert (source1->m_type != DV_DELETED);
  assert (source2->m_type != DV_DELETED);
  assert (dest->m_type != DV_DELETED);
  for (int i = 0; i <= source1->m_size; i++)
    dest->m_data[i] = source2->m_data[i] - source1->m_data[i];
}

void op_normalise_exponential_unity(struct DataVector* source1, struct DataVector* dest)
{
  assert (false); // To be done.
}





