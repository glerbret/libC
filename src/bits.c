/**
   \author Grégory Lerbret
   \file bits.c
   \brief Gestion des bits.<br>
   \date 02/05/2008
   \version 1.0.0
*/

#include <limits.h>
#include "bits.h"
#include "bool.h"

#define xstr(s) str(s)
#define str(s) #s

#define BITS_NAME          "Gestion des bits d'un byte"
#define BITS_VERS_MAJ      1
#define BITS_VERS_MIN      0
#define BITS_VERS_BRCH     0
#define BITS_ID            BITS_NAME " - Version " xstr(BITS_VERS_MAJ) "." xstr(BITS_VERS_MIN) "." xstr(BITS_VERS_BRCH)

/**
   \fn const char* BITS_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char* BITS_Identifier(void)
{
   return BITS_ID;
}

/**
   \fn int BITS_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int BITS_Version(void)
{
   return BITS_VERS_MAJ*10000 + BITS_VERS_MIN*100 + BITS_VERS_BRCH;
}

/**
   \fn unsigned char BITS_SetBit(unsigned char ucByte, size_t szBitNumber)
   \brief Positionnelent d'un bit dans un byte.
   \param[in] ucByte la valeur originale du byte
   \param[in] szBitNumber la position du bit à positionner (CHAR_BIT MSB - 0 LSB)
   \return la valeur finale du byte.
*/
unsigned char BITS_SetBit(unsigned char ucByte, size_t szBitNumber)
{
   if(szBitNumber < CHAR_BIT)
   {
      /* Le bit n'est positionne que s'il appartient bien au byte */
      ucByte |= (1 << szBitNumber);
   }

   return ucByte;
}

/**
   \fn unsigned char BITS_ClearBit(unsigned char ucByte, size_t szBitNumber)
   \brief Suppression d'un bit dans un byte.
   \param[in] ucByte la valeur originale du byte
   \param[in] szBitNumber la position du bit à baisser (CHAR_BIT MSB - 0 LSB)
   \return la valeur finale du byte.
*/
unsigned char BITS_ClearBit(unsigned char ucByte, size_t szBitNumber)
{
   if(szBitNumber < CHAR_BIT)
   {
      /* Le bit n'est modifie que s'il appartient bien au byte */
      ucByte &= ~(1 << szBitNumber);
   }

   return ucByte;
}

/**
   \fn unsigned char BITS_TestBit(unsigned char ucByte, size_t szBitNumber)
   \brief Test d'un bit dans un byte
   \param[in] ucByte la valeur originale du byte
   \param[in] szBitNumber la position du bit à baisser (CHAR_BIT MSB - 0 LSB)
   \return  true si le bit est positionne.br>
            false sinon.
*/
bool BITS_TestBit(unsigned char ucByte, size_t szBitNumber)
{
   bool  bBitIPresent = false;

   if(szBitNumber < CHAR_BIT)
   {
      if((ucByte & (1 << szBitNumber)) == 0x00)
      {
         bBitIPresent = false;
      }
      else
      {
         bBitIPresent = true;
      }
   }
   else
   {
      /* Le bit teste n'appartient pas au byte, il n'est donc pas present */
      bBitIPresent = false;
   }

   return bBitIPresent;
}

/**
   \fn unsigned char BITS_ReverseBit(unsigned char ucByte)
   \brief Inversion des bits d'un octet (le bit 0 devient le bit 7, etc.).
   \param[in] ucByte la valeur originale de l'octet
   \return la valeur finale de l'octet.
*/
unsigned char BITS_ReverseBit(unsigned char ucByte)
{
   ucByte = (ucByte << 4) | (ucByte >> 4);
   ucByte = ((ucByte << 2) & 0xCC) | ((ucByte >> 2) & 0x33);
   ucByte = ((ucByte << 1) & 0xAA) | ((ucByte >> 1) & 0x55);

   return ucByte;
}
