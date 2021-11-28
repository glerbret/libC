/**
   \author Grégory Lerbret
   \file opt.c
   \brief Gestion des options en ligne de commande.<br>
   \date 13/04/2005
   \version 1.0.0
*/

#include <string.h>
#include "opt.h"
#include "bool.h"

#define xstr(s) str(s)
#define str(s) #s

#define OPT_NAME	         "Gestion des options de la ligne de commande"
#define OPT_VERS_MAJ       1
#define OPT_VERS_MIN       0
#define OPT_VERS_BRCH      0
#define OPT_ID		         OPT_NAME " - Version " xstr(OPT_VERS_MAJ) "." xstr(OPT_VERS_MIN) "." xstr(OPT_VERS_BRCH)

/**
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char* OPT_Identifier(void)
{
   return OPT_ID;
}

/**
   \brief Version du module.
   \return La version du module.
*/
int OPT_Version(void)
{
   return OPT_VERS_MAJ*10000 + OPT_VERS_MIN*100 + OPT_VERS_BRCH;
}

/**
   \brief   Analyse des options fournis au programme.<br>
            A chaque appel, la fonction retourne une des options geres.
   \param[in] iNbArg le nombre d'arguments fournis au programme.
   \param[in] pacArg les arguments fournis au programme.
   \param[out] pcData la donnee liee a l'argument.
   \param[in] pcOpt la liste des options a traiter (une option suivi de : indique que l'option accepte des donnees).
   \param[in] iFlag flag de traitement (OPT_FLG_RESET remet a 0 le compteur, l'analyse recommence au premier argument).
   \return  La position de l'option si une option est trouvee.<br>
            OPT_END sinon
*/
int OPT_GetOpt(int iNbArg, const char *pacArg[], const char **pcData, const char* pcOpt, int iFlag)
{
   static int     iIdx     = 0;

   char*          pcOptFind;
   bool	         bExit    = false;
   int	         iRes     = OPT_END;

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
            else if(pacArg[iIdx+1][0] != '-')
            {
               *pcData = pacArg[++iIdx];
            }
         }
      }
      iIdx++;
   }
   return iRes;
}
