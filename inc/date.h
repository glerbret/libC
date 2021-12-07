/**
 * @author Gregory Lerbret
 * @file
 * @brief Gestion de dates
 * @version 1.0.0
 * @copyright MIT license
 */

#ifndef GL_DATE_H
#define GL_DATE_H

#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @return Identifiant du module (nom et version)
 */
const char* DATE_Identifier(void);

/**
 * @return Version du module
 */
int DATE_Version(void);

/**
 * @brief Lecture de la date actuelle
 *
 * @param[out] date Date courante
 * @param[in] dateSize Taille maximal de la date
 * @param[in] format Format de la date
 *
 * @return Date courante (NULL en cas d'erreur)
 */
const char* DATE_GetTodayDate(char* date, size_t dateSize, const char* format);

#ifdef __cplusplus
}
#endif

#endif
