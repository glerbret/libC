#include "modulus97.h"
#include "test.h"

#include <stdio.h>
#include <string.h>

typedef struct
{
    const char* acNum;
    int         iKey;
} modulo97_s;

int TstModulus97(void)
{
    const char* acRIBOK[] =
    {
        "14506020305210889900045"
    };
    const char* acRIBKO[] =
    {
        "14506020305210889900048"
    };
    modulo97_s sCalculRIB[] =
    {
        {"145060203052108899000",  45}
    };
    modulo97_s sNIROK[] =
    {
        {"1781142218207", 63}
    };
    modulo97_s sNIRKO[] =
    {
        {"1781148218207", 63}
    };
    modulo97_s sCalculNIR[] =
    {
        {"1781142218207", 63}
    };
    modulo97_s sReducedOK[] =
    {
        {"12345",   4}
    };
    modulo97_s sReducedKO[] =
    {
        {"12345",   8}
    };
    modulo97_s sCalculReduced[] =
    {
        {"12345",   4}
    };
    const char* acRLMCOK[] =
    {
        "667954504201450690805210889900090"
    };
    const char* acRLMCKO[] =
    {
        "667954504201450690805210889900012"
    };
    modulo97_s sCalculRLMC[] =
    {
        {"6679545042014506908052108899000",  90}
    };
    size_t szIdx;
    int iResult = 0;

    printf("\nTest de \"%s\"\n", MOD97_Identifier());

    /* test de la fonction de verification RIB sur des numeros corrects */
    for(szIdx = 0; szIdx < (sizeof(acRIBOK) / sizeof(acRIBOK[0])); szIdx++)
    {
        if(MOD97_CheckRIBKey(acRIBOK[szIdx]) == MOD97_OK)
        {
            printf("(MOD97_CheckRIBKey) test validite RIB numero correct %d OK\n", (int)(szIdx + 1));
        }
        else
        {
            printf("(MOD97_CheckRIBKey) test validite RIB numero correct %d KO\n", (int)(szIdx + 1));
            iResult = 1;
        }
    }

    /* test de la fonction de verification RIB sur des numeros incorrects */
    for(szIdx = 0; szIdx < (sizeof(acRIBKO) / sizeof(acRIBKO[0])); szIdx++)
    {
        if(MOD97_CheckRIBKey(acRIBKO[szIdx]) == MOD97_OK)
        {
            printf("(MOD97_CheckRIBKey) test validite RIB numero errone %d KO\n", (int)(szIdx + 1));
            iResult = 1;
        }
        else
        {
            printf("(MOD97_CheckRIBKey) test validite RIB numero errone %d OK\n", (int)(szIdx + 1));
        }
    }

    /* test de la fonction de calcul de RIB*/
    for(szIdx = 0; szIdx < (sizeof(sCalculRIB) / sizeof(sCalculRIB[0])); szIdx++)
    {
        if(MOD97_CalculateRIBKey(sCalculRIB[szIdx].acNum) == sCalculRIB[szIdx].iKey)
        {
            printf("(MOD97_CalculateRIBKey) test calcul RIB %d OK\n", (int)(szIdx + 1));
        }
        else
        {
            printf("(MOD97_CalculateRIBKey) test calcul RIB %d KO", (int)(szIdx + 1));
            iResult = 1;
        }
    }

    /* test de la fonction de verification NIR sur des numeros corrects */
    for(szIdx = 0; szIdx < (sizeof(sNIROK) / sizeof(sNIROK[0])); szIdx++)
    {
        if(MOD97_CheckNIRKey(sNIROK[szIdx].acNum, sNIROK[szIdx].iKey) == MOD97_OK)
        {
            printf("(MOD97_CheckNIRKey) test validite NIR numero correct %d OK\n", (int)(szIdx + 1));
        }
        else
        {
            printf("(MOD97_CheckNIRKey) test validite NIR numero correct %d KO\n", (int)(szIdx + 1));
            iResult = 1;
        }
    }

    /* test de la fonction de verification NIR sur des numeros incorrects */
    for(szIdx = 0; szIdx < (sizeof(sNIRKO) / sizeof(sNIRKO[0])); szIdx++)
    {
        if(MOD97_CheckNIRKey(sNIRKO[szIdx].acNum, sNIRKO[szIdx].iKey) == MOD97_OK)
        {
            printf("(MOD97_CheckNIRKey) test validite NIR numero errone %d KO\n", (int)(szIdx + 1));
            iResult = 1;
        }
        else
        {
            printf("(MOD97_CheckNIRKey) test validite NIR numero errone %d OK\n", (int)(szIdx + 1));
        }
    }

    /* test de la fonction de calcul de NIR*/
    for(szIdx = 0; szIdx < (sizeof(sCalculNIR) / sizeof(sCalculNIR[0])); szIdx++)
    {
        if(MOD97_CalculateNIRKey(sCalculNIR[szIdx].acNum) == sCalculNIR[szIdx].iKey)
        {
            printf("(MOD97_CalculateNIRKey) test calcul NIR %d OK\n", (int)(szIdx + 1));
        }
        else
        {
            printf("(MOD97_CalculateNIRKey) test calcul NIR %d KO", (int)(szIdx + 1));
            iResult = 1;
        }
    }

    /* test de la fonction de verification modulo 97 reduit sur des numeros corrects */
    for(szIdx = 0; szIdx < (sizeof(sReducedOK) / sizeof(sReducedOK[0])); szIdx++)
    {
        if(MOD97_CheckReducedMod97Key(sReducedOK[szIdx].acNum, sReducedOK[szIdx].iKey) == MOD97_OK)
        {
            printf("(MOD97_CheckReducedMod97Key) test validite numero correct %d OK\n", (int)(szIdx + 1));
        }
        else
        {
            printf("(MOD97_CheckReducedMod97Key) test validite numero correct %d KO\n", (int)(szIdx + 1));
            iResult = 1;
        }
    }

    /* test de la fonction de verification NIR sur des numeros incorrects */
    for(szIdx = 0; szIdx < (sizeof(sReducedKO) / sizeof(sReducedKO[0])); szIdx++)
    {
        if(MOD97_CheckReducedMod97Key(sReducedKO[szIdx].acNum, sReducedKO[szIdx].iKey) == MOD97_OK)
        {
            printf("(MOD97_CheckReducedMod97Key) test validite numero errone %d KO\n", (int)(szIdx + 1));
            iResult = 1;
        }
        else
        {
            printf("(MOD97_CheckReducedMod97Key) test validite numero errone %d OK\n", (int)(szIdx + 1));
        }
    }

    /* test de la fonction de calcul de NIR*/
    for(szIdx = 0; szIdx < (sizeof(sCalculReduced) / sizeof(sCalculReduced[0])); szIdx++)
    {
        if(MOD97_CalculateReducedMod97Key(sCalculReduced[szIdx].acNum) == sCalculReduced[szIdx].iKey)
        {
            printf("(MOD97_CalculateReducedMod97Key) test calcul %d OK\n", (int)(szIdx + 1));
        }
        else
        {
            printf("(MOD97_CalculateReducedMod97Key) test calcul %d KO", (int)(szIdx + 1));
            iResult = 1;
        }
    }

    /* test de la fonction de verification RLMC sur des numeros corrects */
    for(szIdx = 0; szIdx < (sizeof(acRLMCOK) / sizeof(acRLMCOK[0])); szIdx++)
    {
        if(MOD97_CheckRLMCKey(acRLMCOK[szIdx]) == MOD97_OK)
        {
            printf("(MOD97_CheckRLMCKey) test validite RLMC numero correct %d OK\n", (int)(szIdx + 1));
        }
        else
        {
            printf("(MOD97_CheckRLMCKey) test validite RLMC numero correct %d KO\n", (int)(szIdx + 1));
            iResult = 1;
        }
    }

    /* test de la fonction de verification RLMC sur des numeros incorrects */
    for(szIdx = 0; szIdx < (sizeof(acRLMCKO) / sizeof(acRLMCKO[0])); szIdx++)
    {
        if(MOD97_CheckRLMCKey(acRLMCKO[szIdx]) == MOD97_OK)
        {
            printf("(MOD97_CheckRLMCKey) test validite RLMC numero errone %d KO\n", (int)(szIdx + 1));
            iResult = 1;
        }
        else
        {
            printf("(MOD97_CheckRLMCKey) test validite RLMC numero errone %d OK\n", (int)(szIdx + 1));
        }
    }

    /* test de la fonction de calcul de RLMC*/
    for(szIdx = 0; szIdx < (sizeof(sCalculRLMC) / sizeof(sCalculRLMC[0])); szIdx++)
    {
        if(MOD97_CalculateRLMCKey(sCalculRLMC[szIdx].acNum) == sCalculRLMC[szIdx].iKey)
        {
            printf("(MOD97_CalculateRLMCKey) test calcul RLMC %d OK\n", (int)(szIdx + 1));
        }
        else
        {
            printf("(MOD97_CalculateRLMCKey) test calcul RLMC %d KO", (int)(szIdx + 1));
            iResult = 1;
        }
    }

    return iResult;
}
