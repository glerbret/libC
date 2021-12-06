/**
 * @author Gregory Lerbret
 * @brief Calcul et de controle des cles de Luhn
 * @version 1.0.0
 * @copyright MIT license
 */

#include "luhn.h"

#include <stdio.h>
#include <string.h>

#define xstr(s) str(s)
#define str(s) #s

#define LUHN_NAME	    "Calcul des cles de Luhn"
#define LUHN_VERS_MAJ   1
#define LUHN_VERS_MIN   0
#define LUHN_VERS_BRCH  0
#define LUHN_ID		    LUHN_NAME " - Version " xstr(LUHN_VERS_MAJ) "." xstr(LUHN_VERS_MIN) "." xstr(LUHN_VERS_BRCH)

/// @todo revoir le passage de toDouble dans LUHN_CalculateLuhnSum. Plut�t une info cle presente/non presente
/// @todo Preciser contrainte : ce sont des cha�nes de caracteres
/// @todo LUHN_CalculalteLuhnKey ==> LUHN_CalculateLuhnKey
/// @todo Dans LUHN_CalculalteLuhnKey pourquoi utiliser un char et non un int ?

static int LUHN_CalculateLuhnSum(const char* number, int toDouble)
{
    int idx;
    int value;
    int sum  = 0;

    for(idx = (int)strlen(number) - 1; idx >= 0; idx--)
    {
        value = (number[idx] - '0') * toDouble;
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

char LUHN_CalculalteLuhnKey(const char* number)
{
    char luhnKey;

    luhnKey = (char)(10 - (LUHN_CalculateLuhnSum(number, 2) % 10));
    if(luhnKey == 10)
    {
        luhnKey = 0;
    }
    return (char)(luhnKey + '0');
}

LUHN_Res_e LUHN_CheckLuhnKey(const char* number)
{
    if((LUHN_CalculateLuhnSum(number, 1) % 10) == 0)
    {
        return LUHN_OK;
    }
    else
    {
        return LUHN_KO;
    }
}
