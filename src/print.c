/**
   \author Grégory Lerbret
   \file print.c
   \brief   Gestion des impressions formattees.<br>
            Ce fichier fournie une encapsulation aux fonctions du type snprintf() afin de presenter une interface uniforme independante
            des fonctions reellement implementees sur la cible.<br>
   \date 20/08/2008
   \version 1.0.0
*/

#include <stdarg.h>
#include <stdio.h>
#include "print.h"

#define xstr(s) str(s)
#define str(s) #s

#define PRINT_NAME         "Gestion des impressions formattees"
#define PRINT_VERS_MAJ     1
#define PRINT_VERS_MIN     0
#define PRINT_VERS_BRCH    0
#define PRINT_ID           PRINT_NAME " - Version " xstr(PRINT_VERS_MAJ) "." xstr(PRINT_VERS_MIN) "." xstr(PRINT_VERS_BRCH)

/**
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char* PRINT_Identifier(void)
{
   return PRINT_ID;
}

/**
   \brief Version du module.
   \return La version du module.
*/
int PRINT_Version(void)
{
   return PRINT_VERS_MAJ*10000 + PRINT_VERS_MIN*100 + PRINT_VERS_BRCH;
}

/**
   \brief Construction d'une sortie formattee.
   \param[out] pcDst la chaine contenant la sortie formattee
   \param[in] szLgDst la taille maximale de la sortie
   \param[in] pcFormat la chaine de format
   \param[in] ap la liste de parametres
   \return Le nombre de caracteres imprimes sans le 0 final.
*/
int PRINT_vsnprintf(char *pcDst, size_t szLgDst, const char *pcFormat, va_list ap)
{
#if __STDC_VERSION__ >= 199901L || defined(__MINGW32_VERSION) || defined(__CYGWIN__) || defined(__GNUC__)
   /* Compilateur conforme C99 ou GCC, la fonction vsnprintf() est presente */
   return vsnprintf(pcDst, szLgDst, pcFormat, ap);
#elif (defined(_MSC_VER) && _MSC_VER >= 1400)
   /* Compilateur visual Studio posterieur a la version 8 */
   return vsprintf_s(pcDst, szLgDst, pcFormat, ap);
#elif (defined(_MSC_VER) && _MSC_VER < 1400)
   /* Compilateur visual Studio anterieur a la version 8 */
   return _vsnprintf(pcDst, szLgDst, pcFormat, ap);
#else
   /* Il n'existe pas de fonction equivalente */
   #erreur aucune fonction equivalente a vsnprintf() est presente
#endif
}


/**
   \brief Construction d'une sortie formattee.
   \param[out] pcDst la chaine contenant la sortie formattee
   \param[in] szLgDst la taille maximale de la sortie
   \param[in] pcFormat la chaine de format
   \return Le nombre de caracteres imprimes sans le 0 final.
*/
int PRINT_snprintf(char *pcDst, size_t szLgDst, const char *pcFormat, ...)
{
   va_list     ap;
   int         iNbChar;

   va_start(ap,pcFormat);
   iNbChar = PRINT_vsnprintf(pcDst, szLgDst, pcFormat, ap);
   va_end(ap);

   return iNbChar;
}
















