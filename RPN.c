//
//  RPN.c
//  jgb
//
// Copyright (C) Robert Gledhill (2015, 2023) 
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "RPN.h"
#include "stack.h"
#include "DataVector.h"
#include "operators.h"


//---------------------------------------------------------------------------
struct RPN* RPN_new(int blankCount, int vectorWidth)
{
  // Create space for stacks
  struct RPN* n = (struct RPN*) malloc(sizeof(struct RPN));
  n->m_bin = Stack_new();
  n->m_blanks = Stack_new();
  n->m_eqn = Stack_new();
  n->m_temp = Stack_new();
  n->m_width = vectorWidth;
  
  // Push blank vector SIs onto blanks stack
  for (int i = 0; i < blankCount; i++)
  {
    struct DataVector* v = DataVector_new_blank(0, n->m_width);
    struct StackItem* i = StackItem_new(DATAVECTOR,v);
    Stack_push_top(n->m_blanks, i);
  }
  n->m_status = RPN_BLANK;
  return n;
}


//---------------------------------------------------------------------------
void RPN_delete(struct RPN* t)
{
  Stack_delete(t->m_eqn);
  Stack_delete(t->m_bin);
  Stack_delete(t->m_blanks);
  Stack_delete(t->m_temp);
  t->m_status = RPN_SOLVE_DELETED;
  free (t);
}


//---------------------------------------------------------------------------
void RPN_errorHalt(char* problem)
{
  fprintf(stderr, "[FATAL HALT] : %s", problem);
  exit(-1);
}


//---------------------------------------------------------------------------
void RPN_setup_test_1(struct RPN* t)
{
  // NB that we are pushing items onto the _bottom_ of the stack, that way the RPN expression is added as you would read it from left to right.
  struct DataVector* d = DataVector_new_randomInt(0, t->m_width);
  struct StackItem* si = StackItem_new(DATAVECTOR,d);
  Stack_push_bottom(t->m_eqn, si);
  d = DataVector_new_randomInt(0, t->m_width);
  si = StackItem_new(DATAVECTOR,d);
  Stack_push_bottom(t->m_eqn, si);
  
  si = StackItem_new(OP_ADD,NULL);
  Stack_push_bottom(t->m_eqn, si);
  
  d = DataVector_new_randomInt(0, t->m_width);
  si = StackItem_new(DATAVECTOR,d);
  Stack_push_bottom(t->m_eqn, si);
  
  si = StackItem_new(OP_MULTIPLY,NULL);
  Stack_push_bottom(t->m_eqn, si);

  d = DataVector_new_randomInt(0, t->m_width);
  si = StackItem_new(DATAVECTOR,d);
  Stack_push_bottom(t->m_eqn, si);
  
  si = StackItem_new(OP_SUBTRACT,NULL);
  Stack_push_bottom(t->m_eqn, si);
  
  d = DataVector_new_randomInt(0, t->m_width);
  si = StackItem_new(DATAVECTOR,d);
  Stack_push_bottom(t->m_eqn, si);

  si = StackItem_new(OP_DIVIDE,NULL);
  Stack_push_bottom(t->m_eqn, si);
  
  Stack_printout(t->m_eqn);
}


//---------------------------------------------------------------------------
void RPN_solve(struct RPN* t)
{
  // Solve the RPN equation.  When done, the m_eqn stack should contain exactly one item -- the answer!
  int finished = 0;
  while (finished == 0)
  {
    // If there is exactly one item left on the stack then it is the answer data vector and we have finished
    if ((t->m_eqn->m_itemsInStack == 1) && (t->m_eqn->m_top->m_type == DATAVECTOR))
    {
      finished = 1;
      break;
    }
    
    // If there is nothing left on the stack then something has gone wrong
    if (t->m_eqn->m_itemsInStack == 0)
      RPN_errorHalt("Size of equation stack in RPN solver has reached 0");
    
    struct StackItem* i;
    struct StackItem* j;
    struct StackItem* k;
    enum StackItemType op = t->m_eqn->m_top->m_type;
    if (op == DATAVECTOR)
    {
      i = Stack_pop_top(t->m_eqn);
      Stack_push_top(t->m_temp, i);
    }
    else if((op == SI_LAST_TYPE) || (op == SI_DELETED))
    {
      RPN_errorHalt("Equation stack has a SI_LAST_TYPE or SI_DELETED entry on it");
    }
    else if((op >= OP_ADD) || (op <= OP_INV_SUBTRACT))
    {
      i = Stack_pop_top(t->m_eqn);
      Stack_push_top(t->m_bin, i);
      i = Stack_pop_top(t->m_temp);
      j = Stack_pop_top(t->m_temp);
      k = Stack_pop_top(t->m_blanks);
      assert((i != NULL) && (i->m_type = DATAVECTOR));
      assert((j != NULL) && (j->m_type = DATAVECTOR));
      assert((k != NULL) && (k->m_type = DATAVECTOR));
      switch (op)
      { // ... Then we have a two operand operator
      case OP_ADD:
        op_add(i->m_data, j->m_data, k->m_data);
        break;
      case OP_SUBTRACT:
        op_subtract(i->m_data, j->m_data, k->m_data);
        break;
      case OP_MULTIPLY:
        op_multiply(i->m_data, j->m_data, k->m_data);
        break;
      case OP_DIVIDE:
        op_divide(i->m_data, j->m_data, k->m_data);
        break;
      case OP_INV_DIVIDE:
        op_inv_divide(i->m_data, j->m_data, k->m_data);
        break;
      case OP_INV_SUBTRACT:
        op_inv_subtract(i->m_data, j->m_data, k->m_data);
        break;
      default:
        RPN_errorHalt("Bizarre fall through in RPN two operand operator switch statement.  Enum borked?");
      }
      Stack_push_top(t->m_bin, i);
      Stack_push_top(t->m_bin, j);
      Stack_push_top(t->m_eqn, k);
    }
    else
    {
      RPN_errorHalt("Not implemented yet");
    }
    
  } // while loop over expression
  // Print out our result
  Stack_printout(t->m_eqn);
}






































