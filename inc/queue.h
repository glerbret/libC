/**
 * @author Gregory Lerbret
 * @file
 * @brief Gestion de files
 * @date 24/09/2006
 * @version 1.0.0
 */

#ifndef GL_QUEUE_H
#define GL_QUEUE_H

#include "bool.h"

#include <stddef.h>

/**
 * @brief Structure de la file
 */
typedef struct queue queue_s;

/**
 * @brief Resultat des traitements sur les files
 */
typedef enum
{
    /// @brief Pas d'erreur
    QUEUE_NO_ERROR,
    /// @brief Erreur d'allocation
    QUEUE_MEMORY_ERROR,
    /// @brief La file est vide
    QUEUE_EMPTY_QUEUE
} QUEUE_Error_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @return Identifiant du module (nom et version)
 */
const char* QUEUE_Identifier(void);

/**
 * @return Version du module
 */
int QUEUE_Version(void);

/**
 * @brief Creation d'une file
 * @param[out] eError Resultat de la creation :
 *                      - QUEUE_NO_ERROR : la creation s'est correctement deroulee
 *                      - QUEUE_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire
 *
 * @return File cree (NULL en cas d'erreur).
 */
queue_s* QUEUE_Create(QUEUE_Error_e* eError);

/**
 * @brief Destruction d'une file
 *
 * @param[in] pQueue File
 */
void QUEUE_Destroy(queue_s* pQueue);

/**
 * @brief Verification de la vacuite de la file
 *
 * @param[in] pQueue File
 *
 * @return
 *  - TRUE si la file est vide
 *  - FALSE sinon
 */
bool QUEUE_IsEmpty(const queue_s* pQueue);

/**
 * @brief Calcul du nombre d'element de la file
 *
 * @param[in] pQueue File
 *
 * @return Nombre d'element de la file
 */
size_t QUEUE_Size(const queue_s* pQueue);

/**
 * @brief Ajout d'un element a la file
 *
 * @param[in,out] pQueue File
 * @param[in] pData Element a ajouter
 * @param[in] szDataSize Taille de l'element
 *
 * @return
 *  - QUEUE_NO_ERROR : l'ajout s'est correctement deroule
 *  - QUEUE_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire ou il n'existe pas de donnee a inserer
 */
QUEUE_Error_e QUEUE_Enqueue(queue_s* pQueue, const void* pData, size_t szDataSize);

/**
 * @brief Lecture et suppression d'un element de la file
 *
 * @param[in,out] pQueue File
 * @param[out] eError Resultat de la lecture :
 *                      - QUEUE_NO_ERROR : la lecture s'est correctement deroulee
 *                      - QUEUE_EMPTY_QUEUE : la file est vide
 *
 * @return Element lu (NULL en cas d'erreur)
 */
const void* QUEUE_Dequeue(queue_s* pQueue, QUEUE_Error_e* eError);

/**
 * @brief Lecture d'un element de la file
 *
 * @param[in] pQueue File
 * @param[out] eError Resultat de la lecture :
 *                      - QUEUE_NO_ERROR : la lecture s'est correctement deroulee
 *                      - QUEUE_EMPTY_QUEUE : la file est vide
 *
 * @return Element lu (NULL en cas d'erreur)
 */
const void* QUEUE_Peek(const queue_s* pQueue, QUEUE_Error_e* eError);

/**
 * @brief Suppression d'un element de la file
 *
 * @param[in,out] pQueue File
 *
 * @return
 *  - QUEUE_NO_ERROR : la suppression s'est correctement deroulee
 *  - QUEUE_EMPTY_QUEUE : la pile est vide
 */
QUEUE_Error_e QUEUE_Remove(queue_s* pQueue);

/**
 * @brief Duplication d'une file
 *
 * @param[in] pQueue File a dupliquer
 * @param[out] eError Statut de la duplication :
 *                      - QUEUE_NO_ERROR : la copie s'est correctement deroulee
 *                      - QUEUE_ALLOC_QUEUE : le module n'a pas pu allouer assez de memoire
 *
 * @return Copie de la file
 */
queue_s* QUEUE_Clone(const queue_s* pQueue, QUEUE_Error_e* eError);

#ifdef __cplusplus
}
#endif

#endif
