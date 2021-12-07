/**
 * @author Gregory Lerbret
 * @brief Gestion de files
 * @version 1.0.0
 * @copyright MIT license
 */

#include "queue.h"
#include "bool.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define xstr(s) str(s)
#define str(s) #s

#define QUEUE_NAME	    "Gestion de files"
#define QUEUE_VERS_MAJ	1
#define QUEUE_VERS_MIN	0
#define QUEUE_VERS_BRCH 0
#define QUEUE_ID		QUEUE_NAME " - Version " xstr(QUEUE_VERS_MAJ) "." xstr(QUEUE_VERS_MIN) "." xstr(QUEUE_VERS_BRCH)

typedef struct queue_cell
{
  struct queue_cell*  next;
  struct queue_cell*  prev;
  void*               data;
  size_t              dataSize;
} queue_cell_s;

struct queue
{
  queue_cell_s* head;
  queue_cell_s* tail;
  size_t        nbCells;
};

static queue_cell_s* QUEUE_AllocCell(const void* data, size_t dataSize)
{
  queue_cell_s* cell = NULL;

  if(data || dataSize)
  {
    cell = malloc(sizeof * cell);
    if(cell)
    {
      /* Intialisation de la cellule */
      cell->next = NULL;
      cell->prev = NULL;

      cell->data = malloc(dataSize);
      if(cell->data)
      {
        memcpy(cell->data, data, dataSize);
        cell->dataSize = dataSize;
      }
      else
      {
        /* Echec de l'allocation, on detruit la cellule et on retourne NULL */
        free(cell), cell = NULL;
      }
    }
  }

  return cell;
}

static queue_cell_s* QUEUE_DetachCell(queue_s* queue)
{
  queue_cell_s* tmpCell = NULL;

  if(!QUEUE_IsEmpty(queue))
  {
    /* On detache la cellule */
    tmpCell = queue->tail;
    queue->tail = queue->tail->prev;
    if(queue->tail != NULL)
    {
      queue->tail->next = NULL;
    }
    else
    {
      /* La liste est maintenant vide */
      queue->head = NULL;
    }

    queue->nbCells--;
  }
  return tmpCell;
}

const char* QUEUE_Identifier(void)
{
  return QUEUE_ID;
}

int QUEUE_Version(void)
{
  return QUEUE_VERS_MAJ * 10000 + QUEUE_VERS_MIN * 100 + QUEUE_VERS_BRCH;
}

queue_s* QUEUE_Create(void)
{
  queue_s* queue = malloc(sizeof * queue);
  if(queue)
  {
    /* Initialisation de la file */
    queue->head = NULL;
    queue->tail = NULL;
    queue->nbCells = 0;
  }
  return queue;
}

void QUEUE_Destroy(queue_s* queue)
{
  /* On retire iterativement toutes les cellules de la file */
  while(QUEUE_Remove(queue) != QUEUE_EMPTY_QUEUE)
  {
    /* NOP */
  }

  /* Puis on detruit la file*/
  free(queue), queue = NULL;
}

bool QUEUE_IsEmpty(const queue_s* queue)
{
  return !queue->head;
}

size_t QUEUE_Size(const queue_s* queue)
{
  return queue->nbCells;
}

QUEUE_Error_e QUEUE_Enqueue(queue_s* queue, const void* data, size_t dataSize)
{
  queue_cell_s* cell = QUEUE_AllocCell(data, dataSize);
  if(cell)
  {
    /* Mise a jour du chainage des elements */
    cell->next = queue->head;
    cell->prev = NULL;
    if(queue->head)
    {
      queue->head->prev = cell;
    }

    /* Mise a jour de la file */
    queue->head = cell;
    if(queue->nbCells == 0)
    {
      queue->tail = cell;
    }
    queue->nbCells++;
    return QUEUE_NO_ERROR;
  }
  else
  {
    return QUEUE_MEMORY_ERROR;
  }
}

const void* QUEUE_Dequeue(queue_s* queue)
{
  queue_cell_s* tmpCell = QUEUE_DetachCell(queue);
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

const void* QUEUE_Peek(const queue_s* queue)
{
  if(QUEUE_IsEmpty(queue))
  {
    return NULL;
  }
  else
  {
    return queue->tail->data;
  }
}

QUEUE_Error_e QUEUE_Remove(queue_s* queue)
{
  queue_cell_s* tmpCell = QUEUE_DetachCell(queue);
  if(tmpCell == NULL)
  {
    return QUEUE_EMPTY_QUEUE;
  }
  else
  {
    if(tmpCell->dataSize)
    {
      free(tmpCell->data);
    }
    free(tmpCell);

    return QUEUE_NO_ERROR;
  }
}

queue_s* QUEUE_Clone(const queue_s* queue)
{
  /* Creation de la file clone */
  queue_s* dstQueue = QUEUE_Create();

  if(dstQueue)
  {
    QUEUE_Error_e error = QUEUE_NO_ERROR;

    /* Insertion iterative de tous les elements de la file originale. */
    for(queue_cell_s* currentCell = queue->tail; currentCell != NULL && error == QUEUE_NO_ERROR; currentCell = currentCell->prev)
    {
      error = QUEUE_Enqueue(dstQueue, currentCell->data, currentCell->dataSize);
    }

    /* Une erreur s'est produite lors de l'insertion, on efface la file partiellement dupliquee */
    if(error == QUEUE_MEMORY_ERROR)
    {
      QUEUE_Destroy(dstQueue);
      dstQueue = NULL;
    }
  }
  return dstQueue;
}
