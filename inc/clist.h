/**
   \author Gregory Lerbret
   \file clist.h
   \brief Gestion de listes circulaires.<br>
   \date 24/09/2006
   \version 1.0.0
*/

#ifndef GL_CLIST_H
#define GL_CLIST_H

#include <stddef.h>
#include "bool.h"

/**
   \struct clist_s
   \brief La liste circulaire
*/
typedef struct clist clist_s;

/**
   \enum CLIST_Error_e
   \brief Resultat des traitements sur les listes circulaires
*/
typedef enum
{
/**
   \brief Pas d'erreur
*/
   CLIST_NO_ERROR,
/**
   \brief Erreur d'allocation
*/
   CLIST_MEMORY_ERROR,
/**
   \brief La liste est vide
*/
   CLIST_EMPTY_LIST,
/**
   \brief Element absent
*/
   CLIST_CELL_NOT_FOUND,
/**
   \brief Aucune fonction de comparaison n'est definie
*/
   CLIST_NO_COMP_FONCTION
} CLIST_Error_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
   \fn const char* CLIST_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char*    CLIST_Identifier(void);

/**
   \fn int CLIST_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int            CLIST_Version(void);

/**
   \fn clist_s* CLIST_Create(int (*compar)(const void *, const void *), CLIST_Error_e* eError)
   \brief Creation d'une liste circulaire.
   \param[in] compar la fonction de comparaison des elements
   \param[out] eError le resultat de la creation :<br>
      CLIST_NO_ERROR : la creation s'est correctement deroulee.<br>
      CLIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire.
   \return  La liste circulaire (NULL en cas d'erreur).
*/
clist_s*       CLIST_Create(int (*compar)(const void *, const void *), CLIST_Error_e* eError);

/**
   \fn void CLIST_Destroy(clist_s* pList)
   \brief Destruction d'une liste circulaire.
   \param[in,out] pList la liste circulaire
*/
void           CLIST_Destroy(clist_s* pList);

/**
   \fn void CLIST_SetCmp(clist_s* pList, int (*compar)(const void *, const void *))
   \brief Mise a jour de la fonction de comparaison.
   \param[in,out] pList la liste circulaire
   \param[in] compar la fonction de comparaison
*/
void           CLIST_SetCmp(clist_s* pList, int (*compar)(const void *, const void *));

/**
   \fn bool CLIST_IsEmpty(const clist_s* pList)
   \brief Verification de la vacuite de la liste.
   \param[in] pList la liste circulaire
   \return  true si la liste est vide.<br>
            false sinon.
*/
bool           CLIST_IsEmpty(const clist_s* pList);

/**
   \fn size_t CLIST_Size(const clist_s* pList)
   \brief Calcul du nombre d'element de la liste.
   \param[in] pList la liste circulaire
   \return Le nombre d'element de la liste.
*/
size_t         CLIST_Size(const clist_s* pList);

/**
   \fn bool CLIST_IsHead(const clist_s* pList)
   \brief Verification si l'element courant est le premier.
   \param[in] pList la liste circulaire
   \return  true si l'element est le premier de la liste.<br>
            false sinon.
*/
bool           CLIST_IsHead(const clist_s* pList);

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
CLIST_Error_e  CLIST_InsertFirst(clist_s* pList, const void* pData, size_t szDataSize);

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
CLIST_Error_e  CLIST_InsertNext(clist_s* pList, const void* pData, size_t szDataSize);

/**
   \fn CLIST_Error_e CLIST_InsertPrev(clist_s* pList, const void* pData, size_t szDataSize)
   \brief   Insertion d'un element dans liste avant l'element courant.<br>
            L'element insere devient l'element courant.
   \param[in,out] pList la lise circulaire
   \param[in] pData l'element a ajouter
   \param[in] szDataSize la taille de l'element
   \return  CLIST_NO_ERROR : l'insertion s'est correctement deroulee.<br>
            CLIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire ou il n'existe pas de donnee a inserer.
*/
CLIST_Error_e  CLIST_InsertPrev(clist_s* pList, const void* pData, size_t szDataSize);

/**
   \fn CLIST_Error_e CLIST_SeekFirst(clist_s* pList)
   \brief Deplacement sur le premier element.
   \param[in,out] pList la liste circulaire
   \return  CLIST_NO_ERROR : le deplacement s'est correctement deroule.<br>
            CLIST_EMPTY_LIST : la liste est vide.
*/
CLIST_Error_e  CLIST_SeekFirst(clist_s* pList);

/**
   \fn CLIST_Error_e CLIST_SeekNext(clist_s* pList)
   \brief Deplacement sur l'element suivant.
   \param[in,out] pList la liste circulaire
   \return  CLIST_NO_ERROR : le deplacement s'est correctement deroule.<br>
            CLIST_EMPTY_LIST : la liste est vide.
*/
CLIST_Error_e  CLIST_SeekNext(clist_s* pList);

/**
   \fn CLIST_Error_e CLIST_SeekPrev(clist_s* pList)
   \brief Deplacement sur l'element precedent.
   \param[in,out] pList la liste circulaire
   \return  CLIST_NO_ERROR : le deplacement s'est correctement deroule.<br>
            CLIST_EMPTY_LIST : la liste est vide.
*/
CLIST_Error_e  CLIST_SeekPrev(clist_s* pList);

/**
   \fn const void* CLIST_ReadFirst(const clist_s* pList, CLIST_Error_e* eError)
   \brief Lecture du premier element.
   \param[in] pList la liste circulaire
   \param[out] eError le resultat de la lecture:<br>
               CLIST_NO_ERROR : la lecture a eut lieu.<br>
               CLIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void*    CLIST_ReadFirst(const clist_s* pList, CLIST_Error_e* eError);

/**
   \fn const void* CLIST_ReadCurrent(const clist_s* pList, CLIST_Error_e* eError)
   \brief Lecture de l'element courant.
   \param[in] pList la liste circulaire
   \param[out] eError le resultat de la lecture:<br>
               CLIST_NO_ERROR : la lecture a eut lieu.<br>
               CLIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void*    CLIST_ReadCurrent(const clist_s* pList, CLIST_Error_e* eError);

/**
   \fn const void* CLIST_ReadNext(const clist_s* pList, CLIST_Error_e* eError)
   \brief Lecture de l'element suivant.
   \param[in] pList la liste circulaire
   \param[out] eError le resultat de la lecture:<br>
               CLIST_NO_ERROR : la lecture a eut lieu.<br>
               CLIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void*    CLIST_ReadNext(const clist_s* pList, CLIST_Error_e* eError);

/**
   \fn const void* CLIST_ReadPrev(const clist_s* pList, CLIST_Error_e* eError)
   \brief Lecture de l'element precedent.
   \param[in] pList la liste circulaire
   \param[out] eError le resultat de la lecture:<br>
               CLIST_NO_ERROR : la lecture a eut lieu.<br>
               CLIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void*    CLIST_ReadPrev(const clist_s* pList, CLIST_Error_e* eError);

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
const void*    CLIST_GetFirst(clist_s* pList, CLIST_Error_e* eError);

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
const void*    CLIST_GetCurrent(clist_s* pList, CLIST_Error_e* eError);

/**
   \fn const void* CLIST_GetNext(clist_s* pList, CLIST_Error_e* eError)
   \brief Lecture et suppression de l'element suivant.
   \param[in,out] pList la liste circulaire
   \param[out] eError resultat de la lecture:<br>
               CLIST_NO_ERROR : la lecture a eut lieu.<br>
               CLIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void*    CLIST_GetNext(clist_s* pList, CLIST_Error_e* eError);

/**
   \fn const void* CLIST_GetPrev(clist_s* pList, CLIST_Error_e* eError)
   \brief Lecture et suppression de l'element precedent.
   \param[in,out] pList la liste circulaire
   \param[out] eError resultat de la lecture:<br>
               CLIST_NO_ERROR : la lecture a eut lieu.<br>
               CLIST_EMPTY_LIST : la liste est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void*    CLIST_GetPrev(clist_s* pList, CLIST_Error_e* eError);

/**
   \fn CLIST_Error_e CLIST_RemoveFirst(clist_s* pList)
   \brief   Suppression du premier element.<br>
            Si cet element était l'element courant, l'element suivant devient le nouvel element courant.
   \param[in,out] pList la liste circulaire
   \return  CLIST_NO_ERROR : la suppression a eut lieu.<br>
            CLIST_EMPTY_LIST : la liste est vide.
*/
CLIST_Error_e  CLIST_RemoveFirst(clist_s* pList);

/**
   \fn CLIST_Error_e CLIST_RemoveCurrent(clist_s* pList)
   \brief   Suppression de l'element courant.<br>
            L'element suivant devient l'element courant.
   \param[in,out] pList la liste circulaire
   \return  CLIST_NO_ERROR : la suppression a eut lieu.<br>
            CLIST_EMPTY_LIST : la liste est vide.
*/
CLIST_Error_e  CLIST_RemoveCurrent(clist_s* pList);

/**
   \fn CLIST_Error_e CLIST_RemoveNext(clist_s* pList)
   \brief Suppression de l'element suivant.
   \param[in,out] pList la liste circulaire
   \return  CLIST_NO_ERROR : la suppression a eut lieu.<br>
            CLIST_EMPTY_LIST : la liste est vide.
*/
CLIST_Error_e  CLIST_RemoveNext(clist_s* pList);

/**
   \fn CLIST_Error_e CLIST_RemovePrev(clist_s* pList)
   \brief Suppression de l'element precedent.
   \param[in,out] pList la liste circulaire
   \return  CLIST_NO_ERROR : la suppression a eut lieu.<br>
            CLIST_EMPTY_LIST : la liste est vide.
*/
CLIST_Error_e  CLIST_RemovePrev(clist_s* pList);

/**
   \fn clist_s* CLIST_Clone(const clist_s* pList, CLIST_Error_e* eError)
   \brief Duplication d'une liste.
   \param[in] pList la liste a dupliquer
   \param[out] eError le statut de la duplication:<br>
               CLIST_NO_ERROR : la copie s'est correctement deroulee.<br>
               CLIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire.
   \return La copie de la liste.
*/
clist_s*       CLIST_Clone(const clist_s* pList, CLIST_Error_e* eError);

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
CLIST_Error_e  CLIST_SearchData(clist_s* pList, const void* pData);

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
CLIST_Error_e  CLIST_SearchDataFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *));

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
CLIST_Error_e  CLIST_SearchDataRev(clist_s* pList, const void* pData);

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
CLIST_Error_e  CLIST_SearchDataRevFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *));

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
CLIST_Error_e  CLIST_RemoveData(clist_s* pList, const void* pData);

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
CLIST_Error_e  CLIST_RemoveDataFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *));

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
CLIST_Error_e  CLIST_RemoveDataRev(clist_s* pList, const void* pData);

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
CLIST_Error_e  CLIST_RemoveDataRevFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *));

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
CLIST_Error_e  CLIST_RemoveAllData(clist_s* pList, const void* pData);

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
CLIST_Error_e  CLIST_RemoveAllDataFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *));

#ifdef __cplusplus
}
#endif

#endif
