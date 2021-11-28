/**
   \author Grégory Lerbret
   \file date.h
   \brief Gestion de dates.<br>
   \date 07/04/2005
   \version 1.0.0
*/

#ifndef GL_DATE_H
#define GL_DATE_H

#include <string.h>

/**
   \enum DATE_Res_e
   \brief Resultat des traitements sur les dates
*/
typedef enum
{
/**
   \brief Pas d'erreur
*/
   DATE_OK,
/**
   \brief Echec de lecture de la date
*/
   DATE_READ_ERROR,
/**
   \brief Echec de conversion d'une date
*/
   DATE_CONV_ERROR
} DATE_Res_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
   \fn const char* DATE_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char*    DATE_Identifier(void);

/**
   \fn int DATE_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int            DATE_Version(void);

/**
   \fn DATE_Res_e DATE_GetTodayDate(char* pcDate, size_t szLgDate, const char* pcFormat)
   \brief Lecture de la date actuelle.
   \param[out] pcDate la date courante
   \param[in] szLgDate la taille maximal de la date
   \param[in] pcFormat le format de la date
   \return  DATE_OK : la date a ete lue et formatee avec succes.<br>
            DATE_READ_ERROR : erreur de lecture de la date.<br>
            DATE_CONV_ERROR : erreur de formatage de la date.
*/
DATE_Res_e     DATE_GetTodayDate(char* pcDate, size_t szLgDate, const char* pcFormat);

#ifdef __cplusplus
}
#endif

#endif
