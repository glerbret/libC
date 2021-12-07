/**
 * @author Gregory Lerbret
 * @brief Gestion de listes circulaires
 * @version 1.0.0
 * @copyright MIT license
 */

#include "clist.h"
#include "bool.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define xstr(s) str(s)
#define str(s) #s

#define CLIST_NAME      "Gestion de liste circulaire"
#define CLIST_VERS_MAJ  1
#define CLIST_VERS_MIN  0
#define CLIST_VERS_BRCH 0
#define CLIST_ID        CLIST_NAME " - Version " xstr(CLIST_VERS_MAJ) "." xstr(CLIST_VERS_MIN) "." xstr(CLIST_VERS_BRCH)

typedef struct clist_cell
{
  struct clist_cell*  next;
  struct clist_cell*  prev;
  void*               data;
  size_t              dataSize;
} clist_cell_s;

struct clist
{
  clist_cell_s* head;
  clist_cell_s* current;
  size_t        nbCells;
  int (*compar)(const void *, const void *);
};

static clist_cell_s* CLIST_AllocCell(const void* data, size_t dataSize)
{
  clist_cell_s* cell = NULL;

  if(data && dataSize)
  {
    cell = malloc(sizeof * cell);
    if(cell)
    {
      /* Intialisation de la cellule */
      cell->next = cell;
      cell->prev = cell;

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

static clist_cell_s* CLIST_DetachCell(clist_s* list, clist_cell_s* cellToDelete)
{
  clist_cell_s* cell = NULL;

  if(cellToDelete)
  {
    /* On detache la cellule */
    cell = cellToDelete;

    cell->prev->next = cell->next;
    cell->next->prev = cell->prev;
    list->nbCells--;

    if(list->nbCells == 0)
    {
      /* La liste est maintenant vide */
      list->head = NULL;
      list->current = NULL;
    }
    else
    {
      if(cell == list->current)
      {
        /* On vient de supprimer la cellule courante, la cellule suivante devient la nouvelle cellule courante */
        list->current = cell->next;
      }

      if(cell == list->head)
      {
        /* On vient de supprimer la tete de la liste, la cellule suivante devient la nouvelle tete de liste */
        list->head = cell->next;
      }
    }
  }

  return cell;
}

const char* CLIST_Identifier(void)
{
  return CLIST_ID;
}

int CLIST_Version(void)
{
  return CLIST_VERS_MAJ * 10000 + CLIST_VERS_MIN * 100 + CLIST_VERS_BRCH;
}

clist_s* CLIST_Create(int (*compar)(const void *, const void *))
{
  clist_s* list = malloc(sizeof *list);
  if(list)
  {
    /* Initialisation de la liste */
    list->head = NULL;
    list->current = NULL;
    list->nbCells = 0;
    list->compar = compar;
  }

  return list;
}

void CLIST_Destroy(clist_s* list)
{
  /* On se positionne sur le premier element ... */
  if(CLIST_SeekFirst(list) == CLIST_NO_ERROR)
  {
    /* ... et on retire iterativement toutes les cellules de la liste */
    while(CLIST_RemoveFirst(list) != CLIST_EMPTY_LIST)
    {
      /* NOP */
    }
  }

  /* Puis on detruit la liste*/
  free(list), list = NULL;
}

void CLIST_SetCmp(clist_s* list, int (*compar)(const void *, const void *))
{
  list->compar = compar;
}

bool CLIST_IsEmpty(const clist_s* list)
{
  return !list->head;
}

size_t CLIST_Size(const clist_s* list)
{
  return list->nbCells;
}

bool CLIST_IsHead(const clist_s* list)
{
  return !CLIST_IsEmpty(list) && list->current == list->head;
}

CLIST_Error_e CLIST_InsertFirst(clist_s* list, const void* data, size_t dataSize)
{
  clist_cell_s* cell = CLIST_AllocCell(data, dataSize);
  if(cell)
  {
    /* Mise a jour du chainage des elements */
    if(list->head != NULL)
    {
      cell->next = list->head;
      cell->prev = list->head->prev;
    }
    cell->prev->next = cell;
    cell->next->prev = cell;

    /* Mise a jour de la liste circulaire */
    list->head = cell;
    list->current = cell;
    list->nbCells++;

    return CLIST_NO_ERROR;
  }
  else
  {
    return CLIST_MEMORY_ERROR;
  }
}

CLIST_Error_e CLIST_InsertNext(clist_s* list, const void* data, size_t dataSize)
{
  clist_cell_s* cell = CLIST_AllocCell(data, dataSize);
  if(cell)
  {
    /* Mise a jour du chainage des elements */
    if(list->current != NULL)
    {
      cell->next = list->current->next;
      cell->prev = list->current;
    }
    cell->prev->next = cell;
    cell->next->prev = cell;

    /* Mise a jour de la liste circulaire */
    if(list->nbCells == 0)
    {
      list->head = cell;
    }
    list->current = cell;
    list->nbCells++;

    return CLIST_NO_ERROR;
  }
  else
  {
    return CLIST_MEMORY_ERROR;
  }
}

CLIST_Error_e CLIST_InsertPrev(clist_s* list, const void* data, size_t dataSize)
{
  clist_cell_s* cell = CLIST_AllocCell(data, dataSize);
  if(cell)
  {
    /* Mise a jour du chainage des elements */
    if(list->current != NULL)
    {
      cell->next = list->current;
      cell->prev = list->current->prev;
    }
    cell->prev->next = cell;
    cell->next->prev = cell;

    /* Mise a jour de la liste circulaire */
    if(list->nbCells == 0)
    {
      list->head = cell;
    }
    list->current = cell;
    list->nbCells++;

    return CLIST_NO_ERROR;
  }
  else
  {
    return CLIST_MEMORY_ERROR;
  }
}

CLIST_Error_e CLIST_SeekFirst(clist_s* list)
{
  if(CLIST_IsEmpty(list))
  {
    return CLIST_EMPTY_LIST;
  }
  else
  {
    list->current = list->head;
    return CLIST_NO_ERROR;
  }
}

CLIST_Error_e CLIST_SeekNext(clist_s* list)
{
  if(CLIST_IsEmpty(list))
  {
    return CLIST_EMPTY_LIST;
  }
  else
  {
    list->current = list->current->next;
    return CLIST_NO_ERROR;
  }
}

CLIST_Error_e CLIST_SeekPrev(clist_s* list)
{
  if(CLIST_IsEmpty(list))
  {
    return CLIST_EMPTY_LIST;
  }
  else
  {
    list->current = list->current->prev;
    return CLIST_NO_ERROR;
  }
}

const void* CLIST_ReadFirst(const clist_s* list)
{
  if(CLIST_IsEmpty(list))
  {
    return NULL;
  }
  else
  {
    return list->head->data;
  }
}

const void* CLIST_ReadCurrent(const clist_s* list)
{
  if(CLIST_IsEmpty(list))
  {
    return NULL;
  }
  else
  {
    return list->current->data;
  }
}

const void* CLIST_ReadNext(const clist_s* list)
{
  if(CLIST_IsEmpty(list))
  {
    return NULL;
  }
  else
  {
    return list->current->next->data;
  }
}

const void* CLIST_ReadPrev(const clist_s* list)
{
  if(CLIST_IsEmpty(list))
  {
    return NULL;
  }
  else
  {
    return list->current->prev->data;
  }
}

const void* CLIST_GetFirst(clist_s* list)
{
  if(CLIST_IsEmpty(list))
  {
    return NULL;
  }
  else
  {
    clist_cell_s* tmpCell = CLIST_DetachCell(list, list->head);
    if(tmpCell == NULL)
    {
      /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
      return NULL;
    }
    else
    {
      const void* data = tmpCell->data;
      free(tmpCell), tmpCell = NULL;
      return data;
    }
  }
}

const void* CLIST_GetCurrent(clist_s* list)
{
  if(CLIST_IsEmpty(list))
  {
    return NULL;
  }
  else
  {
    clist_cell_s* tmpCell = CLIST_DetachCell(list, list->current);
    if(tmpCell == NULL)
    {
      /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
      return NULL;
    }
    else
    {
      const void* data = tmpCell->data;
      free(tmpCell), tmpCell = NULL;
      return data;
    }
  }
}

const void* CLIST_GetNext(clist_s* list)
{
  if(CLIST_IsEmpty(list))
  {
    return NULL;
  }
  else
  {
    clist_cell_s* tmpCell = CLIST_DetachCell(list, list->current->next);
    if(tmpCell == NULL)
    {
      /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
      return NULL;
    }
    else
    {
      const void* data = tmpCell->data;
      free(tmpCell), tmpCell = NULL;
      return data;
    }
  }
}

const void* CLIST_GetPrev(clist_s* list)
{
  if(CLIST_IsEmpty(list))
  {
    return NULL;
  }
  else
  {
    clist_cell_s* tmpCell = CLIST_DetachCell(list, list->current->prev);
    if(tmpCell == NULL)
    {
      /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
      return NULL;
    }
    else
    {
      const void* data = tmpCell->data;
      free(tmpCell), tmpCell = NULL;
      return data;
    }
  }
}

CLIST_Error_e CLIST_RemoveFirst(clist_s* list)
{
  if(CLIST_IsEmpty(list))
  {
    return CLIST_EMPTY_LIST;
  }
  else
  {
    clist_cell_s* tmpCell = CLIST_DetachCell(list, list->head);
    if(tmpCell == NULL)
    {
      /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
      return CLIST_EMPTY_LIST;
    }
    else
    {
      if(tmpCell->dataSize)
      {
        free(tmpCell->data);
      }
      free(tmpCell), tmpCell = NULL;
      return CLIST_NO_ERROR;
    }
  }
}

CLIST_Error_e CLIST_RemoveCurrent(clist_s* list)
{
  if(CLIST_IsEmpty(list))
  {
    return CLIST_EMPTY_LIST;
  }
  else
  {
    clist_cell_s* tmpCell = CLIST_DetachCell(list, list->current);
    if(tmpCell == NULL)
    {
      /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
      return CLIST_EMPTY_LIST;
    }
    else
    {
      if(tmpCell->dataSize)
      {
        free(tmpCell->data);
      }
      free(tmpCell), tmpCell = NULL;
      return CLIST_NO_ERROR;
    }
  }
}

CLIST_Error_e CLIST_RemoveNext(clist_s* list)
{
  if(CLIST_IsEmpty(list))
  {
    return CLIST_EMPTY_LIST;
  }
  else
  {
    clist_cell_s* tmpCell = CLIST_DetachCell(list, list->current->next);
    if(tmpCell == NULL)
    {
      /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
      return CLIST_EMPTY_LIST;
    }
    else
    {
      if(tmpCell->dataSize)
      {
        free(tmpCell->data);
      }
      free(tmpCell), tmpCell = NULL;
      return CLIST_NO_ERROR;
    }
  }
}

CLIST_Error_e CLIST_RemovePrev(clist_s* list)
{
  if(CLIST_IsEmpty(list))
  {
    return CLIST_EMPTY_LIST;
  }
  else
  {
    clist_cell_s* tmpCell = CLIST_DetachCell(list, list->current->prev);
    if(tmpCell == NULL)
    {
      /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
      return CLIST_EMPTY_LIST;
    }
    else
    {
      if(tmpCell->dataSize)
      {
        free(tmpCell->data);
      }
      free(tmpCell), tmpCell = NULL;
      return CLIST_NO_ERROR;
    }
  }
}

clist_s* CLIST_Clone(const clist_s* list)
{
  /* Creation de la liste clone */
  clist_s* destList = CLIST_Create(list->compar);

  if(destList)
  {
    CLIST_Error_e error = CLIST_NO_ERROR;

    if(list->head)
    {
      clist_cell_s* currentCell = list->head;

      /* Insertion iterative de tous les elements de la liste originale. La tete de liste sert de marqueur de fin */
      do
      {
        error = CLIST_InsertNext(destList, currentCell->data, currentCell->dataSize);
        currentCell = currentCell->next;
      }
      while(currentCell != list->head && error == CLIST_NO_ERROR);
    }

    if(error == CLIST_MEMORY_ERROR)
    {
      /* Une erreur s'est produite lors de l'insertion, on efface la liste partiellement dupliquee */
      CLIST_Destroy(destList);
      destList = NULL;
    }
    else
    {
      /* Tout s'est bien passe, on initilaise l'element courant */
      destList->current = destList->head;
    }
  }

  return destList;
}

CLIST_Error_e CLIST_SearchData(clist_s* list, const void* data)
{
  /* CLIST_SearchData() n'est qu'une encapsulation de CLIST_SearchDataFct */
  return CLIST_SearchDataFct(list, data, NULL);
}

CLIST_Error_e CLIST_SearchDataFct(clist_s* list, const void* data, int (*compar)(const void *, const void *))
{
  /* On positionne la fonction de recherche a utiliser */
  int (*usedCompar)(const void *, const void *);
  usedCompar = compar ? compar : list->compar;

  if(CLIST_IsEmpty(list))
  {
    return CLIST_EMPTY_LIST;
  }
  else if(usedCompar == NULL)
  {
    return CLIST_NO_COMP_FONCTION;
  }
  else
  {
    /* Parcours des elements de la liste jusqu'a trouver l'element recherche ou a revenir a l'element de depart */
    clist_cell_s* currentCell = list->current;
    do
    {
      if(usedCompar(data, currentCell->data) == 0)
      {
        /* L'element recherche est trouve */
        list->current = currentCell;
        return CLIST_NO_ERROR;
      }

      currentCell = currentCell->next;
    }
    while(currentCell != list->current);

    /* L'element n'a pas ete trouve */
    return CLIST_CELL_NOT_FOUND;
  }
}

CLIST_Error_e CLIST_SearchDataRev(clist_s* list, const void* data)
{
  /* CLIST_SearchDataRev() n'est qu'une encapsulation de CLIST_SearchDataRevFct */
  return CLIST_SearchDataRevFct(list, data, NULL);
}

CLIST_Error_e CLIST_SearchDataRevFct(clist_s* list, const void* data, int (*compar)(const void *, const void *))
{
  /* On positionne la fonction de recherche a utiliser */
  int (*usedCompar)(const void *, const void *);
  usedCompar = compar ? compar : list->compar;

  if(CLIST_IsEmpty(list) == true)
  {
    return CLIST_EMPTY_LIST;
  }
  else if(usedCompar == NULL)
  {
    return CLIST_NO_COMP_FONCTION;
  }
  else
  {
    /* Parcours des elements de la liste jusqu'a trouver l'element recherche ou a revenir a l'element de depart */
    clist_cell_s* currentCell = list->current;
    do
    {
      if(usedCompar(data, currentCell->data) == 0)
      {
        /* L'element recherche est trouve */
        list->current = currentCell;
        return CLIST_NO_ERROR;
      }
      currentCell = currentCell->prev;
    }
    while(currentCell != list->current);

    /* L'element n'a pas ete trouve */
    return CLIST_CELL_NOT_FOUND;
  }
}

CLIST_Error_e CLIST_RemoveData(clist_s* list, const void* data)
{
  /* CLIST_RemoveData() n'est qu'une encapsulation de CLIST_RemoveData() */
  return CLIST_RemoveDataFct(list, data, NULL);
}

CLIST_Error_e CLIST_RemoveDataFct(clist_s* list, const void* data, int (*compar)(const void *, const void *))
{
  /* On positionne la fonction de recherche a utiliser */
  int (*usedCompar)(const void *, const void *);
  usedCompar = compar ? compar : list->compar;

  if(CLIST_IsEmpty(list) == true)
  {
    return CLIST_EMPTY_LIST;
  }
  else if(usedCompar == NULL)
  {
    return CLIST_NO_COMP_FONCTION;
  }
  else
  {
    clist_cell_s* currentCell = list->current;

    /* Recherche de l'element a supprime */
    CLIST_Error_e error = CLIST_SearchDataFct(list, data, usedCompar);

    if(error == CLIST_NO_ERROR)
    {
      /* L'element a ete trouve, on le supprime */
      if(currentCell == list->current)
      {
        currentCell = currentCell->next;
      }
      error = CLIST_RemoveCurrent(list);

      /* Et on restaure l'element courant */
      list->current = currentCell;
    }
    return error;
  }
}

CLIST_Error_e CLIST_RemoveDataRev(clist_s* list, const void* data)
{
  /* CLIST_RemoveData() n'est qu'une encapsulation de CLIST_RemoveData() */
  return CLIST_RemoveDataRevFct(list, data, NULL);
}

CLIST_Error_e CLIST_RemoveDataRevFct(clist_s* list, const void* data, int (*compar)(const void *, const void *))
{
  /* On positionne la fonction de recherche a utiliser */
  int (*usedCompar)(const void *, const void *);
  usedCompar = compar ? compar : list->compar;

  if(CLIST_IsEmpty(list) == true)
  {
    return CLIST_EMPTY_LIST;
  }
  else if(usedCompar == NULL)
  {
    return CLIST_NO_COMP_FONCTION;
  }
  else
  {
    clist_cell_s* currentCell = list->current;

    /* Recherche de l'element a supprime */
    CLIST_Error_e error = CLIST_SearchDataRevFct(list, data, usedCompar);

    if(error == CLIST_NO_ERROR)
    {
      /* L'element a ete trouve, on le supprime */
      if(currentCell == list->current)
      {
        currentCell = currentCell->next;
      }
      error = CLIST_RemoveCurrent(list);

      /* Et on restaure l'element courant */
      list->current = currentCell;
    }

    return error;
  }
}

CLIST_Error_e CLIST_RemoveAllData(clist_s* list, const void* data)
{
  /* CLIST_RemoveAllData() n'est qu'une encapsulation de CLIST_RemoveAllDataFct() */
  return CLIST_RemoveAllDataFct(list, data, NULL);
}

CLIST_Error_e CLIST_RemoveAllDataFct(clist_s* list, const void* data, int (*compar)(const void *, const void *))
{
  CLIST_Error_e error = CLIST_NO_ERROR;

  /* On efface iterativement toutes les cellules correspondant au critere */
  while(error == CLIST_NO_ERROR)
  {
    error = CLIST_RemoveDataFct(list, data, compar);
  }

  /* S'il n'y a plus de cellules correspondantes, la suppression c'est bien passe */
  if(error == CLIST_CELL_NOT_FOUND)
  {
    error = CLIST_NO_ERROR;
  }
  return error;
}
