/**
 * @author Gregory Lerbret
 * @file
 * @brief Gestion de piles
 * @date 24/09/2006
 * @version 1.0.0
 */

#ifndef GL_STACK_H
#define GL_STACK_H

#include "bool.h"

#include <stddef.h>

/**
 * @brief Structure de la pile
 */
typedef struct stack stack_s;

/**
 * @brief Resultat des traitements sur les piles
 */
typedef enum
{
    /// @brief Pas d'erreur
    STACK_NO_ERROR,
    /// @brief Erreur d'allocation
    STACK_MEMORY_ERROR,
    /// @brief La pile est vide
    STACK_EMPTY_STACK
} STACK_Error_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @return Identifiant du module (nom et version)
 */
const char* STACK_Identifier(void);

/**
 * @return Version du module
 */
int STACK_Version(void);

/**
 * @brief Creation d'une pile
 *
 * @param[out] error Resultat de la creation :
 *                      - STACK_NO_ERROR : la creation s'est correctement deroulee
 *                      - STACK_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire
 *
 * @return Pile cree (NULL en cas d'erreur)
 */
stack_s* STACK_Create(STACK_Error_e* error);

/**
 * @brief Destruction d'une pile
 *
 * @param[in] stack Pile
 */
void STACK_Destroy(stack_s* stack);

/**
 * @brief Verification de la vacuite de la pile
 *
 * @param[in] stack Pile
 *
 * @return
 *  - TRUE si la pile est vide
 *  - FALSE sinon
 */
bool STACK_IsEmpty(const stack_s* stack);

/**
 * @brief Calcul du nombre d'element de la pile
 *
 * @param[in] stack Pile
 *
 * @return Nombre d'element de la pile
 */
size_t STACK_Size(const stack_s* stack);

/**
 * @brief Ajout d'un element a la pile
 *
 * @param[in,out] stack Pile
 * @param[in] data Element a ajouter
 * @param[in] dataSize Taille de l'element
 *
 * @return
 *  - STACK_NO_ERROR : l'ajout s'est correctement deroule
 *  - STACK_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire ou il n'existe pas de donnee a inserer
 */
STACK_Error_e STACK_Push(stack_s* stack, const void* data, size_t dataSize);

/**
 * @brief Lecture et suppression d'un element de la pile
 *
 * @param[in,out] stack Pile
 * @param[out] error Resultat de la lecture :
 *                      - STACK_NO_ERROR : la lecture s'est correctement deroulee
 *                      - STACK_EMPTY_STACK : la pile est vide
 *
 * @return Element lu (NULL en cas d'erreur).
 */
const void* STACK_Pop(stack_s* stack, STACK_Error_e* error);

/**
 * @brief Lecture d'un element de la pile
 *
 * @param[in] stack Pile
 * @param[out] error Resultat de la lecture :
 *                      - STACK_NO_ERROR : la lecture s'est correctement deroulee
 *                      - STACK_EMPTY_STACK : la pile est vide
 *
 * @return Element lu (NULL en cas d'erreur)
 */
const void* STACK_Peek(const stack_s* stack, STACK_Error_e* error);

/**
 * @brief Suppression d'un element de la pile
 *
 * @param[in,out] stack Pile
 *
 * @return
 *  - STACK_NO_ERROR : la suppression s'est correctement deroulee
 *  - STACK_EMPTY_STACK : la pile est vide
 */
STACK_Error_e STACK_Remove(stack_s* stack);

/**
 * @brief Duplication d'une pile
 *
 * @param[in] stack Pile
 * @param[out] error Statut de la duplication :
 *                      - STACK_NO_ERROR : la copie s'est correctement deroulee
 *                      - STACK_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire
 * @return La copie de la pile.
 */
stack_s* STACK_Clone(const stack_s* stack, STACK_Error_e* error);

#ifdef __cplusplus
}
#endif

#endif
