/**
   \author Gregory Lerbret
   \file queue.h
   \brief Gestion de files.<br>
   \date 24/09/2006
   \version 1.0.0
*/
#ifndef GL_QUEUE_H
#define GL_QUEUE_H

#include <stddef.h>
#include "bool.h"

/**
   \struct queue_s
   \brief Structure de la file.
*/
typedef struct queue queue_s;

/**
   \enum QUEUE_Error_e
   \brief Resultat des traitements sur les files.
*/
typedef enum
{
/**
   \brief Pas d'erreur.
*/
   QUEUE_NO_ERROR,
/**
   \brief Erreur d'allocation.
*/
   QUEUE_MEMORY_ERROR,
/**
   \brief La file est vide.
*/
   QUEUE_EMPTY_QUEUE
} QUEUE_Error_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
   \fn const char* QUEUE_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char*    QUEUE_Identifier(void);

/**
   \fn int QUEUE_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int            QUEUE_Version(void);

/**
   \fn queue_s* QUEUE_Create(QUEUE_Error_e* eError)
   \brief Creation d'une file.
   \param[out] eError le resultat de la creation :<br>
               QUEUE_NO_ERROR : la creation s'est correctement deroulee.<br>
               QUEUE_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire.
   \return La file cree (NULL en cas d'erreur).
*/
queue_s*       QUEUE_Create(QUEUE_Error_e* eError);

/**
   \fn void QUEUE_Destroy(queue_s* pQueue)
   \brief Destruction d'une file.
   \param[in] pQueue la file
*/
void           QUEUE_Destroy(queue_s* pQueue);

/**
   \fn BOOL QUEUE_IsEmpty(const queue_s* pQueue)
   \brief Verification de la vacuite de la file.
   \param[in] pQueue la file
   \return  TRUE si la file est vide.<br>
            FALSE sinon.
*/
bool           QUEUE_IsEmpty(const queue_s* pQueue);

/**
   \fn size_t QUEUE_Size(const queue_s* pQueue)
   \brief Calcul du nombre d'element de la file.
   \param[in] pQueue la file
   \return Le nombre d'element de la file.
*/
size_t         QUEUE_Size(const queue_s* pQueue);

/**
   \fn QUEUE_Error_e QUEUE_Enqueue(queue_s* pQueue, const void* pData, size_t szDataSize)
   \brief Ajout d'un element a la file.
   \param[in,out] pQueue la file
   \param[in] pData l'element a ajouter
   \param[in] szDataSize la taille de l'element
   \return  QUEUE_NO_ERROR : l'ajout s'est correctement deroule.<br>
            QUEUE_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire ou il n'existe pas de donnee a inserer.
*/
QUEUE_Error_e  QUEUE_Enqueue(queue_s* pQueue, const void* pData, size_t szDataSize);

/**
   \fn const void* QUEUE_Dequeue(queue_s* pQueue, QUEUE_Error_e* eError)
   \brief Lecture et suppression d'un element de la file.
   \param[in,out] pQueue la file
   \param[out] eError le resultat de la lecture :<br>
               QUEUE_NO_ERROR : la lecture s'est correctement deroulee.<br>
               QUEUE_EMPTY_QUEUE : la file est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void*    QUEUE_Dequeue(queue_s* pQueue, QUEUE_Error_e* eError);

/**
   \fn const void* QUEUE_Peek(const queue_s* pQueue, QUEUE_Error_e* eError)
   \brief Lecture d'un element de la file.
   \param[in] pQueue la file
   \param[out] eError le resultat de la lecture :<br>
               QUEUE_NO_ERROR : la lecture s'est correctement deroulee.<br>
               QUEUE_EMPTY_QUEUE : la file est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void*    QUEUE_Peek(const queue_s* pQueue, QUEUE_Error_e* eError);

/**
   \fn QUEUE_Error_e QUEUE_Remove(queue_s* pQueue)
   \brief Suppression d'un element de la file.
   \param[in,out] pQueue la file
   \return  QUEUE_NO_ERROR : la suppression s'est correctement deroulee.<br>
            QUEUE_EMPTY_QUEUE : la pile est vide.
*/
QUEUE_Error_e  QUEUE_Remove(queue_s* pQueue);

/**
   \fn queue_s* QUEUE_Clone(const queue_s* pQueue, QUEUE_Error_e* eError)
   \brief Duplication d'une file.
   \param[in] pQueue la file a dupliquer
   \param[out] eError statut de la duplication :<br>
               QUEUE_NO_ERROR : la copie s'est correctement deroulee.<br>
               QUEUE_ALLOC_QUEUE : le module n'a pas pu allouer assez de memoire.
   \return La copie de la file.
*/
queue_s*       QUEUE_Clone(const queue_s* pQueue, QUEUE_Error_e* eError);

#ifdef __cplusplus
}
#endif

#endif
