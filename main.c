//
//  main.c
//  jgb
//
// Copyright (C) Robert Gledhill (2015, 2023) 
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "stack.h"
#include "DataVector.h"
#include "operators.h"
#include "RPN.h"


int main(int argc, const char** argv)
{

  srand((unsigned int)time(NULL));
  
  struct RPN* r = RPN_new(10, 5);
  RPN_setup_test_1(r);
  RPN_solve(r);
  RPN_delete(r);

  return 0;
}
