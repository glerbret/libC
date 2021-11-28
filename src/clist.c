/**
 * @author Gregory Lerbret
 * @brief Gestion de listes circulaires
 * @date 24/09/2006
 * @version 1.0.0
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
    struct clist_cell*  pNext;
    struct clist_cell*  pPrev;
    void*               pData;
    size_t              szDataSize;
} clist_cell_s;

struct clist
{
    clist_cell_s*   pHead;
    clist_cell_s*   pCurrent;
    size_t          szNbCells;
    int (*mCompar)(const void *, const void *);
};

static clist_cell_s* CLIST_AllocCell(const void* pData, size_t szDataSize)
{
    clist_cell_s* pCell = NULL;

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
            pCell->pNext = pCell;
            pCell->pPrev = pCell;

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

static clist_cell_s* CLIST_DetachCell(clist_s* pList, clist_cell_s* pCellToDelete)
{
    clist_cell_s* pCell = NULL;

    if(pCellToDelete == NULL)
    {
        /* Il n'y a pas de cellule a retirer, on arrete ici et on retourne NULL */
        pCell = NULL;
    }
    else
    {
        /* On detache la cellule */
        pCell = pCellToDelete;

        pCell->pPrev->pNext = pCell->pNext;
        pCell->pNext->pPrev = pCell->pPrev;
        pList->szNbCells--;

        if(pList->szNbCells == 0)
        {
            /* La liste est maintenant vide */
            pList->pHead = NULL;
            pList->pCurrent = NULL;
        }
        else
        {
            if(pCell == pList->pCurrent)
            {
                /* On vient de supprimmer la cellule courante, la cellule suivante devient la nouvelle cellule courante */
                pList->pCurrent = pCell->pNext;
            }
            if(pCell == pList->pHead)
            {
                /* On vient de supprimmer la tete de la liste, la cellule suivante devient la nouvelle tete de liste */
                pList->pHead = pCell->pNext;
            }
        }
    }
    return pCell;
}

const char* CLIST_Identifier(void)
{
    return CLIST_ID;
}

int CLIST_Version(void)
{
    return CLIST_VERS_MAJ * 10000 + CLIST_VERS_MIN * 100 + CLIST_VERS_BRCH;
}

clist_s* CLIST_Create(int (*compar)(const void *, const void *), CLIST_Error_e* eError)
{
    clist_s* pList = malloc(sizeof * pList);

    if(pList == NULL)
    {
        /* La liste n'a pas pu etre creer */
        *eError = CLIST_MEMORY_ERROR;
    }
    else
    {
        /* Initialisation de la liste */
        pList->pHead = NULL;
        pList->pCurrent = NULL;
        pList->szNbCells = 0;
        pList->mCompar = compar;
        *eError = CLIST_NO_ERROR;
    }
    return pList;
}

void CLIST_Destroy(clist_s* pList)
{
    /* On se positionne sur le premier element ... */
    if(CLIST_SeekFirst(pList) == CLIST_NO_ERROR)
    {
        /* ... et on retire iterativement toutes les cellules de la liste */
        while(CLIST_RemoveFirst(pList) != CLIST_EMPTY_LIST)
        {
            /* NOP */
        }
    }

    /* Puis on detruit la liste*/
    free(pList), pList = NULL;
}

void CLIST_SetCmp(clist_s* pList, int (*compar)(const void *, const void *))
{
    pList->mCompar = compar;
}

bool CLIST_IsEmpty(const clist_s* pList)
{
    return pList->pHead == NULL ? true : false;
}

size_t CLIST_Size(const clist_s* pList)
{
    return pList->szNbCells;
}

bool CLIST_IsHead(const clist_s* pList)
{
    bool bIsHead = false;

    if(CLIST_IsEmpty(pList) == true)
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

CLIST_Error_e CLIST_InsertFirst(clist_s* pList, const void* pData, size_t szDataSize)
{
    clist_cell_s* pCell = CLIST_AllocCell(pData, szDataSize);
    CLIST_Error_e eError = CLIST_NO_ERROR;

    if(pCell == NULL)
    {
        eError = CLIST_MEMORY_ERROR;
    }
    else
    {
        /* Mise a jour du chainage des elements */
        if(pList->pHead != NULL)
        {
            pCell->pNext = pList->pHead;
            pCell->pPrev = pList->pHead->pPrev;
        }
        pCell->pPrev->pNext = pCell;
        pCell->pNext->pPrev = pCell;

        /* Mise a jour de la liste circulaire */
        pList->pHead = pCell;
        pList->pCurrent = pCell;
        pList->szNbCells++;

        eError = CLIST_NO_ERROR;
    }
    return eError;
}

CLIST_Error_e CLIST_InsertNext(clist_s* pList, const void* pData, size_t szDataSize)
{
    clist_cell_s* pCell = CLIST_AllocCell(pData, szDataSize);
    CLIST_Error_e eError = CLIST_NO_ERROR;

    if(pCell == NULL)
    {
        eError = CLIST_MEMORY_ERROR;
    }
    else
    {
        /* Mise a jour du chainage des elements */
        if(pList->pCurrent != NULL)
        {
            pCell->pNext = pList->pCurrent->pNext;
            pCell->pPrev = pList->pCurrent;
        }
        pCell->pPrev->pNext = pCell;
        pCell->pNext->pPrev = pCell;

        /* Mise a jour de la liste circulaire */
        if(pList->szNbCells == 0)
        {
            pList->pHead = pCell;
        }
        pList->pCurrent = pCell;
        pList->szNbCells++;

        eError = CLIST_NO_ERROR;
    }
    return eError;
}

CLIST_Error_e CLIST_InsertPrev(clist_s* pList, const void* pData, size_t szDataSize)
{
    clist_cell_s* pCell = CLIST_AllocCell(pData, szDataSize);
    CLIST_Error_e eError = CLIST_NO_ERROR;

    if(pCell == NULL)
    {
        eError = CLIST_MEMORY_ERROR;
    }
    else
    {
        /* Mise a jour du chainage des elements */
        if(pList->pCurrent != NULL)
        {
            pCell->pNext = pList->pCurrent;
            pCell->pPrev = pList->pCurrent->pPrev;
        }
        pCell->pPrev->pNext = pCell;
        pCell->pNext->pPrev = pCell;

        /* Mise a jour de la liste circulaire */
        if(pList->szNbCells == 0)
        {
            pList->pHead = pCell;
        }
        pList->pCurrent = pCell;
        pList->szNbCells++;

        eError = CLIST_NO_ERROR;
    }
    return eError;
}

CLIST_Error_e CLIST_SeekFirst(clist_s* pList)
{
    CLIST_Error_e eError;

    if(CLIST_IsEmpty(pList) == true)
    {
        eError = CLIST_EMPTY_LIST;
    }
    else
    {
        pList->pCurrent = pList->pHead;
        eError = CLIST_NO_ERROR;
    }

    return eError;
}

CLIST_Error_e CLIST_SeekNext(clist_s* pList)
{
    CLIST_Error_e eError;

    if(CLIST_IsEmpty(pList) == true)
    {
        eError = CLIST_EMPTY_LIST;
    }
    else
    {
        pList->pCurrent = pList->pCurrent->pNext;
        eError = CLIST_NO_ERROR;
    }
    return eError;
}

CLIST_Error_e CLIST_SeekPrev(clist_s* pList)
{
    CLIST_Error_e eError;

    if(CLIST_IsEmpty(pList) == true)
    {
        eError = CLIST_EMPTY_LIST;
    }
    else
    {
        pList->pCurrent = pList->pCurrent->pPrev;
        eError = CLIST_NO_ERROR;
    }
    return eError;
}

const void* CLIST_ReadFirst(const clist_s* pList, CLIST_Error_e* eError)
{
    void* pData = NULL;

    if(CLIST_IsEmpty(pList) == true)
    {
        *eError = CLIST_EMPTY_LIST;
    }
    else
    {
        pData = pList->pHead->pData;
        *eError = CLIST_NO_ERROR;
    }
    return pData;
}

const void* CLIST_ReadCurrent(const clist_s* pList, CLIST_Error_e* eError)
{
    void* pData = NULL;

    if(CLIST_IsEmpty(pList) == true)
    {
        *eError = CLIST_EMPTY_LIST;
    }
    else
    {
        pData = pList->pCurrent->pData;
        *eError = CLIST_NO_ERROR;
    }
    return pData;
}

const void* CLIST_ReadNext(const clist_s* pList, CLIST_Error_e* eError)
{
    void* pData = NULL;

    if(CLIST_IsEmpty(pList) == true)
    {
        *eError = CLIST_EMPTY_LIST;
    }
    else
    {
        pData = pList->pCurrent->pNext->pData;
        *eError = CLIST_NO_ERROR;
    }
    return pData;
}

const void* CLIST_ReadPrev(const clist_s* pList, CLIST_Error_e* eError)
{
    void* pData = NULL;

    if(CLIST_IsEmpty(pList) == true)
    {
        *eError = CLIST_EMPTY_LIST;
    }
    else
    {
        pData = pList->pCurrent->pPrev->pData;
        *eError = CLIST_NO_ERROR;
    }
    return pData;
}

const void* CLIST_GetFirst(clist_s* pList, CLIST_Error_e* eError)
{
    void* pData = NULL;
    clist_cell_s* pTmpCell = NULL;

    if(CLIST_IsEmpty(pList) == true)
    {
        *eError = CLIST_EMPTY_LIST;
    }
    else
    {
        pTmpCell = CLIST_DetachCell(pList, pList->pHead);
        if(pTmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            *eError = CLIST_EMPTY_LIST;
        }
        else
        {
            pData = pTmpCell->pData;
            free(pTmpCell), pTmpCell = NULL;

            *eError = CLIST_NO_ERROR;
        }
    }
    return pData;
}

const void* CLIST_GetCurrent(clist_s* pList, CLIST_Error_e* eError)
{
    void* pData = NULL;
    clist_cell_s* pTmpCell = NULL;

    if(CLIST_IsEmpty(pList) == true)
    {
        *eError = CLIST_EMPTY_LIST;
    }
    else
    {
        pTmpCell = CLIST_DetachCell(pList, pList->pCurrent);

        if(pTmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            *eError = CLIST_EMPTY_LIST;
        }
        else
        {
            pData = pTmpCell->pData;
            free(pTmpCell), pTmpCell = NULL;

            *eError = CLIST_NO_ERROR;
        }
    }
    return pData;
}

const void* CLIST_GetNext(clist_s* pList, CLIST_Error_e* eError)
{
    void* pData = NULL;
    clist_cell_s* pTmpCell;

    if(CLIST_IsEmpty(pList) == true)
    {
        *eError = CLIST_EMPTY_LIST;
    }
    else
    {
        pTmpCell = CLIST_DetachCell(pList, pList->pCurrent->pNext);

        if(pTmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            *eError = CLIST_CELL_NOT_FOUND;
        }
        else
        {
            pData = pTmpCell->pData;
            free(pTmpCell), pTmpCell = NULL;

            *eError = CLIST_NO_ERROR;
        }
    }
    return pData;
}

const void* CLIST_GetPrev(clist_s* pList, CLIST_Error_e* eError)
{
    void* pData = NULL;
    clist_cell_s*  pTmpCell;

    if(CLIST_IsEmpty(pList) == true)
    {
        *eError = CLIST_EMPTY_LIST;
    }
    else
    {
        pTmpCell = CLIST_DetachCell(pList, pList->pCurrent->pPrev);
        if(pTmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            *eError = CLIST_CELL_NOT_FOUND;
        }
        else
        {
            pData = pTmpCell->pData;
            free(pTmpCell), pTmpCell = NULL;

            *eError = CLIST_NO_ERROR;
        }
    }
    return pData;
}

CLIST_Error_e CLIST_RemoveFirst(clist_s* pList)
{
    CLIST_Error_e eError;
    clist_cell_s* pTmpCell;

    if(CLIST_IsEmpty(pList) == true)
    {
        eError = CLIST_EMPTY_LIST;
    }
    else
    {
        pTmpCell = CLIST_DetachCell(pList, pList->pHead);

        if(pTmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            eError = CLIST_EMPTY_LIST;
        }
        else
        {
            if(pTmpCell->szDataSize != 0)
            {
                free(pTmpCell->pData);
            }
            free(pTmpCell), pTmpCell = NULL;

            eError = CLIST_NO_ERROR;
        }
    }

    return eError;
}

CLIST_Error_e CLIST_RemoveCurrent(clist_s* pList)
{
    CLIST_Error_e eError;
    clist_cell_s* pTmpCell;

    if(CLIST_IsEmpty(pList) == true)
    {
        eError = CLIST_EMPTY_LIST;
    }
    else
    {
        pTmpCell = CLIST_DetachCell(pList, pList->pCurrent);

        if(pTmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            eError = CLIST_EMPTY_LIST;
        }
        else
        {
            if(pTmpCell->szDataSize != 0)
            {
                free(pTmpCell->pData);
            }
            free(pTmpCell), pTmpCell = NULL;

            eError = CLIST_NO_ERROR;
        }
    }
    return eError;
}

CLIST_Error_e CLIST_RemoveNext(clist_s* pList)
{
    CLIST_Error_e eError;
    clist_cell_s* pTmpCell;

    if(CLIST_IsEmpty(pList) == true)
    {
        eError = CLIST_EMPTY_LIST;
    }
    else
    {
        pTmpCell = CLIST_DetachCell(pList, pList->pCurrent->pNext);

        if(pTmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            eError = CLIST_CELL_NOT_FOUND;
        }
        else
        {
            if(pTmpCell->szDataSize != 0)
            {
                free(pTmpCell->pData);
            }
            free(pTmpCell), pTmpCell = NULL;

            eError = CLIST_NO_ERROR;
        }
    }
    return eError;
}

CLIST_Error_e CLIST_RemovePrev(clist_s* pList)
{
    CLIST_Error_e eError;
    clist_cell_s* pTmpCell;

    if(CLIST_IsEmpty(pList) == true)
    {
        eError = CLIST_EMPTY_LIST;
    }
    else
    {
        pTmpCell = CLIST_DetachCell(pList, pList->pCurrent->pPrev);

        if(pTmpCell == NULL)
        {
            /* Si la cellule n'a pas pu etre detachee, on sort en erreur */
            eError = CLIST_CELL_NOT_FOUND;
        }
        else
        {
            if(pTmpCell->szDataSize != 0)
            {
                free(pTmpCell->pData);
            }
            free(pTmpCell), pTmpCell = NULL;

            eError = CLIST_NO_ERROR;
        }
    }
    return eError;
}

clist_s* CLIST_Clone(const clist_s* pList, CLIST_Error_e* eError)
{
    clist_cell_s* pCurrentCell = NULL;
    /* Creation de la liste clone */
    clist_s* sDestList = CLIST_Create(pList->mCompar, eError);

    if(*eError == CLIST_NO_ERROR)
    {
        if(pList->pHead != NULL)
        {
            pCurrentCell = pList->pHead;

            /* Insertion iterative de tous les elements de la liste originale. La tete de liste sert de marqueur de fin */
            do
            {
                *eError = CLIST_InsertNext(sDestList, pCurrentCell->pData, pCurrentCell->szDataSize);
                pCurrentCell = pCurrentCell->pNext;
            }
            while(pCurrentCell != pList->pHead && *eError == CLIST_NO_ERROR);

        }

        if(*eError == CLIST_MEMORY_ERROR)
        {
            /* Une erreur s'est produite lors de l'insertion, on efface la liste partiellement dupliquee */
            CLIST_Destroy(sDestList);
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

CLIST_Error_e CLIST_SearchData(clist_s* pList, const void* pData)
{
    /* CLIST_SearchData() n'est qu'une encapsulation de CLIST_SearchDataFct */
    return CLIST_SearchDataFct(pList, pData, NULL);
}

CLIST_Error_e CLIST_SearchDataFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *))
{
    CLIST_Error_e eError;
    clist_cell_s* pCurrentCell;
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

    if(CLIST_IsEmpty(pList) == true)
    {
        eError = CLIST_EMPTY_LIST;
    }
    else if(UsedCompar == NULL)
    {
        eError = CLIST_NO_COMP_FONCTION;
    }
    else
    {
        eError = CLIST_CELL_NOT_FOUND;
        pCurrentCell = pList->pCurrent;

        /* Parcours des elements de la liste jusqu'a trouver l'element recherche ou a revenir a l'element de depart */
        do
        {
            if(UsedCompar(pData, pCurrentCell->pData) == 0)
            {
                /* L'element recherche est trouve */
                pList->pCurrent = pCurrentCell;

                eError = CLIST_NO_ERROR;

                /* On arrete la recherche */
                break;
            }

            pCurrentCell = pCurrentCell->pNext;
        }
        while(pCurrentCell != pList->pCurrent);
    }
    return eError;
}

CLIST_Error_e CLIST_SearchDataRev(clist_s* pList, const void* pData)
{
    /* CLIST_SearchDataRev() n'est qu'une encapsulation de CLIST_SearchDataRevFct */
    return CLIST_SearchDataRevFct(pList, pData, NULL);
}

CLIST_Error_e CLIST_SearchDataRevFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *))
{
    CLIST_Error_e eError;
    clist_cell_s* pCurrentCell;
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

    if(CLIST_IsEmpty(pList) == true)
    {
        eError = CLIST_EMPTY_LIST;
    }
    else if(UsedCompar == NULL)
    {
        eError = CLIST_NO_COMP_FONCTION;
    }
    else
    {
        eError = CLIST_CELL_NOT_FOUND;
        pCurrentCell = pList->pCurrent;

        /* Parcours des elements de la liste jusqu'a trouver l'element recherche ou a revenir a l'element de depart */
        do
        {
            if(UsedCompar(pData, pCurrentCell->pData) == 0)
            {
                /* L'element recherche est trouve */
                pList->pCurrent = pCurrentCell;

                eError = CLIST_NO_ERROR;

                /* On arrete la recherche */
                break;
            }

            pCurrentCell = pCurrentCell->pPrev;
        }
        while(pCurrentCell != pList->pCurrent);
    }
    return eError;
}

CLIST_Error_e CLIST_RemoveData(clist_s* pList, const void* pData)
{
    /* CLIST_RemoveData() n'est qu'une encapsulation de CLIST_RemoveData() */
    return CLIST_RemoveDataFct(pList, pData, NULL);
}

CLIST_Error_e CLIST_RemoveDataFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *))
{
    CLIST_Error_e eError;
    clist_cell_s* pCurrentCell = pList->pCurrent;
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

    if(CLIST_IsEmpty(pList) == true)
    {
        eError = CLIST_EMPTY_LIST;
    }
    else if(UsedCompar == NULL)
    {
        eError = CLIST_NO_COMP_FONCTION;
    }
    else
    {
        /* Recherche de l'element a supprime */
        eError = CLIST_SearchDataFct(pList, pData, UsedCompar);

        if(eError == CLIST_NO_ERROR)
        {
            /* L'element a ete trouve, on le supprime */
            if(pCurrentCell == pList->pCurrent)
            {
                pCurrentCell = pCurrentCell->pNext;
            }
            eError = CLIST_RemoveCurrent(pList);

            /* Et on restaure l'element courant */
            pList->pCurrent = pCurrentCell;
        }
    }
    return eError;
}

CLIST_Error_e CLIST_RemoveDataRev(clist_s* pList, const void* pData)
{
    /* CLIST_RemoveData() n'est qu'une encapsulation de CLIST_RemoveData() */
    return CLIST_RemoveDataRevFct(pList, pData, NULL);
}

CLIST_Error_e CLIST_RemoveDataRevFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *))
{
    CLIST_Error_e eError;
    clist_cell_s* pCurrentCell = pList->pCurrent;
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

    if(CLIST_IsEmpty(pList) == true)
    {
        eError = CLIST_EMPTY_LIST;
    }
    else if(UsedCompar == NULL)
    {
        eError = CLIST_NO_COMP_FONCTION;
    }
    else
    {
        /* Recherche de l'element a supprime */
        eError = CLIST_SearchDataRevFct(pList, pData, UsedCompar);

        if(eError == CLIST_NO_ERROR)
        {
            /* L'element a ete trouve, on le supprime */
            if(pCurrentCell == pList->pCurrent)
            {
                pCurrentCell = pCurrentCell->pNext;
            }
            eError = CLIST_RemoveCurrent(pList);

            /* Et on restaure l'element courant */
            pList->pCurrent = pCurrentCell;
        }
    }
    return eError;
}

CLIST_Error_e CLIST_RemoveAllData(clist_s* pList, const void* pData)
{
    /* CLIST_RemoveAllData() n'est qu'une encapsulation de CLIST_RemoveAllDataFct() */
    return CLIST_RemoveAllDataFct(pList, pData, NULL);
}

CLIST_Error_e CLIST_RemoveAllDataFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *))
{
    CLIST_Error_e eError = CLIST_NO_ERROR;

    /* On efface iterativement toutes les cellules correspondant au critere */
    while(eError == CLIST_NO_ERROR)
    {
        eError = CLIST_RemoveDataFct(pList, pData, compar);
    }

    /* S'il n'y a plus de cellules correspodantes, la suppression c'est bien passe */
    if(eError == CLIST_CELL_NOT_FOUND)
    {
        eError = CLIST_NO_ERROR;
    }
    return eError;
}
