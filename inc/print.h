/**
 * @author Gregory Lerbret
 * @file
 * @brief Gestion des impressions formattees
 *        Ce fichier fournie une encapsulation aux fonctions du type snprintf() afin de presenter une interface uniforme independante
 *        des fonctions reellement implementees sur la cible
 * @date 20/08/2008
 * @version 1.0.0
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
 * @return Identifiant du module (nom et version)
 */
const char* PRINT_Identifier(void);

/**
 * @return Version du module
 */
int PRINT_Version(void);

/**
 * @brief Construction d'une sortie formattee
 *
 * @param[out] pcDst Chaine contenant la sortie formattee
 * @param[in] szLgDst Taille maximale de la sortie
 * @param[in] pcFormat Chaine de format
 * @param[in] ap Liste de parametres
 *
 * @return Nombre de caracteres imprimes sans le 0 final.
 */
int PRINT_vsnprintf(char *pcDst, size_t szLgDst, const char *pcFormat, va_list ap);

/**
 * @brief Construction d'une sortie formattee
 *
 * @param[out] pcDst Chaine contenant la sortie formattee
 * @param[in] szLgDst Taille maximale de la sortie
 * @param[in] pcFormat Chaine de format
 *
 * @return Nombre de caracteres imprimes sans le 0 final
 */
int PRINT_snprintf(char *pcDst, size_t szLgDst, const char *pcFormat, ...);

#ifdef __cplusplus
}
#endif

#endif
