 /**
 * @file
 * @brief Gestion de files.
 * @version 1.0.0.
 * @copyright MIT license.
 * @author Gregory Lerbret.
 */

#ifndef GL_QUEUE_H
#define GL_QUEUE_H

#include "bool.h"

#include <stddef.h>

/**
 * @brief Structure de la file.
 */
typedef struct queue queue_s;

/**
 * @brief Resultat des traitements sur les files.
 */
typedef enum
{
  /// @brief Pas d'erreur.
  QUEUE_NO_ERROR,
  /// @brief Erreur d'allocation.
  QUEUE_MEMORY_ERROR,
  /// @brief La file est vide.
  QUEUE_EMPTY_QUEUE
} QUEUE_Error_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @return Identifiant du module (nom et version).
 */
const char* QUEUE_Identifier(void);

/**
 * @return Version du module.
 */
int QUEUE_Version(void);

/**
 * @brief Cree une file.
 *
 * @return File cree (NULL en cas d'erreur).
 */
queue_s* QUEUE_Create(void);

/**
 * @brief Destruit une file.
 *
 * @param[in] queue   File.
 */
void QUEUE_Destroy(queue_s* queue);

/**
 * @brief Verifie la vacuite de la file.
 *
 * @param[in] queue   File.
 *
 * @retval true   Fite vide.
 * @retval false  Au moins un element dans la file.
 */
bool QUEUE_IsEmpty(const queue_s* queue);

/**
 * @brief Calcule le nombre d'element de la file.
 *
 * @param[in] queue   File.
 *
 * @return Nombre d'element de la file.
 */
size_t QUEUE_Size(const queue_s* queue);

/**
 * @brief Ajoute un element a la file.
 *
 * @param[in,out] queue File.
 * @param[in] data      Element a ajouter.
 * @param[in] dataSize  Taille de l'element.
 *
 * @retval QUEUE_NO_ERROR       Ajout reussi.
 * @retval QUEUE_MEMORY_ERROR   Erreur d'allocation ou pas d'element a inserer.
 */
QUEUE_Error_e QUEUE_Enqueue(queue_s* queue, const void* data, size_t dataSize);

/**
 * @brief Lit et supprime un element de la file.
 *
 * @param[in,out] queue   File.
 *
 * @return Element lu (NULL en cas d'erreur).
 */
const void* QUEUE_Dequeue(queue_s* queue);

/**
 * @brief Lit un element de la file.
 *
 * @param[in] queue   File.
 *
 * @return Element lu (NULL en cas d'erreur).
 */
const void* QUEUE_Peek(const queue_s* queue);

/**
 * @brief Supprime un element de la file.
 *
 * @param[in,out] queue   File.
 *
 * @retval QUEUE_NO_ERROR     Suppression reussie.
 * @retval QUEUE_EMPTY_QUEUE  Pile vide.
 */
QUEUE_Error_e QUEUE_Remove(queue_s* queue);

/**
 * @brief Duplique une file.
 *
 * @param[in] queue   File a dupliquer.
 *
 * @return Copie de la file.
 */
queue_s* QUEUE_Clone(const queue_s* queue);

#ifdef __cplusplus
}
#endif

#endif
