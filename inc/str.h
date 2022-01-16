/**
 * @file
 * @brief Gestion des chaines de caracteres.
 * @version 1.0.0.
 * @copyright MIT license.
 * @author Gregory Lerbret.
 */

#ifndef GL_STR_H
#define GL_STR_H

#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @return Identifiant du module (nom et version).
 */
const char* STR_Identifier(void);

/**
 * @return Version du module.
 */
int STR_Version(void);

/**
 * @brief Supprime un caractere donne dans une chaine.
 *
 * @param[out] dst        Chaine apres traitement.
 * @param[in] src         Chaine initiale.
 * @param[in] dstSize     Taille maximale de la chaine apres traitement.
 * @param[in] char2Delete Caractere a supprimer.
 *
 * @return Chaine sans le caractere a supprimer (NULL en cas d'erreur).
 *
 * @pre dst n'est pas NULL. \par
 * @pre src n'est pas NULL. \par
 * @pre dstSize n'est pas NULL. \par
 */
char* STR_DelChar(char* dst, const char* src, size_t dstSize, char char2Delete);

/**
 * @brief Supprime des espaces en debut et en fin de chaine.
 *
 * @param[out] dst    Chaine sans espace superflu.
 * @param[in] src     Chaine initiale.
 * @param[in] dstSize Taille maximale de la chaine sans espace.
 *
 * @return Chaine sans espace superflu (NULL en cas de probleme).
 *
 * @pre dst n'est pas NULL. \par
 * @pre src n'est pas NULL. \par
 * @pre dstSize n'est pas NULL. \par
 */
char* STR_Strip(char* dst, const char* src, size_t dstSize);

/**
 * @brief Convertit la chaine en minuscule
 *
 * @param[out] dst    Chaine en minuscule.
 * @param[in] src     Chaine initiale.
 * @param[in] dstSize Taille maximale de la chaine en minuscule.
 *
 * @return Chaine en minuscule (NULL en cas de probleme).
 *
 * @pre dst n'est pas NULL. \par
 * @pre src n'est pas NULL. \par
 * @pre dstSize n'est pas NULL. \par
 */
char* STR_String2Lower(char* dst, const char* src, size_t dstSize);

/**
 * @brief Convertit la chaine en majuscule
 *
 * @param[out] dst    Chaine en majuscule.
 * @param[in] src     Chaine initiale.
 * @param[in] dstSize Taille maximale de la chaine en majuscule.
 *
 * @return Chaine en majuscule (NULL en cas de probleme).
 *
 * @pre dst n'est pas NULL. \par
 * @pre src n'est pas NULL. \par
 * @pre dstSize n'est pas NULL. \par
 */
char* STR_String2Upper(char* dst, const char* src, size_t dstSize);

/**
 * @brief Padde a gauche d'une chaine de caractere.
 *
 * @param[out] dst    Chaine paddee.
 * @param[in] src     Chaine initiale.
 * @param[in] dstSize Taille maximale de la chaine paddee.
 * @param[in] padding Caractere de padding.
 *
 * @return Chaine paddee (NULL en cas de probleme)
 *
 * @pre dst n'est pas NULL. \par
 * @pre src n'est pas NULL. \par
 * @pre dstSize n'est pas NULL. \par
 */
char* STR_LeftPadding(char* dst, const char* src, size_t dstSize, char padding);

/**
 * @brief Padde a droite d'une chaine de caractere.
 *
 * @param[out] dst    Chaine paddee.
 * @param[in] src     Chaine initiale.
 * @param[in] dstSize Taille maximale de la chaine paddee.
 * @param[in] padding Caractere de padding.
 *
 * @return Chaine paddee (NULL en cas de probleme).
 *
 * @pre dst n'est pas NULL. \par
 * @pre src n'est pas NULL. \par
 * @pre dstSize n'est pas NULL. \par
 */
char* STR_RightPadding(char* dst, const char* src, size_t dstSize, char padding);

/**
 * @brief Centre une chaine de caractere.
 *
 * @param[out] dst    Chaine centree.
 * @param[in] src     Chaine initiale.
 * @param[in] dstSize Taille maximale de la chaine centree.
 * @param[in] padding Caractere de padding.
 *
 * @return Chaine centree (NULL en cas de probleme)
 *
 * @pre dst n'est pas NULL. \par
 * @pre src n'est pas NULL. \par
 * @pre dstSize n'est pas NULL. \par
 */
char* STR_Center(char* dst, const char* src, size_t dstSize, char padding);

/**
 * @brief Duplique d'une chaine
 *
 * @param[in] src Chaine initiale.
 *
 * @return Chaine dupliquee (NULL en cas de probleme).
 *
 * @pre src n'est pas NULL. \par
 *
 * @note Cette fonction a un comportement identique a la fonction strdup() et permet de fournir une alternative fonctionnant sur toutes les cibles.
 * @note La chaine dupliquee ayant ete allouee via malloc(), l'appelant doit liberer cette chaine.
 */
char* STR_StrDup(const char* src);

#ifdef __cplusplus
}
#endif

#endif
