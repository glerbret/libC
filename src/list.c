/**
 * @author Gregory Lerbret
 * @brief Gestion de listes
 * @version 1.0.0
 * @copyright MIT license
 */

#include "list.h"
#include "bool.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define xstr(s) str(s)
#define str(s) #s

#define LIST_NAME	    "Gestion de liste"
#define LIST_VERS_MAJ   1
#define LIST_VERS_MIN   0
#define LIST_VERS_BRCH  0
#define LIST_ID         LIST_NAME " - Version " xstr(LIST_VERS_MAJ) "." xstr(LIST_VERS_MIN) "." xstr(LIST_VERS_BRCH)

typedef struct list_cell
{
    struct list_cell*   next;
    struct list_cell*   prev;
    void*               data;
    size_t              dataSize;
} list_cell_s;

struct list
{
    list_cell_s*    head;
    list_cell_s*    tail;
    list_cell_s*    current;
    size_t          nbCells;
    int (*compar)(const void *, const void *);
};

static list_cell_s* LIST_AllocCell(const void* data, size_t dataSize)
{
    list_cell_s* cell = NULL;

    if(data == NULL || dataSize == 0)
    {
        /* Il n'y a pas d'element a ajouter, on arrete ici et on retourne NULL */
        cell = NULL;
    }
    else
    {
        cell = malloc(sizeof * cell);

        if(cell == NULL)
        {
            /* Echec de l'allocation, on retourne NULL */
            /* NOP */
        }
        else
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

static list_cell_s* LIST_DetachCell(list_s* list, list_cell_s* cellToDelete)
{
    list_cell_s* cell = NULL;

    if(cellToDelete == NULL)
    {
        /* Il n'y a pas de cellule a retirer, on arrete ici et on retourne NULL */
        cell = NULL;
    }
    else
    {
        /* On detache la cellule */
        cell = cellToDelete;

        if(cell->prev == NULL)
        {
            list->head = cell->next;
        }
        else
        {
            cell->prev->next = cell->next;
        }

        if(cell->next == NULL)
        {
            list->tail = cell->prev;
        }
        else
        {
            cell->next->prev = cell->prev;
        }

        list->nbCells--;

        if(list->nbCells == 0)
        {
            /* La liste est maintenant vide */
            list->current = NULL;
        }
        else if(cell == list->current)
        {
            /* On vient de supprimmer la cellule courante, la cellule suivante (ou precedente si c'etait la derniere)
               devient la nouvelle cellule courante */
            if(cell->next != NULL)
            {
                list->current = cell->next;
            }
            else
            {
                list->current = cell->prev;
            }
        }
    }
    return cell;
}

const char* LIST_Identifier(void)
{
    return LIST_ID;
}

int LIST_Version(void)
{
    return LIST_VERS_MAJ * 10000 + LIST_VERS_MIN * 100 + LIST_VERS_BRCH;
}

list_s* LIST_Create(int (*compar)(const void *, const void *), LIST_Error_e* error)
{
    list_s* list = malloc(sizeof * list);

    if(list == NULL)
    {
        /* La liste n'a pas pu etre creer */
        *error = LIST_MEMORY_ERROR;
    }
    else
    {
        /* Initialisation de la liste */
        list->head = NULL;
        list->tail = NULL;
        list->current = NULL;
        list->nbCells = 0;
        list->compar = compar;
        *error = LIST_NO_ERROR;
    }
    return list;
}

void LIST_Destroy(list_s* list)
{
    /* On se positionne sur le premier element ... */
    if(LIST_SeekFirst(list) == LIST_NO_ERROR)
    {
        /* ... et on retire iterative toutes les cellules de la liste */
        while(LIST_RemoveFirst(list) != LIST_EMPTY_LIST)
        {
            /* NOP */
        }
    }

    /* Puis on detruit la liste*/
    free(list), list = NULL;
}

void LIST_SetCmp(list_s* list, int (*compar)(const void *, const void *))
{
    list->compar = compar;
}

bool LIST_IsEmpty(const list_s* list)
{
    return list->head == NULL;
}

size_t LIST_Size(const list_s* list)
{
    return list->nbCells;
}

bool LIST_IsHead(const list_s* list)
{
    return !LIST_IsEmpty(list) && list->current == list->head;
}

bool LIST_IsTail(const list_s* list)
{
    return !LIST_IsEmpty(list) && list->current == list->tail;
}

LIST_Error_e LIST_InsertFirst(list_s* list, const void* data, size_t dataSize)
{
    list_cell_s* cell = LIST_AllocCell(data, dataSize);
    LIST_Error_e error = LIST_NO_ERROR;

    if(cell == NULL)
    {
        error = LIST_MEMORY_ERROR;
    }
    else
    {
        /* Mise a jour du chainage des elements */
        cell->next = list->head;
        cell->prev = NULL;
        if(list->head != NULL)
        {
            list->head->prev = cell;
        }

        /* Mise a jour de la liste */
        list->head = cell;
        if(list->nbCells == 0)
        {
            list->tail = cell;
        }
        list->current = cell;
        list->nbCells++;

        error = LIST_NO_ERROR;
    }
    return error;
}

LIST_Error_e LIST_InsertLast(list_s* list, const void* data, size_t dataSize)
{
    list_cell_s* cell = LIST_AllocCell(data, dataSize);
    LIST_Error_e error = LIST_NO_ERROR;

    if(cell == NULL)
    {
        error = LIST_MEMORY_ERROR;
    }
    else
    {
        /* Mise a jour du chainage des elements */
        cell->next = NULL;
        cell->prev = list->tail;
        if(list->tail != NULL)
        {
            list->tail->next = cell;
        }

        /* Mise a jour de la liste */
        list->tail = cell;
        if(list->nbCells == 0)
        {
            list->head = cell;
        }
        list->current = cell;
        list->nbCells++;

        error = LIST_NO_ERROR;
    }
    return error;
}

LIST_Error_e LIST_InsertNext(list_s* list, const void* data, size_t dataSize)
{
    list_cell_s* cell = LIST_AllocCell(data, dataSize);
    LIST_Error_e error = LIST_NO_ERROR;

    if(cell == NULL)
    {
        error = LIST_MEMORY_ERROR;
    }
    else
    {
        /* Mise a jour du chainage des elements */
        if(list->current != NULL)
        {
            cell->next = list->current->next;
        }
        cell->prev = list->current;
        if(list->current != NULL)
        {
            list->current->next = cell;
        }
        if(cell->next != NULL)
        {
            cell->next->prev = cell;
        }

        /* Mise a jour de la liste */
        if(list->nbCells == 0)
        {
            list->head = cell;
            list->tail = cell;
        }
        if(cell->next == NULL)
        {
            list->tail = cell;
        }
        list->current = cell;
        list->nbCells++;

        error = LIST_NO_ERROR;
    }
    return error;
}

LIST_Error_e LIST_InsertPrev(list_s* list, const void* data, size_t dataSize)
{
    list_cell_s* cell = LIST_AllocCell(data, dataSize);
    LIST_Error_e error = LIST_NO_ERROR;

    if(cell == NULL)
    {
        error = LIST_MEMORY_ERROR;
    }
    else
    {
        /* Mise a jour du chainage des elements */
        cell->next = list->current;
        if(list->current != NULL)
        {
            cell->prev = list->current->prev;
        }
        if(list->current != NULL)
        {
            list->current->prev = cell;
        }
        if(cell->prev != NULL)
        {
            cell->prev->next = cell;
        }

        /* Mise a jour de la liste */
        if(list->nbCells == 0)
        {
            list->head = cell;
            list->tail = cell;
        }
        if(cell->prev == NULL)
        {
            list->head = cell;
        }
        list->current = cell;
        list->nbCells++;

        error = LIST_NO_ERROR;
    }
    return error;
}

LIST_Error_e LIST_SeekFirst(list_s* list)
{
    LIST_Error_e error;

    if(LIST_IsEmpty(list) == true)
    {
        error = LIST_EMPTY_LIST;
    }
    else
    {
        list->current = list->head;
        error = LIST_NO_ERROR;
    }
    return error;
}

LIST_Error_e LIST_SeekLast(list_s* list)
{
    LIST_Error_e error;

    if(LIST_IsEmpty(list) == true)
    {
        error = LIST_EMPTY_LIST;
    }
    else
    {
        list->current = list->tail;
        error = LIST_NO_ERROR;
    }
    return error;
}

LIST_Error_e LIST_SeekNext(list_s* list)
{
    LIST_Error_e error;

    if(LIST_IsEmpty(list) == true)
    {
        error = LIST_EMPTY_LIST;
    }
    else if(list->current->next == NULL)
    {
        error = LIST_CELL_NOT_FOUND;
    }
    else
    {
        list->current = list->current->next;
        error = LIST_NO_ERROR;
    }
    return error;
}

LIST_Error_e LIST_SeekPrev(list_s* list)
{
    LIST_Error_e error;

    if(LIST_IsEmpty(list) == true)
    {
        error = LIST_EMPTY_LIST;
    }
    else if(list->current->prev == NULL)
    {
        error = LIST_CELL_NOT_FOUND;
    }
    else
    {
        list->current = list->current->prev;
        error = LIST_NO_ERROR;
    }
    return error;
}

const void* LIST_ReadFirst(const list_s* list, LIST_Error_e* error)
{
    void* data = NULL;

    if(LIST_IsEmpty(list) == true)
    {
        *error = LIST_EMPTY_LIST;
    }
    else
    {
        data = list->head->data;
        *error = LIST_NO_ERROR;
    }
    return data;
}

const void* LIST_ReadLast(const list_s* list, LIST_Error_e* error)
{
    void* data = NULL;

    if(LIST_IsEmpty(list) == true)
    {
        *error = LIST_EMPTY_LIST;
    }
    else
    {
        data = list->tail->data;
        *error = LIST_NO_ERROR;
    }
    return data;
}

const void* LIST_ReadCurrent(const list_s* list, LIST_Error_e* error)
{
    void* data = NULL;

    if(LIST_IsEmpty(list) == true)
    {
        *error = LIST_EMPTY_LIST;
    }
    else
    {
        data = list->current->data;
        *error = LIST_NO_ERROR;
    }
    return data;
}

const void* LIST_ReadNext(const list_s* list, LIST_Error_e* error)
{
    void* data = NULL;

    if(LIST_IsEmpty(list) == true)
    {
        *error = LIST_EMPTY_LIST;
    }
    else if(list->current->next == NULL)
    {
        *error = LIST_CELL_NOT_FOUND;
    }
    else
    {
        data = list->current->next->data;
        *error = LIST_NO_ERROR;
    }
    return data;
}

const void* LIST_ReadPrev(const list_s* list, LIST_Error_e* error)
{
    void* data = NULL;

    if(LIST_IsEmpty(list) == true)
    {
        *error = LIST_EMPTY_LIST;
    }
    else if(list->current->prev == NULL)
    {
        *error = LIST_CELL_NOT_FOUND;
    }
    else
    {
        data = list->current->prev->data;
        *error = LIST_NO_ERROR;
    }
    return data;
}

const void* LIST_GetFirst(list_s* list, LIST_Error_e* error)
{
    void* data = NULL;

    if(LIST_IsEmpty(list) == true)
    {
        *error = LIST_EMPTY_LIST;
    }
    else
    {
        list_cell_s* tmpCell = LIST_DetachCell(list, list->head);

        if(tmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            *error = LIST_EMPTY_LIST;
        }
        else
        {
            data = tmpCell->data;
            free(tmpCell);

            *error = LIST_NO_ERROR;
        }
    }
    return data;
}

const void* LIST_GetLast(list_s* list, LIST_Error_e* error)
{
    void* data = NULL;

    if(LIST_IsEmpty(list) == true)
    {
        *error = LIST_EMPTY_LIST;
    }
    else
    {
        list_cell_s* tmpCell = LIST_DetachCell(list, list->tail);

        if(tmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            *error = LIST_EMPTY_LIST;
        }
        else
        {
            data = tmpCell->data;
            free(tmpCell);

            *error = LIST_NO_ERROR;
        }
    }
    return data;
}

const void* LIST_GetCurrent(list_s* list, LIST_Error_e* error)
{
    void* data = NULL;

    if(LIST_IsEmpty(list) == true)
    {
        *error = LIST_EMPTY_LIST;
    }
    else
    {
        list_cell_s* tmpCell = LIST_DetachCell(list, list->current);

        if(tmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            *error = LIST_EMPTY_LIST;
        }
        else
        {
            data = tmpCell->data;
            free(tmpCell);

            *error = LIST_NO_ERROR;
        }
    }
    return data;
}

const void* LIST_GetNext(list_s* list, LIST_Error_e* error)
{
    void* data = NULL;

    if(LIST_IsEmpty(list) == true)
    {
        *error = LIST_EMPTY_LIST;
    }
    else if(LIST_IsTail(list) == true)
    {
        *error = LIST_CELL_NOT_FOUND;
    }
    else
    {
        list_cell_s* tmpCell = LIST_DetachCell(list, list->current->next);

        if(tmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            *error = LIST_CELL_NOT_FOUND;
        }
        else
        {
            data = tmpCell->data;
            free(tmpCell);

            *error = LIST_NO_ERROR;
        }
    }
    return data;
}

const void* LIST_GetPrev(list_s* list, LIST_Error_e* error)
{
    void* data = NULL;

    if(LIST_IsEmpty(list) == true)
    {
        *error = LIST_EMPTY_LIST;
    }
    else if(LIST_IsHead(list) == true)
    {
        *error = LIST_CELL_NOT_FOUND;
    }
    else
    {
        list_cell_s* tmpCell = LIST_DetachCell(list, list->current->prev);

        if(tmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            *error = LIST_CELL_NOT_FOUND;
        }
        else
        {
            data = tmpCell->data;
            free(tmpCell);

            *error = LIST_NO_ERROR;
        }
    }
    return data;
}

LIST_Error_e LIST_RemoveFirst(list_s* list)
{
    LIST_Error_e error;

    if(LIST_IsEmpty(list) == true)
    {
        error = LIST_EMPTY_LIST;
    }
    else
    {
        list_cell_s* tmpCell = LIST_DetachCell(list, list->head);

        if(tmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            error = LIST_EMPTY_LIST;
        }
        else
        {
            if(tmpCell->dataSize != 0)
            {
                free(tmpCell->data);
            }
            free(tmpCell);

            error = LIST_NO_ERROR;
        }
    }
    return error;
}

LIST_Error_e LIST_RemoveLast(list_s* list)
{
    LIST_Error_e error;

    if(LIST_IsEmpty(list) == true)
    {
        error = LIST_EMPTY_LIST;
    }
    else
    {
        list_cell_s* tmpCell = LIST_DetachCell(list, list->tail);

        if(tmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            error = LIST_EMPTY_LIST;
        }
        else
        {
            if(tmpCell->dataSize != 0)
            {
                free(tmpCell->data);
            }
            free(tmpCell);

            error = LIST_NO_ERROR;
        }
    }
    return error;
}

LIST_Error_e LIST_RemoveCurrent(list_s* list)
{
    LIST_Error_e error;

    if(LIST_IsEmpty(list) == true)
    {
        error = LIST_EMPTY_LIST;
    }
    else
    {
        list_cell_s* tmpCell = LIST_DetachCell(list, list->current);

        if(tmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            error = LIST_EMPTY_LIST;
        }
        else
        {
            if(tmpCell->dataSize != 0)
            {
                free(tmpCell->data);
            }
            free(tmpCell);

            error = LIST_NO_ERROR;
        }
    }
    return error;
}

LIST_Error_e LIST_RemoveNext(list_s* list)
{
    LIST_Error_e error;

    if(LIST_IsEmpty(list) == true)
    {
        error = LIST_EMPTY_LIST;
    }
    else if(LIST_IsTail(list) == true)
    {
        error = LIST_CELL_NOT_FOUND;
    }
    else
    {
        list_cell_s* tmpCell = LIST_DetachCell(list, list->current->next);

        if(tmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            error = LIST_CELL_NOT_FOUND;
        }
        else
        {
            if(tmpCell->dataSize != 0)
            {
                free(tmpCell->data);
            }
            free(tmpCell);

            error = LIST_NO_ERROR;
        }
    }
    return error;
}

LIST_Error_e LIST_RemovePrev(list_s* list)
{
    LIST_Error_e error;

    if(LIST_IsEmpty(list) == true)
    {
        error = LIST_EMPTY_LIST;
    }
    else if(LIST_IsHead(list) == true)
    {
        error = LIST_CELL_NOT_FOUND;
    }
    else
    {
        list_cell_s* tmpCell = LIST_DetachCell(list, list->current->prev);

        if(tmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            error = LIST_CELL_NOT_FOUND;
        }
        else
        {
            if(tmpCell->dataSize != 0)
            {
                free(tmpCell->data);
            }
            free(tmpCell);

            error = LIST_NO_ERROR;
        }
    }
    return error;
}

list_s* LIST_Clone(const list_s* list, LIST_Error_e* error)
{
    list_cell_s* currentCell = NULL;
    /* Creation de la liste clone */
    list_s* destList = LIST_Create(list->compar, error);

    if(*error == LIST_NO_ERROR)
    {
        /* Insertion iterative de tous les elements de la liste originale. */
        for(currentCell = list->head; currentCell != NULL && *error == LIST_NO_ERROR; currentCell = currentCell->next)
        {
            *error = LIST_InsertNext(destList, currentCell->data, currentCell->dataSize);
        }

        if(*error == LIST_MEMORY_ERROR)
        {
            /* Une erreur s'est produite lors de l'insertion, on efface la liste partiellement dupliquee */
            LIST_Destroy(destList);
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

LIST_Error_e LIST_SearchData(list_s* list, const void* data)
{
    /* LIST_SearchData() n'est qu'une encapsulation de LIST_SearchDataFct */
    return LIST_SearchDataFct(list, data, NULL);
}

LIST_Error_e LIST_SearchDataFct(list_s* list, const void* data, int (*compar)(const void *, const void *))
{
    LIST_Error_e error;
    list_cell_s* currentCell;
    int (*usedCompar)(const void *, const void *);

    /* On positionne la fonction de recherche a utiliser */
    if(compar != NULL)
    {
        usedCompar = compar;
    }
    else
    {
        usedCompar = list->compar;
    }

    if(LIST_IsEmpty(list) == true)
    {
        error = LIST_EMPTY_LIST;
    }
    else if(usedCompar == NULL)
    {
        error = LIST_NO_COMP_FONCTION;
    }
    else
    {
        error = LIST_CELL_NOT_FOUND;

        /* Parcours des elements de la liste jusqu'a trouver l'element recherche ou a atteindre la fin de la liste */
        for(currentCell = list->current; currentCell != NULL; currentCell = currentCell->next)
        {
            /* L'element recherche est trouve */
            if(usedCompar(data, currentCell->data) == 0)
            {
                list->current = currentCell;
                error = LIST_NO_ERROR;

                /* Et on arrete la recherche */
                break;
            }
        }
    }
    return error;
}

LIST_Error_e LIST_SearchDataRev(list_s* list, const void* data)
{
    /* LIST_SearchDataRev() n'est qu'une encapsulation de LIST_SearchDataRevFct */
    return LIST_SearchDataRevFct(list, data, NULL);
}

LIST_Error_e LIST_SearchDataRevFct(list_s* list, const void* data, int (*compar)(const void *, const void *))
{
    LIST_Error_e error;
    list_cell_s* currentCell;
    int (*usedCompar)(const void *, const void *);

    /* On positionne la fonction de recherche a utiliser */
    if(compar != NULL)
    {
        usedCompar = compar;
    }
    else
    {
        usedCompar = list->compar;
    }

    if(LIST_IsEmpty(list) == true)
    {
        error = LIST_EMPTY_LIST;
    }
    else if(usedCompar == NULL)
    {
        error = LIST_NO_COMP_FONCTION;
    }
    else
    {
        error = LIST_CELL_NOT_FOUND;

        /* Parcours des elements de la liste jusqu'a trouver l'element recherche ou a atteindre la tete de la liste */
        for(currentCell = list->current; currentCell != NULL; currentCell = currentCell->prev)
        {
            if(usedCompar(data, currentCell->data) == 0)
            {
                /* L'element recherche est trouve */
                list->current = currentCell;
                error = LIST_NO_ERROR;

                /* Et on arrete la recherche */
                break;
            }
        }
    }
    return error;
}

LIST_Error_e LIST_RemoveData(list_s* list, const void* data)
{
    /* LIST_RemoveData() n'est qu'une encapsulation de LIST_RemoveData() */
    return LIST_RemoveDataFct(list, data, NULL);
}

LIST_Error_e LIST_RemoveDataFct(list_s* list, const void* data, int (*compar)(const void *, const void *))
{
    LIST_Error_e error;
    list_cell_s* currentCell = list->current;
    int (*usedCompar)(const void *, const void *);

    /* On positionne la fonction de recherche a utiliser */
    if(compar != NULL)
    {
        usedCompar = compar;
    }
    else
    {
        usedCompar = list->compar;
    }

    if(LIST_IsEmpty(list) == true)
    {
        error = LIST_EMPTY_LIST;
    }
    else if(usedCompar == NULL)
    {
        error = LIST_NO_COMP_FONCTION;
    }
    else
    {
        /* Recherche de l'element a supprime */
        error = LIST_SearchDataFct(list, data, usedCompar);

        /* L'element a ete trouve */
        if(error == LIST_NO_ERROR)
        {
            /* L'element a ete trouve, on le supprime */
            if(currentCell == list->current)
            {
                if(currentCell->next != NULL)
                {
                    currentCell = currentCell->next;
                }
                else
                {
                    currentCell = currentCell->prev;
                }
            }
            error = LIST_RemoveCurrent(list);

            /* Et on restaure l'element courant */
            list->current = currentCell;
        }
    }
    return error;
}

LIST_Error_e LIST_RemoveDataRev(list_s* list, const void* data)
{
    /* LIST_RemoveData() n'est qu'une encapsulation de LIST_RemoveData() */
    return LIST_RemoveDataRevFct(list, data, NULL);
}

LIST_Error_e LIST_RemoveDataRevFct(list_s* list, const void* data, int (*compar)(const void *, const void *))
{
    LIST_Error_e error;
    list_cell_s* currentCell = list->current;
    int (*usedCompar)(const void *, const void *);

    /* On positionne la fonction de recherche a utiliser */
    if(compar != NULL)
    {
        usedCompar = compar;
    }
    else
    {
        usedCompar = list->compar;
    }

    if(LIST_IsEmpty(list) == true)
    {
        error = LIST_EMPTY_LIST;
    }
    else if(usedCompar == NULL)
    {
        error = LIST_NO_COMP_FONCTION;
    }
    else
    {
        /* Recherche de l'element a supprime */
        error = LIST_SearchDataRevFct(list, data, usedCompar);

        /* L'element a ete trouve */
        if(error == LIST_NO_ERROR)
        {
            /* L'element a ete trouve, on le supprime */
            if(currentCell == list->current)
            {
                if(currentCell->next != NULL)
                {
                    currentCell = currentCell->next;
                }
                else
                {
                    currentCell = currentCell->prev;
                }
            }
            error = LIST_RemoveCurrent(list);

            /* Et on restaure l'element courant */
            list->current = currentCell;
        }
    }
    return error;
}

LIST_Error_e LIST_RemoveAllData(list_s* list, const void* data)
{
    /* LIST_RemoveAllData() n'est qu'une encapsulation de LIST_RemoveAllDataFct() */
    return LIST_RemoveAllDataFct(list, data, NULL);
}

LIST_Error_e LIST_RemoveAllDataFct(list_s* list, const void* data, int (*compar)(const void *, const void *))
{
    LIST_Error_e error = LIST_NO_ERROR;

    /* On efface iterativement toutes les cellules correspondant au critere situee apres l'element courant */
    while(error == LIST_NO_ERROR)
    {
        error = LIST_RemoveDataFct(list, data, compar);
    }

    /* S'il n'y a plus de cellules correspodantes, la suppression c'est bien passe */
    if(error == LIST_CELL_NOT_FOUND)
    {
        error = LIST_NO_ERROR;
    }

    /* puis on efface iterativement toutes les cellules correspondant au critere situee avant l'element courant */
    while(error == LIST_NO_ERROR)
    {
        error = LIST_RemoveDataRevFct(list, data, compar);
    }

    /* S'il n'y a plus de cellules correspodantes, la suppression c'est bien passe */
    if(error == LIST_CELL_NOT_FOUND)
    {
        error = LIST_NO_ERROR;
    }
    return error;
}
