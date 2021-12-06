/**
 * @author Gregory Lerbret
 * @file
 * @brief Gestion de nombres au format BCD
 * @version 1.0.0
 * @copyright MIT license
 */

#ifndef GL_BCD_H
#define GL_BCD_H

#include <stddef.h>

/**
 * @brief Resultat des traitements sur le nombres au format BCD
*/
typedef enum
{
    /// @brief Pas d'erreur
    BCD_OK,
    /// @brief Echec de conversion d'un nombre BCD
    BCD_CONV_ERROR
} BCD_Res_e;

#ifdef __cplusplus
extern "C"
{
#endif
/**
 * @return Identifiant du module (nom et version)
 */
const char* BCD_Identifier(void);

/**
 * @return Version du module.
 */
int BCD_Version(void);

/**
 * @brief Conversion d'un nombre au format BCD vers sa representation textuelle
 *
 * @param[out] ascii Chaine de caracteres representant le nombre
 * @param[in] bcd Nombre au format BCD
 * @param[in] nbDigit Taille du nombre (en digits)
 *
 * @return
 *  - BCD_OK en cas de succes
 *  - BCD_CONV_ERROR en cas d'erreur
 */
BCD_Res_e BCD_ConvBCD2Ascii(char* ascii, const unsigned char* bcd, size_t nbDigit);

/**
 * @brief Conversion de la representation textuelle d'un nombre vers sa representation BCD
 *
 * @param[out] bcd Nombre au format BCD
 * @param[in] ascii Chaine de caracteres representant le nombre
 * @param[in] nbDigit Taille du nombre (en digit)
 *
 * @return
 *  - BCD_OK en cas de succes
 *  - BCD_CONV_ERROR en cas d'erreur
 */
BCD_Res_e BCD_ConvAscii2BCD(unsigned char* bcd, const char* ascii, size_t nbDigit);

#ifdef __cplusplus
}
#endif

#endif
