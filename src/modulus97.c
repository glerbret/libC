/**
 * @author Gregory Lerbret
 * @brief Calcul et de controle des modulo 97
 * @version 1.0.0
 * @copyright MIT license
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

static int MOD97_CalculateModulus97(const char* number)
{
    size_t idx;
    size_t len;
    int modulus;

    /* Longueur du nombre */
    len = strlen(number);

    /* Calcul du modulo */
    for(idx = 0, modulus = 0; idx < len; idx++)
    {
        modulus = ((modulus * 10) + (number[idx] - '0')) % 97;
    }

    return modulus;
}

static int MOD97_CalculateReducedModulus97(const char* number)
{
    int modulus97;
    int reducesModulus97;
    int r0;
    int r1;

    /* Calcul du modulo 97 */
    modulus97 = MOD97_CalculateModulus97(number);

    /* Reduction du modulo 97 */
    r0               = modulus97 % 10;
    r1               = modulus97 / 10;
    reducesModulus97 = (r1 + 2 * r0) % 10;

    return reducesModulus97;
}

const char* MOD97_Identifier(void)
{
    return MOD97_ID;
}

int MOD97_Version(void)
{
    return MOD97_VERS_MAJ * 10000 + MOD97_VERS_MIN * 100 + MOD97_VERS_BRCH;
}

MOD97_Res_e MOD97_CheckRIBKey(const char* number)
{
    if(MOD97_CalculateModulus97(number) == 0)
    {
        return MOD97_OK;
    }
    else
    {
        return MOD97_KO;
    }
}

int MOD97_CalculateRIBKey(const char* number)
{
    int modulus97;

    /* Calcul du modulo des donnees presente */
    modulus97 = MOD97_CalculateModulus97(number);

    /* Calcul de la cle */
    modulus97 = (modulus97 * 100) % 97;
    modulus97 = 97 - modulus97;

    return modulus97;
}

MOD97_Res_e MOD97_CheckNIRKey(const char* number, int key)
{
    int modulus97;

    modulus97 = MOD97_CalculateModulus97(number);

    if(modulus97 + key == 97)
    {
        return MOD97_OK;
    }
    else
    {
        return MOD97_KO;
    }
}

int MOD97_CalculateNIRKey(const char* number)
{
    int modulus97;

    /* Calcul du modulo des donnees presente    */
    modulus97 = MOD97_CalculateModulus97(number);

    /* Calcul de la cle */
    modulus97 = 97 - modulus97;

    return modulus97;
}

MOD97_Res_e MOD97_CheckReducedMod97Key(const char* number, int key)
{
    if(MOD97_CalculateReducedModulus97(number) == key)
    {
        return MOD97_OK;
    }
    else
    {
        return MOD97_KO;
    }
}

int MOD97_CalculateReducedMod97Key(const char* number)
{
    return MOD97_CalculateReducedModulus97(number);
}

MOD97_Res_e MOD97_CheckRLMCKey(const char* number)
{
    if(MOD97_CalculateModulus97(number) == 0)
    {
        return MOD97_OK;
    }
    else
    {
        return MOD97_KO;
    }
}

int MOD97_CalculateRLMCKey(const char* number)
{
    int modulus97;

    /* Calcul du modulo des donnees presente */
    modulus97 = MOD97_CalculateModulus97(number);

    /* Calcul de la cle */
    modulus97 = (modulus97 * 100) % 97;
    modulus97 = 97 - modulus97;

    return modulus97;
}
