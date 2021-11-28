/**
   \author Grégory Lerbret
   \file str.h
   \brief Gestion des chaines de caracteres.<br>
   \date 06/04/2005
   \version 1.0.0
*/

#ifndef GL_STR_H
#define GL_STR_H

#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
   \fn const char* STR_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char* STR_Identifier(void);

/**
   \fn int STR_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int         STR_Version(void);

/**
   \fn char* STR_DelChar(char* pcDst, const char* pcSrc, size_t szLgDst, char cChar2Delete)
   \brief Suppression d'un caractere donne dans une chaine.
   \param[out] pcDst la chaine apres traitement
   \param[in] pcSrc la chaine initiale
   \param[in] szLgDst la taille maximale de la chaine apres traitement
   \param[in] cChar2Delete le caractere a supprimmer
   \return La chaine sans le caractere a supprimmer (NULL en cas d'erreur).
*/
char*       STR_DelChar(char* pcDst, const char* pcSrc, size_t szLgDst, char cChar2Delete);

/**
   \fn char* STR_Strip(char* pcDst, const char* pcSrc, size_t szLgDst)
   \brief Suppression des espaces en debut et en fin de chaine.
   \param[out] pcDst la chaine sans espace superflu
   \param[in] pcSrc la chaine initiale
   \param[in] szLgDst la taille maximale de la chaine sans espace
   \return La chaine sans espace superflu (NULL en cas de probleme).
*/
char*       STR_Strip(char* pcDst, const char* pcSrc, size_t szLgDst);

/**
   \fn char* STR_String2Lower(char* pcDst, const char* pcSrc, size_t szLgDst)
   \brief Conversion de la chaine en minuscule.
   \param[out] pcDst la chaine en minuscule
   \param[in] pcSrc la chaine initiale
   \param[in] szLgDst la taille maximale de la chaine en minuscule
   \return La chaine en minuscule (NULL en cas de probleme).
*/
char*       STR_String2Lower(char* pcDst, const char* pcSrc, size_t szLgDst);

/**
   \fn char* STR_String2Upper(char* pcDst, const char* pcSrc, size_t szLgDst)
   \brief Conversion de la chaine en majuscule
   \param[out] pcDst la chaine en majuscule
   \param[in] pcSrc la chaine initiale
   \param[in] szLgDst la taille maximale de la chaine en majuscule
   \return La chaine en majuscule (NULL en cas de probleme).
*/
char*       STR_String2Upper(char* pcDst, const char* pcSrc, size_t szLgDst);

/**
   \fn char* STR_LeftPadding(char* pcDst, const char* pcSrc, size_t szLgDst, char cPaddingChar)
   \brief Padding a gauche d'une chaine de caractere.
   \param[out] pcDst la chaine paddee
   \param[in] pcSrc la chaine initiale
   \param[in] szLgDst la taille maximale de la chaine paddee
   \param[in] cPaddingChar le caractere de padding
   \return La chaine paddee (NULL en cas de probleme)
*/
char*       STR_LeftPadding(char* pcDst, const char* pcSrc, size_t szLgDst, char cPaddingChar);

/**
   \fn char* STR_RightPadding(char* pcDst, const char* pcSrc, size_t szLgDst, char cPaddingChar)
   \brief Padding a droite d'une chaine de caractere.
   \param[out] pcDst la chaine paddee
   \param[in] pcSrc la chaine initiale
   \param[in] szLgDst la taille maximale de la chaine paddee
   \param[in] cPaddingChar le caractere de padding
   \return La chaine paddee (NULL en cas de probleme)
*/
char*       STR_RightPadding(char* pcDst, const char* pcSrc, size_t szLgDst, char cPaddingChar);

/**
   \fn char* STR_Center(char* pcDst, const char* pcSrc, size_t szLgDst, char cPaddingChar)
   \brief Centrage d'une chaine de caractere.
   \param[out] pcDst la chaine centree
   \param[in] pcSrc la chaine initiale
   \param[in] szLgDst la taille maximale de la chaine centree
   \param[in] cPaddingChar le caractere de padding
   \return La chaine centree (NULL en cas de probleme).
*/
char*       STR_Center(char* pcDst, const char* pcSrc, size_t szLgDst, char cPaddingChar);

/**
   \fn char* STR_StrDup(const char* pcSrc)
   \brief   Duplication d'une chaine.<br>
            Cette fonction a un comportement identique a la fonction strdup() et permet de fournir une alternative fonctionnant
            sur toutes les cibles.<br>
            La chaine dupliquee ayant ete allouee via malloc(), l'appelant doit liberer cette chaine.
   \param[in] pcSrc la chaine initiale
   \return La chaine dupliquee (NULL en cas de probleme).
*/
char*       STR_StrDup(const char* pcSrc);

#ifdef __cplusplus
}
#endif

#endif
