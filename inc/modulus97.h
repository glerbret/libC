/**
 * @author Gregory Lerbret
 * @file
 * @brief Calcul et de controle des modulo 97
 * @date 07/05/2007
 * @version 1.0.0
 */

#ifndef GL_MODULUS97_H
#define GL_MODULUS97_H

/**
 * @brief Resultat de la verification du modulo 97
 */
typedef enum
{
    /// @brief Le modulo 97 est correct
    MOD97_OK,
    /// @brief Le modulo 97 est incorrect
    MOD97_KO
} MOD97_Res_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @return Identifiant du module (nom et version)
 */
const char* MOD97_Identifier(void);

/**
 * @return Version du module
 */
int MOD97_Version(void);

/**
 * @brief Verification de la validite d'un RIB
 *
 * @param[in] pcNumber Numero de RIB complet (y comprit la cle)
 *
 * @return
 *  - MOD97_OK si le RIB est correct
 *  - MOD97_KO sinon
 */
MOD97_Res_e MOD97_CheckRIBKey(const char* pcNumber);

/**
 * @brief Calcul de la cle d'un RIB
 *
 * @param[in] pcNumber Numero de RIB sans la cle
 *
 * @return Cle RIB
 */
int MOD97_CalculateRIBKey(const char* pcNumber);

/**
 * @brief Verification de la validite d'un NIR (Numero de Securite Sociale)
 *
 * @param[in] pcNumber Numero de NIR sans la cle
 * @param[in] iKey Cle du NIR
 *
 * @return
 *  - MOD97_OK si le NIR est correct
 *  - MOD97_KO sinon
 */
MOD97_Res_e MOD97_CheckNIRKey(const char* pcNumber, int iKey);

/**
 * @brief Calcul de la cle d'un NIR (numero de Securite Sociale)
 *
 * @param[in] pcNumber Numero de NIR sans la cle
 *
 * @return Cle NIR
 */
int MOD97_CalculateNIRKey(const char* pcNumber);

/**
 * @brief Verification de la validite d'un modulo 97 reduit
 *
 * @param[in] pcNumber Numero a verifier (cle non comprise)
 * @param[in] iKey Cle du numero
 *
 * @return
 *  - MOD97_OK si le numero est correct
 *  - MOD97_KO sinon
 */
MOD97_Res_e MOD97_CheckReducedMod97Key(const char* pcNumber, int iKey);

/**
 * @brief Calcul d'un modulo 97 reduit
 *
 * @param[in] pcNumber Numero sur lequel calculer la cle
 *
 * @return Cle
 */
int MOD97_CalculateReducedMod97Key(const char* pcNumber);

/**
 * @brief Verification de la validite d'une cle RLMC (cle de cheque)
 *
 * @param[in] pcNumber Numero du cheque suivi de la cle
 *
 * @return
 *  - MOD97_OK si la cle RLMC est correct
 *  - MOD97_KO sinon
 */
MOD97_Res_e MOD97_CheckRLMCKey(const char* pcNumber);

/**
 * @brief Calcul de la cle RLMC (cle de cheque)
 *
 * @param[in] pcNumber Numero du cheque
 *
 * @return Cle RLMC.
 */
int MOD97_CalculateRLMCKey(const char* pcNumber);

#ifdef __cplusplus
}
#endif

#endif
