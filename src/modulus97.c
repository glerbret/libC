/**
 * @author Gregory Lerbret
 * @brief Calcul et de controle des modulo 97
 * @date 04/04/2005
 * @version 1.0.0
 */

#include "modulus97.h"

#include <stdio.h>
#include <string.h>

#define xstr(s) str(s)
#define str(s) #s

#define MOD97_NAME	    "Calcul des modulo 97"
#define MOD97_VERS_MAJ  1
#define MOD97_VERS_MIN  0
#define MOD97_VERS_BRCH 0
#define MOD97_ID        MOD97_NAME " - Version " xstr(MOD97_VERS_MAJ) "." xstr(MOD97_VERS_MIN) "." xstr(MOD97_VERS_BRCH)

static int MOD97_CalculateModulus97(const char* pcNumber)
{
    size_t szIdx;
    size_t szLen;
    int iModulus;

    /* Longueur du nombre */
    szLen = strlen(pcNumber);

    /* Calcul du modulo */
    for(szIdx = 0, iModulus = 0; szIdx < szLen; szIdx++)
    {
        iModulus = ((iModulus * 10) + (pcNumber[szIdx] - '0')) % 97;
    }

    return iModulus;
}

static int MOD97_CalculateReducedModulus97(const char* pcNumber)
{
    int iModulus97;
    int iReducesModulus97;
    int iR0;
    int iR1;

    /* Calcul du modulo 97 */
    iModulus97 = MOD97_CalculateModulus97(pcNumber);

    /* Reduction du modulo 97 */
    iR0               = iModulus97 % 10;
    iR1               = iModulus97 / 10;
    iReducesModulus97 = (iR1 + 2 * iR0) % 10;

    return iReducesModulus97;
}

const char* MOD97_Identifier(void)
{
    return MOD97_ID;
}

int MOD97_Version(void)
{
    return MOD97_VERS_MAJ * 10000 + MOD97_VERS_MIN * 100 + MOD97_VERS_BRCH;
}

MOD97_Res_e MOD97_CheckRIBKey(const char* pcNumber)
{
    if(MOD97_CalculateModulus97(pcNumber) == 0)
    {
        return MOD97_OK;
    }
    else
    {
        return MOD97_KO;
    }
}

int MOD97_CalculateRIBKey(const char* pcNumber)
{
    int iModulus97;

    /* Calcul du modulo des donnees presente */
    iModulus97 = MOD97_CalculateModulus97(pcNumber);

    /* Calcul de la cle */
    iModulus97 = (iModulus97 * 100) % 97;
    iModulus97 = 97 - iModulus97;

    return iModulus97;
}

MOD97_Res_e MOD97_CheckNIRKey(const char* pcNumber, int iKey)
{
    int   iModulus97;

    iModulus97 = MOD97_CalculateModulus97(pcNumber);

    if(iModulus97 + iKey == 97)
    {
        return MOD97_OK;
    }
    else
    {
        return MOD97_KO;
    }
}

int MOD97_CalculateNIRKey(const char* pcNumber)
{
    int   iModulus97;

    /* Calcul du modulo des donnees presente    */
    iModulus97 = MOD97_CalculateModulus97(pcNumber);

    /* Calcul de la cle */
    iModulus97 = 97 - iModulus97;

    return iModulus97;
}

MOD97_Res_e MOD97_CheckReducedMod97Key(const char* pcNumber, int iKey)
{
    if(MOD97_CalculateReducedModulus97(pcNumber) == iKey)
    {
        return MOD97_OK;
    }
    else
    {
        return MOD97_KO;
    }
}

int MOD97_CalculateReducedMod97Key(const char* pcNumber)
{
    return MOD97_CalculateReducedModulus97(pcNumber);
}

MOD97_Res_e MOD97_CheckRLMCKey(const char* pcNumber)
{
    if(MOD97_CalculateModulus97(pcNumber) == 0)
    {
        return MOD97_OK;
    }
    else
    {
        return MOD97_KO;
    }
}

int MOD97_CalculateRLMCKey(const char* pcNumber)
{
    int iModulus97;

    /* Calcul du modulo des donnees presente */
    iModulus97 = MOD97_CalculateModulus97(pcNumber);

    /* Calcul de la cle */
    iModulus97 = (iModulus97 * 100) % 97;
    iModulus97 = 97 - iModulus97;

    return iModulus97;
}
