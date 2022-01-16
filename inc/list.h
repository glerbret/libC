/**
 * @file
 * @brief Gestion de listes.
 * @version 1.0.0.
 * @copyright MIT license.
 * @author Gregory Lerbret.
 */

#ifndef GL_LIST_H
#define GL_LIST_H

#include "bool.h"

/// @cond
#include <stddef.h>
/// @endcond

/**
 * @brief Liste.
 */
typedef struct list list_s;

/**
 * @brief Resultat des traitements sur les listes.
 */
typedef enum
{
  /// @brief Pas d'erreur.
  LIST_NO_ERROR,
  /// @brief Erreur d'allocation.
  LIST_MEMORY_ERROR,
  /// @brief La liste est vide.
  LIST_EMPTY_LIST,
  /// @brief Element absent.
  LIST_CELL_NOT_FOUND,
  /// @brief Aucune fonction de comparaison n'est definie.
  LIST_NO_COMP_FONCTION
} LIST_Error_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @return Identifiant du module (nom et version).
 */
const char* LIST_Identifier(void);

/**
 * @return Version du module.
 */
int LIST_Version(void);

/**
 * @brief Cree une liste.
 *
 * @param[in] compar  Fonction de comparaison des elements.
 *
 * @return Liste (NULL en cas d'erreur).
 */
list_s* LIST_Create(int (*compar)(const void *, const void *));

/**
 * @brief Destruction d'une liste.
 *
 * @param[in,out] list  Liste.
 */
void LIST_Destroy(list_s* list);

/**
 * @brief Met a jour la fonction de comparaison.
 *
 * @param[in,out] list  Liste.
 * @param[in] compar    Fonction de comparaison.
 */
void LIST_SetCmp(list_s* list, int (*compar)(const void *, const void *));

/**
 * @brief Verifie la vacuite de la liste.
 *
 * @param[in] list  Liste.
 *
 * @retval true   Liste vide.
 * @retval false  Au moins un element present.
 */
bool LIST_IsEmpty(const list_s* list);

/**
 * @brief Calcule le nombre d'element de la liste.
 *
 * @param[in] list  Liste.
 *
 * @return Nombre d'element de la liste.
 */
size_t LIST_Size(const list_s* list);

/**
 * @brief Verifie si l'element courant est le premier.
 *
 * @param[in] list  Liste.
 *
 * @retval true   Premier element de la liste.
 * @retval false  Autre element.
 */
bool LIST_IsHead(const list_s* list);

/**
 * @brief Verifie si l'element courant est le dernier.
 *
 * @param[in] list  Liste.
 *
 * @retval true   Dernier element de la liste.
 * @retval false  Autre element.
 */
bool LIST_IsTail(const list_s* list);

/**
 * @brief Insere un element en tete de liste.
 *
 * @param[in,out] list  Liste.
 * @param[in] data      Element a ajouter.
 * @param[in] dataSize  Taille de l'element.
 *
 * @retval LIST_NO_ERROR      Insertion reussie.
 * @retval LIST_MEMORY_ERROR  Erreur d'allocation ou pas d'element a inserer.
 *
 * @note L'element insere devient l'element courant.
 */
LIST_Error_e LIST_InsertFirst(list_s* list, const void* data, size_t dataSize);

/**
 * @brief Insere un element en fin de liste.
 *
 * @param[in,out] list  Liste.
 * @param[in] data      Element a ajouter.
 * @param[in] dataSize  Taille de l'element.
 *
 * @retval LIST_NO_ERROR      Insertion reussie.
 * @retval LIST_MEMORY_ERROR  Erreur d'allocation ou pas d'element a inserer.
 *
 * @note L'element insere devient l'element courant.
 */
LIST_Error_e LIST_InsertLast(list_s* list, const void* data, size_t dataSize);

/**
 * @brief Insere un element dans liste apres l'element courant.
 *
 * @param[in,out] list  Liste.
 * @param[in] data      Element a ajouter.
 * @param[in] dataSize  Taille de l'element.
 *
 * @retval LIST_NO_ERROR      Insertion reussie.
 * @retval LIST_MEMORY_ERROR  Erreur d'allocation ou pas d'element a inserer.
 *
 * @note L'element insere devient l'element courant.
 */
LIST_Error_e LIST_InsertNext(list_s* list, const void* data, size_t dataSize);

/**
 * @brief Insere un element dans liste avant l'element courant.
 *
 * @param[in,out] list  Liste.
 * @param[in] data      Element a ajouter.
 * @param[in] dataSize  Taille de l'element.
 *
 * @retval LIST_NO_ERROR      Insertion reussie.
 * @retval LIST_MEMORY_ERROR  Erreur d'allocation ou pas d'element a inserer.
 *
 * @note L'element insere devient l'element courant.
 */
LIST_Error_e LIST_InsertPrev(list_s* list, const void* data, size_t dataSize);

/**
 * @brief Selectionne le premier element.
 *
 * @param[in,out] list  Liste.
 *
 * @retval LIST_NO_ERROR    Selection reussie.
 * @retval LIST_EMPTY_LIST  Liste vide.
 */
LIST_Error_e LIST_SeekFirst(list_s* list);

/**
 * @brief Selectionne le dernier element.
 *
 * @param[in,out] list  Liste.
 *
 * @retval LIST_NO_ERROR    Selection reussie.
 * @retval LIST_EMPTY_LIST  Liste vide.
 */
LIST_Error_e LIST_SeekLast(list_s* list);

/**
 * @brief Selectionne l'element suivant.
 *
 * @param[in,out] list  Liste.
 *
 * @retval LIST_NO_ERROR        Selection reussie.
 * @retval LIST_EMPTY_LIST      Liste vide.
 * @retval LIST_CELL_NOT_FOUND  Element courant est le dernier de la liste.
 */
LIST_Error_e LIST_SeekNext(list_s* list);

/**
 * @brief Selectionne l'element precedent.
 *
 * @param[in,out] list  Liste.
 *
 * @retval LIST_NO_ERROR        Selection reussie.
 * @retval LIST_EMPTY_LIST      Liste vide.
 * @retval LIST_CELL_NOT_FOUND  Element courant est le premier de la liste.
 */
LIST_Error_e LIST_SeekPrev(list_s* list);

/**
 * @brief Lit le premier element.
 *
 * @param[in] list  Liste.
 *
 * @return Element lu (NULL en cas d'erreur).
 */
const void* LIST_ReadFirst(const list_s* list);

/**
 * @brief Lit le dernier element.
 *
 * @param[in] list  Liste.
 *
 * @return Element lu (NULL en cas d'erreur).
 */
const void* LIST_ReadLast(const list_s* list);

/**
 * @brief Lit l'element courant.
 *
 * @param[in] list  Liste.
 *
 * @return Element lu (NULL en cas d'erreur).
 */
const void* LIST_ReadCurrent(const list_s* list);

/**
 * @brief Lit l'element suivant.
 *
 * @param[in] list  Liste.
 *
 * @return Element lu (NULL en cas d'erreur).
 */
const void* LIST_ReadNext(const list_s* list);

/**
 * @brief Lit l'element precedent.
 *
 * @param[in] list  Liste.
 *
 * @return Element lu (NULL en cas d'erreur).
 */
const void* LIST_ReadPrev(const list_s* list);

/**
 * @brief Lit et supprime le premier element.
 *
 * @param[in,out] list  Liste.
 *
 * @return Element lu (NULL en cas d'erreur).
 *
 * @note Si cet element etait l'element courant, l'element suivant devient le nouvel element courant.
 */
const void* LIST_GetFirst(list_s* list);

/**
 * @brief Lit et supprime le dernier element.
 *
 * @param[in,out] list  Liste.
 *
 * @return Element lu (NULL en cas d'erreur).
 *
 * @note Si cet element etait l'element courant, l'element suivant devient le nouvel element courant.
 */
const void* LIST_GetLast(list_s* list);

/**
 * @brief Lit et supprime l'element courant.
 *
 * @param[in,out] list  Liste.
 *
 * @return Element lu (NULL en cas d'erreur).
 *
 * @note L'element suivant (ou l'element precedent si l'element courant etait le dernier de la liste) devient l'element courant.
 */
const void* LIST_GetCurrent(list_s* list);

/**
 * @brief Lit et supprime l'element suivant.
 *
 * @param[in,out] list  Liste.
 *
 * @return Element lu (NULL en cas d'erreur).
 */
const void* LIST_GetNext(list_s* list);

/**
 * @brief Lit et supprime l'element precedent.
 *
 * @param[in,out] list  Liste.
 *
 * @return Element lu (NULL en cas d'erreur).
 */
const void* LIST_GetPrev(list_s* list);

/**
 * @brief Supprime le premier element.
 *
 * @param[in,out] list  Liste.
 *
 * @retval LIST_NO_ERROR    Suppression reussie.
 * @retval LIST_EMPTY_LIST  Liste vide.
 *
 * @note Si cet element etait l'element courant, l'element suivant devient le nouvel element courant.
 */
LIST_Error_e LIST_RemoveFirst(list_s* list);

/**
 * @brief Supprime le dernier element.
 *
 * @param[in,out] list  Liste.
 *
 * @retval LIST_NO_ERROR    Suppression reussie.
 * @retval LIST_EMPTY_LIST  Liste vide.
 *
 * @note Si cet element etait l'element courant, l'element precedent devient le nouvel element courant.
 */
LIST_Error_e LIST_RemoveLast(list_s* list);

/**
 * @brief Supprime l'element courant.
  *
 * @param[in,out] list  Liste.
 *
 * @retval LIST_NO_ERROR    Suppression reussie.
 * @retval LIST_EMPTY_LIST  Liste vide.
 *
 * @note L'element suivant (ou precedent si l'element courant est le dernier de la liste) devient l'element courant.
 */
LIST_Error_e LIST_RemoveCurrent(list_s* list);

/**
 * @brief Supprime l'element suivant.
 *
 * @param[in,out] list  Liste.
 *
 * @retval LIST_NO_ERROR        Suppression reussie.
 * @retval LIST_EMPTY_LIST      Liste vide.
 * @retval LIST_CELL_NOT_FOUND  Element courant est le dernier de la liste.
 */
LIST_Error_e LIST_RemoveNext(list_s* list);

/**
 * @brief Supprime l'element precedent.
 *
 * @param[in,out] list  Liste.
 *
 * @retval LIST_NO_ERROR        Suppression reussie.
 * @retval LIST_EMPTY_LIST      Liste vide.
 * @retval LIST_CELL_NOT_FOUND  Element courant est le premier de la liste.
 */
LIST_Error_e LIST_RemovePrev(list_s* list);

/**
 * @brief Duplique une liste.
 *
 * @param[in] list  Liste a dupliquer.
 *
 * @return Copie de la liste (NULL en cas d'erreur).
 */
list_s* LIST_Clone(const list_s* list);

/**
 * @brief Recherche un element dans la liste apres l'element courant.
 *
 * @param[in,out] list  Liste.
 * @param[in] data      Donnee recherchee.
 *
 * @retval LIST_NO_ERROR          Element trouve.
 * @retval LIST_EMPTY_LIST        Liste vide.
 * @retval LIST_CELL_NOT_FOUND    Element absent.
 * @retval LIST_NO_COMP_FONCTION  Aucune fonction de comparaison n'est definie.
 *
 * @note Si l'element est present, il devient le nouvel element courant de la liste.
 */
LIST_Error_e LIST_SearchData(list_s* list, const void* data);

/**
 * @brief Recherche un element dans la liste apres l'element courant.
 *
 * @param[in,out] list  Liste.
 * @param[in] data      Donnee recherchee.
 * @param[in] compar    Fonction de comparaison (si NULL la fonction par defaut est utilisee).
 *
 * @retval LIST_NO_ERROR          Element trouve.
 * @retval LIST_EMPTY_LIST        Liste vide.
 * @retval LIST_CELL_NOT_FOUND    Element absent.
 * @retval LIST_NO_COMP_FONCTION  Aucune fonction de comparaison n'est definie.
 *
 * @note Si l'element est present, il devient le nouvel element courant de la liste.
 */
LIST_Error_e LIST_SearchDataFct(list_s* list, const void* data, int (*compar)(const void *, const void *));

/**
 * @brief Recherche un element dans la liste avant l'element courant.
 *
 * @param[in,out] list  Liste.
 * @param[in] data      Donnee recherchee.
 *
 * @retval LIST_NO_ERROR          Element trouve.
 * @retval LIST_EMPTY_LIST        Liste vide.
 * @retval LIST_CELL_NOT_FOUND    Element absent.
 * @retval LIST_NO_COMP_FONCTION  Aucune fonction de comparaison n'est definie.
 *
 * @note Si l'element est present, il devient le nouvel element courant de la liste.
 */
LIST_Error_e LIST_SearchDataRev(list_s* list, const void* data);

/**
 * @brief Recherche un element dans la liste avant l'element courant.
 *
 * @param[in,out] list  Liste.
 * @param[in] data      Donnee recherchee.
 * @param[in] compar    Fonction de comparaison (si NULL la fonction par defaut est utilisee).
 *
 * @retval LIST_NO_ERROR          Element trouve.
 * @retval LIST_EMPTY_LIST        Liste vide.
 * @retval LIST_CELL_NOT_FOUND    Element absent.
 * @retval LIST_NO_COMP_FONCTION  Aucune fonction de comparaison n'est definie.
 *
 * @note Si l'element est present, il devient le nouvel element courant de la liste.
 */
LIST_Error_e LIST_SearchDataRevFct(list_s* list, const void* data, int (*compar)(const void *, const void *));

/**
 * @brief Supprime la premiere cellule situee apres l'element courant contenant la donnee recherchee.
 *
 * @param[in,out] list  Liste.
 * @param[in] data      Donnee a supprimee.
 *
 * @retval LIST_NO_ERROR          Element supprime.
 * @retval LIST_EMPTY_LIST        Liste vide.
 * @retval LIST_CELL_NOT_FOUND    Element absent.
 * @retval LIST_NO_COMP_FONCTION  Aucune fonction de comparaison n'est definie.
 *
 * @note Si l'element courant correspond au critere de recherche, l'element suivant (ou l'element precedent
 *        si l'element courant est le dernier de la liste) devient le nouvel element courant
 */
LIST_Error_e LIST_RemoveData(list_s* list, const void* data);

/**
 * @brief Supprime la premiere cellule situee apres l'element courant contenant la donnee recherchee.
 *
 * @param[in,out] list  Liste.
 * @param[in] data      Donnee a supprimee.
 * @param[in] compar    Fonction de comparaison (si NULL la fonction par defaut est utilisee).
 *
 * @retval LIST_NO_ERROR          Element supprime.
 * @retval LIST_EMPTY_LIST        Liste vide.
 * @retval LIST_CELL_NOT_FOUND    Element absent.
 * @retval LIST_NO_COMP_FONCTION  Aucune fonction de comparaison n'est definie.
 *
 * @note Si l'element courant correspond au critere de recherche, l'element suivant (ou l'element precedent
 *        si l'element courant est le dernier de la liste) devient le nouvel element courant.
 */
LIST_Error_e LIST_RemoveDataFct(list_s* list, const void* data, int (*compar)(const void *, const void *));

/**
 * @brief Supprime la premiere cellule situee avant l'element courant contenant la donnee recherchee
 *
 * @param[in,out] list  Liste.
 * @param[in] data      Donnee a supprimee.
 *
 * @retval LIST_NO_ERROR          Element supprime.
 * @retval LIST_EMPTY_LIST        Liste vide.
 * @retval LIST_CELL_NOT_FOUND    Element absent.
 * @retval LIST_NO_COMP_FONCTION  Aucune fonction de comparaison n'est definie.
 *
 * @note Si l'element courant correspond au critere de recherche, l'element suivant (ou l'element precedent
 *        si l'element courant est le dernier de la liste) devient le nouvel element courant.
 */
LIST_Error_e   LIST_RemoveDataRev(list_s* list, const void* data);

/**
 * @brief Supprime la premiere cellule situee avant l'element courant contenant la donnee recherchee.
 *
 * @param[in,out] list  Liste.
 * @param[in] data      Donnee a supprimee.
 * @param[in] compar    Fonction de comparaison (si NULL la fonction par defaut est utilisee).
 *
 * @retval LIST_NO_ERROR          Element supprime.
 * @retval LIST_EMPTY_LIST        Liste vide.
 * @retval LIST_CELL_NOT_FOUND    Element absent.
 * @retval LIST_NO_COMP_FONCTION  Aucune fonction de comparaison n'est definie.
 *
 * @note Si l'element courant correspond au critere de recherche, l'element suivant (ou l'element precedent
 *        si l'element courant est le dernier de la liste) devient le nouvel element courant.
 */
LIST_Error_e LIST_RemoveDataRevFct(list_s* list, const void* data, int (*compar)(const void *, const void *));

/**
 * @brief Supprime toutes les cellules contenant la donnee recherchee.
 *
 * @param[in,out] list  Liste.
 * @param[in] data      Donnee a supprimee.
 *
 * @retval LIST_NO_ERROR          Element supprime.
 * @retval LIST_EMPTY_LIST        Liste vide.
 * @retval LIST_NO_COMP_FONCTION  Aucune fonction de comparaison n'est definie.
 *
 * @note Si l'element courant correspond au critere de recherche, l'element suivant (ou l'element precedent
 *        si l'element courant est le dernier) devient le nouvel element courant.
 */
LIST_Error_e LIST_RemoveAllData(list_s* list, const void* data);

/**
 * @brief Supprime toutes les cellules contenant la donnee recherchee.
 *
 * @param[in,out] list  Liste.
 * @param[in] data      Donnee a supprimee.
 * @param[in] compar    Fonction de comparaison (si NULL la fonction par defaut est utilisee).
 *
 * @retval LIST_NO_ERROR          Element supprime.
 * @retval LIST_EMPTY_LIST        Liste vide.
 * @retval LIST_NO_COMP_FONCTION  Aucune fonction de comparaison n'est definie.
 *
 * @note Si l'element courant correspond au critere de recherche, l'element suivant (ou l'element precedent
 *        si l'element courant est le dernier) devient le nouvel element courant.
 */
LIST_Error_e LIST_RemoveAllDataFct(list_s* list, const void* data, int (*compar)(const void *, const void *));

#ifdef __cplusplus
}
#endif

#endif
