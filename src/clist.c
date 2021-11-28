/**
   \author Gregory Lerbret
   \file clist.c
   \brief Gestion de listes circulaires.<br>
   \date 24/09/2006
   \version 1.0.0
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bool.h"
#include "clist.h"

#define xstr(s) str(s)
#define str(s) #s

#define CLIST_NAME	      "Gestion de liste circulaire"
#define CLIST_VERS_MAJ     1
#define CLIST_VERS_MIN     0
#define CLIST_VERS_BRCH    0
#define CLIST_ID           CLIST_NAME " - Version " xstr(CLIST_VERS_MAJ) "." xstr(CLIST_VERS_MIN) "." xstr(CLIST_VERS_BRCH)

/**
   \struct clist_cell_s
   \brief Structure d'une cellule de la liste cirulaire
*/
typedef struct clist_cell
{
/**
   \brief pointeur sur la cellule suivante
*/
   struct clist_cell*      pNext;
/**
   \brief pointeur sur la cellule precedente
*/
   struct clist_cell*      pPrev;
/**
   \brief pointeur sur la zone de donnee
*/
   void*                   pData;
/**
   \brief taille de la zone de donnee
*/
   size_t                  szDataSize;
} clist_cell_s;

/**
   \struct clist_s
   \brief Structure de la liste circulaire
*/
struct clist
{
/**
   \brief Pointeur sur la tete de la liste
*/
   clist_cell_s*     pHead;
/**
   \brief Pointeur sur l'element courant de la liste
*/
   clist_cell_s*     pCurrent;
/**
   \brief Nombre d'element de la liste
*/
   size_t            szNbCells;
/**
   \brief Fonction de comparaison des elements de la liste
*/
   int (*mCompar)(const void *, const void *);
};

/**
   \fn CLIST_Cell* CLIST_AllocCell(const void* pData, size_t szDataSize)
   \brief Allocation et initialisation d'une cellule.
   \param[in] pData l'element a ajouter a la liste
   \param[in] szDataSize la taille de l'element
   \return  la cellule allouee (NULL en cas d'erreur).
*/
static clist_cell_s* CLIST_AllocCell(const void* pData, size_t szDataSize)
{
   clist_cell_s*  pCell = NULL;

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

/**
   \fn CLIST_Cell* CLIST_DetachCell(clist_s* pList, CLIST_Cell* pCellToDelete)
   \brief Retrait d'une cellule de la liste.
   \param[in] pList la liste circulaire
   \param[in] pCellToDelete la cellule a supprimmer
   \return  la cellule detachee de la liste (NULL en cas d'erreur).
*/
static clist_cell_s* CLIST_DetachCell(clist_s* pList, clist_cell_s* pCellToDelete)
{
   clist_cell_s*  pCell = NULL;

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

/**
   \fn const char* CLIST_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char* CLIST_Identifier(void)
{
   return CLIST_ID;
}

/**
   \fn int CLIST_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int CLIST_Version(void)
{
   return CLIST_VERS_MAJ*10000 + CLIST_VERS_MIN*100 + CLIST_VERS_BRCH;
}

/**
   \fn clist_s* CLIST_Create(int (*compar)(const void *, const void *), CLIST_Error_e* eError)
   \brief Creation d'une liste circulaire.
   \param[in] compar la fonction de comparaison des elements
   \param[out] eError le resultat de la creation :<br>
      CLIST_NO_ERROR : la creation s'est correctement deroulee.<br>
      CLIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire.
   \return  La liste circulaire (NULL en cas d'erreur).
*/
clist_s* CLIST_Create(int (*compar)(const void *, const void *), CLIST_Error_e* eError)
{
   clist_s*    pList = malloc(sizeof *pList);

   if(pList == NULL)
   {
      /* La liste n'a pas pu etre creer */
      *eError = CLIST_MEMORY_ERROR;
   }
   else
   {
      /* Initialisation de la liste */
      pList->pHead      = NULL;
      pList->pCurrent   = NULL;
      pList->szNbCells  = 0;
      pList->mCompar    = compar;
      *eError           = CLIST_NO_ERROR;
   }
   return pList;
}

/**
   \fn void CLIST_Destroy(clist_s* pList)
   \brief Destruction d'une liste circulaire.
   \param[in,out] pList la liste circulaire
*/
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

/**
   \fn void CLIST_SetCmp(clist_s* pList, int (*compar)(const void *, const void *))
   \brief Mise a jour de la fonction de comparaison..
   \param[in,out] pList la liste circulaire
   \param[in] compar la fonction de comparaison
*/
void CLIST_SetCmp(clist_s* pList, int (*compar)(const void *, const void *))
{
   pList->mCompar = compar;
}

/**
   \fn bool CLIST_IsEmpty(const clist_s* pList)
   \brief Verification de la vacuite de la liste.
   \param[in] pList la liste circulaire
   \return  true si la liste est vide.<br>
            false sinon.
*/
bool CLIST_IsEmpty(const clist_s* pList)
{
   return pList->pHead == NULL ? true : false;
}

/**
   \fn size_t CLIST_Size(const clist_s* pList)
   \brief Calcul du nombre d'element de la liste.
   \param[in] pList la liste circulaire
   \return Le nombre d'element de la liste.
*/
size_t CLIST_Size(const clist_s* pList)
{
   return pList->szNbCells;
}

/**
   \fn bool CLIST_IsHead(const clist_s* pList)
   \brief Verification si l'element courant est le premier.
   \param[in] pList la liste circulaire
   \return  true si l'element est le premier de la liste.<br>
            false sinon.
*/
bool CLIST_IsHead(const clist_s* pList)
{
   bool     bIsHead = false;

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

/**
   \fn CLIST_Error_e CLIST_InsertFirst(clist_s* pList, const void* pData, size_t szDataSize)
   \brief   Insertion d'un element en tete de liste.<br>
            L'element insere devient l'element courant.
   \param[in,out] pList la liste circulaire
   \param[in] pData l'element a ajouter
   \param[in] szDataSize la taille de l'element
   \return  CLIST_NO_ERROR : l'insertion s'est correctement deroulee.<br>
            CLIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire ou il n'existe pas de donnee a inserer.
*/
CLIST_Error_e CLIST_InsertFirst(clist_s* pList, const void* pData, size_t szDataSize)
{
   clist_cell_s*  pCell    = CLIST_AllocCell(pData, szDataSize);
   CLIST_Error_e  eError   = CLIST_NO_ERROR;

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

/**
   \fn CLIST_Error_e CLIST_InsertNext(clist_s* pList, const void* pData, size_t szDataSize)
   \brief   Insertion d'un element dans liste apres l'element courant.<br>
            L'element insere devient l'element courant.
   \param[in,out] pList la liste circulaire
   \param[in] pData l'element a ajouter
   \param[in] szDataSize la taille de l'element
   \return  CLIST_NO_ERROR : l'insertion s'est correctement deroulee.<br>
            CLIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire ou il n'existe pas de donnee a inserer.
*/
CLIST_Error_e CLIST_InsertNext(clist_s* pList, const void* pData, size_t szDataSize)
{
   clist_cell_s*  pCell    = CLIST_AllocCell(pData, szDataSize);
   CLIST_Error_e  eError   = CLIST_NO_ERROR;

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

/**
   \fn CLIST_Error_e CLIST_InsertPrev(clist_s* pList, const void* pData, size_t szDataSize)
   \brief    Insertion d'un element dans liste avant l'element courant.<br>
            L'element insere devient l'element courant.
   \param[in,out] pList la lise circulaire
   \param[in] pData l'element a ajouter
   \param[in] szDataSize la taille de l'element
   \return  CLIST_NO_ERROR : l'insertion s'est correctement deroulee.<br>
            CLIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire ou il n'existe pas de donnee a inserer.
*/
CLIST_Error_e CLIST_InsertPrev(clist_s* pList, const void* pData, size_t szDataSize)
{
   clist_cell_s*  pCell    = CLIST_AllocCell(pData, szDataSize);
   CLIST_Error_e  eError   = CLIST_NO_ERROR;

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

/**
   \fn CLIST_Error_e CLIST_SeekFirst(clist_s* pList)
   \brief Deplacement sur le premier element.
   \param[in,out] pList la liste circulaire
   \return  CLIST_NO_ERROR : le deplacement s'est correctement deroule.<br>
            CLIST_EMPTY_LIST : la liste est vide.
*/
CLIST_Error_e CLIST_SeekFirst(clist_s* pList)
{
   CLIST_Error_e  eError;

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

/**
   \fn CLIST_Error_e CLIST_SeekNext(clist_s* pList)
   \brief Deplacement sur l'element suivant.
   \param[in,out] pList la liste circulaire
   \return  CLIST_NO_ERROR : le deplacement s'est correctement deroule.<br>
            CLIST_EMPTY_LIST : la liste est vide.
*/
CLIST_Error_e CLIST_SeekNext(clist_s* pList)
{
   CLIST_Error_e  eError;

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

/**
   \fn CLIST_Error_e CLIST_SeekPrev(clist_s* pList)
   \brief Deplacement sur l'element precedent.
   \param[in,out] pList la liste circulaire
   \return  CLIST_NO_ERROR : le deplacement s'est correctement deroule.<br>
            CLIST_EMPTY_LIST : la liste est vide.
*/
CLIST_Error_e CLIST_SeekPrev(clist_s* pList)
{
   CLIST_Error_e  eError;

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

/**
   \fn const void* CLIST_ReadFirst(const clist_s* pList, CLIST_Error_e* eError)
   \brief Lecture du premier element.
   \param[in] pList la liste circulaire
   \param[out] eError le resultat de la lecture:<br>
               CLIST_NO_ERROR : la lecture a eut lieu.<br>
               CLIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void* CLIST_ReadFirst(const clist_s* pList, CLIST_Error_e* eError)
{
   void*    pData = NULL;

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

/**
   \fn const void* CLIST_ReadCurrent(const clist_s* pList, CLIST_Error_e* eError)
   \brief Lecture de l'element courant.
   \param[in] pList la liste circulaire
   \param[out] eError le resultat de la lecture:<br>
               CLIST_NO_ERROR : la lecture a eut lieu.<br>
               CLIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void* CLIST_ReadCurrent(const clist_s* pList, CLIST_Error_e* eError)
{
   void*    pData = NULL;

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

/**
   \fn const void* CLIST_ReadNext(const clist_s* pList, CLIST_Error_e* eError)
   \brief Lecture de l'element suivant.
   \param[in] pList la liste circulaire
   \param[out] eError le resultat de la lecture:<br>
               CLIST_NO_ERROR : la lecture a eut lieu.<br>
               CLIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void* CLIST_ReadNext(const clist_s* pList, CLIST_Error_e* eError)
{
   void*    pData = NULL;

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

/**
   \fn const void* CLIST_ReadPrev(const clist_s* pList, CLIST_Error_e* eError)
   \brief Lecture de l'element precedent.
   \param[in] pList la liste circulaire
   \param[out] eError le resultat de la lecture:<br>
               CLIST_NO_ERROR : la lecture a eut lieu.<br>
               CLIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void* CLIST_ReadPrev(const clist_s* pList, CLIST_Error_e* eError)
{
   void*    pData = NULL;

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

/**
   \fn const void* CLIST_GetFirst(clist_s* pList, CLIST_Error_e* eError)
   \brief Lecture et suppression du premier element.<br>
      Si cet element était l'element courant, l'element suivant devient le nouvel element courant.
   \param[in,out] pList la liste circulaire
   \param[out] eError resultat de la lecture:<br>
               CLIST_NO_ERROR : la lecture a eut lieu.<br>
               CLIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void* CLIST_GetFirst(clist_s* pList, CLIST_Error_e* eError)
{
   void*          pData    = NULL;
   clist_cell_s*  pTmpCell = NULL;

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

/**
   \fn const void* CLIST_GetCurrent(clist_s* pList, CLIST_Error_e* eError)
   \brief Lecture et suppression de l'element courant.<br>
          L'element suivant devient l'element courant.
   \param[in,out] pList la liste circulaire
   \param[out] eError resultat de la lecture:<br>
               CLIST_NO_ERROR : la lecture a eut lieu.<br>
               CLIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void* CLIST_GetCurrent(clist_s* pList, CLIST_Error_e* eError)
{
   void*          pData    = NULL;
   clist_cell_s*  pTmpCell = NULL;

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

/**
   \fn const void* CLIST_GetNext(clist_s* pList, CLIST_Error_e* eError)
   \brief Lecture et suppression de l'element suivant.
   \param[in,out] pList la liste circulaire
   \param[out] eError resultat de la lecture:<br>
               CLIST_NO_ERROR : la lecture a eut lieu.<br>
               CLIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void* CLIST_GetNext(clist_s* pList, CLIST_Error_e* eError)
{
   void*          pData = NULL;
   clist_cell_s*  pTmpCell;

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

/**
   \fn const void* CLIST_GetPrev(clist_s* pList, CLIST_Error_e* eError)
   \brief Lecture et suppression de l'element precedent.
   \param[in,out] pList la liste circulaire
   \param[out] eError resultat de la lecture:<br>
               CLIST_NO_ERROR : la lecture a eut lieu.<br>
               CLIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void* CLIST_GetPrev(clist_s* pList, CLIST_Error_e* eError)
{
   void*          pData = NULL;
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

/**
   \fn CLIST_Error_e CLIST_RemoveFirst(clist_s* pList)
   \brief   Suppression du premier element.<br>
            Si cet element était l'element courant, l'element suivant devient le nouvel element courant.
   \param[in,out] pList la liste circulaire
   \return  CLIST_NO_ERROR : la suppression a eut lieu.<br>
            CLIST_EMPTY_LIST : la liste est vide.
*/
CLIST_Error_e CLIST_RemoveFirst(clist_s* pList)
{
   CLIST_Error_e  eError;
   clist_cell_s*  pTmpCell;

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

/**
   \fn CLIST_Error_e CLIST_RemoveCurrent(clist_s* pList)
   \brief   Suppression de l'element courant.<br>
            L'element suivant devient l'element courant.
   \param[in,out] pList la liste circulaire
   \return  CLIST_NO_ERROR : la suppression a eut lieu.<br>
            CLIST_EMPTY_LIST : la liste est vide.
*/
CLIST_Error_e CLIST_RemoveCurrent(clist_s* pList)
{
   CLIST_Error_e  eError;
   clist_cell_s*  pTmpCell;

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

/**
   \fn CLIST_Error_e CLIST_RemoveNext(clist_s* pList)
   \brief Suppression de l'element suivant.
   \param[in,out] pList la liste circulaire
   \return  CLIST_NO_ERROR : la suppression a eut lieu.<br>
            CLIST_EMPTY_LIST : la liste est vide.
*/
CLIST_Error_e CLIST_RemoveNext(clist_s* pList)
{
   CLIST_Error_e  eError;
   clist_cell_s*  pTmpCell;

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

/**
   \fn CLIST_Error_e CLIST_RemovePrev(clist_s* pList)
   \brief Suppression de l'element precedent.
   \param[in,out] pList la liste circulaire
   \return  CLIST_NO_ERROR : la suppression a eut lieu.<br>
            CLIST_EMPTY_LIST : la liste est vide.
*/
CLIST_Error_e CLIST_RemovePrev(clist_s* pList)
{
   CLIST_Error_e  eError;
   clist_cell_s*  pTmpCell;

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

/**
   \fn clist_s* CLIST_Clone(const clist_s* pList, CLIST_Error_e* eError)
   \brief Duplication d'une liste.
   \param[in] pList la liste a dupliquer
   \param[out] eError le statut de la duplication:<br>
               CLIST_NO_ERROR : la copie s'est correctement deroulee.<br>
               CLIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire.
   \return La copie de la liste.
*/
clist_s* CLIST_Clone(const clist_s* pList, CLIST_Error_e* eError)
{
   clist_cell_s*  pCurrentCell = NULL;
   /* Creation de la liste clone */
   clist_s*       sDestList     = CLIST_Create(pList->mCompar, eError);

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
         } while(pCurrentCell != pList->pHead && *eError == CLIST_NO_ERROR);

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

/**
   \fn CLIST_Error_e CLIST_SearchData(clist_s* pList, const void* pData)
   \brief   Recherche d'un element dans la liste.<br>
            Si l'element est present, il devient le nouvel element courant de la liste.
   \param[in,out] pList la liste circulaire
   \param[in] pData la donnee recherchee
   \return  CLIST_NO_ERROR : l'element a ete trouve.<br>
            CLIST_EMPTY_LIST : la liste est vide.<br>
            CLIST_CELL_NOT_FOUND : l'element n'est pas present.<br>
            CLIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie.
*/
CLIST_Error_e CLIST_SearchData(clist_s* pList, const void* pData)
{
   /* CLIST_SearchData() n'est qu'une encapsulation de CLIST_SearchDataFct */
   return CLIST_SearchDataFct(pList, pData, NULL);
}

/**
   \fn CLIST_Error_e CLIST_SearchDataFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *))
   \brief   Recherche d'un element dans la liste.<br>
            Si l'element est present, il devient le nouvel element courant de la liste.
   \param[in,out] pList la liste circulaire
   \param[in] pData la donnee recherchee
   \param[in] compar la fonction de comparaison (si NULL la fonction par defaut est utilisee)
   \return  CLIST_NO_ERROR : l'element a ete trouve.<br>
            CLIST_EMPTY_LIST : la liste est vide.<br>
            CLIST_CELL_NOT_FOUND : l'element n'est pas present.<br>
            CLIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie.
*/
CLIST_Error_e CLIST_SearchDataFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *))
{
   CLIST_Error_e  eError;
   clist_cell_s*  pCurrentCell;
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
      } while(pCurrentCell != pList->pCurrent);
   }
   return eError;
}

/**
   \fn CLIST_Error_e CLIST_SearchDataRev(clist_s* pList, const void* pData)
   \brief   Recherche d'un element dans la liste.<br>
            La recherche s'effectue en remontant la liste.<br>
            Si l'element est present, il devient le nouvel element courant de la liste.
   \param[in,out] pList la liste circulaire
   \param[in] pData la donnee recherchee
   \return  CLIST_NO_ERROR : l'element a ete trouve.<br>
            CLIST_EMPTY_LIST : la liste est vide.<br>
            CLIST_CELL_NOT_FOUND : l'element n'est pas present.<br>
            CLIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie.
*/
CLIST_Error_e CLIST_SearchDataRev(clist_s* pList, const void* pData)
{
   /* CLIST_SearchDataRev() n'est qu'une encapsulation de CLIST_SearchDataRevFct */
   return CLIST_SearchDataRevFct(pList, pData, NULL);
}

/**
   \fn CLIST_Error_e CLIST_SearchDataRevFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *))
   \brief   Recherche d'un element dans la liste.<br>
            La recherche s'effectue en remontant la liste.<br>
            Si l'element est present, il devient le nouvel element courant de la liste.
   \param[in,out] pList la liste circulaire
   \param[in] pData la donnee recherchee
   \param[in] compar la fonction de comparaison (si NULL la fonction par defaut est utilisee)
   \return  CLIST_NO_ERROR : l'element a ete trouve.<br>
            CLIST_EMPTY_LIST : la liste est vide.<br>
            CLIST_CELL_NOT_FOUND : l'element n'est pas present.<br>
            CLIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie.
*/
CLIST_Error_e CLIST_SearchDataRevFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *))
{
   CLIST_Error_e  eError;
   clist_cell_s*  pCurrentCell;
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
      } while(pCurrentCell != pList->pCurrent);
   }
   return eError;
}

/**
   \fn CLIST_Error_e CLIST_RemoveData(clist_s* pList, const void* pData)
   \brief   Supression de la premiere cellule contenant la donnee recherchee.<br>
            Si l'element courant correspond au critere de recherche, l'element suivant devient le nouvel element courant.
   \param[in,out] pList la liste circulaire
   \param[in] pData la donnee a supprimee
   \return  CLIST_NO_ERROR : l'element a ete suppime.<br>
            CLIST_EMPTY_LIST : la liste est vide.<br>
            CLIST_CELL_NOT_FOUND : l'element n'est pas present.<br>
            CLIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie.
*/
CLIST_Error_e CLIST_RemoveData(clist_s* pList, const void* pData)
{
   /* CLIST_RemoveData() n'est qu'une encapsulation de CLIST_RemoveData() */
   return CLIST_RemoveDataFct(pList, pData, NULL);
}

/**
   \fn CLIST_Error_e CLIST_RemoveDataFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *))
   \brief   Supression de la premiere cellule contenant la donnee recherchee.<br>
            Si l'element courant correspond au critere de recherche, l'element suivant devient le nouvel element courant.
   \param[in,out] pList la liste circulaire
   \param[in] pData la donnee a supprimee
   \param[in] compar la fonction de comparaison (si NULL la fonction par defaut est utilisee)
   \return  CLIST_NO_ERROR : l'element a ete suppime.<br>
            CLIST_EMPTY_LIST : la liste est vide.<br>
            CLIST_CELL_NOT_FOUND : l'element n'est pas present.<br>
            CLIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie.
*/
CLIST_Error_e CLIST_RemoveDataFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *))
{
   CLIST_Error_e  eError;
   clist_cell_s*  pCurrentCell = pList->pCurrent;
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

/**
   \fn CLIST_Error_e CLIST_RemoveDataRev(clist_s* pList, const void* pData)
   \brief   Supression de la premiere cellule contenant la donnee recherchee.<br>
            La recherche s'effectue en remontant la liste.<br>
            Si l'element courant correspond au critere de recherche, l'element suivant devient le nouvel element courant.
   \param[in,out] pList la liste circulaire
   \param[in] pData la donnee a supprimee
   \return  CLIST_NO_ERROR : l'element a ete suppime.<br>
            CLIST_EMPTY_LIST : la liste est vide.<br>
            CLIST_CELL_NOT_FOUND : l'element n'est pas present.<br>
            CLIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie.
*/
CLIST_Error_e CLIST_RemoveDataRev(clist_s* pList, const void* pData)
{
   /* CLIST_RemoveData() n'est qu'une encapsulation de CLIST_RemoveData() */
   return CLIST_RemoveDataRevFct(pList, pData, NULL);
}

/**
   \fn CLIST_Error_e CLIST_RemoveDataRevFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *))
   \brief   Supression de la premiere cellule contenant la donnee recherchee.<br>
            La recherche s'effectue en remontant la liste.<br>
            Si l'element courant correspond au critere de recherche, l'element suivant devient le nouvel element courant.
   \param[in,out] pList la liste circulaire
   \param[in] pData la donnee a supprimee
   \param[in] compar la fonction de comparaison (si NULL la fonction par defaut est utilisee)
   \return  CLIST_NO_ERROR : l'element a ete suppime.<br>
            CLIST_EMPTY_LIST : la liste est vide.<br>
            CLIST_CELL_NOT_FOUND : l'element n'est pas present.<br>
            CLIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie.
*/
CLIST_Error_e CLIST_RemoveDataRevFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *))
{
   CLIST_Error_e  eError;
   clist_cell_s*  pCurrentCell = pList->pCurrent;
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

/**
   \fn CLIST_Error_e CLIST_RemoveAllData(clist_s* pList, const void* pData)
   \brief   Suppression de toutes les cellules contenant la donnee recherchee.
            Si l'element courant correspond au critere de recherche, l'element suivant devient le nouvel element courant.
   \param[in,out] pList la liste circulaire
   \param[in] pData la donnee a supprimee
   \return  CLIST_NO_ERROR : l'element a ete suppime.<br>
            CLIST_EMPTY_LIST : la liste est vide.<br>
            CLIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie.
*/
CLIST_Error_e CLIST_RemoveAllData(clist_s* pList, const void* pData)
{
   /* CLIST_RemoveAllData() n'est qu'une encapsulation de CLIST_RemoveAllDataFct() */
   return CLIST_RemoveAllDataFct(pList, pData, NULL);
}

/**
   \fn CLIST_Error_e CLIST_RemoveAllDataFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *))
   \brief   Suppression de toutes les cellules contenant la donnee recherchee.
            Si l'element courant correspond au critere de recherche, l'element suivant devient le nouvel element courant.
   \param[in,out] pList la liste circulaire
   \param[in] pData la donnee a supprimee
   \param[in] compar la fonction de comparaison (si NULL la fonction par defaut est utilisee)
   \return  CLIST_NO_ERROR : l'element a ete suppime.<br>
            CLIST_EMPTY_LIST : la liste est vide.<br>
            CLIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie.
*/
CLIST_Error_e CLIST_RemoveAllDataFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *))
{
   CLIST_Error_e  eError = CLIST_NO_ERROR;

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
