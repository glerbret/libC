/**
 * @author Gregory Lerbret
 * @brief Gestion de piles
 * @date 24/09/2006
 * @version 1.0.0
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
#define STACK_ID		STACK_NAME " - Version " xstr(STACK_VERS_MAJ) "." xstr(STACK_VERS_MIN) "." xstr(STACK_VERS_BRCH)

typedef struct stack_cell
{
    struct stack_cell*  pNext;
    struct stack_cell*  pPrev;
    void*               pData;
    size_t              szDataSize;
} stack_cell_s;

struct stack
{
    stack_cell_s*   pHead;
    stack_cell_s*   pTail;
    size_t          szNbCells;
};

static stack_cell_s* STACK_AllocCell(const void* pData, size_t szDataSize)
{
    stack_cell_s* pCell = NULL;

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

static stack_cell_s* STACK_DetachCell(stack_s* pStack)
{
    stack_cell_s*  pTmpCell = NULL;

    if(STACK_IsEmpty(pStack) == true)
    {
        /* Il n'y a pas de cellule a retirer, on arrete ici et on retourne NULL */
        pTmpCell = NULL;
    }
    else
    {
        /* On detache la cellule */
        pTmpCell = pStack->pHead;
        pStack->pHead = pTmpCell->pNext;
        if(pStack->pHead != NULL)
        {
            pStack->pHead->pPrev = NULL;
        }
        else
        {
            /* La liste est maintenant vide */
            pStack->pTail = NULL;
        }

        pStack->szNbCells--;
    }
    return pTmpCell;
}

const char* STACK_Identifier(void)
{
    return STACK_ID;
}

int STACK_Version(void)
{
    return STACK_VERS_MAJ * 10000 + STACK_VERS_MIN * 100 + STACK_VERS_BRCH;
}

stack_s* STACK_Create(STACK_Error_e* eError)
{
    stack_s* pStack = malloc(sizeof * pStack);

    if(pStack == NULL)
    {
        /* La pile n'a pas pu etre creer */
        *eError = STACK_MEMORY_ERROR;
    }
    else
    {
        /* Initialisation de la pile */
        pStack->pHead = NULL;
        pStack->pTail = NULL;
        pStack->szNbCells = 0;
        *eError = STACK_NO_ERROR;
    }
    return pStack;
}

void STACK_Destroy(stack_s* pStack)
{
    /* On retire iterativement toutes les cellules de la pile */
    while(STACK_Remove(pStack) != STACK_EMPTY_STACK)
    {
        /* NOP */
    }

    /* Puis on detruit la pile*/
    free(pStack);
}

bool STACK_IsEmpty(const stack_s* pStack)
{
    return pStack->pHead == NULL;
}

size_t STACK_Size(const stack_s* pStack)
{
    return pStack->szNbCells;
}

STACK_Error_e STACK_Push(stack_s* pStack, const void* pData, size_t szDataSize)
{
    stack_cell_s* pCell = STACK_AllocCell(pData, szDataSize);
    STACK_Error_e eError = STACK_NO_ERROR;

    if(pCell == NULL)
    {
        eError = STACK_MEMORY_ERROR;
    }
    else
    {
        /* Mise a jour du chainage des elements */
        pCell->pNext = pStack->pHead;
        pCell->pPrev = NULL;

        if(pStack->pHead != NULL)
        {
            pStack->pHead->pPrev = pCell;
        }

        /* Mise a jour de la pile */
        pStack->pHead = pCell;
        if(pStack->szNbCells == 0)
        {
            pStack->pTail = pCell;
        }
        pStack->szNbCells++;
    }
    return eError;
}

const void* STACK_Pop(stack_s* pStack, STACK_Error_e* eError)
{
    void* pData = NULL;
    stack_cell_s* pTmpCell = STACK_DetachCell(pStack);

    if(pTmpCell == NULL)
    {
        *eError = STACK_EMPTY_STACK;
    }
    else
    {
        pData = pTmpCell->pData;
        free(pTmpCell);

        *eError = STACK_NO_ERROR;
    }
    return pData;
}

const void* STACK_Peek(const stack_s* pStack, STACK_Error_e* eError)
{
    void* pData = NULL;

    if(STACK_IsEmpty(pStack) == true)
    {
        *eError = STACK_EMPTY_STACK;
    }
    else
    {
        pData = pStack->pHead->pData;
        *eError = STACK_NO_ERROR;
    }
    return pData;
}

STACK_Error_e STACK_Remove(stack_s* pStack)
{
    stack_cell_s* pTmpCell = STACK_DetachCell(pStack);
    STACK_Error_e eError;

    if(pTmpCell == NULL)
    {
        eError = STACK_EMPTY_STACK;
    }
    else
    {
        if(pTmpCell->szDataSize)
        {
            free(pTmpCell->pData);
        }
        free(pTmpCell);

        eError = STACK_NO_ERROR;
    }
    return eError;
}

stack_s* STACK_Clone(const stack_s* pStack, STACK_Error_e* eError)
{
    stack_cell_s* pCurrentCell = NULL;
    /* Creation de la pile clone */
    stack_s* pDestStack = STACK_Create(eError);

    if(*eError == STACK_NO_ERROR)
    {
        /* Insertion iterative de tous les elements de la pile originale. */
        for(pCurrentCell = pStack->pTail; pCurrentCell != NULL && *eError == STACK_NO_ERROR; pCurrentCell = pCurrentCell->pPrev)
        {
            *eError = STACK_Push(pDestStack, pCurrentCell->pData, pCurrentCell->szDataSize);
        }

        /* Une erreur s'est produite lors de l'insertion, on efface la pile partiellement dupliquee */
        if(*eError == STACK_MEMORY_ERROR)
        {
            STACK_Destroy(pDestStack);
            pDestStack = NULL;
        }
    }
    return pDestStack;
}
