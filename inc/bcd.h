/**
 * @file
 * @brief Gestion de nombres au format BCD.
 * @version 1.0.0.
 * @copyright MIT license.
 * @author Gregory Lerbret.
 */

#ifndef GL_BCD_H
#define GL_BCD_H

/// @cond
#include <stddef.h>
/// @endcond

#ifdef __cplusplus
extern "C"
{
#endif
/**
 * @return Identifiant du module (nom et version).
 */
const char* BCD_Identifier(void);

/**
 * @return Version du module.
 */
int BCD_Version(void);

/**
 * @brief Convertit un nombre du format BCD vers sa representation textuelle.
 *
 * @param[out] ascii  Chaine de caracteres representant le nombre.
 * @param[in] bcd     Nombre au format BCD.
 * @param[in] nbDigit Taille du nombre (en digits).
 *
 * @return Chaine de caracteres representant le nombre.
 *
 * @pre ascii n'est pas NULL. \par
 * @pre bcd n'est pas NULL. \par
 * @pre nbDigit n'est pas NULL. \par
 */
char* BCD_ConvBCD2Ascii(char* ascii, const unsigned char* bcd, size_t nbDigit);

/**
 * @brief Convertit la representation textuelle d'un nombre vers sa representation BCD.
 *
 * @param[out] bcd    Nombre au format BCD.
 * @param[in] ascii   Chaine de caracteres representant le nombre.
 * @param[in] nbDigit Taille du nombre (en digit).
 *
 * @return Nombre au format BCD.
 *
 * @pre bcd n'est pas NULL. \par
 * @pre ascii n'est pas NULL. \par
 * @pre nbDigit n'est pas NULL. \par
 */
unsigned char* BCD_ConvAscii2BCD(unsigned char* bcd, const char* ascii, size_t nbDigit);

#ifdef __cplusplus
}
#endif

#endif
