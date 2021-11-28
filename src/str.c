/**
   \author Grégory Lerbret
   \file str.c
   \brief Gestion des chaines de caracteres.<br>
   \date 06/04/2005
   \version 1.0.0
*/
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"

#define xstr(s) str(s)
#define str(s) #s

#define STR_NAME	         "Gestion des chaines de caracteres"
#define STR_VERS_MAJ       1
#define STR_VERS_MIN       0
#define STR_VERS_BRCH      0
#define STR_ID		         STR_NAME " - Version " xstr(STR_VERS_MAJ) "." xstr(STR_VERS_MIN) "." xstr(STR_VERS_BRCH)

/**
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char* STR_Identifier(void)
{
   return STR_ID;
}

/**
   \brief Version du module.
   \return La version du module.
*/
int STR_Version(void)
{
   return STR_VERS_MAJ*10000 + STR_VERS_MIN*100 + STR_VERS_BRCH;
}

/**
   \brief Suppression d'un caractere donne dans une chaine.
   \param[out] pcDst la chaine apres traitement
   \param[in] pcSrc la chaine initiale
   \param[in] szLgDst la taille maximale de la chaine apres traitement
   \param[in] cChar2Delete le caractere a supprimmer
   \return La chaine sans le caractere a supprimmer (NULL en cas d'erreur).
*/
char* STR_DelChar(char* pcDst, const char* pcSrc, size_t szLgDst, char cChar2Delete)
{
   /* Verification des conditions initiales */
   if(pcDst == NULL || pcSrc == NULL || szLgDst == 0)
   {
      return NULL;
   }

   for(; *pcSrc != '\0' && szLgDst > 1; pcSrc++)
   {
      if(*pcSrc != cChar2Delete)
      {
         /* Le caractere courant doit etre conserve */
         *pcDst = *pcSrc;
         pcDst++;
         szLgDst--;
      }
   }

   /* Une chaine se termine par un 0 */
   *pcDst = '\0';
   return pcDst;
}

/**
   \brief Suppression des espaces en debut et en fin de chaine.
   \param[out] pcDst la chaine sans espace superflu
   \param[in] pcSrc la chaine initiale
   \param[in] szLgDst la taille maximale de la chaine sans espace
   \return La chaine sans espace superflu (NULL en cas de probleme).
*/
char* STR_Strip(char* pcDst, const char* pcSrc, size_t szLgDst)
{
   char* pcSavDst = pcDst;

   /* Verification des conditions initiales */
   if(pcDst == NULL || pcSrc == NULL || szLgDst == 0)
   {
      return NULL;
   }

   /* Recherche du premier caractere non blanc de la chaine */
   for(; isspace(*pcSrc) != 0 && *pcSrc != '\0'; pcSrc++)
   {
      /* NOP */
   }

   /* Suppression des espaces superlus en debut de chaine */
   for(; *pcSrc != '\0' && szLgDst > 1; pcSrc++, szLgDst--, pcDst++)
   {
      *pcDst = *pcSrc;
   }

   /* Suppression des espaces superlus en fin de chaine
      Si rien n'a ete copie dans la chaine resultante (chaine initiale ne
      contenant que des espaces ou longueur de la chaine resultante de 1),
      on ne fait rien */
   for(; pcSavDst != pcDst && isspace(*(pcDst - 1)) != 0; pcDst--)
   {
      /* NOP */
   }

   /* Une chaine se termine par un 0 */
   *pcDst = '\0';
   return pcSavDst;
}

/**
   \brief Conversion de la chaine en minuscule.
   \param[out] pcDst la chaine en minuscule
   \param[in] pcSrc la chaine initiale
   \param[in] szLgDst la taille maximale de la chaine en minuscule
   \return La chaine en minuscule (NULL en cas de probleme).
*/
char* STR_String2Lower(char* pcDst, const char* pcSrc, size_t szLgDst)
{
   /* Verication des conditions intiales */
   if(pcDst == NULL || pcSrc == NULL || szLgDst == 0)
   {
      return NULL;
   }

   /* Parcours iteratif de la chaine de caractere avec conversion en minuscule */
   for(; *pcSrc != '\0' && szLgDst > 1; szLgDst--, pcDst++, pcSrc++)
   {
      *pcDst = (char)tolower(*pcSrc);
   }

   /* Une chaine se termine par un 0 */
   *pcDst = '\0';
   return pcDst;
}

/**
   \brief Conversion de la chaine en majuscule
   \param[out] pcDst la chaine en majuscule
   \param[in] pcSrc la chaine initiale
   \param[in] szLgDst la taille maximale de la chaine en majuscule
   \return La chaine en majuscule (NULL en cas de probleme).
*/
char* STR_String2Upper(char* pcDst, const char* pcSrc, size_t szLgDst)
{
   /* Verication des conditions intiales */
   if(pcDst == NULL || pcSrc == NULL || szLgDst == 0)
   {
      return NULL;
   }

   /* Parcours iteratif de la chaine de caractere avec conversion en majuscule */
   for(; *pcSrc != '\0' && szLgDst > 1; szLgDst--, pcDst++, pcSrc++)
   {
      *pcDst=(char)toupper(*pcSrc);
   }

   /* Une chaine se termine par un 0 */
   *pcDst = '\0';
   return pcDst;
}

/**
   \brief Padding a gauche d'une chaine de caractere.
   \param[out] pcDst la chaine paddee
   \param[in] pcSrc la chaine initiale
   \param[in] szLgDst la taille maximale de la chaine paddee
   \param[in] cPaddingChar le caractere de padding
   \return La chaine paddee (NULL en cas de probleme)
*/
char* STR_LeftPadding(char* pcDst, const char* pcSrc, size_t szLgDst, char cPaddingChar)
{
   size_t   szLgSrc;

   /* Verification des conditions initiales */
   if(pcDst == NULL || pcSrc == NULL || szLgDst == 0)
   {
      return NULL;
   }

   szLgSrc = strlen(pcSrc);

   if(szLgSrc >= szLgDst)
   {
      /* La chaine intiale est trop longue, on tronque */
      memcpy(pcDst, pcSrc, szLgDst-1);
   }
   else
   {
      /* On remplit le buffer avec le caractere de padding ... */
      memset(pcDst, cPaddingChar, szLgDst-1);

      /* ... et on copie la chaine initiale a la bonne position */
      memcpy(pcDst + szLgDst - szLgSrc - 1, pcSrc, szLgSrc);
   }

   /* Une chaine se termine par un 0 */
   pcDst[szLgDst-1] = '\0';
   return pcDst;
}

/**
   \brief Padding a droite d'une chaine de caractere.
   \param[out] pcDst la chaine paddee
   \param[in] pcSrc la chaine initiale
   \param[in] szLgDst la taille maximale de la chaine paddee
   \param[in] cPaddingChar le caractere de padding
   \return La chaine paddee (NULL en cas de probleme)
*/
char* STR_RightPadding(char* pcDst, const char* pcSrc, size_t szLgDst, char cPaddingChar)
{
   size_t   szLgSrc;

   /* Verification des conditions initiales */
   if(pcDst == NULL || pcSrc == NULL || szLgDst == 0)
   {
      return NULL;
   }

   szLgSrc = strlen(pcSrc);

   if(szLgSrc >= szLgDst)
   {
      /* La chaine intiale est trop longue, on tronque */
      memcpy(pcDst, pcSrc, szLgDst-1);
   }
   else
   {
      /* On remplit le buffer avec le caractere de padding ... */
      memset(pcDst, cPaddingChar, szLgDst-1);

      /* ... et on copie la chaine initiale a la bonne position */
      memcpy(pcDst, pcSrc, szLgSrc);
   }

   /* Une chaine se termine par un 0 */
   pcDst[szLgDst-1] = '\0';
   return pcDst;
}

/**
   \brief Centrage d'une chaine de caractere.
   \param[out] pcDst la chaine centree
   \param[in] pcSrc la chaine initiale
   \param[in] szLgDst la taille maximale de la chaine centree
   \param[in] cPaddingChar le caractere de padding
   \return La chaine centree (NULL en cas de probleme).
*/
char* STR_Center(char* pcDst, const char* pcSrc, size_t szLgDst, char cPaddingChar)
{
   size_t   szLgSrc;

   /* Verification des conditions initiales */
   if(pcDst == NULL || pcSrc == NULL || szLgDst == 0)
   {
      return NULL;
   }

   szLgSrc = strlen(pcSrc);

   if(szLgSrc >= szLgDst)
   {
      /* La chaine intiale est trop longue, on tronque */
      memcpy(pcDst, pcSrc, szLgDst-1);
   }
   else
   {
      /* On remplit le buffer avec le caractere de padding ... */
      memset(pcDst, cPaddingChar, szLgDst-1);

      /* ... et on copie la chaine initiale a la bonne position */
      memcpy(pcDst + ((szLgDst - 1 - szLgSrc) / 2), pcSrc, szLgSrc);
   }

   /* Une chaine se termine par un 0 */
   pcDst[szLgDst-1] = '\0';
   return pcDst;
}

/**
   \brief   Duplication d'une chaine.<br>
            Cette fonction a un comportement identique a la fonction strdup() et permet de fournir une alternative fonctionnant
            sur toutes les cibles.<br>
            La chaine dupliquee ayant ete allouee via malloc(), l'appelant doit liberer cette chaine.
   \param[in] pcSrc la chaine initiale
   \return La chaine dupliquee (NULL en cas de probleme).
*/
char* STR_StrDup(const char* pcSrc)
{
   char* pcDst = malloc(strlen(pcSrc) + 1);
   if(pcDst != NULL)
   {
      strcpy(pcDst, pcSrc);
   }

   return pcDst;
}
