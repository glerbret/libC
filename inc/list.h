/**
   \author Gregory Lerbret
   \file list.h
   \brief Gestion de listes.<br>
   \date 24/09/2006
   \version 1.0.0
*/

#ifndef GL_LIST_H
#define GL_LIST_H

#include <stddef.h>
#include "bool.h"

/**
   \struct list_s
   \brief La liste
*/
typedef struct list list_s;

/**
   \enum LIST_Error_e
   \brief Resultat des traitements sur les listes
*/
typedef enum
{
/**
   \brief Pas d'erreur
*/
   LIST_NO_ERROR,
/**
   \brief Erreur d'allocation
*/
   LIST_MEMORY_ERROR,
/**
   \brief La liste est vide
*/
   LIST_EMPTY_LIST,
/**
   \brief Element absent
*/
   LIST_CELL_NOT_FOUND,
/**
   \brief Aucune fonction de comparaison n'est definie
*/
   LIST_NO_COMP_FONCTION
} LIST_Error_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
   \fn const char* LIST_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char*    LIST_Identifier(void);

/**
   \fn int LIST_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int            LIST_Version(void);

/**
   \fn list_s* LIST_Create(int (*compar)(const void *, const void *), LIST_Error_e* eError)
   \brief Creation d'une liste.
   \param[in] compar la fonction de comparaison des elements
   \param[out] eError le resultat de la creation :<br>
      CLIST_NO_ERROR : la creation s'est correctement deroulee.<br>
      CLIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire.
   \return  La liste (NULL en cas d'erreur).
*/
list_s*        LIST_Create(int (*compar)(const void *, const void *), LIST_Error_e* eError);

/**
   \fn void LIST_Destroy(list_s* pList)
   \brief Destruction d'une liste.
   \param[in,out] pList la liste
*/
void           LIST_Destroy(list_s* pList);

/**
   \fn void LIST_SetCmp(list_s* pList, int (*compar)(const void *, const void *))
   \brief Mise a jour de la fonction de comparaison.
   \param[in,out] pList la liste
   \param[in] compar la fonction de comparaison
*/
void           LIST_SetCmp(list_s* pList, int (*compar)(const void *, const void *));

/**
   \fn bool LIST_IsEmpty(const list_s* pList)
   \brief Verification de la vacuite de la liste.
   \param[in] pList la liste
   \return  true si la liste est vide.<br>
            false sinon.
*/
bool           LIST_IsEmpty(const list_s* pList);

/**
   \fn size_t LIST_Size(const list_s* pList)
   \brief Calcul du nombre d'element de la liste.
   \param[in] pList la liste
   \return Le nombre d'element de la liste.
*/
size_t         LIST_Size(const list_s* pList);

/**
   \fn bool LIST_IsHead(const list_s* pList)
   \brief Verification si l'element courant est le premier.
   \param[in] pList la liste
   \return  true si l'element est le premier de la liste.<br>
            false sinon.
*/
bool           LIST_IsHead(const list_s* pList);

/**
   \fn bool LIST_IsTail(const list_s* pList)
   \brief Verification si l'element courant est le dernier.
   \param[in] pList la liste
   \return  true si l'element est le dernier de la liste.<br>
            false sinon.
*/
bool           LIST_IsTail(const list_s* pList);

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
LIST_Error_e   LIST_InsertFirst(list_s* pList, const void* pData, size_t szDataSize);

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
LIST_Error_e   LIST_InsertLast(list_s* pList, const void* pData, size_t szDataSize);

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
LIST_Error_e   LIST_InsertNext(list_s* pList, const void* pData, size_t szDataSize);

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
LIST_Error_e   LIST_InsertPrev(list_s* pList, const void* pData, size_t szDataSize);

/**
   \fn LIST_Error_e LIST_SeekFirst(list_s* pList)
   \brief Deplacement sur le premier element.
   \param[in,out] pList la liste
   \return  LIST_NO_ERROR : le deplacement s'est correctement deroule.<br>
            LIST_EMPTY_LIST : la liste est vide.
*/
LIST_Error_e   LIST_SeekFirst(list_s* pList);

/**
   \fn LIST_Error_e LIST_SeekLast(list_s* pList)
   \brief Deplacement sur le dernier element.
   \param[in,out] pList la liste
   \return  LIST_NO_ERROR : le deplacement s'est correctement deroule.<br>
            LIST_EMPTY_LIST : la liste est vide.
*/
LIST_Error_e   LIST_SeekLast(list_s* pList);

/**
   \fn LIST_Error_e LIST_SeekNext(list_s* pList)
   \brief Deplacement sur l'element suivant.
   \param[in,out] pList la liste
   \return  LIST_NO_ERROR : le deplacement s'est correctement deroule.<br>
            LIST_EMPTY_LIST : la liste est vide.<br>
            LIST_CELL_NOT_FOUND : l'element courant est le dernier.
*/
LIST_Error_e   LIST_SeekNext(list_s* pList);

/**
   \fn LIST_Error_e LIST_SeekPrev(list_s* pList)
   \brief Deplacement sur l'element precedent.
   \param[in,out] pList la liste
   \return  LIST_NO_ERROR : le deplacement s'est correctement deroule.<br>
            LIST_EMPTY_LIST : la liste est vide.<br>
            LIST_CELL_NOT_FOUND : l'element courant est le premier.
*/
LIST_Error_e   LIST_SeekPrev(list_s* pList);

/**
   \fn const void* LIST_ReadFirst(const list_s* pList, LIST_Error_e* eError)
   \brief Lecture du premier element.
   \param[in] pList la liste
   \param[out] eError le resultat de la lecture:<br>
               LIST_NO_ERROR : la lecture a eut lieu.<br>
               LIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void*    LIST_ReadFirst(const list_s* pList, LIST_Error_e* eError);

/**
   \fn const void* LIST_ReadLast(const list_s* pList, LIST_Error_e* eError)
   \brief Lecture du dernier element.
   \param[in] pList la liste
   \param[out] eError le resultat de la lecture:<br>
               LIST_NO_ERROR : la lecture a eut lieu.<br>
               LIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void*    LIST_ReadLast(const list_s* pList, LIST_Error_e* eError);

/**
   \fn const void* LIST_ReadCurrent(const list_s* pList, LIST_Error_e* eError)
   \brief Lecture de l'element courant.
   \param[in] pList la liste
   \param[out] eError le resultat de la lecture:<br>
               LIST_NO_ERROR : la lecture a eut lieu.<br>
               LIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void*    LIST_ReadCurrent(const list_s* pList, LIST_Error_e* eError);

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
const void*    LIST_ReadNext(const list_s* pList, LIST_Error_e* eError);

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
const void*    LIST_ReadPrev(const list_s* pList, LIST_Error_e* eError);

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
const void*    LIST_GetFirst(list_s* pList, LIST_Error_e* eError);

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
const void*    LIST_GetLast(list_s* pList, LIST_Error_e* eError);

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
const void*    LIST_GetCurrent(list_s* pList, LIST_Error_e* eError);

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
const void*    LIST_GetNext(list_s* pList, LIST_Error_e* eError);

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
const void*    LIST_GetPrev(list_s* pList, LIST_Error_e* eError);

/**
   \fn LIST_Error_e LIST_RemoveFirst(list_s* pList)
   \brief   Suppression du premier element.<br>
            Si cet element était l'element courant, l'element suivant devient le nouvel element courant.
   \param[in,out] pList la liste
   \return  LIST_NO_ERROR : la suppression a eut lieu.<br>
            LIST_EMPTY_LIST : la liste est vide.
*/
LIST_Error_e   LIST_RemoveFirst(list_s* pList);

/**
   \fn LIST_Error_e LIST_RemoveLast(list_s* pList)
   \brief   Suppression du dernier element.<br>
            Si cet element était l'element courant, l'element precedent devient le nouvel element courant.
   \param[in,out] pList la liste
   \return  LIST_NO_ERROR : la suppression a eut lieu.<br>
            LIST_EMPTY_LIST : la liste est vide.
*/
LIST_Error_e   LIST_RemoveLast(list_s* pList);

/**
   \fn LIST_Error_e LIST_RemoveCurrent(list_s* pList)
   \brief   Suppression de l'element courant.<br>
            L'element suivant (ou precedent si l'element courant est le dernier de la liste) devient l'element courant.
   \param[in,out] pList la liste
   \return  LIST_NO_ERROR : la suppression a eut lieu.<br>
            LIST_EMPTY_LIST : la liste est vide.
*/
LIST_Error_e   LIST_RemoveCurrent(list_s* pList);

/**
   \fn LIST_Error_e LIST_RemoveNext(list_s* pList)
   \brief Suppression de l'element suivant.
   \param[in,out] pList la liste
   \return  LIST_NO_ERROR : la suppression a eut lieu.<br>
            LIST_EMPTY_LIST : la liste est vide.<br>
            LIST_CELL_NOT_FOUND : l'element courant est le dernier de la liste.
*/
LIST_Error_e   LIST_RemoveNext(list_s* pList);

/**
   \fn LIST_Error_e LIST_RemovePrev(list_s* pList)
   \brief Suppression de l'element precedent.
   \param[in,out] pList la liste
   \return  LIST_NO_ERROR : la suppression a eut lieu.<br>
            LIST_EMPTY_LIST : la liste est vide.<br>
            LIST_CELL_NOT_FOUND : l'element courant est le premier de la liste.
*/
LIST_Error_e   LIST_RemovePrev(list_s* pList);

/**
   \fn list_s* LIST_Clone(const list_s* pList, LIST_Error_e* eError)
   \brief Duplication d'une liste.
   \param[in] pList la liste a dupliquer
   \param[out] eError le statut de la duplication :<br>
               LIST_NO_ERROR : la copie s'est correctement deroulee.<br>
               LIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire.
   \return La copie de la liste.
*/
list_s*        LIST_Clone(const list_s* pList, LIST_Error_e* eError);

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
LIST_Error_e   LIST_SearchData(list_s* pList, const void* pData);

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
LIST_Error_e   LIST_SearchDataFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *));

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
LIST_Error_e   LIST_SearchDataRev(list_s* pList, const void* pData);

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
LIST_Error_e   LIST_SearchDataRevFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *));

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
LIST_Error_e   LIST_RemoveData(list_s* pList, const void* pData);

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
LIST_Error_e   LIST_RemoveDataFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *));

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
LIST_Error_e   LIST_RemoveDataRev(list_s* pList, const void* pData);

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
LIST_Error_e   LIST_RemoveDataRevFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *));

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
LIST_Error_e   LIST_RemoveAllData(list_s* pList, const void* pData);

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
*/
LIST_Error_e   LIST_RemoveAllDataFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *));

#ifdef __cplusplus
}
#endif

#endif
