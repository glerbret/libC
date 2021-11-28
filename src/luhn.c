/**
 * @author Gregory Lerbret
 * @brief Calcul et de controle des cles de Luhn
 * @date 04/04/2005
 * @version 1.0.0
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

/// @todo revoir le passage de iDouble dans LUHN_CalculateLuhnSum. Plutôt une info cle presente/non presente
/// @todo Preciser contrainte : ce sont des chaînes de caracteres
/// @todo LUHN_CalculalteLuhnKey ==> LUHN_CalculateLuhnKey
/// @todo Dans LUHN_CalculalteLuhnKey pourquoi utiliser un char et non un int ?

static int LUHN_CalculateLuhnSum(const char* pcNumber, int iDouble)
{
    int iIdx;
    int iValue;
    int iSum  = 0;

    for(iIdx = (int)strlen(pcNumber) - 1; iIdx >= 0; iIdx--)
    {
        iValue = (pcNumber[iIdx] - '0') * iDouble;
        if(iValue >= 10)
        {
            iValue = (iValue % 10) + 1;
        }
        iSum += iValue;
        iDouble = (iDouble == 2 ? 1 : 2);
    }
    return iSum;
}

const char* LUHN_Identifier(void)
{
    return LUHN_ID;
}

int LUHN_Version(void)
{
    return LUHN_VERS_MAJ * 10000 + LUHN_VERS_MIN * 100 + LUHN_VERS_BRCH;
}

char LUHN_CalculalteLuhnKey(const char* pcNumber)
{
    char cLuhn;

    cLuhn = (char)(10 - (LUHN_CalculateLuhnSum(pcNumber, 2) % 10));
    if(cLuhn == 10)
    {
        cLuhn = 0;
    }
    return (char)(cLuhn + '0');
}

LUHN_Res_e LUHN_CheckLuhnKey(const char* pcNumber)
{
    if((LUHN_CalculateLuhnSum(pcNumber, 1) % 10) == 0)
    {
        return LUHN_OK;
    }
    else
    {
        return LUHN_KO;
    }
}
