//
//  RPN.h
//  jgb
//
// Copyright (C) Robert Gledhill (2015, 2023) 
//

#ifndef __jgb__RPN__
#define __jgb__RPN__

#include "DataVector.h"
#include "stack.h"

enum RPN_Status
{
  RPN_BLANK = 0,            // Created, and with blank vector list set up, but no eqn to solve yet
  RPN_READY_TO_SOLVE = 1,
  RPN_SOLVED_OK = 2,
  RPN_SOLVE_ERROR = 3,
  RPN_SOLVE_DELETED = 4
};

struct RPN
{
  struct Stack* m_eqn;      // The equation we will be solving.
  struct Stack* m_blanks;   // A stack of blank SIs for scratch in the calculation
  struct Stack* m_bin;      // Bin for SIs we have finished with
  struct Stack* m_temp;     // Temporary work space for solver
  enum RPN_Status m_status; // What state the solver is in
  int m_width;              // Width of the vectors
};


// Set up a test for the solver
void RPN_setup_test_1(struct RPN* t);

// Solve the RPN equation.  When done, the m_eqn stack should contain exactly one item left -- the answer!
void RPN_solve(struct RPN* t);

// Create
struct RPN* RPN_new(int blankCount, int vectorWidth);

// Delete
void RPN_delete(struct RPN* t);

// Internally used halt function
void RPN_errorHalt(char* problem);



#endif /* defined(__jgb__RPN__) */
