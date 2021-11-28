/**
   \author Grégory Lerbret
   \file print.h
   \brief   Gestion des impressions formattees.<br>
            Ce fichier fournie une encapsulation aux fonctions du type snprintf() afin de presenter une interface uniforme independante
            des fonctions reellement implementees sur la cible.<br>
   \date 20/08/2008
   \version 1.0.0
*/

#ifndef GL_PRINT_H
#define GL_PRINT_H

#include <stddef.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
   \fn const char* PRINT_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char* PRINT_Identifier(void);

/**
   \fn int PRINT_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int         PRINT_Version(void);

/**
   \fn int PRINT_vsnprintf(char *pcDst, size_t szLgDst, const char *pcFormat, va_list ap)
   \brief Construction d'une sortie formattee.
   \param[out] pcDst la chaine contenant la sortie formattee
   \param[in] szLgDst la taille maximale de la sortie
   \param[in] pcFormat la chaine de format
   \param[in] ap la liste de parametres
   \return Le nombre de caracteres imprimes sans le 0 final.
*/
int         PRINT_vsnprintf(char *pcDst, size_t szLgDst, const char *pcFormat, va_list ap);

/**
   \fn int PRINT_snprintf(char *pcDst, size_t szLgDst, const char *pcFormat, ...)
   \brief Construction d'une sortie formattee.
   \param[out] pcDst la chaine contenant la sortie formattee
   \param[in] szLgDst la taille maximale de la sortie
   \param[in] pcFormat la chaine de format
   \return Le nombre de caracteres imprimes sans le 0 final.
*/
int         PRINT_snprintf(char *pcDst, size_t szLgDst, const char *pcFormat, ...);

#ifdef __cplusplus
}
#endif

#endif
