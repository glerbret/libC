/**
 * @author Gregory Lerbret
 * @brief Gestion des bits
 * @date 02/05/2008
 * @version 1.0.0
 */

#include "bits.h"
#include "bool.h"

#include <limits.h>

#define xstr(s) str(s)
#define str(s) #s

#define BITS_NAME       "Gestion des bits d'un byte"
#define BITS_VERS_MAJ   1
#define BITS_VERS_MIN   0
#define BITS_VERS_BRCH  0
#define BITS_ID         BITS_NAME " - Version " xstr(BITS_VERS_MAJ) "." xstr(BITS_VERS_MIN) "." xstr(BITS_VERS_BRCH)

const char* BITS_Identifier(void)
{
    return BITS_ID;
}

int BITS_Version(void)
{
    return BITS_VERS_MAJ * 10000 + BITS_VERS_MIN * 100 + BITS_VERS_BRCH;
}

unsigned char BITS_SetBit(unsigned char ucByte, size_t szBitNumber)
{
    if(szBitNumber < CHAR_BIT)
    {
        /* Le bit n'est positionne que s'il appartient bien au byte */
        ucByte |= (1 << szBitNumber);
    }

    return ucByte;
}

unsigned char BITS_ClearBit(unsigned char ucByte, size_t szBitNumber)
{
    if(szBitNumber < CHAR_BIT)
    {
        /* Le bit n'est modifie que s'il appartient bien au byte */
        ucByte &= ~(1 << szBitNumber);
    }

    return ucByte;
}

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

unsigned char BITS_ReverseBit(unsigned char ucByte)
{
    ucByte = (ucByte << 4) | (ucByte >> 4);
    ucByte = ((ucByte << 2) & 0xCC) | ((ucByte >> 2) & 0x33);
    ucByte = ((ucByte << 1) & 0xAA) | ((ucByte >> 1) & 0x55);

    return ucByte;
}
