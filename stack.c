//
//  stack.c
//  jgb
//
// Copyright (C) Robert Gledhill (2015, 2023) 
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"


//---------------------------------------------------------------------------
char OperatorShortForm[] = {'0','D','+','-','*','/','|','_','N','R'};
char* OperatorLongForm[]={
  "NULL",
  "DATAVECTOR",
  "OP_ADD",
  "OP_SUBTRACT",
  "OP_MULTIPLY",
  "OP_DIVIDE",
  "OP_INV_DIVIDE",
  "OP_INV_SUBTRACT",
  "OP_NORMALISE_EXPONENTIAL_UNITY",
  "REPORT"
  };


//---------------------------------------------------------------------------
void Stack_push_top(struct Stack* s, struct StackItem* i)
{
  i->m_above = NULL;
  i->m_below = s->m_top;
  if (s->m_itemsInStack != 0)
    s->m_top->m_above = i;
  s->m_top = i;
  if (s->m_itemsInStack == 0)
    s->m_bottom = i;
  s->m_itemsInStack++;

}


//---------------------------------------------------------------------------
void Stack_push_bottom(struct Stack* s, struct StackItem* i)
{
  i->m_above = s->m_bottom;
  i->m_below = NULL;
  if (s->m_itemsInStack != 0)
    s->m_bottom->m_below = i;
  s->m_bottom = i;
  if (s->m_itemsInStack == 0)
    s->m_top = i;
  s->m_itemsInStack++;

}

//---------------------------------------------------------------------------
struct StackItem* Stack_pop_top(struct Stack* s)
{
  struct StackItem* i;
  if (s->m_itemsInStack == 0)
    return NULL;
  else if (s->m_itemsInStack == 1)
  {
    assert(s->m_bottom == s->m_top);
    i = s->m_top;
    s->m_bottom = NULL;
    s->m_top = NULL;
    s->m_itemsInStack = 0;
    i->m_above = NULL;
    i->m_below = NULL;
    return i;
  }
  else
  {
    i = s->m_top;
    s->m_top = i->m_below;
    s->m_top->m_above = NULL;
    s->m_itemsInStack--;
    i->m_above = NULL;
    i->m_below = NULL;
    return i;
  }
}


//---------------------------------------------------------------------------
struct StackItem* Stack_pop_bottom(struct Stack* s)
{
  struct StackItem* i;
  if (s->m_itemsInStack == 0)
    return NULL;
  else if (s->m_itemsInStack == 1)
  {
    assert(s->m_bottom == s->m_top);
    i = s->m_bottom;
    s->m_bottom = NULL;
    s->m_top = NULL;
    s->m_itemsInStack = 0;
    i->m_above = NULL;
    i->m_below = NULL;
    return i;
  }
  else
  {
    i = s->m_bottom;
    s->m_bottom = i->m_above;
    s->m_bottom->m_below = NULL;
    s->m_itemsInStack--;
    i->m_above = NULL;
    i->m_below = NULL;
    return i;
  }
}


//---------------------------------------------------------------------------
void Stack_printout(struct Stack* s)
{
  struct StackItem* i;
  //Long form list with details of each item
  int j = 0;
  i = s->m_top;
  fprintf(stdout, "[TOP]\n");
  while (i != NULL)
  {
    fprintf(stdout,"%i : <%s>", j, OperatorLongForm[i->m_type]);
    if (i->m_type == DATAVECTOR)
      DataVector_printLong(i->m_data);
    else
      fprintf(stdout, "\n");
    j++;
    i = i->m_below;
  }
  fprintf(stdout, "[BOTTOM]\n");
  // Short form single line RPN expression at end
  i = s->m_top;
  while (i != NULL)
  {
    fprintf(stdout,"%c", OperatorShortForm[i->m_type]);
    i = i->m_below;
  }
  fprintf(stdout, "\n");
}


//---------------------------------------------------------------------------
struct Stack* Stack_new()
{
  struct Stack* s = (struct Stack*) malloc(sizeof(struct Stack));
  s->m_bottom = NULL;
  s->m_top = NULL;
  s->m_itemsInStack = 0;
  return s;
}


//---------------------------------------------------------------------------
void Stack_delete(struct Stack* s)
{
  struct StackItem* i = Stack_pop_top(s);
  while (i != NULL)
  {
    StackItem_delete(i);
    i = Stack_pop_top(s);
  }
  assert(s->m_top == NULL);
  assert(s->m_bottom == NULL);
  assert(s->m_itemsInStack == 0);
  free(s);
}


//---------------------------------------------------------------------------
struct StackItem* StackItem_new(enum StackItemType type, struct DataVector* v)
{
  assert((type > 0) && (type < SI_LAST_TYPE));
  struct StackItem* i = (struct StackItem*) malloc(sizeof(struct StackItem));
  i->m_type = type;
  i->m_data = v;
  i->m_above = NULL;
  i->m_below = NULL;
  return i;
}


//---------------------------------------------------------------------------
void StackItem_delete(struct StackItem* i)
{
  assert(i != NULL);
  assert(i->m_type != SI_DELETED);
  i->m_type = SI_DELETED;
  i->m_above = NULL;
  i->m_below = NULL;
  if (i->m_data != NULL)
    DataVector_delete(i->m_data);
  i->m_data = NULL;
  free(i);
}

















