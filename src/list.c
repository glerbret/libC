/**
   \author Gregory Lerbret
   \file list.c
   \brief Gestion de listes.<br>
   \date 24/09/2006
   \version 1.0.0
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bool.h"
#include "list.h"

#define xstr(s) str(s)
#define str(s) #s

#define LIST_NAME	         "Gestion de liste"
#define LIST_VERS_MAJ      1
#define LIST_VERS_MIN      0
#define LIST_VERS_BRCH     0
#define LIST_ID            LIST_NAME " - Version " xstr(LIST_VERS_MAJ) "." xstr(LIST_VERS_MIN) "." xstr(LIST_VERS_BRCH)

/**
   \struct list_cell_s
   \brief Structure d'une cellule de la liste
*/
typedef struct list_cell
{
/**
   \brief pointeur sur la cellule suivante
*/
   struct list_cell*       pNext;
/**
   \brief pointeur sur la cellule precedente
*/
   struct list_cell*       pPrev;
/**
   \brief pointeur sur la zone de donnee
*/
   void*                   pData;
/**
   \brief taille de la zone de donnee
*/
   size_t                  szDataSize;
} list_cell_s;

/**
   \struct list_s
   \brief Structure de la liste
*/
struct list
{
/**
   \brief Pointeur sur la tete de la liste
*/
   list_cell_s*         pHead;
/**
   \brief Pointeur sur la fin de la liste
*/
   list_cell_s*         pTail;
/**
   \brief Pointeur sur l'element courant de la liste
*/
   list_cell_s*         pCurrent;
/**
   \brief Nombre d'element de la liste
*/
   size_t               szNbCells;
/**
   \brief Fonction de comparaison des elements de la liste
*/
   int (*mCompar)(const void *, const void *);
};

/**
   \fn LIST_Cell* LIST_AllocCell(const void* pData, size_t szDataSize)
   \brief Allocation et initialisation d'une cellule.
   \param[in] pData l'element a ajouter a la liste
   \param[in] szDataSize la taille de l'element
   \return la cellule allouee (NULL en cas d'erreur).
*/
static list_cell_s* LIST_AllocCell(const void* pData, size_t szDataSize)
{
   list_cell_s*   pCell = NULL;

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
   \fn LIST_Cell* LIST_DetachCell(list_s* pList, LIST_Cell* pCellToDelete)
   \brief Retrait d'une cellule de la liste.
   \param[in] pList la liste
   \param[in] pCellToDelete la cellule a supprimmer
   \return la cellule detachee de la pile (NULL en cas d'erreur)
*/
static list_cell_s* LIST_DetachCell(list_s* pList, list_cell_s* pCellToDelete)
{
   list_cell_s*   pCell = NULL;

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

/**
   \fn const char* LIST_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char* LIST_Identifier(void)
{
   return LIST_ID;
}

/**
   \fn int LIST_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int LIST_Version(void)
{
   return LIST_VERS_MAJ*10000 + LIST_VERS_MIN*100 + LIST_VERS_BRCH;
}

/**
   \fn list_s* LIST_Create(int (*compar)(const void *, const void *), LIST_Error_e* eError)
   \brief Creation d'une liste.
   \param[in] compar la fonction de comparaison des elements
   \param[out] eError le resultat de la creation :<br>
      CLIST_NO_ERROR : la creation s'est correctement deroulee.<br>
      CLIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire.
   \return  La liste (NULL en cas d'erreur).
*/
list_s* LIST_Create(int (*compar)(const void *, const void *), LIST_Error_e* eError)
{
   list_s*  pList = malloc(sizeof *pList);

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

/**
   \fn void LIST_Destroy(list_s* pList)
   \brief Destruction d'une liste.
   \param[in,out] pList la liste
*/
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

/**
   \fn void LIST_SetCmp(list_s* pList, int (*compar)(const void *, const void *))
   \brief Mise a jour de la fonction de comparaison.
   \param[in,out] pList la liste
   \param[in] compar la fonction de comparaison
*/
void LIST_SetCmp(list_s* pList, int (*compar)(const void *, const void *))
{
   pList->mCompar = compar;
}

/**
   \fn bool LIST_IsEmpty(const list_s* pList)
   \brief Verification de la vacuite de la liste.
   \param[in] pList la liste
   \return  true si la liste est vide.<br>
            false sinon.
*/
bool LIST_IsEmpty(const list_s* pList)
{
   return pList->pHead == NULL ? true : false;
}

/**
   \fn size_t LIST_Size(const list_s* pList)
   \brief Calcul du nombre d'element de la liste.
   \param[in] pList la liste
   \return Le nombre d'element de la liste.
*/
size_t LIST_Size(const list_s* pList)
{
   return pList->szNbCells;
}

/**
   \fn bool LIST_IsHead(const list_s* pList)
   \brief Verification si l'element courant est le premier.
   \param[in] pList la liste
   \return  true si l'element est le premier de la liste.<br>
            false sinon.
*/
bool LIST_IsHead(const list_s* pList)
{
   bool     bIsHead = false;

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

/**
   \fn bool LIST_IsTail(const list_s* pList)
   \brief Verification si l'element courant est le dernier.
   \param[in] pList la liste
   \return  true si l'element est le dernier de la liste.<br>
            false sinon.
*/
bool LIST_IsTail(const list_s* pList)
{
   bool     bIsTail = false;

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

/**
   \fn LIST_Error_e LIST_InsertFirst(list_s* pList, const void* pData, size_t szDataSize)
   \brief   Insertion d'un element en tete de liste.<br>
            L'element insere devient l'element courant.
   \param[in,out] pList la liste
   \param[in] pData l'element a ajouter
   \param[in] szDataSize la taille de l'element
   \return  LIST_NO_ERROR : l'insertion s'est correctement deroulee.<br>
            LIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire ou il n'existe pas de donnee a inserer.
*/
LIST_Error_e LIST_InsertFirst(list_s* pList, const void* pData, size_t szDataSize)
{
   list_cell_s*   pCell    = LIST_AllocCell(pData, szDataSize);
   LIST_Error_e   eError   = LIST_NO_ERROR;

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

/**
   \fn LIST_Error_e LIST_InsertLast(list_s* pList, const void* pData, size_t szDataSize)
   \brief   Insertion d'un element en fin de liste.<br>
            L'element insere devient l'element courant.
   \param[in,out] pList la liste
   \param[in] pData l'element a ajouter
   \param[in] szDataSize la taille de l'element
   \return  LIST_NO_ERROR : l'insertion s'est correctement deroulee.<br>
            LIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire ou il n'existe pas de donnee a inserer.
*/
LIST_Error_e LIST_InsertLast(list_s* pList, const void* pData, size_t szDataSize)
{
   list_cell_s*   pCell    = LIST_AllocCell(pData, szDataSize);
   LIST_Error_e   eError   = LIST_NO_ERROR;

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

/**
   \fn LIST_Error_e LIST_InsertNext(list_s* pList, const void* pData, size_t szDataSize)
   \brief   Insertion d'un element dans liste apres l'element courant.<br>
            L'element insere devient l'element courant.
   \param[in,out] pList la liste
   \param[in] pData l'element a ajouter
   \param[in] szDataSize la taille de l'element
   \return  LIST_NO_ERROR : l'insertion s'est correctement deroulee.<br>
            LIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire ou il n'existe pas de donnee a inserer.
*/
LIST_Error_e LIST_InsertNext(list_s* pList, const void* pData, size_t szDataSize)
{
   list_cell_s*   pCell    = LIST_AllocCell(pData, szDataSize);
   LIST_Error_e   eError   = LIST_NO_ERROR;

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

/**
   \fn LIST_Error_e LIST_InsertPrev(list_s* pList, const void* pData, size_t szDataSize)
   \brief   Insertion d'un element dans liste avant l'element courant.<br>
            L'element insere devient l'element courant.
   \param[in,out] pList la lise
   \param[in] pData l'element a ajouter
   \param[in] szDataSize la taille de l'element
   \return  LIST_NO_ERROR : l'insertion s'est correctement deroulee.<br>
            LIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire ou il n'existe pas de donnee a inserer.
*/
LIST_Error_e LIST_InsertPrev(list_s* pList, const void* pData, size_t szDataSize)
{
   list_cell_s*   pCell    = LIST_AllocCell(pData, szDataSize);
   LIST_Error_e   eError   = LIST_NO_ERROR;

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

/**
   \fn LIST_Error_e LIST_SeekFirst(list_s* pList)
   \brief Deplacement sur le premier element.
   \param[in,out] pList la liste
   \return  LIST_NO_ERROR : le deplacement s'est correctement deroule.<br>
            LIST_EMPTY_LIST : la liste est vide.
*/
LIST_Error_e LIST_SeekFirst(list_s* pList)
{
   LIST_Error_e   eError;

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

/**
   \fn LIST_Error_e LIST_SeekLast(list_s* pList)
   \brief Deplacement sur le dernier element.
   \param[in,out] pList la liste
   \return  LIST_NO_ERROR : le deplacement s'est correctement deroule.<br>
            LIST_EMPTY_LIST : la liste est vide.
*/
LIST_Error_e LIST_SeekLast(list_s* pList)
{
   LIST_Error_e   eError;

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

/**
   \fn LIST_Error_e LIST_SeekNext(list_s* pList)
   \brief Deplacement sur l'element suivant.
   \param[in,out] pList la liste
   \return  LIST_NO_ERROR : le deplacement s'est correctement deroule.<br>
            LIST_EMPTY_LIST : la liste est vide.<br>
            LIST_CELL_NOT_FOUND : l'element courant est le dernier.
*/
LIST_Error_e LIST_SeekNext(list_s* pList)
{
   LIST_Error_e   eError;

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

/**
   \fn LIST_Error_e LIST_SeekPrev(list_s* pList)
   \brief Deplacement sur l'element precedent.
   \param[in,out] pList la liste
   \return  LIST_NO_ERROR : le deplacement s'est correctement deroule.<br>
            LIST_EMPTY_LIST : la liste est vide.<br>
            LIST_CELL_NOT_FOUND : l'element courant est le premier.
*/
LIST_Error_e LIST_SeekPrev(list_s* pList)
{
   LIST_Error_e   eError;

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

/**
   \fn const void* LIST_ReadFirst(const list_s* pList, LIST_Error_e* eError)
   \brief Lecture du premier element.
   \param[in] pList la liste
   \param[out] eError le resultat de la lecture:<br>
               LIST_NO_ERROR : la lecture a eut lieu.<br>
               LIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void* LIST_ReadFirst(const list_s* pList, LIST_Error_e* eError)
{
   void*    pData = NULL;

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

/**
   \fn const void* LIST_ReadLast(const list_s* pList, LIST_Error_e* eError)
   \brief Lecture du dernier element.
   \param[in] pList la liste
   \param[out] eError le resultat de la lecture:<br>
               LIST_NO_ERROR : la lecture a eut lieu.<br>
               LIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void* LIST_ReadLast(const list_s* pList, LIST_Error_e* eError)
{
   void*    pData = NULL;

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

/**
   \fn const void* LIST_ReadCurrent(const list_s* pList, LIST_Error_e* eError)
   \brief Lecture de l'element courant.
   \param[in] pList la liste
   \param[out] eError le resultat de la lecture:<br>
               LIST_NO_ERROR : la lecture a eut lieu.<br>
               LIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void* LIST_ReadCurrent(const list_s* pList, LIST_Error_e* eError)
{
   void*    pData = NULL;

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

/**
   \fn const void* LIST_ReadNext(const list_s* pList, LIST_Error_e* eError)
   \brief Lecture de l'element suivant.
   \param[in] pList la liste
   \param[out] eError le resultat de la lecture:<br>
               LIST_NO_ERROR : la lecture a eut lieu.<br>
               LIST_EMPTY_LIST : la liste est vide.<br>
               LIST_CELL_NOT_FOUND : l'element courant est le dernier de la liste.
   \return L'element lu (NULL en cas d'erreur).
*/
const void* LIST_ReadNext(const list_s* pList, LIST_Error_e* eError)
{
   void*    pData = NULL;

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

/**
   \fn const void* LIST_ReadPrev(const list_s* pList, LIST_Error_e* eError)
   \brief Lecture de l'element precedent.
   \param[in] pList la liste
   \param[out] eError le resultat de la lecture:<br>
               LIST_NO_ERROR : la lecture a eut lieu.<br>
               LIST_EMPTY_LIST : la liste est vide.<br>
               LIST_CELL_NOT_FOUND : l'element courant est le premier de la liste.
   \return L'element lu (NULL en cas d'erreur).
*/
const void* LIST_ReadPrev(const list_s* pList, LIST_Error_e* eError)
{
   void*    pData = NULL;

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

/**
   \fn const void* LIST_GetFirst(list_s* pList, LIST_Error_e* eError)
   \brief   Lecture et suppression du premier element.<br>
            Si cet element était l'element courant, l'element suivant devient le nouvel element courant.
   \param[in,out] pList la liste
   \param[out] eError resultat de la lecture:<br>
               LIST_NO_ERROR : la lecture a eut lieu.<br>
               LIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void* LIST_GetFirst(list_s* pList, LIST_Error_e* eError)
{
   void*          pData    = NULL;
   list_cell_s*   pTmpCell = NULL;

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

/**
   \fn const void* LIST_GetLast(list_s* pList, LIST_Error_e* eError)
   \brief   Lecture et suppression du dernier element.<br>
            Si cet element était l'element courant, l'element precedent devient le nouvel element courant.
   \param[in,out] pList la liste
   \param[out] eError resultat de la lecture:<br>
               LIST_NO_ERROR : la lecture a eut lieu.<br>
               LIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void* LIST_GetLast(list_s* pList, LIST_Error_e* eError)
{
   void*          pData = NULL;
   list_cell_s*   pTmpCell;

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

/**
   \fn const void* LIST_GetCurrent(list_s* pList, LIST_Error_e* eError)
   \brief Lecture et suppression de l'element courant.<br>
          L'element suivant (ou l'element precedent si l'element courant etait le dernier de la liste) devient l'element courant.
   \param[in,out] pList la liste
   \param[out] eError resultat de la lecture:<br>
               LIST_NO_ERROR : la lecture a eut lieu.<br>
               LIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void* LIST_GetCurrent(list_s* pList, LIST_Error_e* eError)
{
   void*          pData    = NULL;
   list_cell_s*   pTmpCell = NULL;

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

/**
   \fn const void* LIST_GetNext(list_s* pList, LIST_Error_e* eError)
   \brief Lecture et suppression de l'element suivant.
   \param[in,out] pList la liste
   \param[out] eError resultat de la lecture:<br>
               LIST_NO_ERROR : la lecture a eut lieu.<br>
               LIST_EMPTY_LIST : la liste est vide.<br>
               LIST_CELL_NOT_FOUND : l'element courant est le dernier de la liste.
   \return L'element lu (NULL en cas d'erreur).
*/
const void* LIST_GetNext(list_s* pList, LIST_Error_e* eError)
{
   void*          pData = NULL;
   list_cell_s*   pTmpCell;

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

/**
   \fn const void* LIST_GetPrev(list_s* pList, LIST_Error_e* eError)
   \brief Lecture et suppression de l'element precedent.
   \param[in,out] pList la liste
   \param[out] eError resultat de la lecture:<br>
               LIST_NO_ERROR : la lecture a eut lieu.<br>
               LIST_EMPTY_LIST : la liste est vide.<br>
               LIST_CELL_NOT_FOUND : l'element courant est le premier de la liste.
   \return L'element lu (NULL en cas d'erreur).
*/
const void* LIST_GetPrev(list_s* pList, LIST_Error_e* eError)
{
   void*          pData = NULL;
   list_cell_s*   pTmpCell;

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

/**
   \fn LIST_Error_e LIST_RemoveFirst(list_s* pList)
   \brief   Suppression du premier element.<br>
            Si cet element était l'element courant, l'element suivant devient le nouvel element courant.
   \param[in,out] pList la liste
   \return  LIST_NO_ERROR : la suppression a eut lieu.<br>
            LIST_EMPTY_LIST : la liste est vide.
*/
LIST_Error_e LIST_RemoveFirst(list_s* pList)
{
   LIST_Error_e   eError;
   list_cell_s*   pTmpCell;

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

/**
   \fn LIST_Error_e LIST_RemoveLast(list_s* pList)
   \brief   Suppression du dernier element.<br>
            Si cet element était l'element courant, l'element precedent devient le nouvel element courant.
   \param[in,out] pList la liste
   \return  LIST_NO_ERROR : la suppression a eut lieu.<br>
            LIST_EMPTY_LIST : la liste est vide.
*/
LIST_Error_e LIST_RemoveLast(list_s* pList)
{
   LIST_Error_e   eError;
   list_cell_s*   pTmpCell;

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

/**
   \fn LIST_Error_e LIST_RemoveCurrent(list_s* pList)
   \brief   Suppression de l'element courant.<br>
            L'element suivant (ou precedent si l'element courant est le dernier de la liste) devient l'element courant.
   \param[in,out] pList la liste
   \return  LIST_NO_ERROR : la suppression a eut lieu.<br>
            LIST_EMPTY_LIST : la liste est vide.
*/
LIST_Error_e LIST_RemoveCurrent(list_s* pList)
{
   LIST_Error_e   eError;
   list_cell_s*   pTmpCell;

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

/**
   \fn LIST_Error_e LIST_RemoveNext(list_s* pList)
   \brief Suppression de l'element suivant.
   \param[in,out] pList la liste
   \return  LIST_NO_ERROR : la suppression a eut lieu.<br>
            LIST_EMPTY_LIST : la liste est vide.<br>
            LIST_CELL_NOT_FOUND : l'element courant est le dernier de la liste.
*/
LIST_Error_e LIST_RemoveNext(list_s* pList)
{
   LIST_Error_e   eError;
   list_cell_s*   pTmpCell;

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

/**
   \fn LIST_Error_e LIST_RemovePrev(list_s* pList)
   \brief Suppression de l'element precedent.
   \param[in,out] pList la liste
   \return  LIST_NO_ERROR : la suppression a eut lieu.<br>
            LIST_EMPTY_LIST : la liste est vide.<br>
            LIST_CELL_NOT_FOUND : l'element courant est le premier de la liste.
*/
LIST_Error_e LIST_RemovePrev(list_s* pList)
{
   LIST_Error_e   eError;
   list_cell_s*   pTmpCell;

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

/**
   \fn list_s* LIST_Clone(const list_s* pList, LIST_Error_e* eError)
   \brief Duplication d'une liste.
   \param[in] pList la liste a dupliquer
   \param[out] eError le statut de la duplication:<br>
               LIST_NO_ERROR : la copie s'est correctement deroulee.<br>
               LIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire.
   \return La copie de la liste.
*/
list_s* LIST_Clone(const list_s* pList, LIST_Error_e* eError)
{
   list_cell_s*   pCurrentCell = NULL;
   /* Creation de la liste clone */
   list_s*        sDestList     = LIST_Create(pList->mCompar, eError);

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

/**
   \fn LIST_Error_e LIST_SearchData(list_s* pList, const void* pData)
   \brief   Recherche d'un element dans la liste apres l'element courant.<br>
            Si l'element est present, il devient le nouvel element courant de la liste.
   \param[in,out] pList la liste
   \param[in] pData la donnee recherchee
   \return  LIST_NO_ERROR : l'element a ete trouve.<br>
            LIST_EMPTY_LIST : la liste est vide.<br>
            LIST_CELL_NOT_FOUND : l'element n'est pas present.<br>
            LIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie.
*/
LIST_Error_e LIST_SearchData(list_s* pList, const void* pData)
{
   /* LIST_SearchData() n'est qu'une encapsulation de LIST_SearchDataFct */
   return LIST_SearchDataFct(pList, pData, NULL);
}

/**
   \fn LIST_Error_e LIST_SearchDataFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *))
   \brief   Recherche d'un element dans la liste apres l'element courant.<br>
            Si l'element est present, il devient le nouvel element courant de la liste.
   \param[in,out] pList la liste
   \param[in] pData la donnee recherchee
   \param[in] compar la fonction de comparaison (si NULL la fonction par defaut est utilisee)
   \return  LIST_NO_ERROR : l'element a ete trouve.<br>
            LIST_EMPTY_LIST : la liste est vide.<br>
            LIST_CELL_NOT_FOUND : l'element n'est pas present.<br>
            LIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie.
*/
LIST_Error_e LIST_SearchDataFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *))
{
   LIST_Error_e   eError;
   list_cell_s*   pCurrentCell;
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

/**
   \fn LIST_Error_e LIST_SearchDataRev(list_s* pList, const void* pData)
   \brief   Recherche d'un element dans la liste avant l'element courant.<br>
            Si l'element est present, il devient le nouvel element courant de la liste.
   \param[in,out] pList la liste
   \param[in] pData la donnee recherchee
   \return  LIST_NO_ERROR : l'element a ete trouve.<br>
            LIST_EMPTY_LIST : la liste est vide.<br>
            LIST_CELL_NOT_FOUND : l'element n'est pas present.<br>
            LIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie.
*/
LIST_Error_e LIST_SearchDataRev(list_s* pList, const void* pData)
{
   /* LIST_SearchDataRev() n'est qu'une encapsulation de LIST_SearchDataRevFct */
   return LIST_SearchDataRevFct(pList, pData, NULL);
}

/**
   \fn LIST_Error_e LIST_SearchDataRevFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *))
   \brief   Recherche d'un element dans la liste avant l'element courant.<br>
            Si l'element est present, il devient le nouvel element courant de la liste.
   \param[in,out] pList la liste
   \param[in] pData la donnee recherchee
   \param[in] compar la fonction de comparaison (si NULL la fonction par defaut est utilisee)
   \return  LIST_NO_ERROR : l'element a ete trouve.<br>
            LIST_EMPTY_LIST : la liste est vide.<br>
            LIST_CELL_NOT_FOUND : l'element n'est pas present.<br>
            LIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie.
*/
LIST_Error_e LIST_SearchDataRevFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *))
{
   LIST_Error_e   eError;
   list_cell_s*   pCurrentCell;
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

/**
   \fn LIST_Error_e LIST_RemoveData(list_s* pList, const void* pData)
   \brief   Supression de la premiere cellule situee apres l'element courant contenant la donnee recherchee.<br>
            Si l'element courant correspond au critere de recherche, l'element suivant (ou l'element precedent
            si l'element courant est le dernier de la liste) devient le nouvel element courant.
   \param[in,out] pList la liste
   \param[in] pData la donnee a supprimee
   \return  LIST_NO_ERROR : l'element a ete suppime.<br>
            LIST_EMPTY_LIST : la liste est vide.<br>
            LIST_CELL_NOT_FOUND : l'element n'est pas present.<br>
            LIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie.
*/
LIST_Error_e LIST_RemoveData(list_s* pList, const void* pData)
{
   /* LIST_RemoveData() n'est qu'une encapsulation de LIST_RemoveData() */
   return LIST_RemoveDataFct(pList, pData, NULL);
}

/**
   \fn LIST_Error_e LIST_RemoveDataFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *))
   \brief   Supression de la premiere cellule situee apres l'element courant contenant la donnee recherchee.<br>
            Si l'element courant correspond au critere de recherche, l'element suivant (ou l'element precedent
            si l'element courant est le dernier de la liste) devient le nouvel element courant.
   \param[in,out] pList la liste
   \param[in] pData la donnee a supprimee
   \param[in] compar la fonction de comparaison (si NULL la fonction par defaut est utilisee)
   \return  LIST_NO_ERROR : l'element a ete suppime.<br>
            LIST_EMPTY_LIST : la liste est vide.<br>
            LIST_CELL_NOT_FOUND : l'element n'est pas present.<br>
            LIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie.
*/
LIST_Error_e LIST_RemoveDataFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *))
{
   LIST_Error_e   eError;
   list_cell_s*   pCurrentCell = pList->pCurrent;
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

/**
   \fn LIST_Error_e LIST_RemoveDataRev(list_s* pList, const void* pData)
   \brief   Supression de la premiere cellule situee avant l'element courant contenant la donnee recherchee.<br>
            Si l'element courant correspond au critere de recherche, l'element suivant (ou l'element precedent
            si l'element courant est le dernier de la liste) devient le nouvel element courant.
   \param[in,out] pList la liste
   \param[in] pData la donnee a supprimee
   \return  LIST_NO_ERROR : l'element a ete suppime.<br>
            LIST_EMPTY_LIST : la liste est vide.<br>
            LIST_CELL_NOT_FOUND : l'element n'est pas present.<br>
            LIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie.
*/
LIST_Error_e LIST_RemoveDataRev(list_s* pList, const void* pData)
{
   /* LIST_RemoveData() n'est qu'une encapsulation de LIST_RemoveData() */
   return LIST_RemoveDataRevFct(pList, pData, NULL);
}

/**
   \fn LIST_Error_e LIST_RemoveDataRevFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *))
   \brief   Supression de la premiere cellule situee avant l'element courant contenant la donnee recherchee.<br>
            Si l'element courant correspond au critere de recherche, l'element suivant (ou l'element precedent
            si l'element courant est le dernier de la liste) devient le nouvel element courant.
   \param[in,out] pList la liste
   \param[in] pData la donnee a supprimee
   \param[in] compar la fonction de comparaison (si NULL la fonction par defaut est utilisee)
   \return  LIST_NO_ERROR : l'element a ete suppime.<br>
            LIST_EMPTY_LIST : la liste est vide.<br>
            LIST_CELL_NOT_FOUND : l'element n'est pas present.<br>
            LIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie.
*/
LIST_Error_e LIST_RemoveDataRevFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *))
{
   LIST_Error_e   eError;
   list_cell_s*   pCurrentCell = pList->pCurrent;
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

/**
   \fn LIST_Error_e LIST_RemoveAllData(list_s* pList, const void* pData)
   \brief   Suppression de toutes les cellules contenant la donnee recherchee.
            Si l'element courant correspond au critere de recherche, l'element suivant (ou l'element precedent
            si l'element courant est le dernier) devient le nouvel element courant.
   \param[in,out] pList la liste
   \param[in] pData la donnee a supprimee
   \return  LIST_NO_ERROR : l'element a ete suppime.<br>
            LIST_EMPTY_LIST : la liste est vide.<br>
            LIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie.
*/
LIST_Error_e LIST_RemoveAllData(list_s* pList, const void* pData)
{
   /* LIST_RemoveAllData() n'est qu'une encapsulation de LIST_RemoveAllDataFct() */
   return LIST_RemoveAllDataFct(pList, pData, NULL);
}

/**
      \fn LIST_Error_e LIST_RemoveAllDataFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *))
   \brief   Suppression de toutes les cellules contenant la donnee recherchee.
            Si l'element courant correspond au critere de recherche, l'element suivant (ou l'element precedent
            si l'element courant est le dernier) devient le nouvel element courant.
   \param[in,out] pList la liste
   \param[in] pData la donnee a supprimee
   \param[in] compar la fonction de comparaison (si NULL la fonction par defaut est utilisee)
   \return  LIST_NO_ERROR : l'element a ete suppime.<br>
            LIST_EMPTY_LIST : la liste est vide.<br>
            LIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie.
   LIST_NO_COMP_FONCTION : il n'y a pas de fonction de comparaison de definie
*/
LIST_Error_e LIST_RemoveAllDataFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *))
{
   LIST_Error_e   eError = LIST_NO_ERROR;

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
