/**
   \author Grégory Lerbret
   \file ini.c
   \brief Gestion des fichiers au format ini.<br>
   \date 06/04/2005
   \version 1.0.0
*/

#if defined(__BORLANDC__) || (defined(_MSC_VER) && _MSC_VER < 1400)
#include <windows.h>
#endif
#include <string.h>
#include <stdio.h>
#include "ini.h"
#include "str.h"
#include "bool.h"

#define xstr(s) str(s)
#define str(s) #s

#define INI_NAME	         "Gestion des fichiers au format .ini"
#define INI_VERS_MAJ       1
#define INI_VERS_MIN       0
#define INI_VERS_BRCH      0
#define INI_ID		         INI_NAME " - Version " xstr(INI_VERS_MAJ) "." xstr(INI_VERS_MIN) "." xstr(INI_VERS_BRCH)

/**
   \fn const char* INI_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char* INI_Identifier(void)
{
   return INI_ID;
}

/**
   \fn int INI_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int INI_Version(void)
{
   return INI_VERS_MAJ*10000 + INI_VERS_MIN*100 + INI_VERS_BRCH;
}

/**
   \fn unsigned int INI_ReadIni(const char* pcSectionName, const char* pcKeyName, const char* pcDefault, char* pcReturnedString, size_t szSize, const char* pcFileName)
   \brief Lecture d'un element dans un fichier .ini.
   \param[in] pcSectionName le nom de la section
   \param[in] pcKeyName le nom de la cle
   \param[in] pcDefault la valeur par defaut
   \param[out] pcReturnedString la valeur lue
   \param[in] szSize la taille maximale de la valeur
   \param[in] pcFileName le nom du fichier .ini
   \return le nombre de caracteres lus
*/
size_t INI_ReadIni(const char* pcSectionName, const char* pcKeyName, const char* pcDefault, char* pcReturnedString, size_t szSize, const char* pcFileName)
{
   /* Verification des conditions initiales */
   {
      if(pcReturnedString == NULL  || szSize == 0)
      {
         return 0;
      }

      if(pcSectionName == NULL || pcSectionName[0] == '\0' || pcKeyName == NULL || pcKeyName[0] == '\0')
      {
         pcReturnedString[0] = '\0';
         return 0;
      }
   }

   /* Lecture de la valeur */
   {
#if defined(__BORLANDC__) || (defined(_MSC_VER) && _MSC_VER < 1400)
      /* Si une fonction systeme permettant de lire les fichiers ini existe, on l'utilise */
      return (size_t)GetPrivateProfileString(pcSectionName, pcKeyName, pcDefault, pcReturnedString, (DWORD)szSize, pcFileName);
#else
      FILE*       fp                = NULL;
      int         iSectionFind      = 0;
      int         iKeyFind          = 0;
      char        acRead[BUFSIZ+1]  = "";
      char        acTmp1[BUFSIZ+1];
      char        acSection[50+1]   = "";
      char        acKey[50+1]       = "";
      char*       pcSep;

      /* La fonction est case-insensitive */
      STR_String2Lower(acSection, pcSectionName, sizeof acSection);
      STR_String2Lower(acKey, pcKeyName, sizeof acKey);

      fp = fopen( pcFileName, "r");
      if (fp==NULL)
      {
         if (pcDefault!=NULL)
         {
            strncpy(pcReturnedString, pcDefault, szSize-1);
            pcReturnedString[szSize-1] = '\0';
         }
         else
         {
            pcReturnedString[0] = '\0';
         }
      }
      else
      {
         fseek(fp,0L,SEEK_SET);

         /* recherche de la section */
         while (fgets(acRead, sizeof acRead - 1, fp) != NULL && iKeyFind == 0)
         {
            /* suppression du '\n' */
            pcSep = strchr(acRead, '\n');
            if(pcSep != NULL)
            {
               pcSep[0] = '\0';
            }

            /* La fonction est case-insensitive et les espaces ne sont pas significatifs */
            STR_Strip(acRead, acRead, sizeof acRead);
            STR_String2Lower(acRead, acRead, sizeof acRead);

            switch(acRead[0])
            {
               case '\n':     /* Ligne vide */
               case ';':      /* Commentaire */
               case '#':      /* Commentaire */
                  break;

               case '[':
                  if (strncmp(acSection, &acRead[1], strlen(acSection)) ==0 && acRead[strlen(acSection) + 1] == ']')
                  {
                     /* la section est trouve */
                     iSectionFind = 1;
                  }
                  else
                  {
                     /* on se trouve dans une autre section */
                     iSectionFind = 0;
                  }
                  break;

               default:
                  if(iSectionFind == 1)
                  {
                     /* separation de la chaine */
                     strcpy(acTmp1, &acRead[strcspn(acRead, "=") + 1]);
                     STR_Strip(acTmp1, acTmp1, sizeof acTmp1);
                     acRead[strcspn(acRead, "=")] = '\0';

                     /* Les espaces ne sont pas significatifs */
                     STR_Strip(acRead, acRead, sizeof acRead);

                     if (memcmp(acRead, acKey, strlen(acKey)) == 0)
                     {
                        strncpy(pcReturnedString, acTmp1, szSize-1);
                        pcReturnedString[szSize-1] = '\0';
                        iKeyFind = 1;
                     }
                  }
            }
         }

         /* la cle n'a pas ete trouve, on renvoie la valeur par defaut si elle existe */
         if (iKeyFind == 0 && pcDefault!=NULL)
         {
            strncpy(pcReturnedString, pcDefault, szSize-1);
            pcReturnedString[szSize-1] = '\0';
         }
         else if (iKeyFind == 0 && pcDefault==NULL)
         {
            pcReturnedString[0] = '\0';
         }

         fclose(fp);
      }
      return strlen(pcReturnedString);
#endif
   }
}

/**
   \fn INI_Res_e INI_WriteIni(const char* pcSectionName, const char* pcKeyName, const char* pcWriteString, const char* pcFileName)
   \brief Ecriture d'un element dans un fichier .ini.
   \param[in] pcSectionName le nom de la section
   \param[in] pcKeyName le nom de la cle
   \param[in] pcWriteString la valeur a inscrire
   \param[in] pcFileName le nom du fichier .ini
   \return  INI_OK si l'ecriture c'est bien deroulee.<br>
            INI_KO sinon.
*/
INI_Res_e INI_WriteIni(const char* pcSectionName, const char* pcKeyName, const char* pcWriteString, const char* pcFileName)
{
   /* Verification des conditions initiales */
   if(pcSectionName == NULL || pcSectionName[0] == '\0'  ||
      pcKeyName == NULL || pcKeyName[0] == '\0'          ||
      pcWriteString == NULL || pcWriteString[0] == '\0'  ||
      pcFileName ==NULL || pcFileName[0] == '\0')
   {
      return INI_KO;
   }

   /* Ecriture de la valeur */
   {
#if defined(__BORLANDC__) || (defined(_MSC_VER) && _MSC_VER < 1400)
      /* Si une fonction systeme permettant d'ecrire les fichiers ini existe, on l'utilise */
      if(WritePrivateProfileString(pcSectionName, pcKeyName, pcWriteString, pcFileName) == true)
      {
         return INI_OK;
      }
      else
      {
         return INI_KO;
      }
#else
      const char  acProvFileName[]="./INI_GL_Prov.ini";

      FILE*       fDest                = NULL;
      FILE*       fSource              = NULL;
      char        acSection[50+1]      = "";
      char        acKey[50+1]          = "";
      char        acRead[BUFSIZ+1]     = "";
      char        acTmp1[BUFSIZ+1]     = "";
      char        acTmp2[BUFSIZ+1]     = "";
      int         iSectionFind         = 0;
      bool        bExit                = false;
      INI_Res_e   eResult              = INI_OK;

      /* La fonction est case-insensitive */
      STR_String2Lower(acSection, pcSectionName, sizeof acSection);
      STR_String2Lower(acKey, pcKeyName, sizeof acKey);

      fDest=fopen(acProvFileName, "w");
      if(fDest ==  NULL)
      {
         eResult = INI_KO;
      }

      fSource=fopen(pcFileName, "r");
      if(fSource ==  NULL)
      {
         eResult = INI_KO;
      }

      if(eResult == INI_OK)
      {
         /* recherche de la section et ecriture avant la section dans le fichier temporaire */
         while(iSectionFind == 0 && fgets(acRead, sizeof acRead - 1, fSource) != NULL)
         {
            /* La fonction est case-insensitive et les espaces ne sont pas significatifs */
            STR_Strip(acTmp1, acRead, sizeof acTmp1);
            STR_String2Lower(acTmp1, acTmp1, sizeof acTmp1);

            if(acTmp1[0] == '[' && strncmp(acSection,&acTmp1[1],strlen(acSection)) ==0 && acTmp1[strlen(acSection)+1] == ']')
            {
               /* la section est trouve */
               iSectionFind = 1;
            }

            /* copie le buffer dans la destination */
            fputs(acRead, fDest);
         }

         /* si la section n'a pas ete trouve */
         if(iSectionFind == 0)
         {
            /* la section n'a pas ete trouvee et on se trouve donc en fin de fichier,
               on rajoute la nouvelle section ... */
            strcpy(acTmp1, "\n[");
            strcat(acTmp1, pcSectionName);
            strcat(acTmp1, "]\n");
            fputs(acTmp1, fDest);

            /* ... la cle et la valeur */
            strcpy(acTmp1, pcKeyName);
            strcat(acTmp1, "=");
            strcat(acTmp1, pcWriteString);
            strcat(acTmp1, "\n");
            fputs(acTmp1, fDest);
         }
         else
         {
            /* la section a ete trouve, on cherche la cle */
            while (bExit == false)
            {
               if (fgets(acRead, sizeof acRead - 1, fSource) == NULL)
               {
                  /* La cle n'a pas ete trouvee, on rajoute la nouvelle cle et la valeur */
                  strcpy(acTmp1, pcKeyName);
                  strcat(acTmp1, "=");
                  strcat(acTmp1, pcWriteString);
                  strcat(acTmp1, "\n");
                  fputs(acTmp1, fDest);
                  bExit = true;
               }
               else
               {
                  if(acRead[0] == '\n')
                  {
                     /* Il s'agit d'un saut de ligne, on n'inscrit rien afin de ne pas avoir de saut de ligne parasite */
                     /* NOP */
                  }
                  else if(acRead[0] == '[')
                  {
                     /* On rentrer dans une nouvelle section et la cle n'a pas ete trouvee dans, on rajoute la nouvelle cle et la valeur ... */
                     strcpy(acTmp1, pcKeyName);
                     strcat(acTmp1, "=");
                     strcat(acTmp1, pcWriteString);
                     strcat(acTmp1, "\n\n");
                     fputs(acTmp1, fDest);

                     /* ... et ce que l'on vient de lire */
                     fputs(acRead, fDest);
                     bExit = true;
                  }
                  else
                  {
                     /* On rcupere la cle courante */
                     strcpy(acTmp1, acRead);
                     acTmp1[strcspn(acTmp1,"=")]='\0';

                     /* La fonction est case-insensitive et les espaces ne sont pas significatifs */
                     STR_Strip(acTmp2, acTmp1, sizeof acTmp2);
                     STR_String2Lower(acTmp2, acTmp2, sizeof acTmp2);

                     if (memcmp(acTmp2, acKey, strlen(acKey))==0)
                     {
                        /* La cle est trouve, on ecrit la nouvelle valeur */
                        strcpy(acTmp2, acTmp1);
                        strcat(acTmp2, "=");
                        strcat(acTmp2, pcWriteString);
                        strcat(acTmp2, "\n");
                        fputs(acTmp2, fDest);
                        bExit = true;
                     }
                     else
                     {
                        /* Ce n'est pas la bonne cle, on ecrit ce qui vient d'etre lu */
                        fputs(acRead, fDest);
                     }
                  }
               }
            }

            /* on ecrit la fin du fichier */
            while(fgets(acRead, sizeof(acRead) - 1, fSource) != NULL)
            {
               fputs(acRead, fDest);
            }
         }
      }

      if(fDest != NULL)
      {
         fclose(fDest), fDest = NULL;
      }
      if(fSource != NULL)
      {
         fclose(fSource), fSource = NULL;
      }

      /* On recopie le fichier temporaire dans le .ini */
      if(eResult == INI_OK)
      {
         remove(pcFileName);
         if(rename(acProvFileName,pcFileName) != 0)
         {
            eResult = INI_KO;
         }
      }

      return eResult;
#endif
   }
}
