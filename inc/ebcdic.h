/**
 * @author Gregory Lerbret
 * @file
 * @brief Gestion du chaset EBCDIC
 * @date 14/12/2005
 * @version 1.0.0
 */

#ifndef GL_EBCDIC_H
#define GL_EBCDIC_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @return Identifiant du module (nom et version)
 */
const char* EBCDIC_Identifier(void);

/**
 * @return Version du module
 */
int EBCDIC_Version(void);

/**
 * @brief Conversion ASCI vers EBCDIC
 *
 * @param[in] iASCII Caractere au format ASCII
 *
 * @return Caractere au format EBCDIC.
 */
int EBCDIC_ConvertASCII2EBCDIC(int iASCII);

/**
 * @brief Conversion EBCDIC vers ASCII
 *
 * @param[in] iEBCDIC Caractere au format EBCDIC
 *
 * @return Caractere au format ASCII
 */
int EBCDIC_ConvertEBCDIC2ASCII(int iEBCDIC);

#ifdef __cplusplus
}
#endif

#endif
