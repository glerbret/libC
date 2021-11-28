/**
 * @author Gregory Lerbret
 * @brief Gestion de files
 * @date 24/09/2006
 * @version 1.0.0
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
    struct queue_cell*  pNext;
    struct queue_cell*  pPrev;
    void*               pData;
    size_t              szDataSize;
} queue_cell_s;

struct queue
{
    queue_cell_s*   pHead;
    queue_cell_s*   pTail;
    size_t          szNbCells;
};

static queue_cell_s* QUEUE_AllocCell(const void* pData, size_t szDataSize)
{
    queue_cell_s* pCell = NULL;


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

static queue_cell_s* QUEUE_DetachCell(queue_s* pQueue)
{
    queue_cell_s* pTmpCell = NULL;

    if(QUEUE_IsEmpty(pQueue) == true)
    {
        /* Il n'y a pas de cellule a retirer, on arrete ici et on retourne NULL */
        pTmpCell = NULL;
    }
    else
    {
        /* On detache la cellule */
        pTmpCell = pQueue->pTail;
        pQueue->pTail = pQueue->pTail->pPrev;
        if(pQueue->pTail != NULL)
        {
            pQueue->pTail->pNext = NULL;
        }
        else
        {
            /* La liste est maintenant vide */
            pQueue->pHead = NULL;
        }

        pQueue->szNbCells--;
    }
    return pTmpCell;
}

const char* QUEUE_Identifier(void)
{
    return QUEUE_ID;
}

int QUEUE_Version(void)
{
    return QUEUE_VERS_MAJ * 10000 + QUEUE_VERS_MIN * 100 + QUEUE_VERS_BRCH;
}

queue_s* QUEUE_Create(QUEUE_Error_e* eError)
{
    queue_s* pQueue = malloc(sizeof * pQueue);

    if(pQueue == NULL)
    {
        /* La file n'a pas pu etre creer */
        *eError = QUEUE_MEMORY_ERROR;
    }
    else
    {
        /* Initialisation de la file */
        pQueue->pHead = NULL;
        pQueue->pTail = NULL;
        pQueue->szNbCells = 0;
        *eError = QUEUE_NO_ERROR;
    }
    return pQueue;
}

void QUEUE_Destroy(queue_s* pQueue)
{
    /* On retire iterativement toutes les cellules de la file */
    while(QUEUE_Remove(pQueue) != QUEUE_EMPTY_QUEUE)
    {
        /* NOP */
    }

    /* Puis on detruit la file*/
    free(pQueue), pQueue = NULL;
}

bool QUEUE_IsEmpty(const queue_s* pQueue)
{
    return pQueue->pHead == NULL;
}

size_t QUEUE_Size(const queue_s* pQueue)
{
    return pQueue->szNbCells;
}

QUEUE_Error_e QUEUE_Enqueue(queue_s* pQueue, const void* pData, size_t szDataSize)
{
    queue_cell_s* pCell = QUEUE_AllocCell(pData, szDataSize);
    QUEUE_Error_e eError = QUEUE_NO_ERROR;

    if(pCell == NULL)
    {
        eError = QUEUE_MEMORY_ERROR;
    }
    else
    {
        /* Mise a jour du chainage des elements */
        pCell->pNext = pQueue->pHead;
        pCell->pPrev = NULL;
        if(pQueue->pHead != NULL)
        {
            pQueue->pHead->pPrev = pCell;
        }

        /* Mise a jour de la file */
        pQueue->pHead = pCell;
        if(pQueue->szNbCells == 0)
        {
            pQueue->pTail = pCell;
        }
        pQueue->szNbCells++;
    }
    return eError;
}

const void* QUEUE_Dequeue(queue_s* pQueue, QUEUE_Error_e* eError)
{
    void* pData = NULL;
    queue_cell_s* pTmpCell = QUEUE_DetachCell(pQueue);

    if(pTmpCell == NULL)
    {
        *eError = QUEUE_EMPTY_QUEUE;
    }
    else
    {
        pData = pTmpCell->pData;
        free(pTmpCell);

        *eError = QUEUE_NO_ERROR;
    }
    return pData;
}

const void* QUEUE_Peek(const queue_s* pQueue, QUEUE_Error_e* eError)
{
    void* pData = NULL;

    if(QUEUE_IsEmpty(pQueue) == true)
    {
        *eError = QUEUE_EMPTY_QUEUE;
    }
    else
    {
        pData = pQueue->pTail->pData;
        *eError = QUEUE_NO_ERROR;
    }
    return pData;
}

QUEUE_Error_e QUEUE_Remove(queue_s* pQueue)
{
    queue_cell_s* pTmpCell = QUEUE_DetachCell(pQueue);
    QUEUE_Error_e eError;

    if(pTmpCell == NULL)
    {
        eError = QUEUE_EMPTY_QUEUE;
    }
    else
    {
        if(pTmpCell->szDataSize)
        {
            free(pTmpCell->pData);
        }
        free(pTmpCell);

        eError = QUEUE_NO_ERROR;
    }
    return eError;
}

queue_s* QUEUE_Clone(const queue_s* pQueue, QUEUE_Error_e* eError)
{
    queue_cell_s* pCurrentCell = NULL;
    /* Creation de la file clone */
    queue_s* pDestQueue = QUEUE_Create(eError);

    if(*eError == QUEUE_NO_ERROR)
    {
        /* Insertion iterative de tous les elements de la file originale. */
        for(pCurrentCell = pQueue->pTail; pCurrentCell != NULL && *eError == QUEUE_NO_ERROR; pCurrentCell = pCurrentCell->pPrev)
        {
            *eError = QUEUE_Enqueue(pDestQueue, pCurrentCell->pData, pCurrentCell->szDataSize);
        }

        /* Une erreur s'est produite lors de l'insertion, on efface la file partiellement dupliquee */
        if(*eError == QUEUE_MEMORY_ERROR)
        {
            QUEUE_Destroy(pDestQueue);
            pDestQueue = NULL;
        }
    }
    return pDestQueue;
}
