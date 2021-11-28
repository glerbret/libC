#include <stdio.h>
#include <string.h>
#include "ini.h"
#include "test.h"

typedef struct
{
   const char* pcSection;
   const char* pcCle;
   const char* pcValeur;
} ini_s;

int TstIni(void)
{
   size_t            szIdx;
   int               iResult=0;
   char              acRead[50];
   const char        acFileName[]="./testini.ini";
   FILE*             fp;

   printf("\nTest de \"%s\"\n", INI_Identifier());

   /* Test de la fonction INI_ReadIni */
   {
      const char        acDefault[]="non";
      const char        acIniTFile[]="[seCtion1]\nclE1=valeur1\ncLE2=valeur2\n";
      ini_s             sIni[] =
      {
         {"section1"    , "cle1"    , "valeur1"},
         {"section1"    , "cle3"    , "non"},
         {"section2"    , "cle1"    , "non"}
      };

      /* Creation du fichier de travail */
      fp=fopen(acFileName, "w");
      if(fp == NULL)
      {
         printf("(INI_ReadIni) Echec ouverture fichier pour ecriture");
         return 1;
      }
      fputs(acIniTFile, fp);
      fclose(fp);

      /* Test de l'absence de fichier */
      INI_ReadIni("section1", "cle1", acDefault, acRead, sizeof acRead, "inexistant.ini");
      if(strcmp(acRead, acDefault) == 0)
      {
         printf("(INI_ReadIni) Test fichier absent OK\n");
      }
      else
      {
         printf("(INI_ReadIni) Test fichier absent KO\n");
         iResult = 1;
      }

      /* Test de l'absence de valeur par defaut */
      if(INI_ReadIni("section1", "cle1", NULL, acRead, sizeof acRead, "inexistant.ini") == 0)
      {
         printf("(INI_ReadIni) Test pas de valeur par defaut OK\n");
      }
      else
      {
         printf("(INI_ReadIni) Test pas de valeur par defaut KO\n");
         iResult = 1;
      }

      /* Test de l'absence de section */
      if(INI_ReadIni(NULL, "cle1", NULL, acRead, sizeof acRead, "inexistant.ini") == 0)
      {
         printf("(INI_ReadIni) Test absence section OK\n");
      }
      else
      {
         printf("(INI_ReadIni) Test absence section KO\n");
         iResult = 1;
      }

      /* Test de section vide */
      if(INI_ReadIni("", "cle1", NULL, acRead, sizeof acRead, "inexistant.ini") == 0)
      {
         printf("(INI_ReadIni) Test section vide OK\n");
      }
      else
      {
         printf("(INI_ReadIni) Test section vide KO\n");
         iResult = 1;
      }

      /* Test de l'absence de cle */
      if(INI_ReadIni("section1", NULL, NULL, acRead, sizeof acRead, "inexistant.ini") == 0)
      {
         printf("(INI_ReadIni) Test absence cle OK\n");
      }
      else
      {
         printf("(INI_ReadIni) Test absence cle KO\n");
         iResult = 1;
      }

      /* Test de cle vide */
      if(INI_ReadIni("section1", "", NULL, acRead, sizeof acRead, "inexistant.ini") == 0)
      {
         printf("(INI_ReadIni) Test cle vide OK\n");
      }
      else
      {
         printf("(INI_ReadIni) Test cle vide KO\n");
         iResult = 1;
      }

      /* Test d'absence de retour */
      if(INI_ReadIni("section1", "cle1", NULL, NULL, sizeof acRead, "inexistant.ini") == 0)
      {
         printf("(INI_ReadIni) Test absence de retour OK\n");
      }
      else
      {
         printf("(INI_ReadIni) Test absence de retour KO\n");
         iResult = 1;
      }

      /* Test taille nulle */
      if(INI_ReadIni("section1", "cle1", NULL, acRead, 0, "inexistant.ini") == 0)
      {
         printf("(INI_ReadIni) Test taille nulle OK\n");
      }
      else
      {
         printf("(INI_ReadIni) Test taille nulle KO\n");
         iResult = 1;
      }

      for(szIdx=0; szIdx<(sizeof(sIni)/sizeof(sIni[0])); szIdx++)
      {
         INI_ReadIni(sIni[szIdx].pcSection, sIni[szIdx].pcCle, acDefault, acRead, sizeof acRead, acFileName);
         if(strcmp(acRead, sIni[szIdx].pcValeur) == 0)
         {
            printf("(INI_ReadIni) Test %d OK\n", (int)(szIdx+1));
         }
         else
         {
            printf("(INI_ReadIni) Test %d KO\n", (int)(szIdx+1));
            iResult = 1;
         }
      }

      /* on remet tout en etat */
      remove(acFileName);
   }

   /* Test de la fonction INI_WriteIni */
   {
      const char        acIniTFile[]="[sectiOn1]\ncLe1=valeur1\n\n[section2]\ncle2=valeur2\n";
      int               iState=0;
      char*             pcSep;

      /* Creation du fichier de travail */
      fp=fopen(acFileName, "w");
      if(fp == NULL)
      {
         printf("(INI_WriteIni) Echec ouverture fichier pour ecriture");
         return 1;
      }
      fputs(acIniTFile, fp);
      fclose(fp);

      /* Test de l'absence de section */
      if(INI_WriteIni(NULL, "cle1", "valeur_test", acFileName) == INI_KO)
      {
         printf("(INI_WriteIni) Test absence section OK\n");
      }
      else
      {
         printf("(INI_WriteIni) Test absence section KO\n");
         iResult = 1;
      }

      /* Test de section vide */
      if(INI_WriteIni("", "cle1", "valeur_test", acFileName) == INI_KO)
      {
         printf("(INI_WriteIni) Test section vide OK\n");
      }
      else
      {
         printf("(INI_WriteIni) Test section vide KO\n");
         iResult = 1;
      }

      /* Test de l'absence de cle */
      if(INI_WriteIni("section1", NULL, "valeur_test", acFileName) == INI_KO)
      {
         printf("(INI_WriteIni) Test absence cle OK\n");
      }
      else
      {
         printf("(INI_WriteIni) Test absence cle KO\n");
         iResult = 1;
      }

      /* Test de cle vide */
      if(INI_WriteIni("section1", "", "valeur_test", acFileName) == INI_KO)
      {
         printf("(INI_WriteIni) Test cle vide OK\n");
      }
      else
      {
         printf("(INI_WriteIni) Test cle vide KO\n");
         iResult = 1;
      }

      /* Test de l'absence de valeur */
      if(INI_WriteIni("section1", "cle1", NULL, acFileName) == INI_KO)
      {
         printf("(INI_WriteIni) Test absence de valeur OK\n");
      }
      else
      {
         printf("(INI_WriteIni) Test absence de valeur KO\n");
         iResult = 1;
      }

      /* Test de cle vide */
      if(INI_WriteIni("section1", "cle1", "", acFileName) == INI_KO)
      {
         printf("(INI_WriteIni) Test valeur vide OK\n");
      }
      else
      {
         printf("(INI_WriteIni) Test valeur vide KO\n");
         iResult = 1;
      }

      INI_WriteIni("section1", "cle1", "valeur1_modif", acFileName);
      INI_WriteIni("section1", "cLe1bis", "vaLeur1bis", acFileName);
      INI_WriteIni("section3", "clE3", "valeur3", acFileName);

      fp=fopen(acFileName, "r");
      if(fp == NULL)
      {
         printf("(INI_WriteIni) Echec ouverture fichier pour lecture");
         return 1;
      }

      /* Analyse du fichier */
      while(fgets(acRead, sizeof acRead, fp) != NULL)
      {
         /* On ne tient pas compte des lignes vide */
         if(acRead[0] == '\n')
         {
            continue;
         }

         /* suppression du '\n' */
		   pcSep = strchr(acRead, '\n');
   		if(pcSep != NULL)
	   	{
		      pcSep[0] = '\0';
		   }

		   /* Verification des champs en foncion de l'etape */
		   switch(iState)
		   {
		      case 0:
		         if(strcmp(acRead, "[sectiOn1]") != 0)
		         {
		            iResult = 1;
		         }
		         break;

		      case 1:
		         if(strcmp(acRead, "cLe1=valeur1_modif") != 0)
		         {
		            iResult = 1;
		         }
		         break;

		      case 2:
		         if(strcmp(acRead, "cLe1bis=vaLeur1bis") != 0)
		         {
		            iResult = 1;
		         }
		         break;

		      case 3:
		         if(strcmp(acRead, "[section2]") != 0)
		         {
		            iResult = 1;
		         }
		         break;

		      case 4:
		         if(strcmp(acRead, "cle2=valeur2") != 0)
		         {
		            iResult = 1;
		         }
		         break;

		      case 5:
		         if(strcmp(acRead, "[section3]") != 0)
		         {
		            iResult = 1;
		         }
		         break;

		      case 6:
		         if(strcmp(acRead, "clE3=valeur3") != 0)
		         {
		            iResult = 1;
		         }
		         break;

            default:
               /* Si on arrive ici, il y a un probleme */
               iResult =1;
               break;
		   }

		   iState++;
      }
      fclose(fp);

      if(iResult == 0)
      {
         printf("(INI_WriteIni) Test OK\n");
      }
      else
      {
         printf("(INI_WriteIni) Test KO\n");
      }

      /* on remet tout en etat */
      remove(acFileName);
   }

   return iResult;
}
