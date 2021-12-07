/**
 * @author Gregory Lerbret
 * @brief Gestion de piles
 * @version 1.0.0
 * @copyright MIT license
 */

#include "stack.h"
#include "bool.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define xstr(s) str(s)
#define str(s) #s

#define STACK_NAME	    "Gestion de piles"
#define STACK_VERS_MAJ	1
#define STACK_VERS_MIN  0
#define STACK_VERS_BRCH 0
#define STACK_ID		    STACK_NAME " - Version " xstr(STACK_VERS_MAJ) "." xstr(STACK_VERS_MIN) "." xstr(STACK_VERS_BRCH)

typedef struct stack_cell
{
  struct stack_cell*  next;
  struct stack_cell*  prev;
  void*               data;
  size_t              dataSize;
} stack_cell_s;

struct stack
{
  stack_cell_s*   head;
  stack_cell_s*   tail;
  size_t          nbCells;
};

static stack_cell_s* STACK_AllocCell(const void* data, size_t dataSize)
{
  stack_cell_s* cell = NULL;
  if(data || dataSize)
  {
    cell = malloc(sizeof * cell);
    if(cell)
    {
      /* Intialisation de la cellule */
      cell->next = NULL;
      cell->prev = NULL;

      cell->data = malloc(dataSize);
      if(cell->data == NULL)
      {
        /* Echec de l'allocation, on detruit la cellule et on retourne NULL */
        free(cell), cell = NULL;
      }
      else
      {
        memcpy(cell->data, data, dataSize);
        cell->dataSize = dataSize;
      }
    }
  }
  return cell;
}

static stack_cell_s* STACK_DetachCell(stack_s* stack)
{
  stack_cell_s* tmpCell = NULL;

  if(!STACK_IsEmpty(stack))
  {
    /* On detache la cellule */
    tmpCell = stack->head;
    stack->head = tmpCell->next;
    if(stack->head)
    {
      stack->head->prev = NULL;
    }
    else
    {
      /* La liste est maintenant vide */
      stack->tail = NULL;
    }

    stack->nbCells--;
  }
  return tmpCell;
}

const char* STACK_Identifier(void)
{
  return STACK_ID;
}

int STACK_Version(void)
{
  return STACK_VERS_MAJ * 10000 + STACK_VERS_MIN * 100 + STACK_VERS_BRCH;
}

stack_s* STACK_Create(void)
{
  stack_s* stack = malloc(sizeof *stack);
  if(stack)
  {
    /* Initialisation de la pile */
    stack->head = NULL;
    stack->tail = NULL;
    stack->nbCells = 0;
  }
  return stack;
}

void STACK_Destroy(stack_s* stack)
{
  /* On retire iterativement toutes les cellules de la pile */
  while(STACK_Remove(stack) != STACK_EMPTY_STACK)
  {
    /* NOP */
  }

  /* Puis on detruit la pile*/
  free(stack);
}

bool STACK_IsEmpty(const stack_s* stack)
{
  return !stack->head;
}

size_t STACK_Size(const stack_s* stack)
{
  return stack->nbCells;
}

STACK_Error_e STACK_Push(stack_s* stack, const void* data, size_t dataSize)
{
  stack_cell_s* cell = STACK_AllocCell(data, dataSize);
  if(cell)
  {
    /* Mise a jour du chainage des elements */
    cell->next = stack->head;
    cell->prev = NULL;

    if(stack->head)
    {
      stack->head->prev = cell;
    }

    /* Mise a jour de la pile */
    stack->head = cell;
    if(stack->nbCells == 0)
    {
      stack->tail = cell;
    }
    stack->nbCells++;
    return STACK_NO_ERROR;
  }
  else
  {
    return STACK_MEMORY_ERROR;
  }
}

const void* STACK_Pop(stack_s* stack)
{
  stack_cell_s* tmpCell = STACK_DetachCell(stack);
  if(tmpCell)
  {
    const void* data = tmpCell->data;
    free(tmpCell);
    return data;
  }
  else
  {
    return NULL;
  }
}

const void* STACK_Peek(const stack_s* stack)
{
  if(STACK_IsEmpty(stack))
  {
    return NULL;
  }
  else
  {
    return stack->head->data;
  }
}

STACK_Error_e STACK_Remove(stack_s* stack)
{
  stack_cell_s* tmpCell = STACK_DetachCell(stack);
  if(tmpCell == NULL)
  {
    return STACK_EMPTY_STACK;
  }
  else
  {
    if(tmpCell->dataSize)
    {
      free(tmpCell->data);
    }
    free(tmpCell);

    return STACK_NO_ERROR;
  }
}

stack_s* STACK_Clone(const stack_s* stack)
{
  /* Creation de la pile clone */
  stack_s* dstStack = STACK_Create();
  if(dstStack)
  {
    STACK_Error_e error = STACK_NO_ERROR;

    /* Insertion iterative de tous les elements de la pile originale. */
    for(stack_cell_s* currentCell = stack->tail; currentCell != NULL && error == STACK_NO_ERROR; currentCell = currentCell->prev)
    {
      error = STACK_Push(dstStack, currentCell->data, currentCell->dataSize);
    }

    /* Une erreur s'est produite lors de l'insertion, on efface la pile partiellement dupliquee */
    if(error == STACK_MEMORY_ERROR)
    {
      STACK_Destroy(dstStack);
      dstStack = NULL;
    }
  }
  return dstStack;
}
