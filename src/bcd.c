/**
 * @brief Gestion de nombres au format BCD.
 * @version 1.0.0.
 * @copyright MIT license.
 * @author Gregory Lerbret.
 */

#include "bcd.h"

#include <assert.h>

#define xstr(s) str(s)
#define str(s) #s

#define BCD_NAME          "Gestion des nombres au format BCD"
#define BCD_VERS_MAJ      1
#define BCD_VERS_MIN      0
#define BCD_VERS_BRCH     0
#define BCD_ID  BCD_NAME  " - Version " xstr(BCD_VERS_MAJ) "." xstr(BCD_VERS_MIN) "." xstr(BCD_VERS_BRCH)

const char* BCD_Identifier(void)
{
  return BCD_ID;
}

int BCD_Version(void)
{
  return BCD_VERS_MAJ * 10000 + BCD_VERS_MIN * 100 + BCD_VERS_BRCH;
}

char* BCD_ConvBCD2Ascii(char* ascii, const unsigned char* bcd, size_t nbDigit)
{
  size_t indexAscii = 0;
  size_t indexBcd = 0;

  assert(ascii);
  assert(bcd);
  assert(nbDigit);

  /* Si la taille du nombre est impaire, le premier caractere ne conient q'un seul
     digit (dans le quartet de poid faible) */
  if((nbDigit % 2) != 0)
  {
    ascii[0] = (char)((bcd[0] & 0x0F) + '0');
    nbDigit--;
    indexAscii++;
    indexBcd++;
  }

  for(; indexAscii < nbDigit; indexAscii += 2, indexBcd++)
  {
    ascii[indexAscii]     = (char)(((bcd[indexBcd] >> 4) & 0x0F) + '0');
    ascii[indexAscii + 1] = (char)((bcd[indexBcd] & 0x0F) + '0');
  }

  return ascii;
}

unsigned char* BCD_ConvAscii2BCD(unsigned char* bcd, const char* ascii, size_t nbDigit)
{
  assert(bcd);
  assert(ascii);
  assert(nbDigit);

  if((nbDigit % 2) != 0)
  {
    bcd[0] = (char)(ascii[0] - '0');
    for(size_t index = 1; index < (nbDigit + 1) / 2; index++)
    {
        bcd[index] = (char)(((ascii[index * 2 - 1] - '0') << 4) + (ascii[index * 2] - '0'));
    }
  }
  else
  {
    for(size_t index = 0; index < (nbDigit + 1) / 2; index++)
    {
      bcd[index] = (char)(((ascii[index * 2] - '0') << 4) + (ascii[index * 2 + 1] - '0'));
    }
  }

  return bcd;
}
