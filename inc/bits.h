/**
 * @author Gregory Lerbret
 * @file
 * @brief Gestion des bits
 * @version 1.0.0
 * @copyright MIT license
 */

#ifndef GL_BITS_H
#define GL_BITS_H

#include "bool.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @return Identifiant du module (nom et version)
 */
const char* BITS_Identifier(void);

/**
 * @return Version du module
 */
int BITS_Version(void);

/**
 * @brief Positionnement d'un bit dans un byte
 *
 * @param[in] byte Valeur originale du byte
 * @param[in] bitNumber Position du bit a positionner (CHAR_BIT-1 MSB - 0 LSB)
 *
 * @return Valeur finale du byte
 *
 * @pre bitNumber est strictement inferieur a CHAR_BIT
 */
unsigned char BITS_SetBit(unsigned char byte, size_t bitNumber);

/**
 * @brief Suppression d'un bit dans un byte
 *
 * @param[in] byte Valeur originale du byte
 * @param[in] bitNumber Position du bit a baisser (CHAR_BIT-1 MSB - 0 LSB)
 *
 * @return Valeur finale du byte
 *
 * @pre bitNumber est strictement inferieur a CHAR_BIT
 */
unsigned char BITS_ClearBit(unsigned char byte, size_t bitNumber);

/**
 * @brief Test d'un bit dans un byte
 *
 * @param[in] byte Valeur originale du byte
 * @param[in] bitNumber Position du bit a baisser (CHAR_BIT-1 MSB - 0 LSB)
 *
 * @return
 *  - true si le bit est positionne
 *  - false sinon
 *
 * @pre bitNumber est strictement inferieur a CHAR_BIT
 */
bool BITS_TestBit(unsigned char byte, size_t bitNumber);

/**
 * @brief Inversion des bits d'un octet (le bit 0 devient le bit 7, etc.)
 *
 * @param[in] byte Valeur originale de l'octet
 *
 * @return Valeur finale de l'octet
*/
unsigned char  BITS_ReverseBit(unsigned char byte);

#ifdef __cplusplus
}
#endif

#endif
