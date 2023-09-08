//
//  operators.h
//  jgb
//
// Copyright (C) Robert Gledhill (2015, 2023) 
//

#ifndef __jgb__operators__
#define __jgb__operators__


#include "DataVector.h"

void op_add(struct DataVector* source1, struct DataVector* source2, struct DataVector* dest);
void op_subtract(struct DataVector* source1, struct DataVector* source2, struct DataVector* dest);
void op_multiply(struct DataVector* source1, struct DataVector* source2, struct DataVector* dest);
void op_divide(struct DataVector* source1, struct DataVector* source2, struct DataVector* dest);
void op_inv_divide(struct DataVector* source1, struct DataVector* source2, struct DataVector* dest);
void op_inv_subtract(struct DataVector* source1, struct DataVector* source2, struct DataVector* dest);
void op_normalise_exponential_unity(struct DataVector* source1, struct DataVector* dest);







#endif /* defined(__jgb__operators__) */
