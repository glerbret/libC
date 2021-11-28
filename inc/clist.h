/**
 * @author Gregory Lerbret
 * @file
 * @brief Gestion de listes circulaires
 * @date 24/09/2006
 * @version 1.0.0
 */

#ifndef GL_CLIST_H
#define GL_CLIST_H

#include "bool.h"

#include <stddef.h>

/**
 * @brief Liste circulaire
 */
typedef struct clist clist_s;

/**
 * @brief Resultat des traitements sur les listes circulaires
 */
typedef enum
{
    /// @brief Pas d'erreur
    CLIST_NO_ERROR,
    /// @brief Erreur d'allocation
    CLIST_MEMORY_ERROR,
    /// @brief La liste est vide
    CLIST_EMPTY_LIST,
    /// @brief Element absent
    CLIST_CELL_NOT_FOUND,
    /// @brief Aucune fonction de comparaison n'est definie
    CLIST_NO_COMP_FONCTION
} CLIST_Error_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @return Identifiant du module (nom et version)
 */
const char* CLIST_Identifier(void);

/**
 * @return Version du module
 */
int CLIST_Version(void);

/**
 * @brief Creation d'une liste circulaire
 *
 * @param[in] compar Fonction de comparaison des elements
 * @param[out] eError Resultat de la creation :
 *      - CLIST_NO_ERROR : la creation s'est correctement deroulee
 *      - CLIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire
 *
 * @return  Liste circulaire (NULL en cas d'erreur)
 */
clist_s* CLIST_Create(int (*compar)(const void *, const void *), CLIST_Error_e* eError);

/**
 * @brief Destruction d'une liste circulaire
 *
 * @param[in,out] pList Liste circulaire
 */
void CLIST_Destroy(clist_s* pList);

/**
 * @brief Mise a jour de la fonction de comparaison
 *
 * @param[in,out] pList Liste circulaire
 * @param[in] compar Fonction de comparaison
 */
void CLIST_SetCmp(clist_s* pList, int (*compar)(const void *, const void *));

/**
 * @brief Verification de la vacuite de la liste
 *
 * @param[in] pList Liste circulaire
 *
 * @return
 *  - true si la liste est vide
 *  - false sinon
 */
bool CLIST_IsEmpty(const clist_s* pList);

/**
 * @brief Calcul du nombre d'element de la liste
 *
 * @param[in] pList Liste circulaire
 *
 * @return Nombre d'element de la liste.
 */
size_t CLIST_Size(const clist_s* pList);

/**
 * @brief Verification si l'element courant est le premier
 *
 * @param[in] pList Liste circulaire
 *
 * @return
 *  - true si l'element est le premier de la liste
 *  - false sinon
 */
bool CLIST_IsHead(const clist_s* pList);

/**
 * @brief Insertion d'un element en tete de liste
 *        L'element insere devient l'element courant
 *
 * @param[in,out] pList Liste circulaire
 * @param[in] pData Element a ajouter
 * @param[in] szDataSize Taille de l'element
 *
 * @return
 *  - CLIST_NO_ERROR : l'insertion s'est correctement deroulee
 *  - CLIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire ou il n'existe pas de donnee a inserer
 */
CLIST_Error_e CLIST_InsertFirst(clist_s* pList, const void* pData, size_t szDataSize);

/**
 * @brief Insertion d'un element dans liste apres l'element courant
 *        L'element insere devient l'element courant
 *
 * @param[in,out] pList Liste circulaire
 * @param[in] pData Element a ajouter
 * @param[in] szDataSize Taille de l'element
 *
 * @return
 *  - CLIST_NO_ERROR : l'insertion s'est correctement deroulee
 *  - CLIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire ou il n'existe pas de donnee a inserer
 */
CLIST_Error_e CLIST_InsertNext(clist_s* pList, const void* pData, size_t szDataSize);

/**
 * @brief Insertion d'un element dans liste avant l'element courant
 *        L'element insere devient l'element courant
 *
 * @param[in,out] pList Liste circulaire
 * @param[in] pData Element a ajouter
 * @param[in] szDataSize Taille de l'element
 *
 * @return
 *  - CLIST_NO_ERROR : l'insertion s'est correctement deroulee
 *  -CLIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire ou il n'existe pas de donnee a inserer
 */
CLIST_Error_e CLIST_InsertPrev(clist_s* pList, const void* pData, size_t szDataSize);

/**
 * @brief Deplacement sur le premier element
 *
 * @param[in,out] pList Liste circulaire
 * @return
 *  - CLIST_NO_ERROR : le deplacement s'est correctement deroule
 *  - CLIST_EMPTY_LIST : la liste est vide
 */
CLIST_Error_e CLIST_SeekFirst(clist_s* pList);

/**
 * @brief Deplacement sur l'element suivant
 *
 * @param[in,out] pList Liste circulaire
 *
 * @return
 *  - CLIST_NO_ERROR : le deplacement s'est correctement deroule
 *  - CLIST_EMPTY_LIST : la liste est vide
 */
CLIST_Error_e CLIST_SeekNext(clist_s* pList);

/**
 * @brief Deplacement sur l'element precedent
 *
 * @param[in,out] pList Liste circulaire
 *
 * @return
 *  - CLIST_NO_ERROR : le deplacement s'est correctement deroule
 *  - CLIST_EMPTY_LIST : la liste est vide
 */
CLIST_Error_e CLIST_SeekPrev(clist_s* pList);

/**
 * @brief Lecture du premier element
 *
 * @param[in] pList Liste circulaire
 * @param[out] eError Resultat de la lecture :
 *                  - CLIST_NO_ERROR : la lecture a eut lieu
 *                  - CLIST_EMPTY_LIST : la liste est vide
 *
 * @return Element lu (NULL en cas d'erreur)
 */
const void* CLIST_ReadFirst(const clist_s* pList, CLIST_Error_e* eError);

/**
 * @brief Lecture de l'element courant
 *
 * @param[in] pList Liste circulaire
 * @param[out] eError Resultat de la lecture :
 *                      - CLIST_NO_ERROR : la lecture a eut lieu
 *                      - CLIST_EMPTY_LIST : la liste est vide
 *
 * @return Element lu (NULL en cas d'erreur)
 */
const void* CLIST_ReadCurrent(const clist_s* pList, CLIST_Error_e* eError);

/**
 * @brief Lecture de l'element suivant
 *
 * @param[in] pList Liste circulaire
 * @param[out] eError Resultat de la lecture :
 *                      - CLIST_NO_ERROR : la lecture a eut lieu
 *                      - CLIST_EMPTY_LIST : la liste est vide
 *
 * @return Element lu (NULL en cas d'erreur)
 */
const void* CLIST_ReadNext(const clist_s* pList, CLIST_Error_e* eError);

/**
 * @brief Lecture de l'element precedent
 *
 * @param[in] pList Liste circulaire
 * @param[out] eError Resultat de la lecture :
 *                      - CLIST_NO_ERROR : la lecture a eut lieu
 *                      - CLIST_EMPTY_LIST : la liste est vide
 *
 * @return Element lu (NULL en cas d'erreur)
 */
const void* CLIST_ReadPrev(const clist_s* pList, CLIST_Error_e* eError);

/**
 * @brief Lecture et suppression du premier element
 *        Si cet element etait l'element courant, l'element suivant devient le nouvel element courant
 *
 * @param[in,out] pList Liste circulaire
 * @param[out] eError Resultat de la lecture :
 *                      - CLIST_NO_ERROR : la lecture a eut lieu
 *                      - CLIST_EMPTY_LIST : la liste est vide
 *
 * @return Element lu (NULL en cas d'erreur)
 */
const void* CLIST_GetFirst(clist_s* pList, CLIST_Error_e* eError);

/**
 * @brief Lecture et suppression de l'element courant
 *        L'element suivant devient l'element courant
 *
 * @param[in,out] pList Liste circulaire
 * @param[out] eError Resultat de la lecture :
 *                      - CLIST_NO_ERROR : la lecture a eut lieu
 *                      - CLIST_EMPTY_LIST : la liste est vide
 *
 * @return Element lu (NULL en cas d'erreur)
 */
const void* CLIST_GetCurrent(clist_s* pList, CLIST_Error_e* eError);

/**
 * @brief Lecture et suppression de l'element suivant
 *
 * @param[in,out] pList Liste circulaire
 * @param[out] eError Resultat de la lecture :
 *                      - CLIST_NO_ERROR : la lecture a eut lieu
 *                      - CLIST_EMPTY_LIST : la liste est vide
 *
 * @return Element lu (NULL en cas d'erreur)
 */
const void* CLIST_GetNext(clist_s* pList, CLIST_Error_e* eError);

/**
 * @brief Lecture et suppression de l'element precedent
 *
 * @param[in,out] pList Liste circulaire
 * @param[out] eError Resultat de la lecture :
 *                      - CLIST_NO_ERROR : la lecture a eut lieu
 *                      - CLIST_EMPTY_LIST : la liste est vide
 *
 * @return Element lu (NULL en cas d'erreur)
*/
const void* CLIST_GetPrev(clist_s* pList, CLIST_Error_e* eError);

/**
 * @brief Suppression du premier element
 *        Si cet element etait l'element courant, l'element suivant devient le nouvel element courant
 *
 * @param[in,out] pList Liste circulaire
 *
 * @return
 *  - CLIST_NO_ERROR : la suppression a eut lieu
 *  - CLIST_EMPTY_LIST : la liste est vide
 */
CLIST_Error_e CLIST_RemoveFirst(clist_s* pList);

/**
 * @brief Suppression de l'element courant
 *        L'element suivant devient l'element courant
 *
 * @param[in,out] pList Liste circulaire
 * @return
 *  - CLIST_NO_ERROR : la suppression a eut lieu
 *  - CLIST_EMPTY_LIST : la liste est vide
 */
CLIST_Error_e CLIST_RemoveCurrent(clist_s* pList);

/**
 * @brief Suppression de l'element suivant
 *
 * @param[in,out] pList Liste circulaire
 *
 * @return
 *  - CLIST_NO_ERROR : la suppression a eut lieu
 *  - CLIST_EMPTY_LIST : la liste est vide
 */
CLIST_Error_e CLIST_RemoveNext(clist_s* pList);

/**
 * @brief Suppression de l'element precedent
 *
 * @param[in,out] pList Liste circulaire
 *
 * @return
 *  - CLIST_NO_ERROR : la suppression a eut lieu
 *  - CLIST_EMPTY_LIST : la liste est vide
 */
CLIST_Error_e CLIST_RemovePrev(clist_s* pList);

/**
 * @brief Duplication d'une liste
 *
 * @param[in] pList Liste a dupliquer
 * @param[out] eError Statut de la duplication:
 *                      - CLIST_NO_ERROR : la copie s'est correctement deroulee
 *                      - CLIST_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire
 * @return La copie de la liste
 */
clist_s* CLIST_Clone(const clist_s* pList, CLIST_Error_e* eError);

/**
 * @brief Recherche d'un element dans la liste
 *        Si l'element est present, il devient le nouvel element courant de la liste
 *
 * @param[in,out] pList Liste circulaire
 * @param[in] pData Donnee recherchee
 *
 * @return
 *  - CLIST_NO_ERROR : l'element a ete trouve
 *  - CLIST_EMPTY_LIST : la liste est vide
 *  - CLIST_CELL_NOT_FOUND : l'element n'est pas present
 *  - CLIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie
*/
CLIST_Error_e CLIST_SearchData(clist_s* pList, const void* pData);

/**
 * @brief Recherche d'un element dans la liste
 *        Si l'element est present, il devient le nouvel element courant de la liste
 *
 * @param[in,out] pList Liste circulaire
 * @param[in] pData Donnee recherchee
 * @param[in] compar Fonction de comparaison (si NULL la fonction par defaut est utilisee)
 *
 * @return
 *  - CLIST_NO_ERROR : l'element a ete trouve
 *  - CLIST_EMPTY_LIST : la liste est vide
 *  - CLIST_CELL_NOT_FOUND : l'element n'est pas present
 *  - CLIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie
 */
CLIST_Error_e CLIST_SearchDataFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *));

/**
 * @brief Recherche d'un element dans la liste
 *        La recherche s'effectue en remontant la liste
 *        Si l'element est present, il devient le nouvel element courant de la liste
 *
 * @param[in,out] pList Liste circulaire
 * @param[in] pData Donnee recherchee
 *
 * @return
 *  - CLIST_NO_ERROR : l'element a ete trouve
 *  - CLIST_EMPTY_LIST : la liste est vide
 *  - CLIST_CELL_NOT_FOUND : l'element n'est pas present
 *  - CLIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie
*/
CLIST_Error_e CLIST_SearchDataRev(clist_s* pList, const void* pData);

/**
 * @brief Recherche d'un element dans la liste
 *        La recherche s'effectue en remontant la liste
 *        Si l'element est present, il devient le nouvel element courant de la liste
 *
 * @param[in,out] pList Liste circulaire
 * @param[in] pData Donnee recherchee
 * @param[in] compar Fonction de comparaison (si NULL la fonction par defaut est utilisee)
 *
 * @return
 *  - CLIST_NO_ERROR : l'element a ete trouve
 *  - CLIST_EMPTY_LIST : la liste est vide
 *  - CLIST_CELL_NOT_FOUND : l'element n'est pas present
 *  - CLIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie
 */
CLIST_Error_e CLIST_SearchDataRevFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *));

/**
 * @brief Supression de la premiere cellule contenant la donnee recherchee
 *        Si l'element courant correspond au critere de recherche, l'element suivant devient le nouvel element courant
 *
 * @param[in,out] pList Liste circulaire
 * @param[in] pData Donnee a supprimee
 *
 * @return
 *  - CLIST_NO_ERROR : l'element a ete suppimme
 *  - CLIST_EMPTY_LIST : la liste est vide
 *  - CLIST_CELL_NOT_FOUND : l'element n'est pas present
 *  - CLIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie
 */
CLIST_Error_e CLIST_RemoveData(clist_s* pList, const void* pData);

/**
 * @brief Supression de la premiere cellule contenant la donnee recherchee
 *        Si l'element courant correspond au critere de recherche, l'element suivant devient le nouvel element courant
 *
 * @param[in,out] pList Liste circulaire
 * @param[in] pData Donnee a supprimee
 * @param[in] compar Fonction de comparaison (si NULL la fonction par defaut est utilisee)
 *
 * @return
 *  - CLIST_NO_ERROR : l'element a ete suppimme
 *  - CLIST_EMPTY_LIST : la liste est vide
 *  - CLIST_CELL_NOT_FOUND : l'element n'est pas present
 *  - CLIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie
 */
CLIST_Error_e CLIST_RemoveDataFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *));

/**
 * @brief Supression de la premiere cellule contenant la donnee recherchee
 *        La recherche s'effectue en remontant la liste
 *        Si l'element courant correspond au critere de recherche, l'element suivant devient le nouvel element courant
 *
 * @param[in,out] pList Liste circulaire
 * @param[in] pData Donnee a supprimee
 *
 * @return
 *  - CLIST_NO_ERROR : l'element a ete supprimme
 *  - CLIST_EMPTY_LIST : la liste est vide
 *  - CLIST_CELL_NOT_FOUND : l'element n'est pas present
 *  - CLIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie
 */
CLIST_Error_e CLIST_RemoveDataRev(clist_s* pList, const void* pData);

/**
 * @brief Supression de la premiere cellule contenant la donnee recherchee
 *        La recherche s'effectue en remontant la liste
 *        Si l'element courant correspond au critere de recherche, l'element suivant devient le nouvel element courant
 *
 * @param[in,out] pList Liste circulaire
 * @param[in] pData Donnee a supprimee
 * @param[in] compar Fonction de comparaison (si NULL la fonction par defaut est utilisee)
 *
 * @return
 *  - CLIST_NO_ERROR : l'element a ete supprime
 *  - CLIST_EMPTY_LIST : la liste est vide
 *  - CLIST_CELL_NOT_FOUND : l'element n'est pas present
 *  - CLIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie
 */
CLIST_Error_e CLIST_RemoveDataRevFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *));

/**
 * @brief Suppression de toutes les cellules contenant la donnee recherchee
 *        Si l'element courant correspond au critere de recherche, l'element suivant devient le nouvel element courant
 *
 * @param[in,out] pList Liste circulaire
 * @param[in] pData Donnee a supprimee
 *
 * @return
 *  - CLIST_NO_ERROR : l'element a ete suppime
 *  - CLIST_EMPTY_LIST : la liste est vide
 *  - CLIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie
 */
CLIST_Error_e CLIST_RemoveAllData(clist_s* pList, const void* pData);

/**
 * @brief Suppression de toutes les cellules contenant la donnee recherchee
 *        Si l'element courant correspond au critere de recherche, l'element suivant devient le nouvel element courant
 *
 * @param[in,out] pList Liste circulaire
 * @param[in] pData Donnee a supprimee
 * @param[in] compar Fonction de comparaison (si NULL la fonction par defaut est utilisee)
 *
 * @return
 *  - CLIST_NO_ERROR : l'element a ete suppime
 *  - CLIST_EMPTY_LIST : la liste est vide
 *  - CLIST_NO_COMP_FONCTION : aucune fonction de comparaison n'est definie
 */
CLIST_Error_e CLIST_RemoveAllDataFct(clist_s* pList, const void* pData, int (*compar)(const void *, const void *));

#ifdef __cplusplus
}
#endif

#endif
