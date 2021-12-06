/**
 * @author Gregory Lerbret
 * @brief Gestion des bits
 * @version 1.0.0
 * @copyright MIT license
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

unsigned char BITS_SetBit(unsigned char byte, size_t bitNumber)
{
    if(bitNumber < CHAR_BIT)
    {
        /* Le bit n'est positionne que s'il appartient bien au byte */
        byte |= (1 << bitNumber);
    }

    return byte;
}

unsigned char BITS_ClearBit(unsigned char byte, size_t bitNumber)
{
    if(bitNumber < CHAR_BIT)
    {
        /* Le bit n'est modifie que s'il appartient bien au byte */
        byte &= ~(1 << bitNumber);
    }

    return byte;
}

bool BITS_TestBit(unsigned char byte, size_t bitNumber)
{
    bool isPresent = false;

    if(bitNumber < CHAR_BIT)
    {
        if((byte & (1 << bitNumber)) == 0x00)
        {
            isPresent = false;
        }
        else
        {
            isPresent = true;
        }
    }
    else
    {
        /* Le bit teste n'appartient pas au byte, il n'est donc pas present */
        isPresent = false;
    }

    return isPresent;
}

unsigned char BITS_ReverseBit(unsigned char byte)
{
    byte = (byte << 4) | (byte >> 4);
    byte = ((byte << 2) & 0xCC) | ((byte >> 2) & 0x33);
    byte = ((byte << 1) & 0xAA) | ((byte >> 1) & 0x55);

    return byte;
}
