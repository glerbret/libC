/**
 * @author Gregory Lerbret
 * @brief Gestion de listes
 * @date 24/09/2006
 * @version 1.0.0
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
    struct list_cell*   pNext;
    struct list_cell*   pPrev;
    void*               pData;
    size_t              szDataSize;
} list_cell_s;

struct list
{
    list_cell_s*    pHead;
    list_cell_s*    pTail;
    list_cell_s*    pCurrent;
    size_t          szNbCells;
    int (*mCompar)(const void *, const void *);
};

static list_cell_s* LIST_AllocCell(const void* pData, size_t szDataSize)
{
    list_cell_s* pCell = NULL;

    if(pData == NULL || szDataSize == 0)
    {
        /* Il n'y a pas d'element a ajouter, on arrete ici et on retourne NULL */
        pCell = NULL;
    }
    else
    {
        pCell = malloc(sizeof * pCell);

        if(pCell == NULL)
        {
            /* Echec de l'allocation, on retourne NULL */
            /* NOP */
        }
        else
        {
            /* Intialisation de la cellule */
            pCell->pNext = NULL;
            pCell->pPrev = NULL;

            pCell->pData = malloc(szDataSize);
            if(pCell->pData == NULL)
            {
                /* Echec de l'allocation, on detruit la cellule et on retourne NULL */
                free(pCell), pCell = NULL;
            }
            else
            {
                memcpy(pCell->pData, pData, szDataSize);
                pCell->szDataSize = szDataSize;
            }
        }
    }

    return pCell;
}

static list_cell_s* LIST_DetachCell(list_s* pList, list_cell_s* pCellToDelete)
{
    list_cell_s* pCell = NULL;

    if(pCellToDelete == NULL)
    {
        /* Il n'y a pas de cellule a retirer, on arrete ici et on retourne NULL */
        pCell = NULL;
    }
    else
    {
        /* On detache la cellule */
        pCell = pCellToDelete;

        if(pCell->pPrev == NULL)
        {
            pList->pHead = pCell->pNext;
        }
        else
        {
            pCell->pPrev->pNext = pCell->pNext;
        }

        if(pCell->pNext == NULL)
        {
            pList->pTail = pCell->pPrev;
        }
        else
        {
            pCell->pNext->pPrev = pCell->pPrev;
        }

        pList->szNbCells--;

        if(pList->szNbCells == 0)
        {
            /* La liste est maintenant vide */
            pList->pCurrent = NULL;
        }
        else if(pCell == pList->pCurrent)
        {
            /* On vient de supprimmer la cellule courante, la cellule suivante (ou precedente si c'etait la derniere)
               devient la nouvelle cellule courante */
            if(pCell->pNext != NULL)
            {
                pList->pCurrent = pCell->pNext;
            }
            else
            {
                pList->pCurrent = pCell->pPrev;
            }
        }
    }
    return pCell;
}

const char* LIST_Identifier(void)
{
    return LIST_ID;
}

int LIST_Version(void)
{
    return LIST_VERS_MAJ * 10000 + LIST_VERS_MIN * 100 + LIST_VERS_BRCH;
}

list_s* LIST_Create(int (*compar)(const void *, const void *), LIST_Error_e* eError)
{
    list_s* pList = malloc(sizeof * pList);

    if(pList == NULL)
    {
        /* La liste n'a pas pu etre creer */
        *eError = LIST_MEMORY_ERROR;
    }
    else
    {
        /* Initialisation de la liste */
        pList->pHead = NULL;
        pList->pTail = NULL;
        pList->pCurrent = NULL;
        pList->szNbCells = 0;
        pList->mCompar = compar;
        *eError = LIST_NO_ERROR;
    }
    return pList;
}

void LIST_Destroy(list_s* pList)
{
    /* On se positionne sur le premier element ... */
    if(LIST_SeekFirst(pList) == LIST_NO_ERROR)
    {
        /* ... et on retire iterative toutes les cellules de la liste */
        while(LIST_RemoveFirst(pList) != LIST_EMPTY_LIST)
        {
            /* NOP */
        }
    }

    /* Puis on detruit la liste*/
    free(pList), pList = NULL;
}

void LIST_SetCmp(list_s* pList, int (*compar)(const void *, const void *))
{
    pList->mCompar = compar;
}

bool LIST_IsEmpty(const list_s* pList)
{
    return pList->pHead == NULL ? true : false;
}

size_t LIST_Size(const list_s* pList)
{
    return pList->szNbCells;
}

bool LIST_IsHead(const list_s* pList)
{
    bool bIsHead = false;

    if(LIST_IsEmpty(pList) == true)
    {
        bIsHead = false;
    }
    else if(pList->pCurrent == pList->pHead)
    {
        bIsHead = true;
    }
    else
    {
        bIsHead = false;
    }
    return bIsHead;
}

bool LIST_IsTail(const list_s* pList)
{
    bool bIsTail = false;

    if(LIST_IsEmpty(pList) == true)
    {
        bIsTail = false;
    }
    else if(pList->pCurrent == pList->pTail)
    {
        bIsTail = true;
    }
    else
    {
        bIsTail = false;
    }
    return bIsTail;
}

LIST_Error_e LIST_InsertFirst(list_s* pList, const void* pData, size_t szDataSize)
{
    list_cell_s* pCell = LIST_AllocCell(pData, szDataSize);
    LIST_Error_e eError = LIST_NO_ERROR;

    if(pCell == NULL)
    {
        eError = LIST_MEMORY_ERROR;
    }
    else
    {
        /* Mise a jour du chainage des elements */
        pCell->pNext = pList->pHead;
        pCell->pPrev = NULL;
        if(pList->pHead != NULL)
        {
            pList->pHead->pPrev = pCell;
        }

        /* Mise a jour de la liste */
        pList->pHead = pCell;
        if(pList->szNbCells == 0)
        {
            pList->pTail = pCell;
        }
        pList->pCurrent = pCell;
        pList->szNbCells++;

        eError = LIST_NO_ERROR;
    }
    return eError;
}

LIST_Error_e LIST_InsertLast(list_s* pList, const void* pData, size_t szDataSize)
{
    list_cell_s* pCell = LIST_AllocCell(pData, szDataSize);
    LIST_Error_e eError = LIST_NO_ERROR;

    if(pCell == NULL)
    {
        eError = LIST_MEMORY_ERROR;
    }
    else
    {
        /* Mise a jour du chainage des elements */
        pCell->pNext = NULL;
        pCell->pPrev = pList->pTail;
        if(pList->pTail != NULL)
        {
            pList->pTail->pNext = pCell;
        }

        /* Mise a jour de la liste */
        pList->pTail = pCell;
        if(pList->szNbCells == 0)
        {
            pList->pHead = pCell;
        }
        pList->pCurrent = pCell;
        pList->szNbCells++;

        eError = LIST_NO_ERROR;
    }
    return eError;
}

LIST_Error_e LIST_InsertNext(list_s* pList, const void* pData, size_t szDataSize)
{
    list_cell_s* pCell = LIST_AllocCell(pData, szDataSize);
    LIST_Error_e eError = LIST_NO_ERROR;

    if(pCell == NULL)
    {
        eError = LIST_MEMORY_ERROR;
    }
    else
    {
        /* Mise a jour du chainage des elements */
        if(pList->pCurrent != NULL)
        {
            pCell->pNext = pList->pCurrent->pNext;
        }
        pCell->pPrev = pList->pCurrent;
        if(pList->pCurrent != NULL)
        {
            pList->pCurrent->pNext = pCell;
        }
        if(pCell->pNext != NULL)
        {
            pCell->pNext->pPrev = pCell;
        }

        /* Mise a jour de la liste */
        if(pList->szNbCells == 0)
        {
            pList->pHead = pCell;
            pList->pTail = pCell;
        }
        if(pCell->pNext == NULL)
        {
            pList->pTail = pCell;
        }
        pList->pCurrent = pCell;
        pList->szNbCells++;

        eError = LIST_NO_ERROR;
    }
    return eError;
}

LIST_Error_e LIST_InsertPrev(list_s* pList, const void* pData, size_t szDataSize)
{
    list_cell_s* pCell = LIST_AllocCell(pData, szDataSize);
    LIST_Error_e eError = LIST_NO_ERROR;

    if(pCell == NULL)
    {
        eError = LIST_MEMORY_ERROR;
    }
    else
    {
        /* Mise a jour du chainage des elements */
        pCell->pNext = pList->pCurrent;
        if(pList->pCurrent != NULL)
        {
            pCell->pPrev = pList->pCurrent->pPrev;
        }
        if(pList->pCurrent != NULL)
        {
            pList->pCurrent->pPrev = pCell;
        }
        if(pCell->pPrev != NULL)
        {
            pCell->pPrev->pNext = pCell;
        }

        /* Mise a jour de la liste */
        if(pList->szNbCells == 0)
        {
            pList->pHead = pCell;
            pList->pTail = pCell;
        }
        if(pCell->pPrev == NULL)
        {
            pList->pHead = pCell;
        }
        pList->pCurrent = pCell;
        pList->szNbCells++;

        eError = LIST_NO_ERROR;
    }
    return eError;
}

LIST_Error_e LIST_SeekFirst(list_s* pList)
{
    LIST_Error_e eError;

    if(LIST_IsEmpty(pList) == true)
    {
        eError = LIST_EMPTY_LIST;
    }
    else
    {
        pList->pCurrent = pList->pHead;
        eError = LIST_NO_ERROR;
    }
    return eError;
}

LIST_Error_e LIST_SeekLast(list_s* pList)
{
    LIST_Error_e eError;

    if(LIST_IsEmpty(pList) == true)
    {
        eError = LIST_EMPTY_LIST;
    }
    else
    {
        pList->pCurrent = pList->pTail;
        eError = LIST_NO_ERROR;
    }
    return eError;
}

LIST_Error_e LIST_SeekNext(list_s* pList)
{
    LIST_Error_e eError;

    if(LIST_IsEmpty(pList) == true)
    {
        eError = LIST_EMPTY_LIST;
    }
    else if(pList->pCurrent->pNext == NULL)
    {
        eError = LIST_CELL_NOT_FOUND;
    }
    else
    {
        pList->pCurrent = pList->pCurrent->pNext;
        eError = LIST_NO_ERROR;
    }
    return eError;
}

LIST_Error_e LIST_SeekPrev(list_s* pList)
{
    LIST_Error_e eError;

    if(LIST_IsEmpty(pList) == true)
    {
        eError = LIST_EMPTY_LIST;
    }
    else if(pList->pCurrent->pPrev == NULL)
    {
        eError = LIST_CELL_NOT_FOUND;
    }
    else
    {
        pList->pCurrent = pList->pCurrent->pPrev;
        eError = LIST_NO_ERROR;
    }
    return eError;
}

const void* LIST_ReadFirst(const list_s* pList, LIST_Error_e* eError)
{
    void* pData = NULL;

    if(LIST_IsEmpty(pList) == true)
    {
        *eError = LIST_EMPTY_LIST;
    }
    else
    {
        pData = pList->pHead->pData;
        *eError = LIST_NO_ERROR;
    }
    return pData;
}

const void* LIST_ReadLast(const list_s* pList, LIST_Error_e* eError)
{
    void* pData = NULL;

    if(LIST_IsEmpty(pList) == true)
    {
        *eError = LIST_EMPTY_LIST;
    }
    else
    {
        pData = pList->pTail->pData;
        *eError = LIST_NO_ERROR;
    }
    return pData;
}

const void* LIST_ReadCurrent(const list_s* pList, LIST_Error_e* eError)
{
    void* pData = NULL;

    if(LIST_IsEmpty(pList) == true)
    {
        *eError = LIST_EMPTY_LIST;
    }
    else
    {
        pData = pList->pCurrent->pData;
        *eError = LIST_NO_ERROR;
    }
    return pData;
}

const void* LIST_ReadNext(const list_s* pList, LIST_Error_e* eError)
{
    void* pData = NULL;

    if(LIST_IsEmpty(pList) == true)
    {
        *eError = LIST_EMPTY_LIST;
    }
    else if(pList->pCurrent->pNext == NULL)
    {
        *eError = LIST_CELL_NOT_FOUND;
    }
    else
    {
        pData = pList->pCurrent->pNext->pData;
        *eError = LIST_NO_ERROR;
    }
    return pData;
}

const void* LIST_ReadPrev(const list_s* pList, LIST_Error_e* eError)
{
    void* pData = NULL;

    if(LIST_IsEmpty(pList) == true)
    {
        *eError = LIST_EMPTY_LIST;
    }
    else if(pList->pCurrent->pPrev == NULL)
    {
        *eError = LIST_CELL_NOT_FOUND;
    }
    else
    {
        pData = pList->pCurrent->pPrev->pData;
        *eError = LIST_NO_ERROR;
    }
    return pData;
}

const void* LIST_GetFirst(list_s* pList, LIST_Error_e* eError)
{
    void* pData = NULL;
    list_cell_s* pTmpCell = NULL;

    if(LIST_IsEmpty(pList) == true)
    {
        *eError = LIST_EMPTY_LIST;
    }
    else
    {
        pTmpCell = LIST_DetachCell(pList, pList->pHead);

        if(pTmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            *eError = LIST_EMPTY_LIST;
        }
        else
        {
            pData = pTmpCell->pData;
            free(pTmpCell);

            *eError = LIST_NO_ERROR;
        }
    }
    return pData;
}

const void* LIST_GetLast(list_s* pList, LIST_Error_e* eError)
{
    void* pData = NULL;
    list_cell_s* pTmpCell;

    if(LIST_IsEmpty(pList) == true)
    {
        *eError = LIST_EMPTY_LIST;
    }
    else
    {
        pTmpCell = LIST_DetachCell(pList, pList->pTail);

        if(pTmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            *eError = LIST_EMPTY_LIST;
        }
        else
        {
            pData = pTmpCell->pData;
            free(pTmpCell);

            *eError = LIST_NO_ERROR;
        }
    }
    return pData;
}

const void* LIST_GetCurrent(list_s* pList, LIST_Error_e* eError)
{
    void* pData = NULL;
    list_cell_s* pTmpCell = NULL;

    if(LIST_IsEmpty(pList) == true)
    {
        *eError = LIST_EMPTY_LIST;
    }
    else
    {
        pTmpCell = LIST_DetachCell(pList, pList->pCurrent);

        if(pTmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            *eError = LIST_EMPTY_LIST;
        }
        else
        {
            pData = pTmpCell->pData;
            free(pTmpCell);

            *eError = LIST_NO_ERROR;
        }
    }
    return pData;
}

const void* LIST_GetNext(list_s* pList, LIST_Error_e* eError)
{
    void* pData = NULL;
    list_cell_s* pTmpCell;

    if(LIST_IsEmpty(pList) == true)
    {
        *eError = LIST_EMPTY_LIST;
    }
    else if(LIST_IsTail(pList) == true)
    {
        *eError = LIST_CELL_NOT_FOUND;
    }
    else
    {
        pTmpCell = LIST_DetachCell(pList, pList->pCurrent->pNext);

        if(pTmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            *eError = LIST_CELL_NOT_FOUND;
        }
        else
        {
            pData = pTmpCell->pData;
            free(pTmpCell);

            *eError = LIST_NO_ERROR;
        }
    }
    return pData;
}

const void* LIST_GetPrev(list_s* pList, LIST_Error_e* eError)
{
    void* pData = NULL;
    list_cell_s* pTmpCell;

    if(LIST_IsEmpty(pList) == true)
    {
        *eError = LIST_EMPTY_LIST;
    }
    else if(LIST_IsHead(pList) == true)
    {
        *eError = LIST_CELL_NOT_FOUND;
    }
    else
    {
        pTmpCell = LIST_DetachCell(pList, pList->pCurrent->pPrev);

        if(pTmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            *eError = LIST_CELL_NOT_FOUND;
        }
        else
        {
            pData = pTmpCell->pData;
            free(pTmpCell);

            *eError = LIST_NO_ERROR;
        }
    }
    return pData;
}

LIST_Error_e LIST_RemoveFirst(list_s* pList)
{
    LIST_Error_e eError;
    list_cell_s* pTmpCell;

    if(LIST_IsEmpty(pList) == true)
    {
        eError = LIST_EMPTY_LIST;
    }
    else
    {
        pTmpCell = LIST_DetachCell(pList, pList->pHead);

        if(pTmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            eError = LIST_EMPTY_LIST;
        }
        else
        {
            if(pTmpCell->szDataSize != 0)
            {
                free(pTmpCell->pData);
            }
            free(pTmpCell);

            eError = LIST_NO_ERROR;
        }
    }
    return eError;
}

LIST_Error_e LIST_RemoveLast(list_s* pList)
{
    LIST_Error_e eError;
    list_cell_s* pTmpCell;

    if(LIST_IsEmpty(pList) == true)
    {
        eError = LIST_EMPTY_LIST;
    }
    else
    {
        pTmpCell = LIST_DetachCell(pList, pList->pTail);

        if(pTmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            eError = LIST_EMPTY_LIST;
        }
        else
        {
            if(pTmpCell->szDataSize != 0)
            {
                free(pTmpCell->pData);
            }
            free(pTmpCell);

            eError = LIST_NO_ERROR;
        }
    }
    return eError;
}

LIST_Error_e LIST_RemoveCurrent(list_s* pList)
{
    LIST_Error_e eError;
    list_cell_s* pTmpCell;

    if(LIST_IsEmpty(pList) == true)
    {
        eError = LIST_EMPTY_LIST;
    }
    else
    {
        pTmpCell = LIST_DetachCell(pList, pList->pCurrent);

        if(pTmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            eError = LIST_EMPTY_LIST;
        }
        else
        {
            if(pTmpCell->szDataSize != 0)
            {
                free(pTmpCell->pData);
            }
            free(pTmpCell);

            eError = LIST_NO_ERROR;
        }
    }
    return eError;
}

LIST_Error_e LIST_RemoveNext(list_s* pList)
{
    LIST_Error_e eError;
    list_cell_s* pTmpCell;

    if(LIST_IsEmpty(pList) == true)
    {
        eError = LIST_EMPTY_LIST;
    }
    else if(LIST_IsTail(pList) == true)
    {
        eError = LIST_CELL_NOT_FOUND;
    }
    else
    {
        pTmpCell = LIST_DetachCell(pList, pList->pCurrent->pNext);

        if(pTmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            eError = LIST_CELL_NOT_FOUND;
        }
        else
        {
            if(pTmpCell->szDataSize != 0)
            {
                free(pTmpCell->pData);
            }
            free(pTmpCell);

            eError = LIST_NO_ERROR;
        }
    }
    return eError;
}

LIST_Error_e LIST_RemovePrev(list_s* pList)
{
    LIST_Error_e eError;
    list_cell_s* pTmpCell;

    if(LIST_IsEmpty(pList) == true)
    {
        eError = LIST_EMPTY_LIST;
    }
    else if(LIST_IsHead(pList) == true)
    {
        eError = LIST_CELL_NOT_FOUND;
    }
    else
    {
        pTmpCell = LIST_DetachCell(pList, pList->pCurrent->pPrev);

        if(pTmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            eError = LIST_CELL_NOT_FOUND;
        }
        else
        {
            if(pTmpCell->szDataSize != 0)
            {
                free(pTmpCell->pData);
            }
            free(pTmpCell);

            eError = LIST_NO_ERROR;
        }
    }
    return eError;
}

list_s* LIST_Clone(const list_s* pList, LIST_Error_e* eError)
{
    list_cell_s* pCurrentCell = NULL;
    /* Creation de la liste clone */
    list_s* sDestList = LIST_Create(pList->mCompar, eError);

    if(*eError == LIST_NO_ERROR)
    {
        /* Insertion iterative de tous les elements de la liste originale. */
        for(pCurrentCell = pList->pHead; pCurrentCell != NULL && *eError == LIST_NO_ERROR; pCurrentCell = pCurrentCell->pNext)
        {
            *eError = LIST_InsertNext(sDestList, pCurrentCell->pData, pCurrentCell->szDataSize);
        }

        if(*eError == LIST_MEMORY_ERROR)
        {
            /* Une erreur s'est produite lors de l'insertion, on efface la liste partiellement dupliquee */
            LIST_Destroy(sDestList);
            sDestList = NULL;
        }
        else
        {
            /* Tout s'est bien passe, on initilaise l'element courant */
            sDestList->pCurrent = sDestList->pHead;
        }
    }
    return sDestList;
}

LIST_Error_e LIST_SearchData(list_s* pList, const void* pData)
{
    /* LIST_SearchData() n'est qu'une encapsulation de LIST_SearchDataFct */
    return LIST_SearchDataFct(pList, pData, NULL);
}

LIST_Error_e LIST_SearchDataFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *))
{
    LIST_Error_e eError;
    list_cell_s* pCurrentCell;
    int (*UsedCompar)(const void *, const void *);

    /* On positionne la fonction de recherche a utiliser */
    if(compar != NULL)
    {
        UsedCompar = compar;
    }
    else
    {
        UsedCompar = pList->mCompar;
    }

    if(LIST_IsEmpty(pList) == true)
    {
        eError = LIST_EMPTY_LIST;
    }
    else if(UsedCompar == NULL)
    {
        eError = LIST_NO_COMP_FONCTION;
    }
    else
    {
        eError = LIST_CELL_NOT_FOUND;

        /* Parcours des elements de la liste jusqu'a trouver l'element recherche ou a atteindre la fin de la liste */
        for(pCurrentCell = pList->pCurrent; pCurrentCell != NULL; pCurrentCell = pCurrentCell->pNext)
        {
            /* L'element recherche est trouve */
            if(UsedCompar(pData, pCurrentCell->pData) == 0)
            {
                pList->pCurrent = pCurrentCell;
                eError = LIST_NO_ERROR;

                /* Et on arrete la recherche */
                break;
            }
        }
    }
    return eError;
}

LIST_Error_e LIST_SearchDataRev(list_s* pList, const void* pData)
{
    /* LIST_SearchDataRev() n'est qu'une encapsulation de LIST_SearchDataRevFct */
    return LIST_SearchDataRevFct(pList, pData, NULL);
}

LIST_Error_e LIST_SearchDataRevFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *))
{
    LIST_Error_e eError;
    list_cell_s* pCurrentCell;
    int (*UsedCompar)(const void *, const void *);

    /* On positionne la fonction de recherche a utiliser */
    if(compar != NULL)
    {
        UsedCompar = compar;
    }
    else
    {
        UsedCompar = pList->mCompar;
    }

    if(LIST_IsEmpty(pList) == true)
    {
        eError = LIST_EMPTY_LIST;
    }
    else if(UsedCompar == NULL)
    {
        eError = LIST_NO_COMP_FONCTION;
    }
    else
    {
        eError = LIST_CELL_NOT_FOUND;

        /* Parcours des elements de la liste jusqu'a trouver l'element recherche ou a atteindre la tete de la liste */
        for(pCurrentCell = pList->pCurrent; pCurrentCell != NULL; pCurrentCell = pCurrentCell->pPrev)
        {
            if(UsedCompar(pData, pCurrentCell->pData) == 0)
            {
                /* L'element recherche est trouve */
                pList->pCurrent = pCurrentCell;
                eError = LIST_NO_ERROR;

                /* Et on arrete la recherche */
                break;
            }
        }
    }
    return eError;
}

LIST_Error_e LIST_RemoveData(list_s* pList, const void* pData)
{
    /* LIST_RemoveData() n'est qu'une encapsulation de LIST_RemoveData() */
    return LIST_RemoveDataFct(pList, pData, NULL);
}

LIST_Error_e LIST_RemoveDataFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *))
{
    LIST_Error_e eError;
    list_cell_s* pCurrentCell = pList->pCurrent;
    int (*UsedCompar)(const void *, const void *);

    /* On positionne la fonction de recherche a utiliser */
    if(compar != NULL)
    {
        UsedCompar = compar;
    }
    else
    {
        UsedCompar = pList->mCompar;
    }

    if(LIST_IsEmpty(pList) == true)
    {
        eError = LIST_EMPTY_LIST;
    }
    else if(UsedCompar == NULL)
    {
        eError = LIST_NO_COMP_FONCTION;
    }
    else
    {
        /* Recherche de l'element a supprime */
        eError = LIST_SearchDataFct(pList, pData, UsedCompar);

        /* L'element a ete trouve */
        if(eError == LIST_NO_ERROR)
        {
            /* L'element a ete trouve, on le supprime */
            if(pCurrentCell == pList->pCurrent)
            {
                if(pCurrentCell->pNext != NULL)
                {
                    pCurrentCell = pCurrentCell->pNext;
                }
                else
                {
                    pCurrentCell = pCurrentCell->pPrev;
                }
            }
            eError = LIST_RemoveCurrent(pList);

            /* Et on restaure l'element courant */
            pList->pCurrent = pCurrentCell;
        }
    }
    return eError;
}

LIST_Error_e LIST_RemoveDataRev(list_s* pList, const void* pData)
{
    /* LIST_RemoveData() n'est qu'une encapsulation de LIST_RemoveData() */
    return LIST_RemoveDataRevFct(pList, pData, NULL);
}

LIST_Error_e LIST_RemoveDataRevFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *))
{
    LIST_Error_e eError;
    list_cell_s* pCurrentCell = pList->pCurrent;
    int (*UsedCompar)(const void *, const void *);

    /* On positionne la fonction de recherche a utiliser */
    if(compar != NULL)
    {
        UsedCompar = compar;
    }
    else
    {
        UsedCompar = pList->mCompar;
    }

    if(LIST_IsEmpty(pList) == true)
    {
        eError = LIST_EMPTY_LIST;
    }
    else if(UsedCompar == NULL)
    {
        eError = LIST_NO_COMP_FONCTION;
    }
    else
    {
        /* Recherche de l'element a supprime */
        eError = LIST_SearchDataRevFct(pList, pData, UsedCompar);

        /* L'element a ete trouve */
        if(eError == LIST_NO_ERROR)
        {
            /* L'element a ete trouve, on le supprime */
            if(pCurrentCell == pList->pCurrent)
            {
                if(pCurrentCell->pNext != NULL)
                {
                    pCurrentCell = pCurrentCell->pNext;
                }
                else
                {
                    pCurrentCell = pCurrentCell->pPrev;
                }
            }
            eError = LIST_RemoveCurrent(pList);

            /* Et on restaure l'element courant */
            pList->pCurrent = pCurrentCell;
        }
    }
    return eError;
}

LIST_Error_e LIST_RemoveAllData(list_s* pList, const void* pData)
{
    /* LIST_RemoveAllData() n'est qu'une encapsulation de LIST_RemoveAllDataFct() */
    return LIST_RemoveAllDataFct(pList, pData, NULL);
}

LIST_Error_e LIST_RemoveAllDataFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *))
{
    LIST_Error_e eError = LIST_NO_ERROR;

    /* On efface iterativement toutes les cellules correspondant au critere situee apres l'element courant */
    while(eError == LIST_NO_ERROR)
    {
        eError = LIST_RemoveDataFct(pList, pData, compar);
    }

    /* S'il n'y a plus de cellules correspodantes, la suppression c'est bien passe */
    if(eError == LIST_CELL_NOT_FOUND)
    {
        eError = LIST_NO_ERROR;
    }

    /* puis on efface iterativement toutes les cellules correspondant au critere situee avant l'element courant */
    while(eError == LIST_NO_ERROR)
    {
        eError = LIST_RemoveDataRevFct(pList, pData, compar);
    }

    /* S'il n'y a plus de cellules correspodantes, la suppression c'est bien passe */
    if(eError == LIST_CELL_NOT_FOUND)
    {
        eError = LIST_NO_ERROR;
    }
    return eError;
}
