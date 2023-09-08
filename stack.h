//
//  RPN.h
//  jgb
//
// Copyright (C) Robert Gledhill (2015, 2023)  
//
#ifndef jgb_stack_h
#define jgb_stack_h



#include "DataVector.h"

// Item type
enum StackItemType
{
  DATAVECTOR = 1,
  // Operators taking two arguments to produce a result
  OP_ADD = 2,
  OP_SUBTRACT = 3,
  OP_MULTIPLY = 4,
  OP_DIVIDE = 5,
  OP_INV_DIVIDE = 6,
  OP_INV_SUBTRACT = 7,
  //Operators taking one argument to produce a result
  OP_NORMALISE_EXPONENTIAL_UNITY = 8,
  //Other...
  REPORT = 9,
  SI_LAST_TYPE,
  SI_DELETED = 9999
};

// Stack item: can either be an operator, or a datavector (pointer is stored)
struct StackItem
{
  struct StackItem* m_above;
  struct StackItem* m_below;
  enum StackItemType m_type;
  struct DataVector* m_data;  // NULL if unused
};

// Functions for stack item
struct StackItem* StackItem_new(enum StackItemType, struct DataVector*);
void StackItem_delete(struct StackItem*);

// Strictly this is a total misnomer now, as it has morphed into a double ended queue!
struct Stack
{
  int m_itemsInStack;
  struct StackItem* m_top;
  struct StackItem* m_bottom;
};

// Functions for stack
void Stack_push_top(struct Stack*, struct StackItem*);
void Stack_push_bottom(struct Stack*, struct StackItem*);
struct StackItem* Stack_pop_top(struct Stack*);
struct StackItem* Stack_pop_bottom(struct Stack*);
void Stack_printout(struct Stack*);
struct Stack* Stack_new();
void Stack_delete(struct Stack*);





#endif
