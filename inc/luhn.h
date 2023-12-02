/**
 * @file
 * @brief Calcul et de controle des cles de Luhn.
 * @version 1.0.0.
 * @copyright MIT license.
 * @author Gregory Lerbret.
 */

#ifndef GL_LUHN_H
#define GL_LUHN_H

#include "bool.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @return Identifiant du module (nom et version).
 */
const char* LUHN_Identifier(void);

/**
 * @return Version du module.
 */
int LUHN_Version(void);

/**
 * @brief Calcule la cle de Luhn.
 *
 * @param[in] number  Numero dont on veut calculer la cle de Luhn.
 *
 * @return Cle de Luhn sous sa forme ASCII.
 */
char LUHN_CalculateLuhnKey(const char* number);

/**
 * @brief Verifie la cle de Luhn.
 *
 * @param[in] number  Numero a verifier.
 *
 * @retval true   Cle de Luhn valide.
 * @retval false  Cle de Luhn invalide.
 */
bool LUHN_CheckLuhnKey(const char* number);

#ifdef __cplusplus
}
#endif

#endif
