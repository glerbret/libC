/**
 * @author Gregory Lerbret
 * @brief Gestion des options en ligne de commande
 * @date 13/04/2005
 * @version 1.0.0
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

int OPT_GetOpt(int iNbArg, const char *pacArg[], const char **pcData, const char* pcOpt, int iFlag)
{
    static int iIdx = 0;

    char* pcOptFind;
    bool bExit = false;
    int iRes = OPT_END;

    /* Initialisation des variables */
    if(pcData != NULL)
    {
        *pcData = NULL;
    }

    if((iFlag & OPT_FLG_RESET) != 0)
    {
        iIdx = 0;
    }

    while(bExit == false && iIdx < iNbArg)
    {
        /* Recheche de la prochaine option */
        for(; pacArg[iIdx][0] != '-' && iIdx < iNbArg; iIdx++)
        {
            /* NOP */
        }

        if((pcOptFind = strchr(pcOpt, pacArg[iIdx][1])) != NULL)
        {
            /* L'option est presente dans la liste des options a traiter */
            bExit = true;
            iRes = (int)pacArg[iIdx][1];

            /* Recuperation des donnees liees a l'option */
            if(pcOptFind[1] == ':' && pcData != NULL)
            {
                if(pacArg[iIdx][2] != '\0')
                {
                    *pcData = &pacArg[iIdx][2];
                }
                else if(pacArg[iIdx + 1][0] != '-')
                {
                    *pcData = pacArg[++iIdx];
                }
            }
        }
        iIdx++;
    }
    return iRes;
}
