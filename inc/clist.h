/**
 * @file
 * @brief Gestion de listes circulaires.
 * @version 1.0.0.
 * @copyright MIT license.
 * @author Gregory Lerbret.
 */

#ifndef GL_CLIST_H
#define GL_CLIST_H

#include "bool.h"

/// @cond
#include <stddef.h>
/// @endcond

/**
 * @brief Liste circulaire.
 */
typedef struct clist clist_s;

/**
 * @brief Resultat des traitements sur les listes circulaires.
 */
typedef enum
{
  /// @brief Pas d'erreur.
  CLIST_NO_ERROR,
  /// @brief Erreur d'allocation.
  CLIST_MEMORY_ERROR,
  /// @brief La liste est vide.
  CLIST_EMPTY_LIST,
  /// @brief Element absent.
  CLIST_CELL_NOT_FOUND,
  /// @brief Aucune fonction de comparaison n'est definie.
  CLIST_NO_COMP_FONCTION
} CLIST_Error_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @return Identifiant du module (nom et version).
 */
const char* CLIST_Identifier(void);

/**
 * @return Version du module.
 */
int CLIST_Version(void);

/**
 * @brief Cree une liste circulaire.
 *
 * @param[in] compar  Fonction de comparaison des elements.
 *
 * @return  Liste circulaire (NULL en cas d'erreur).
 */
clist_s* CLIST_Create(int (*compar)(const void *, const void *));

/**
 * @brief Detruit une liste circulaire.
 *
 * @param[in,out] list  Liste circulaire.
 */
void CLIST_Destroy(clist_s* list);

/**
 * @brief Met a jour la fonction de comparaison.
 *
 * @param[in,out] list  Liste circulaire.
 * @param[in] compar    Fonction de comparaison.
 */
void CLIST_SetCmp(clist_s* list, int (*compar)(const void *, const void *));

/**
 * @brief Verifie la vacuite de la liste.
 *
 * @param[in] list Liste circulaire.
 *
 * @retval true   Liste vide.
 * @retval false  Au moins un element dans la liste.
 */
bool CLIST_IsEmpty(const clist_s* list);

/**
 * @brief Calcule le nombre d'element de la liste.
 *
 * @param[in] list  Liste circulaire.
 *
 * @return Nombre d'element de la liste.
 */
size_t CLIST_Size(const clist_s* list);

/**
 * @brief Verifie si l'element courant est le premier.
 *
 * @param[in] list Liste circulaire.
 *
 * @retval true   Premier element de la liste.
 * @retval false  Autre element.
 */
bool CLIST_IsHead(const clist_s* list);

/**
 * @brief Insere un element en tete de liste.
 *
 *
 * @param[in,out] list  Liste circulaire
 * @param[in] data      Element a ajouter
 * @param[in] dataSize  Taille de l'element
 *
 * @retval CLIST_NO_ERROR     Insertion reussie.
 * @retval CLIST_MEMORY_ERROR Erreur d'allocation ou pas d'element a inserer.
 *
 * @note L'element insere devient l'element courant.
 */
CLIST_Error_e CLIST_InsertFirst(clist_s* list, const void* data, size_t dataSize);

/**
 * @brief Insere un element dans liste apres l'element courant.
 *
 * @param[in,out] list  Liste circulaire.
 * @param[in] data      Element a ajouter.
 * @param[in] dataSize  Taille de l'element.
 *
 * @retval CLIST_NO_ERROR     Insertion reussie.
 * @retval CLIST_MEMORY_ERROR Erreur d'allocation ou pas d'element a inserer.
 *
 * @note L'element insere devient l'element courant.
 */
CLIST_Error_e CLIST_InsertNext(clist_s* list, const void* data, size_t dataSize);

/**
 * @brief Insere un element dans liste avant l'element courant.
 *
 * @param[in,out] list  Liste circulaire.
 * @param[in] data      Element a ajouter.
 * @param[in] dataSize  Taille de l'element.
 *
 * @retval CLIST_NO_ERROR     Insertion reussie.
 * @retval CLIST_MEMORY_ERROR Erreur d'allocation ou pas d'element a inserer.
 *
 * @note L'element insere devient l'element courant.
 */
CLIST_Error_e CLIST_InsertPrev(clist_s* list, const void* data, size_t dataSize);

/**
 * @brief Selectionne le premier element.
 *
 * @param[in,out] list  Liste circulaire.
 *
 * @retval CLIST_NO_ERROR     Selection reussi.
 * @retval CLIST_EMPTY_LIST   Liste vide.
 */
CLIST_Error_e CLIST_SeekFirst(clist_s* list);

/**
 * @brief Selectionne l'element suivant.
 *
 * @param[in,out] list  Liste circulaire.
 *
 * @retval CLIST_NO_ERROR     Selection reussi.
 * @retval CLIST_EMPTY_LIST   Liste vide.
 */
CLIST_Error_e CLIST_SeekNext(clist_s* list);

/**
 * @brief Selectionne l'element precedent.
 *
 * @param[in,out] list  Liste circulaire.
 *
 * @retval CLIST_NO_ERROR     Selection reussi.
 * @retval CLIST_EMPTY_LIST   Liste vide.
 */
CLIST_Error_e CLIST_SeekPrev(clist_s* list);

/**
 * @brief Lit le premier element.
 *
 * @param[in] list  Liste circulaire.
 *
 * @return Element lu (NULL en cas d'erreur).
 */
const void* CLIST_ReadFirst(const clist_s* list);

/**
 * @brief Lit l'element courant.
 *
 * @param[in] list  Liste circulaire.
 *
 * @return Element lu (NULL en cas d'erreur).
 */
const void* CLIST_ReadCurrent(const clist_s* list);

/**
 * @brief Lit l'element suivant.
 *
 * @param[in] list  Liste circulaire.
 *
 * @return Element lu (NULL en cas d'erreur).
 */
const void* CLIST_ReadNext(const clist_s* list);

/**
 * @brief Lit l'element precedent.
 *
 * @param[in] list  Liste circulaire.
 *
 * @return Element lu (NULL en cas d'erreur).
 */
const void* CLIST_ReadPrev(const clist_s* list);

/**
 * @brief Lit et supprime le premier element.
 *
 * @param[in,out] list  Liste circulaire.
 *
 * @return Element lu (NULL en cas d'erreur).
 *
 * @note Si cet element etait l'element courant, l'element suivant devient le nouvel element courant.
 */
const void* CLIST_GetFirst(clist_s* list);

/**
 * @brief Lit et supprime l'element courant.
 *
 * @param[in,out] list  Liste circulaire.
 *
 * @return Element lu (NULL en cas d'erreur).
 *
 * @note L'element suivant devient le nouvel element courant.
 */
const void* CLIST_GetCurrent(clist_s* list);

/**
 * @brief Lit et supprime l'element suivant.
 *
 * @param[in,out] list  Liste circulaire.
 *
 * @return Element lu (NULL en cas d'erreur).
 */
const void* CLIST_GetNext(clist_s* list);

/**
 * @brief Lit et supprime l'element precedent.
 *
 * @param[in,out] list  Liste circulaire.
 *
 * @return Element lu (NULL en cas d'erreur).
*/
const void* CLIST_GetPrev(clist_s* list);

/**
 * @brief Supprime le premier element.
 *
 * @param[in,out] list  Liste circulaire.
 *
 * @retval CLIST_NO_ERROR   Suppression reussie.
 * @retval CLIST_EMPTY_LIST Liste vide.
 *
 * @note Si cet element etait l'element courant, l'element suivant devient le nouvel element courant.
 */
CLIST_Error_e CLIST_RemoveFirst(clist_s* list);

/**
 * @brief Supprime l'element courant.
 *
 * @param[in,out] list  Liste circulaire.
 *
 * @retval CLIST_NO_ERROR   Suppression reussie.
 * @retval CLIST_EMPTY_LIST Liste vide.
 *
 * @note L'element suivant devient le nouvel element courant.
 */
CLIST_Error_e CLIST_RemoveCurrent(clist_s* list);

/**
 * @brief Supprime l'element suivant.
 *
 * @param[in,out] list  Liste circulaire.
 *
 * @retval CLIST_NO_ERROR   Suppression reussie.
 * @retval CLIST_EMPTY_LIST Liste vide.
 */
CLIST_Error_e CLIST_RemoveNext(clist_s* list);

/**
 * @brief Supprime l'element precedent.
 *
 * @param[in,out] list  Liste circulaire.
 *
 * @retval CLIST_NO_ERROR   Suppression reussie.
 * @retval CLIST_EMPTY_LIST Liste vide.
 */
CLIST_Error_e CLIST_RemovePrev(clist_s* list);

/**
 * @brief Duplique une liste.
 *
 * @param[in] list  Liste a dupliquer.
 *
 * @return Copie de la liste.
 */
clist_s* CLIST_Clone(const clist_s* list);

/**
 * @brief Recherche un element dans la liste.
 *
 * @param[in,out] list  Liste circulaire.
 * @param[in] data      Donnee recherchee.
 *
 * @retval CLIST_NO_ERROR         Element trouve.
 * @retval CLIST_EMPTY_LIST       Liste vide.
 * @retval CLIST_CELL_NOT_FOUND   Element absent.
 * @retval CLIST_NO_COMP_FONCTION Aucune fonction  de comparaison definie.
 *
 * @note Si l'element est present, il devient le nouvel element courant de la liste.
*/
CLIST_Error_e CLIST_SearchData(clist_s* list, const void* data);

/**
 * @brief Recherche un element dans la liste.
 *
 * @param[in,out] list  Liste circulaire.
 * @param[in] data      Donnee recherchee.
 * @param[in] compar    Fonction de comparaison (si NULL la fonction par defaut est utilisee).
 *
 * @retval CLIST_NO_ERROR         Element trouve.
 * @retval CLIST_EMPTY_LIST       Liste vide.
 * @retval CLIST_CELL_NOT_FOUND   Element absent.
 * @retval CLIST_NO_COMP_FONCTION Aucune fonction  de comparaison definie.
 *
 * @note Si l'element est present, il devient le nouvel element courant de la liste.
 */
CLIST_Error_e CLIST_SearchDataFct(clist_s* list, const void* data, int (*compar)(const void *, const void *));

/**
 * @brief Recherche un element dans la liste.
 *
 * @param[in,out] list  Liste circulaire.
 * @param[in] data      Donnee recherchee.
 *
 * @retval CLIST_NO_ERROR         Element trouve.
 * @retval CLIST_EMPTY_LIST       Liste vide.
 * @retval CLIST_CELL_NOT_FOUND   Element absent.
 * @retval CLIST_NO_COMP_FONCTION Aucune fonction  de comparaison definie.
 *
 * @note La recherche s'effectue en remontant la liste.
 * @note Si l'element est present, il devient le nouvel element courant de la liste.
 */
CLIST_Error_e CLIST_SearchDataRev(clist_s* list, const void* data);

/**
 * @brief Recherche un element dans la liste.
 *
 * @param[in,out] list  Liste circulaire.
 * @param[in] data      Donnee recherchee.
 * @param[in] compar    Fonction de comparaison (si NULL la fonction par defaut est utilisee).
 *
 * @retval CLIST_NO_ERROR         Element trouve.
 * @retval CLIST_EMPTY_LIST       Liste vide.
 * @retval CLIST_CELL_NOT_FOUND   Element absent.
 * @retval CLIST_NO_COMP_FONCTION Aucune fonction  de comparaison definie.
 *
 * @note La recherche s'effectue en remontant la liste.
 * @note Si l'element est present, il devient le nouvel element courant de la liste.
 */
CLIST_Error_e CLIST_SearchDataRevFct(clist_s* list, const void* data, int (*compar)(const void *, const void *));

/**
 * @brief Supprime la premiere cellule contenant la donnee recherchee.
 *
 * @param[in,out] list  Liste circulaire.
 * @param[in] data      Donnee a supprimee.
 *
 * @retval CLIST_NO_ERROR         Element supprimme.
 * @retval CLIST_EMPTY_LIST       Liste vide.
 * @retval CLIST_CELL_NOT_FOUND   Element absent.
 * @retval CLIST_NO_COMP_FONCTION Aucune fonction  de comparaison definie.
 *
 * @note Si l'element courant correspond au critere de recherche, l'element suivant devient le nouvel element courant.
 */
CLIST_Error_e CLIST_RemoveData(clist_s* list, const void* data);

/**
 * @brief Supprime la premiere cellule contenant la donnee recherchee.
 *
 * @param[in,out] list  Liste circulaire.
 * @param[in] data      Donnee a supprimee.
 * @param[in] compar    Fonction de comparaison (si NULL la fonction par defaut est utilisee).
 *
 * @retval CLIST_NO_ERROR         Element supprimme.
 * @retval CLIST_EMPTY_LIST       Liste vide.
 * @retval CLIST_CELL_NOT_FOUND   Element absent.
 * @retval CLIST_NO_COMP_FONCTION Aucune fonction  de comparaison definie.
 *
 * @note Si l'element courant correspond au critere de recherche, l'element suivant devient le nouvel element courant.
 */
CLIST_Error_e CLIST_RemoveDataFct(clist_s* list, const void* data, int (*compar)(const void *, const void *));

/**
 * @brief Supprime la premiere cellule contenant la donnee recherchee.
 *
 * @param[in,out] list  Liste circulaire.
 * @param[in] data      Donnee a supprimee.
 *
 * @retval CLIST_NO_ERROR         Element supprimme.
 * @retval CLIST_EMPTY_LIST       Liste vide.
 * @retval CLIST_CELL_NOT_FOUND   Element absent.
 * @retval CLIST_NO_COMP_FONCTION Aucune fonction  de comparaison definie.
 *
 * @note La recherche s'effectue en remontant la liste.
 * @note Si l'element courant correspond au critere de recherche, l'element suivant devient le nouvel element courant.
 */
CLIST_Error_e CLIST_RemoveDataRev(clist_s* list, const void* data);

/**
 * @brief Supprime la premiere cellule contenant la donnee recherchee.
 *
 * @param[in,out] list  Liste circulaire.
 * @param[in] data      Donnee a supprimee.
 * @param[in] compar    Fonction de comparaison (si NULL la fonction par defaut est utilisee).
 *
 * @retval CLIST_NO_ERROR         Element supprimme.
 * @retval CLIST_EMPTY_LIST       Liste vide.
 * @retval CLIST_CELL_NOT_FOUND   Element absent.
 * @retval CLIST_NO_COMP_FONCTION Aucune fonction  de comparaison definie.
 *
 * @note La recherche s'effectue en remontant la liste.
 * @note Si l'element courant correspond au critere de recherche, l'element suivant devient le nouvel element courant.
 */
CLIST_Error_e CLIST_RemoveDataRevFct(clist_s* list, const void* data, int (*compar)(const void *, const void *));

/**
 * @brief Supprime toutes les cellules contenant la donnee recherchee.
 *
 * @param[in,out] list  Liste circulaire.
 * @param[in] data      Donnee a supprimee.
 *
 * @retval CLIST_NO_ERROR         Elements supprimmes.
 * @retval CLIST_EMPTY_LIST       Liste vide.
 * @retval CLIST_NO_COMP_FONCTION Aucune fonction  de comparaison definie.
 *
 * @note Si l'element courant correspond au critere de recherche, l'element suivant devient le nouvel element courant.
 */
CLIST_Error_e CLIST_RemoveAllData(clist_s* list, const void* data);

/**
 * @brief Supprime toutes les cellules contenant la donnee recherchee.
 *
 * @param[in,out] list  Liste circulaire
 * @param[in] data      Donnee a supprimee
 * @param[in] compar    Fonction de comparaison (si NULL la fonction par defaut est utilisee)
 *
 * @retval CLIST_NO_ERROR         Elements supprimmes.
 * @retval CLIST_EMPTY_LIST       Liste vide.
 * @retval CLIST_NO_COMP_FONCTION Aucune fonction  de comparaison definie.
 *
 * @note Si l'element courant correspond au critere de recherche, l'element suivant devient le nouvel element courant.
 */
CLIST_Error_e CLIST_RemoveAllDataFct(clist_s* list, const void* data, int (*compar)(const void *, const void *));

#ifdef __cplusplus
}
#endif

#endif
