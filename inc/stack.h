/**
 * @file
 * @brief Gestion de piles.
 * @version 1.0.0.
 * @copyright MIT license.
 * @author Gregory Lerbret.
 */

#ifndef GL_STACK_H
#define GL_STACK_H

#include "bool.h"

#include <stddef.h>

/**
 * @brief Structure de la pile.
 */
typedef struct stack stack_s;

/**
 * @brief Resultat des traitements sur les piles.
 */
typedef enum
{
  /// @brief Pas d'erreur.
  STACK_NO_ERROR,
  /// @brief Erreur d'allocation.
  STACK_MEMORY_ERROR,
  /// @brief La pile est vide.
  STACK_EMPTY_STACK
} STACK_Error_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @return Identifiant du module (nom et version).
 */
const char* STACK_Identifier(void);

/**
 * @return Version du module.
 */
int STACK_Version(void);

/**
 * @brief Cree une pile.
 *
 * @return Pile cree (NULL en cas d'erreur).
 */
stack_s* STACK_Create(void);

/**
 * @brief Destruit une pile.
 *
 * @param[in] stack   Pile a detruire.
 */
void STACK_Destroy(stack_s* stack);

/**
 * @brief Verifie la vacuite de la pile.
 *
 * @param[in] stack   Pile.
 *
 * @retval true   Pile vide.
 * @retval false  Au moins un element dans la pile.
 */
bool STACK_IsEmpty(const stack_s* stack);

/**
 * @brief Calcule le nombre d'elements de la pile.
 *
 * @param[in] stack   Pile.
 *
 * @return Nombre d'elements de la pile.
 */
size_t STACK_Size(const stack_s* stack);

/**
 * @brief Ajoute un element a la pile.
 *
 * @param[in,out] stack Pile.
 * @param[in] data      Element a ajouter.
 * @param[in] dataSize  Taille de l'element.
 *
 * @retval STACK_NO_ERROR     Ajout reussi.
 * @retval STACK_MEMORY_ERROR Erreur d'allocation ou pas d'element a inserer.
 */
STACK_Error_e STACK_Push(stack_s* stack, const void* data, size_t dataSize);

/**
 * @brief Lit et supprime un element de la pile.
 *
 * @param[in,out] stack   Pile.
 *
 * @return Element lu (NULL en cas d'erreur).
 */
const void* STACK_Pop(stack_s* stack);

/**
 * @brief Lit un element de la pile.
 *
 * @param[in] stack   Pile.
 *
 * @return Element lu (NULL en cas d'erreur).
 */
const void* STACK_Peek(const stack_s* stack);

/**
 * @brief Supprime un element de la pile.
 *
 * @param[in,out] stack   Pile.
 *
 * @retval STACK_NO_ERROR     Suppression reussie.
 * @retval STACK_EMPTY_STACK  Pile vide.
 */
STACK_Error_e STACK_Remove(stack_s* stack);

/**
 * @brief Duplique d'une pile.
 *
 * @param[in] stack   Pile.
 *
 * @return Copie de la pile.
 */
stack_s* STACK_Clone(const stack_s* stack);

#ifdef __cplusplus
}
#endif

#endif
