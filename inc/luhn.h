/**
 * @author Gregory Lerbret
 * @file
 * @brief Calcul et de controle des cles de Luhn
 * @date 04/04/2005
 * @version 1.0.0
 */

#ifndef GL_LUHN_H
#define GL_LUHN_H

/**
 * @brief Resultat de la verification de la cle de Luhn
 */
typedef enum
{
    /// @brief La cle de Luhn est correcte
    LUHN_OK,
    /// @brief La cle de Luhn est incorrecte
    LUHN_KO
} LUHN_Res_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @return Identifiant du module (nom et version)
 */
const char* LUHN_Identifier(void);

/**
 * @return Version du module.
 */
int LUHN_Version(void);

/**
 * @brief Calcul de la cle de Luhn
 *
 * @param[in] number Numero dont on veut calculer la cle de Luhn
 *
 * @return Cle de Luhn sous sa forme ASCII
 */
char LUHN_CalculalteLuhnKey(const char* number);

/**
 * @brief Verification de la cle de Luhn
 *
 * @param[in] number Numero a verifier
 *
 * @return
 *  - LUHN_OK pour une cle de Luhn correcte
 *  - LUHN_KO sinon
 */
LUHN_Res_e LUHN_CheckLuhnKey(const char* number);

#ifdef __cplusplus
}
#endif

#endif
