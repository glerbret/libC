/**
 * @file
 * @brief Calcul et de controle des modulo 97.
 * @version 1.0.0.
 * @copyright MIT license.
 * @author Gregory Lerbret.
 */

#ifndef GL_MODULUS97_H
#define GL_MODULUS97_H

#include "bool.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @return Identifiant du module (nom et version).
 */
const char* MOD97_Identifier(void);

/**
 * @return Version du module.
 */
int MOD97_Version(void);

/**
 * @brief Verifie la validite d'un RIB.
 *
 * @param[in] number  Numero de RIB complet (y comprit la cle).
 *
 * @retval true   RIB valide.
 * @retval false  RIB invalide.
 */
bool MOD97_CheckRIBKey(const char* number);

/**
 * @brief Calcule la cle d'un RIB.
 *
 * @param[in] number  Numero de RIB sans la cle.
 *
 * @return Cle RIB.
 */
int MOD97_CalculateRIBKey(const char* number);

/**
 * @brief Verifie la validite d'un NIR (Numero de Securite Sociale).
 *
 * @param[in] number  Numero de NIR sans la cle.
 * @param[in] key     Cle du NIR.
 *
 * @retval true   NIR valide.
 * @retval false  NIR invalide
 */
bool MOD97_CheckNIRKey(const char* number, int key);

/**
 * @brief Calcule la cle d'un NIR (numero de Securite Sociale).
 *
 * @param[in] number  Numero de NIR sans la cle.
 *
 * @return Cle NIR.
 */
int MOD97_CalculateNIRKey(const char* number);

/**
 * @brief Verifie la validite d'un modulo 97 reduit.
 *
 * @param[in] number  Numero a verifier (cle non comprise).
 * @param[in] key     Cle du numero.
 *
 * @retval true   Cle valide.
 * @retval false  Cle invalide
 */
bool MOD97_CheckReducedMod97Key(const char* number, int key);

/**
 * @brief Calcule un modulo 97 reduit.
 *
 * @param[in] number  Numero sur lequel calculer la cle.
 *
 * @return Cle.
 */
int MOD97_CalculateReducedMod97Key(const char* number);

/**
 * @brief Verifie la validite d'une cle RLMC (cle de cheque).
 *
 * @param[in] number  Numero du cheque suivi de la cle.
 *
 * @retval true   Cle RLMC valide.
 * @retval false  Cle RLMC invalide
 */
bool MOD97_CheckRLMCKey(const char* number);

/**
 * @brief Calcule la cle RLMC (cle de cheque).
 *
 * @param[in] number  Numero du cheque.
 *
 * @return Cle RLMC.
 */
int MOD97_CalculateRLMCKey(const char* number);

#ifdef __cplusplus
}
#endif

#endif
