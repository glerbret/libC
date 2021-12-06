#include "opt.h"
#include "bool.h"
#include "test.h"

#include <stdio.h>
#include <string.h>

typedef struct
{
    int         nbOpt;
    const char* line[7];
    const char* result;
} lignecom_s;

int TstOpt(void)
{
    int result = 0;
    size_t idx;

    printf("\nTest de \"%s\"\n", OPT_Identifier());

    /* Test de la fonction OPT_GetOpt */
    {
        lignecom_s lines[] =
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
        const char options[] = "ab:c";
        char output[25];
        const char* data;
        bool exit;
        int flag;
        int res;

        /* Test de recuperation */
        for(idx = 0; idx < (sizeof(lines) / sizeof(lines[0])); idx++)
        {
            exit = false;
            flag = OPT_FLG_RESET;
            output[0] = '\0';

            while(exit == false)
            {
                if((res = OPT_GetOpt(lines[idx].nbOpt, lines[idx].line, &data, options, flag)) != OPT_END)
                {
                    sprintf(output + strlen(output), "%c", (char)res);
                    if(data != NULL)
                    {
                        strcat(output, data);
                    }
                    strcat(output, " ");
                }
                else
                {
                    exit = true;
                }
                flag = 0;
            }

            if(strcmp(output, lines[idx].result) == 0)
            {
                printf("(OPT_GetOpt) test %d OK\n", (int)(idx + 1));
            }
            else
            {
                printf("(OPT_GetOpt) test %d KO\n", (int)(idx + 1));
                result = 1;
            }
        }
    }

    return result;
}
