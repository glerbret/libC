/**
   \author Grégory Lerbret
   \file date.c
   \brief Gestion de dates.<br>
   \date 07/04/2005
   \version 1.0.0
*/

#include <time.h>
#include <locale.h>
#include "date.h"

#define xstr(s) str(s)
#define str(s) #s

#define DATE_NAME	         "Gestion des dates"
#define DATE_VERS_MAJ      1
#define DATE_VERS_MIN      0
#define DATE_VERS_BRCH     0
#define DATE_ID		      DATE_NAME " - Version " xstr(DATE_VERS_MAJ) "." xstr(DATE_VERS_MIN) "." xstr(DATE_VERS_BRCH)

/**
   \fn const char* DATE_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char* DATE_Identifier(void)
{
   return DATE_ID;
}

/**
   \fnint DATE_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int DATE_Version(void)
{
   return DATE_VERS_MAJ*10000 + DATE_VERS_MIN*100 + DATE_VERS_BRCH;
}

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
DATE_Res_e DATE_GetTodayDate(char* pcDate, size_t szLgDate, const char* pcFormat)
{
   time_t      Date_bin;
   struct tm*  Date_struct;

   setlocale(LC_ALL, "");

   /* Lecture de la date */
   if(time(&Date_bin) == (time_t) -1)
   {
      return DATE_READ_ERROR;
   }

   /* Formatage de la date */
   Date_struct = localtime(&Date_bin);
   if (strftime(pcDate, szLgDate, pcFormat, Date_struct) == (size_t) 0)
   {
      return DATE_CONV_ERROR;
   }

   return DATE_OK;
}
