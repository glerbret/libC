/**
 * @author Gregory Lerbret
 * @file
 * @brief Gestion de dates
 * @date 07/04/2005
 * @version 1.0.0
 */

#ifndef GL_DATE_H
#define GL_DATE_H

#include <string.h>

/**
 * @brief Resultat des traitements sur les dates
 */
typedef enum
{
    /// @brief Pas d'erreur
    DATE_OK,
    /// @brief Echec de lecture de la date
    DATE_READ_ERROR,
    /// @brief Echec de conversion d'une date
    DATE_CONV_ERROR
} DATE_Res_e;

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
 * @param[out] pcDate Date courante
 * @param[in] szLgDate Taille maximal de la date
 * @param[in] pcFormat Format de la date
 *
 * @return
 *  - DATE_OK : la date a ete lue et formatee avec succes
 *  - DATE_READ_ERROR : erreur de lecture de la date
 *  - DATE_CONV_ERROR : erreur de formatage de la date
 */
DATE_Res_e DATE_GetTodayDate(char* pcDate, size_t szLgDate, const char* pcFormat);

#ifdef __cplusplus
}
#endif

#endif
