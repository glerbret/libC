/**
 * @author Gregory Lerbret
 * @brief Gestion des options en ligne de commande
 * @version 1.0.0
 * @copyright MIT license
 */

#include "opt.h"
#include "bool.h"

#include <string.h>

#define xstr(s) str(s)
#define str(s) #s

#define OPT_NAME	    "Gestion des options de la ligne de commande"
#define OPT_VERS_MAJ    1
#define OPT_VERS_MIN    0
#define OPT_VERS_BRCH   0
#define OPT_ID		    OPT_NAME " - Version " xstr(OPT_VERS_MAJ) "." xstr(OPT_VERS_MIN) "." xstr(OPT_VERS_BRCH)

const char* OPT_Identifier(void)
{
    return OPT_ID;
}

int OPT_Version(void)
{
    return OPT_VERS_MAJ * 10000 + OPT_VERS_MIN * 100 + OPT_VERS_BRCH;
}

int OPT_GetOpt(int argc, const char *argv[], const char **data, const char* opt, int flags)
{
    static int idx = 0;

    char* pcOptFind;
    bool exit = false;
    int res = OPT_END;

    /* Initialisation des variables */
    if(data != NULL)
    {
        *data = NULL;
    }

    if((flags & OPT_FLG_RESET) != 0)
    {
        idx = 0;
    }

    while(exit == false && idx < argc)
    {
        /* Recheche de la prochaine option */
        for(; argv[idx][0] != '-' && idx < argc; idx++)
        {
            /* NOP */
        }

        if((pcOptFind = strchr(opt, argv[idx][1])) != NULL)
        {
            /* L'option est presente dans la liste des options a traiter */
            exit = true;
            res = (int)argv[idx][1];

            /* Recuperation des donnees liees a l'option */
            if(pcOptFind[1] == ':' && data != NULL)
            {
                if(argv[idx][2] != '\0')
                {
                    *data = &argv[idx][2];
                }
                else if(argv[idx + 1][0] != '-')
                {
                    *data = argv[++idx];
                }
            }
        }
        idx++;
    }
    return res;
}
