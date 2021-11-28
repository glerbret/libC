#include "luhn.h"
#include "test.h"

#include <stdio.h>
#include <string.h>

typedef struct
{
    const char* acNum;
    char        cCle;
} carte_s;

int TstLuhn(void)
{
    const char* acNumTest[] =
    {
        "67030403669228008",
        "4972880061065935"
    };
    const char* acNumTestKO[] =
    {
        "67030403569228008",
        "4972880021065935"
    };
    carte_s sCarteTest[] =
    {
        {"6703040366922800", '8'},
        {"497288006106593",  '5'}
    };
    size_t szIdx;
    int iResult = 0;

    printf("\nTest de \"%s\"\n", LUHN_Identifier());

    /* test de la fonction de verification sur des numeros corrects */
    for(szIdx = 0; szIdx < (sizeof(acNumTest) / sizeof(acNumTest[0])); szIdx++)
    {
        if(LUHN_CheckLuhnKey(acNumTest[szIdx]) == LUHN_OK)
        {
            printf("(LUHN_CheckLuhnKey) test validite numero correct %d OK\n", (int)(szIdx + 1));
        }
        else
        {
            printf("(LUHN_CheckLuhnKey) test validite numero correct %d KO\n", (int)(szIdx + 1));
            iResult = 1;
        }
    }

    /* test de la fonction de verification sur des numeros incorrects */
    for(szIdx = 0; szIdx < (sizeof(acNumTestKO) / sizeof(acNumTestKO[0])); szIdx++)
    {
        if(LUHN_CheckLuhnKey(acNumTestKO[szIdx]) == LUHN_OK)
        {
            printf("(LUHN_CheckLuhnKey) test validite numero errone %d KO\n", (int)(szIdx + 1));
            iResult = 1;
        }
        else
        {
            printf("(LUHN_CheckLuhnKey) test validite numero errone %d OK\n", (int)(szIdx + 1));
        }
    }

    /* test de la fonction de calcul */
    for(szIdx = 0; szIdx < (sizeof(sCarteTest) / sizeof(sCarteTest[0])); szIdx++)
    {
        if(LUHN_CalculalteLuhnKey(sCarteTest[szIdx].acNum) == sCarteTest[szIdx].cCle)
        {
            printf("(LUHN_CalculalteLuhnKey) test calcul %d OK\n", (int)(szIdx + 1));
        }
        else
        {
            printf("(LUHN_CalculalteLuhnKey) test calcul %d KO", (int)(szIdx + 1));
            iResult = 1;
        }
    }

    return iResult;
}
