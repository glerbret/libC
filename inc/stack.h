/**
   \author Gregory Lerbret
   \file stack.h
   \brief Gestion de piles.<br>
   \date 24/09/2006
   \version 1.0.0
*/

#ifndef GL_STACK_H
#define GL_STACK_H

#include <stddef.h>
#include "bool.h"

/**
   \struct stack_s
   \brief Structure de la pile.
*/
typedef struct stack stack_s;

/**
   \enum STACK_Error_e
   \brief Resultat des traitements sur les piles.
*/
typedef enum
{
/**
   \brief Pas d'erreur.
*/
   STACK_NO_ERROR,
/**
   \brief Erreur d'allocation.
*/
   STACK_MEMORY_ERROR,
/**
   \brief La pile est vide.
*/
   STACK_EMPTY_STACK
} STACK_Error_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
   \fn const char* STACK_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char*    STACK_Identifier(void);

/**
   \fn int STACK_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int            STACK_Version(void);

/**
   \fn stack_s* STACK_Create(STACK_Error_e* eError)
   \brief Creation d'une pile.
   \param[out] eError le resultat de la creation :<br>
               STACK_NO_ERROR : la creation s'est correctement deroulee.<br>
               STACK_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire.
   \return La pile cree (NULL en cas d'erreur).
*/
stack_s*       STACK_Create(STACK_Error_e* eError);

/**
   \fn void STACK_Destroy(stack_s* pStack)
   \brief Destruction d'une pile.
   \param[in] pStack la pile
*/
void           STACK_Destroy(stack_s* pStack);

/**
   \fn BOOL STACK_IsEmpty(const stack_s* pStack)
   \brief Verification de la vacuite de la pile
   \param[in] pStack la pile
   \return  TRUE si la pile est vide.<br>
            FALSE sinon.
*/
bool           STACK_IsEmpty(const stack_s* pStack);

/**
   \fn size_t STACK_Size(const stack_s* pStack)
   \brief Calcul du nombre d'element de la pile.
   \param[in] pStack la pile
   \return Le nombre d'element de la pile.
*/
size_t         STACK_Size(const stack_s* pStack);

/**
   \fn STACK_Error_e STACK_Push(stack_s* pStack, const void* pData, size_t szDataSize)
   \brief Ajout d'un element a la pile.
   \param[in,out] pStack la pile
   \param[in] pData l'element a ajouter
   \param[in] szDataSize la taille de l'element
   \return  STACK_NO_ERROR : l'ajout s'est correctement deroule.<br>
            STACK_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire ou il n'existe pas de donnee a inserer.
*/
STACK_Error_e  STACK_Push(stack_s* pStack, const void* pData, size_t szDataSize);

/**
   \fn const void* STACK_Pop(stack_s* pStack, STACK_Error_e* eError)
   \brief Lecture et suppression d'un element de la pile.
   \param[in,out] pStack la pile
   \param[out] eError le resultat de la lecture :<br>
               STACK_NO_ERROR : la lecture s'est correctement deroulee.<br>
               STACK_EMPTY_STACK : la pile est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void*    STACK_Pop(stack_s* pStack, STACK_Error_e* eError);

/**
   \fn const void* STACK_Peek(const stack_s* pStack, STACK_Error_e* eError)
   \brief Lecture d'un element de la pile.
   \param[in] pStack la pile
   \param[out] eError le resultat de la lecture :<br>
               STACK_NO_ERROR : la lecture s'est correctement deroulee.<br>
               STACK_EMPTY_STACK : la pile est vide.
   \return L'element lu (NULL en cas d'erreur).
*/
const void*    STACK_Peek(const stack_s* pStack, STACK_Error_e* eError);

/**
   \fn STACK_Error_e STACK_Remove(stack_s* pStack)
   \brief Suppresion d'un element de la pile.
   \param[in,out] pStack la pile
   \return  STACK_NO_ERROR : la suppression s'est correctement deroulee.<br>
            STACK_EMPTY_STACK : la pile est vide.
*/
STACK_Error_e  STACK_Remove(stack_s* pStack);

/**
   \fn stack_s* STACK_Clone(const stack_s* pStack, STACK_Error_e* eError)
   \brief Duplication d'une pile.
   \param[in] pStack la pile
   \param[out] eError statut de la duplication :<br>
               STACK_NO_ERROR : la copie s'est correctement deroulee.<br>
               STACK_MEMORY_ERROR : le module n'a pas pu allouer assez de memoire.
   \return La copie de la pile.
*/
stack_s*       STACK_Clone(const stack_s* pStack, STACK_Error_e* eError);

#ifdef __cplusplus
}
#endif

#endif
