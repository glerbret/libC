/**
 * @brief Calcul et de controle des cles de Luhn.
 * @version 1.0.0.
 * @copyright MIT license.
 * @author Gregory Lerbret.
 */

#include "luhn.h"
#include "bool.h"

#include <stdio.h>
#include <string.h>

#define xstr(s) str(s)
#define str(s) #s

#define LUHN_NAME	    "Calcul des cles de Luhn"
#define LUHN_VERS_MAJ   1
#define LUHN_VERS_MIN   0
#define LUHN_VERS_BRCH  0
#define LUHN_ID		    LUHN_NAME " - Version " xstr(LUHN_VERS_MAJ) "." xstr(LUHN_VERS_MIN) "." xstr(LUHN_VERS_BRCH)

static int LUHN_CalculateLuhnSum(const char* number, int toDouble)
{
  int sum  = 0;

  for(int idx = (int)strlen(number) - 1; idx >= 0; idx--)
  {
    int value = (number[idx] - '0') * toDouble;
    if(value >= 10)
    {
      value = (value % 10) + 1;
    }
    sum += value;
    toDouble = (toDouble == 2 ? 1 : 2);
  }
  return sum;
}

const char* LUHN_Identifier(void)
{
  return LUHN_ID;
}

int LUHN_Version(void)
{
  return LUHN_VERS_MAJ * 10000 + LUHN_VERS_MIN * 100 + LUHN_VERS_BRCH;
}

char LUHN_CalculateLuhnKey(const char* number)
{
  char luhnKey = (char)(10 - (LUHN_CalculateLuhnSum(number, 2) % 10));
  if(luhnKey == 10)
  {
    luhnKey = 0;
  }
  return (char)(luhnKey + '0');
}

bool LUHN_CheckLuhnKey(const char* number)
{
  return (LUHN_CalculateLuhnSum(number, 1) % 10) == 0;
}
