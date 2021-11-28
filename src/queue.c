/**
   \author Gregory Lerbret
   \file queue.c
   \brief Gestion de files.<br>
   \date 24/09/2006
   \version 1.0.0
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bool.h"
#include "queue.h"

#define xstr(s) str(s)
#define str(s) #s

#define QUEUE_NAME	      "Gestion de files"
#define QUEUE_VERS_MAJ	   1
#define QUEUE_VERS_MIN	   0
#define QUEUE_VERS_BRCH	   0
#define QUEUE_ID		      QUEUE_NAME " - Version " xstr(QUEUE_VERS_MAJ) "." xstr(QUEUE_VERS_MIN) "." xstr(QUEUE_VERS_BRCH)

/**
   \struct queue_cell_s
   \brief Structure d'une cellule de la file.
*/
typedef struct queue_cell
{
/**
   \brief Pointeur sur la cellule suivante.
*/
   struct queue_cell*      pNext;
/**
   \brief Pointeur sur la cellule precedente.
*/
   struct queue_cell*      pPrev;
/**
   \brief Pointeur sur la zone de donnee.
*/
   void*                   pData;
/**
   \brief Taille de la zone de donnee.
*/
   size_t                  szDataSize;
} queue_cell_s;

/**
   \struct queue_s
   \brief Structure de la file.
*/
struct queue
{
/**
   \brief Pointeur sur la tete de la file.
*/
   queue_cell_s*        pHead;
/**
   \brief Pointeur sur la fin de la file.
*/
   queue_cell_s*        pTail;
/**
   \brief Nombre d'element de la file.
*/
   size_t               szNbCells;
};

/**
   \brief Allocation et initialisation d'une cellule.
   \param[in] pData l'element a ajouter a la file
   \param[in] szDataSize la taille de l'element
   \return la cellule allouee (NULL en cas d'erreur).
*/
static queue_cell_s* QUEUE_AllocCell(const void* pData, size_t szDataSize)
{
   queue_cell_s*  pCell    = NULL;


   if(pData == NULL || szDataSize == 0)
   {
      /* Il n'y a pas d'element a ajouter, on arrete ici et on retourne NULL */
      pCell = NULL;
   }
   else
   {
      pCell = malloc(sizeof *pCell);

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

/**
   \brief Retrait d'une cellule de la file.
   \param[in] pQueue la file
   \return la cellule detachee de la pile (NULL en cas d'erreur).
*/
static queue_cell_s* QUEUE_DetachCell(queue_s* pQueue)
{
   queue_cell_s*  pTmpCell = NULL;

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
      if(pQueue->pTail !=NULL)
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

/**
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char* QUEUE_Identifier(void)
{
   return QUEUE_ID;
}

/**
   \brief Version du module.
   \return La version du module.
*/
int QUEUE_Version(void)
{
   return QUEUE_VERS_MAJ*10000 + QUEUE_VERS_MIN*100 + QUEUE_VERS_BRCH;
}

/**
   \brief Creation d'une file.
   \param[out] eError le resultat de la creation :<br>
               QUEUE_NO_ERROR : la creation s'est correctement deroulee.<br>
               QUEUE_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire.
   \return La file cree (NULL en cas d'erreur).
*/
queue_s* QUEUE_Create(QUEUE_Error_e* eError)
{
   queue_s*    pQueue = malloc(sizeof *pQueue);

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

/**
   \brief Destruction d'une file.
   \param[in] pQueue la file
*/
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

/**
   \brief Verification de la vacuite de la file.
   \param[in] pQueue la file
   \return  TRUE si la file est vide.<br>
            FALSE sinon.
*/
bool QUEUE_IsEmpty(const queue_s* pQueue)
{
   return pQueue->pHead == NULL ? true : false;
}

/**
   \brief Calcul du nombre d'element de la file.
   \param[in] pQueue la file
   \return Le nombre d'element de la file.
*/
size_t QUEUE_Size(const queue_s* pQueue)
{
   return pQueue->szNbCells;
}

/**
   \brief Ajout d'un element a la file.
   \param[in,out] pQueue la file
   \param[in] pData l'element a ajouter
   \param[in] szDataSize la taille de l'element
   \return  QUEUE_NO_ERROR : l'ajout s'est correctement deroule.<br>
            QUEUE_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire ou il n'existe pas de donnee a inserer.
*/
QUEUE_Error_e QUEUE_Enqueue(queue_s* pQueue, const void* pData, size_t szDataSize)
{
   queue_cell_s*  pCell    = QUEUE_AllocCell(pData, szDataSize);
   QUEUE_Error_e  eError   = QUEUE_NO_ERROR;

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

/**
   \brief Lecture et suppression d'un element de la file.
   \param[in,out] pQueue la file
   \param[out] eError le resultat de la lecture :<br>
               QUEUE_NO_ERROR : la lecture s'est correctement deroulee.<br>
               QUEUE_EMPTY_QUEUE : la file est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void* QUEUE_Dequeue(queue_s* pQueue, QUEUE_Error_e* eError)
{
   void*          pData    = NULL;
   queue_cell_s*  pTmpCell = QUEUE_DetachCell(pQueue);

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

/**
   \brief Lecture d'un element de la file.
   \param[in] pQueue la file
   \param[out] eError le resultat de la lecture :<br>
               QUEUE_NO_ERROR : la lecture s'est correctement deroulee.<br>
               QUEUE_EMPTY_QUEUE : la file est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void* QUEUE_Peek(const queue_s* pQueue, QUEUE_Error_e* eError)
{
   void*    pData = NULL;

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

/**
   \brief Suppression d'un element de la file.
   \param[in,out] pQueue la file
   \return  QUEUE_NO_ERROR : la suppression s'est correctement deroulee.<br>
            QUEUE_EMPTY_QUEUE : la pile est vide.
*/
QUEUE_Error_e QUEUE_Remove(queue_s* pQueue)
{
   queue_cell_s*  pTmpCell = QUEUE_DetachCell(pQueue);
   QUEUE_Error_e  eError;

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

/**
   \brief Duplication d'une file.
   \param[in] pQueue la file a dupliquer
   \param[out] eError statut de la duplication :<br>
               QUEUE_NO_ERROR : la copie s'est correctement deroulee.<br>
               QUEUE_ALLOC_QUEUE : le module n'a pas pu allouer assez de memoire.
   \return La copie de la file.
*/
queue_s* QUEUE_Clone(const queue_s* pQueue, QUEUE_Error_e* eError)
{
   queue_cell_s*     pCurrentCell   = NULL;
   /* Creation de la file clone */
   queue_s*          pDestQueue     = QUEUE_Create(eError);

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
