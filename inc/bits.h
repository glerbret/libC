/**
   \author Grégory Lerbret
   \file bits.h
   \brief Gestion des bits.<br>
   \date 02/05/2008
   \version 1.0.0
*/

#ifndef GL_BITS_H
#define GL_BITS_H

#include <stddef.h>
#include "bool.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
   \fn const char* BITS_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char*    BITS_Identifier(void);

/**
   \fn int BITS_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int            BITS_Version(void);

/**
   \fn unsigned char BITS_SetBit(unsigned char ucByte, size_t szBitNumber)
   \brief Positionnelent d'un bit dans un byte.
   \param[in] ucByte la valeur originale du byte
   \param[in] szBitNumber la position du bit à positionner (CHAR_BIT MSB - 0 LSB)
   \return la valeur finale du byte.
*/
unsigned char  BITS_SetBit(unsigned char ucByte, size_t szBitNumber);

/**
   \fn unsigned char BITS_ClearBit(unsigned char ucByte, size_t szBitNumber)
   \brief Suppression d'un bit dans un byte.
   \param[in] ucByte la valeur originale du byte
   \param[in] szBitNumber la position du bit à baisser (CHAR_BIT MSB - 0 LSB)
   \return la valeur finale du byte.
*/
unsigned char  BITS_ClearBit(unsigned char ucByte, size_t szBitNumber);

/**
   \fn unsigned char BITS_TestBit(unsigned char ucByte, size_t szBitNumber)
   \brief Test d'un bit dans un byte.
   \param[in] ucByte la valeur originale du byte
   \param[in] szBitNumber la position du bit à baisser (CHAR_BIT MSB - 0 LSB)
   \return  true si le bit est positionne.<br>
            false sinon.
*/
bool           BITS_TestBit(unsigned char ucByte, size_t szBitNumber);

/**
   \fn unsigned char BITS_ReverseBit(unsigned char ucByte)
   \brief Inversion des bits d'un octet (le bit 0 devient le bit 7, etc.).
   \param[in] ucByte la valeur originale de l'octet
   \return la valeur finale de l'octet.
*/
unsigned char  BITS_ReverseBit(unsigned char ucByte);

#ifdef __cplusplus
}
#endif

#endif
