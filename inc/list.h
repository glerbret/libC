/**
 * @author Gregory Lerbret
 * @file
 * @brief Gestion de listes
 * @date 24/09/2006
 * @version 1.0.0
 */

#ifndef GL_LIST_H
#define GL_LIST_H

#include "bool.h"

#include <stddef.h>

/**
 * @brief Liste
 */
typedef struct list list_s;

/**
 * @brief Resultat des traitements sur les listes
 */
typedef enum
{
    /// @brief Pas d'erreur
    LIST_NO_ERROR,
    /// @brief Erreur d'allocation
    LIST_MEMORY_ERROR,
    /// @brief La liste est vide
    LIST_EMPTY_LIST,
    /// @brief Element absent
    LIST_CELL_NOT_FOUND,
    /// @brief Aucune fonction de comparaison n'est definie
    LIST_NO_COMP_FONCTION
} LIST_Error_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @return Identifiant du module (nom et version)
 */
const char* LIST_Identifier(void);

/**
 * @return Version du module
 */
int LIST_Version(void);

/**
 * @brief Creation d'une liste
 *
 * @param[in] compar Fonction de comparaison des elements
 * @param[out] eError Resultat de la creation :
 *                      - CLIST_NO_ERROR : la creation s'est correctement deroulee
 *                      - CLIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire
 * @return Liste (NULL en cas d'erreur)
 */
list_s* LIST_Create(int (*compar)(const void *, const void *), LIST_Error_e* eError);

/**
 * @brief Destruction d'une liste
 *
 * @param[in,out] pList Liste
 */
void LIST_Destroy(list_s* pList);

/**
 * @brief Mise a jour de la fonction de comparaison
 *
 * @param[in,out] pList Liste
 * @param[in] compar Fonction de comparaison
 */
void LIST_SetCmp(list_s* pList, int (*compar)(const void *, const void *));

/**
 * @brief Verification de la vacuite de la liste
 *
 * @param[in] pList Liste
 *
 * @return
 *  - true si la liste est vide
 *  - false sinon
 */
bool LIST_IsEmpty(const list_s* pList);

/**
 * @brief Calcul du nombre d'element de la liste
 *
 * @param[in] pList Liste
 *
 * @return Nombre d'element de la liste
 */
size_t LIST_Size(const list_s* pList);

/**
 * @brief Verification si l'element courant est le premier
 *
 * @param[in] pList Liste
 *
 * @return
 *  - true si l'element est le premier de la liste
 *  - false sinon
 */
bool LIST_IsHead(const list_s* pList);

/**
 * @brief Verification si l'element courant est le dernier
 *
 * @param[in] pList Liste
 *
 * @return
 *  - true si l'element est le dernier de la liste
 *  - false sinon
 */
bool LIST_IsTail(const list_s* pList);

/**
 * @brief Insertion d'un element en tete de liste
 *        L'element insere devient l'element courant
 *
 * @param[in,out] pList Liste
 * @param[in] pData Element a ajouter
 * @param[in] szDataSize Taille de l'element
 *
 * @return
 *  - LIST_NO_ERROR : l'insertion s'est correctement deroulee
 *  - LIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire ou il n'existe pas de donnee a inserer
 */
LIST_Error_e LIST_InsertFirst(list_s* pList, const void* pData, size_t szDataSize);

/**
 * @brief Insertion d'un element en fin de liste
 *        L'element insere devient l'element courant
 *
 * @param[in,out] pList Liste
 * @param[in] pData Element a ajouter
 * @param[in] szDataSize Taille de l'element
 *
 * @return
 *  - LIST_NO_ERROR : l'insertion s'est correctement deroulee
 *  - LIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire ou il n'existe pas de donnee a inserer
 */
LIST_Error_e LIST_InsertLast(list_s* pList, const void* pData, size_t szDataSize);

/**
 * @brief Insertion d'un element dans liste apres l'element courant
 *        L'element insere devient l'element courant
 *
 * @param[in,out] pList Liste
 * @param[in] pData Element a ajouter
 * @param[in] szDataSize Taille de l'element
 *
 * @return
 *  - LIST_NO_ERROR : l'insertion s'est correctement deroulee
 *  - LIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire ou il n'existe pas de donnee a inserer
 */
LIST_Error_e LIST_InsertNext(list_s* pList, const void* pData, size_t szDataSize);

/**
 * @brief Insertion d'un element dans liste avant l'element courant
 *        L'element insere devient l'element courant
 *
 * @param[in,out] pList Liste
 * @param[in] pData Element a ajouter
 * @param[in] szDataSize Taille de l'element
 *
 * @return
 *  - LIST_NO_ERROR : l'insertion s'est correctement deroulee
 *  - LIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire ou il n'existe pas de donnee a inserer
 */
LIST_Error_e LIST_InsertPrev(list_s* pList, const void* pData, size_t szDataSize);

/**
 * @brief Deplacement sur le premier element
 *
 * @param[in,out] pList Liste
 *
 * @return
 *  - LIST_NO_ERROR : le deplacement s'est correctement deroule
 *  - LIST_EMPTY_LIST : la liste est vide
 */
LIST_Error_e LIST_SeekFirst(list_s* pList);

/**
 * @brief Deplacement sur le dernier element
 *
 * @param[in,out] pList Liste
 *
 * @return
 *  - LIST_NO_ERROR : le deplacement s'est correctement deroule
 *  - LIST_EMPTY_LIST : la liste est vide
 */
LIST_Error_e LIST_SeekLast(list_s* pList);

/**
 * @brief Deplacement sur l'element suivant
 *
 * @param[in,out] pList Liste
 *
 * @return
 *  - LIST_NO_ERROR : le deplacement s'est correctement deroule
 *  - LIST_EMPTY_LIST : la liste est vide
 *  - LIST_CELL_NOT_FOUND : l'element courant est le dernier
 */
LIST_Error_e LIST_SeekNext(list_s* pList);

/**
 * @brief Deplacement sur l'element precedent
 *
 * @param[in,out] pList Liste
 *
 * @return
 *  - LIST_NO_ERROR : le deplacement s'est correctement deroule
 *  - LIST_EMPTY_LIST : la liste est vide
 *  - LIST_CELL_NOT_FOUND : l'element courant est le premier
 */
LIST_Error_e LIST_SeekPrev(list_s* pList);

/**
 * @brief Lecture du premier element
 *
 * @param[in] pList Liste
 * @param[out] eError Resultat de la lecture :
 *                      - LIST_NO_ERROR : la lecture a eut lieu
 *                      - LIST_EMPTY_LIST : la liste est vide
 *
 * @return Element lu (NULL en cas d'erreur)
 */
const void* LIST_ReadFirst(const list_s* pList, LIST_Error_e* eError);

/**
 * @brief Lecture du dernier element
 *
 * @param[in] pList Liste
 * @param[out] eError Resultat de la lecture :
 *                      - LIST_NO_ERROR : la lecture a eut lieu
 *                      - LIST_EMPTY_LIST : la liste est vide
 *
 * @return Element lu (NULL en cas d'erreur).
 */
const void* LIST_ReadLast(const list_s* pList, LIST_Error_e* eError);

/**
 * @brief Lecture de l'element courant
 *
 * @param[in] pList Liste
 * @param[out] eError Resultat de la lecture :
 *                      - LIST_NO_ERROR : la lecture a eut lieu
 *                      - LIST_EMPTY_LIST : la liste est vide
 *
 * @return Element lu (NULL en cas d'erreur)
 */
const void* LIST_ReadCurrent(const list_s* pList, LIST_Error_e* eError);

/**
 * @brief Lecture de l'element suivant
 *
 * @param[in] pList Liste
 * @param[out] eError Resultat de la lecture :
 *                      - LIST_NO_ERROR : la lecture a eut lieu
 *                      - LIST_EMPTY_LIST : la liste est vide
 *                      - LIST_CELL_NOT_FOUND : l'element courant est le dernier de la liste
 *
 * @return Element lu (NULL en cas d'erreur)
 */
const void* LIST_ReadNext(const list_s* pList, LIST_Error_e* eError);

/**
 * @brief Lecture de l'element precedent
 *
 * @param[in] pList Liste
 * @param[out] eError Resultat de la lecture :
 *                      - LIST_NO_ERROR : la lecture a eut lieu
 *                      - LIST_EMPTY_LIST : la liste est vide
 *                      - LIST_CELL_NOT_FOUND : l'element courant est le premier de la liste
 *
 * @return Element lu (NULL en cas d'erreur)
 */
const void* LIST_ReadPrev(const list_s* pList, LIST_Error_e* eError);

/**
 * @brief Lecture et suppression du premier element
 *        Si cet element etait l'element courant, l'element suivant devient le nouvel element courant
 *
 * @param[in,out] pList Liste
 * @param[out] eError Resultat de la lecture :
 *                      - LIST_NO_ERROR : la lecture a eut lieu
 *                      - LIST_EMPTY_LIST : la liste est vide
 *
 * @return Element lu (NULL en cas d'erreur)
 */
const void* LIST_GetFirst(list_s* pList, LIST_Error_e* eError);

/**
 * @brief Lecture et suppression du dernier element
 *        Si cet element etait l'element courant, l'element precedent devient le nouvel element courant
 *
 * @param[in,out] pList Liste
 * @param[out] eError Resultat de la lecture :
 *                      - LIST_NO_ERROR : la lecture a eut lieu
 *                      - LIST_EMPTY_LIST : la liste est vide
 *
 * @return Element lu (NULL en cas d'erreur)
 */
const void* LIST_GetLast(list_s* pList, LIST_Error_e* eError);

/**
 * @brief Lecture et suppression de l'element courant
 *        L'element suivant (ou l'element precedent si l'element courant etait le dernier de la liste) devient l'element courant
 *
 * @param[in,out] pList Liste
 * @param[out] eError Resultat de la lecture :
 *                      - LIST_NO_ERROR : la lecture a eut lieu
 *                      - LIST_EMPTY_LIST : la liste est vide
 *
 * @return Element lu (NULL en cas d'erreur)
 */
const void* LIST_GetCurrent(list_s* pList, LIST_Error_e* eError);

/**
 * @brief Lecture et suppression de l'element suivant
 *
 * @param[in,out] pList Liste
 * @param[out] eError Resultat de la lecture :
 *                      - LIST_NO_ERROR : la lecture a eut lieu
 *                      - LIST_EMPTY_LIST : la liste est vide
 *                      - LIST_CELL_NOT_FOUND : l'element courant est le dernier de la liste
 *
 * @return Element lu (NULL en cas d'erreur)
 */
const void* LIST_GetNext(list_s* pList, LIST_Error_e* eError);

/**
 * @brief Lecture et suppression de l'element precedent
 *
 * @param[in,out] pList Liste
 * @param[out] eError Resultat de la lecture :
 *                      - LIST_NO_ERROR : la lecture a eut lieu
 *                      - LIST_EMPTY_LIST : la liste est vide
 *                      - LIST_CELL_NOT_FOUND : l'element courant est le premier de la liste
 *
 * @return Element lu (NULL en cas d'erreur)
 */
const void* LIST_GetPrev(list_s* pList, LIST_Error_e* eError);

/**
 * @brief Suppression du premier element
 *        Si cet element etait l'element courant, l'element suivant devient le nouvel element courant
 *
 * @param[in,out] pList Liste
 *
 * @return
 *  - LIST_NO_ERROR : la suppression a eut lieu
 *  - LIST_EMPTY_LIST : la liste est vide
 */
LIST_Error_e LIST_RemoveFirst(list_s* pList);

/**
 * @brief Suppression du dernier element
 *        Si cet element etait l'element courant, l'element precedent devient le nouvel element courant
 *
 * @param[in,out] pList Liste
 *
 * @return
 *  - LIST_NO_ERROR : la suppression a eut lieu
 *  - LIST_EMPTY_LIST : la liste est vide
 */
LIST_Error_e LIST_RemoveLast(list_s* pList);

/**
 * @brief Suppression de l'element courant
 *        L'element suivant (ou precedent si l'element courant est le dernier de la liste) devient l'element courant
 *
 * @param[in,out] pList Liste
 *
 * @return
 *  - LIST_NO_ERROR : la suppression a eut lieu
 *  - LIST_EMPTY_LIST : la liste est vide
 */
LIST_Error_e LIST_RemoveCurrent(list_s* pList);

/**
 * @brief Suppression de l'element suivant
 *
 * @param[in,out] pList Liste.
 *
 * @return
 *  - LIST_NO_ERROR : la suppression a eut lieu
 *  - LIST_EMPTY_LIST : la liste est vide
 *  - LIST_CELL_NOT_FOUND : l'element courant est le dernier de la liste
 */
LIST_Error_e LIST_RemoveNext(list_s* pList);

/**
 * @brief Suppression de l'element precedent
 *
 * @param[in,out] pList Liste
 *
 * @return
 *  - LIST_NO_ERROR : la suppression a eut lieu
 *  - LIST_EMPTY_LIST : la liste est vide
 *  - LIST_CELL_NOT_FOUND : l'element courant est le premier de la liste
 */
LIST_Error_e LIST_RemovePrev(list_s* pList);

/**
 * @brief Duplication d'une liste
 *
 * @param[in] pList Liste a dupliquer
 * @param[out] eError Statut de la duplication :
 *                      - LIST_NO_ERROR : la copie s'est correctement deroulee
 *                      - LIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire
 *
 * @return La copie de la liste
 */
list_s* LIST_Clone(const list_s* pList, LIST_Error_e* eError);

/**
 * @brief Recherche d'un element dans la liste apres l'element courant
 *        Si l'element est present, il devient le nouvel element courant de la liste
 *
 * @param[in,out] pList Liste
 * @param[in] pData Donnee recherchee
 *
 * @return
 *  - LIST_NO_ERROR : l'element a ete trouve
 *  - LIST_EMPTY_LIST : la liste est vide
 *  - LIST_CELL_NOT_FOUND : l'element n'est pas present
 *  - LIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie
 */
LIST_Error_e LIST_SearchData(list_s* pList, const void* pData);

/**
 * @brief Recherche d'un element dans la liste apres l'element courant
 *        Si l'element est present, il devient le nouvel element courant de la liste
 *
 * @param[in,out] pList Liste
 * @param[in] pData Donnee recherchee
 * @param[in] compar Fonction de comparaison (si NULL la fonction par defaut est utilisee)
 *
 * @return
 *  - LIST_NO_ERROR : l'element a ete trouve
 *  - LIST_EMPTY_LIST : la liste est vide
 *  - LIST_CELL_NOT_FOUND : l'element n'est pas present
 *  - LIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie
 */
LIST_Error_e LIST_SearchDataFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *));

/**
 * @brief Recherche d'un element dans la liste avant l'element courant
 *        Si l'element est present, il devient le nouvel element courant de la liste
 *
 * @param[in,out] pList Liste
 * @param[in] pData Donnee recherchee
 *
 * @return
 *  - LIST_NO_ERROR : l'element a ete trouve
 *  - LIST_EMPTY_LIST : la liste est vide
 *  - LIST_CELL_NOT_FOUND : l'element n'est pas present
 *  - LIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie
 */
LIST_Error_e LIST_SearchDataRev(list_s* pList, const void* pData);

/**
 * @brief Recherche d'un element dans la liste avant l'element courant
 *        Si l'element est present, il devient le nouvel element courant de la liste
 *
 * @param[in,out] pList Liste
 * @param[in] pData Donnee recherchee
 * @param[in] compar Fonction de comparaison (si NULL la fonction par defaut est utilisee)
 *
 * @return
 *  - LIST_NO_ERROR : l'element a ete trouve
 *  - LIST_EMPTY_LIST : la liste est vide
 *  - LIST_CELL_NOT_FOUND : l'element n'est pas present
 *  - LIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie
 */
LIST_Error_e LIST_SearchDataRevFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *));

/**
 * @brief Suppression de la premiere cellule situee apres l'element courant contenant la donnee recherchee
 *        Si l'element courant correspond au critere de recherche, l'element suivant (ou l'element precedent
 *        si l'element courant est le dernier de la liste) devient le nouvel element courant
 *
 * @param[in,out] pList Liste
 * @param[in] pData Donnee a supprimee
 *
 * @return
 *  - LIST_NO_ERROR : l'element a ete supprime
 *  - LIST_EMPTY_LIST : la liste est vide
 *  - LIST_CELL_NOT_FOUND : l'element n'est pas present
 *  - LIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie
 */
LIST_Error_e LIST_RemoveData(list_s* pList, const void* pData);

/**
 * @brief Suppression de la premiere cellule situee apres l'element courant contenant la donnee recherchee
 *        Si l'element courant correspond au critere de recherche, l'element suivant (ou l'element precedent
 *        si l'element courant est le dernier de la liste) devient le nouvel element courant
 *
 * @param[in,out] pList Liste
 * @param[in] pData Donnee a supprimee
 * @param[in] compar Fonction de comparaison (si NULL la fonction par defaut est utilisee)
 *
 * @return
 *  - LIST_NO_ERROR : l'element a ete suppime
 *  - LIST_EMPTY_LIST : la liste est vide
 *  - LIST_CELL_NOT_FOUND : l'element n'est pas present
 *  - LIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie
 */
LIST_Error_e LIST_RemoveDataFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *));

/**
 * @brief Suppression de la premiere cellule situee avant l'element courant contenant la donnee recherchee
 *        Si l'element courant correspond au critere de recherche, l'element suivant (ou l'element precedent
 *        si l'element courant est le dernier de la liste) devient le nouvel element courant
 *
 * @param[in,out] pList Liste
 * @param[in] pData Donnee a supprimee
 *
 * @return
 *  - LIST_NO_ERROR : l'element a ete supprime
 *  - LIST_EMPTY_LIST : la liste est vide
 *  - LIST_CELL_NOT_FOUND : l'element n'est pas present
 *  - LIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie
 */
LIST_Error_e   LIST_RemoveDataRev(list_s* pList, const void* pData);

/**
 * @brief Suppression de la premiere cellule situee avant l'element courant contenant la donnee recherchee
 *        Si l'element courant correspond au critere de recherche, l'element suivant (ou l'element precedent
 *        si l'element courant est le dernier de la liste) devient le nouvel element courant
 *
 * @param[in,out] pList Liste
 * @param[in] pData Donnee a supprimee
 * @param[in] compar Fonction de comparaison (si NULL la fonction par defaut est utilisee)
 *
 * @return
 *  - LIST_NO_ERROR : l'element a ete supprime
 *  - LIST_EMPTY_LIST : la liste est vide
 *  - LIST_CELL_NOT_FOUND : l'element n'est pas present
 *  - LIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie
 */
LIST_Error_e LIST_RemoveDataRevFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *));

/**
 * @brief Suppression de toutes les cellules contenant la donnee recherchee
 *        Si l'element courant correspond au critere de recherche, l'element suivant (ou l'element precedent
 *        si l'element courant est le dernier) devient le nouvel element courant
 *
 * @param[in,out] pList Liste
 * @param[in] pData Donnee a supprimee
 *
 * @return
 *  - LIST_NO_ERROR : l'element a ete supprime
 *  - LIST_EMPTY_LIST : la liste est vide
 *  - LIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie
 */
LIST_Error_e LIST_RemoveAllData(list_s* pList, const void* pData);

/**
 * @brief Suppression de toutes les cellules contenant la donnee recherchee
 *        Si l'element courant correspond au critere de recherche, l'element suivant (ou l'element precedent
 *        si l'element courant est le dernier) devient le nouvel element courant
 *
 * @param[in,out] pList Liste
 * @param[in] pData Donnee a supprimee
 * @param[in] compar Fonction de comparaison (si NULL la fonction par defaut est utilisee)
 *
 * @return
 *  - LIST_NO_ERROR : l'element a ete supprime
 *  - LIST_EMPTY_LIST : la liste est vide
 *  - LIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie
 */
LIST_Error_e LIST_RemoveAllDataFct(list_s* pList, const void* pData, int (*compar)(const void *, const void *));

#ifdef __cplusplus
}
#endif

#endif
