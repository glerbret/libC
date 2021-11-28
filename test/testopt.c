#include "opt.h"
#include "bool.h"
#include "test.h"

#include <stdio.h>
#include <string.h>

typedef struct
{
    int         iNbOpt;
    const char* pcLine[7];
    const char* pcResult;
} lignecom_s;

int TstOpt(void)
{
    int iResult = 0;
    size_t szIdx;

    printf("\nTest de \"%s\"\n", OPT_Identifier());

    /* Test de la fonction OPT_GetOpt */
    {
        lignecom_s asLine[] =
        {
            {
                5,
                {"nom", "-a", "-e", "-b", "-f", NULL, NULL},
                "a b "
            },
            {
                5,
                {"nom", "-a", "-e", "-bdonnee", "-f", NULL, NULL},
                "a bdonnee "
            },
            {
                6,
                {"nom", "-a", "-e", "-b", "donnee", "-f", NULL},
                "a bdonnee "
            }
        };
        const char acOpt[] = "ab:c";
        char acResult[25];
        const char* pcData;
        bool bExit;
        int iFlag;
        int iRes;

        /* Test de recuperation */
        for(szIdx = 0; szIdx < (sizeof(asLine) / sizeof(asLine[0])); szIdx++)
        {
            bExit = false;
            iFlag = OPT_FLG_RESET;
            acResult[0] = '\0';

            while(bExit == false)
            {
                if((iRes = OPT_GetOpt(asLine[szIdx].iNbOpt, asLine[szIdx].pcLine, &pcData, acOpt, iFlag)) != OPT_END)
                {
                    sprintf(acResult + strlen(acResult), "%c", (char)iRes);
                    if(pcData != NULL)
                    {
                        strcat(acResult, pcData);
                    }
                    strcat(acResult, " ");
                }
                else
                {
                    bExit = true;
                }
                iFlag = 0;
            }

            if(strcmp(acResult, asLine[szIdx].pcResult) == 0)
            {
                printf("(OPT_GetOpt) test %d OK\n", (int)(szIdx + 1));
            }
            else
            {
                printf("(OPT_GetOpt) test %d KO\n", (int)(szIdx + 1));
                iResult = 1;
            }
        }
    }

    return iResult;
}
