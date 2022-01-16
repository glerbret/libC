/**
 * @brief Gestion des fichiers au format ini.
 * @version 1.0.0.
 * @copyright MIT license.
 * @author Gregory Lerbret.
 */

#include "ini.h"
#include "str.h"
#include "bool.h"

#if defined(__BORLANDC__) || (defined(_MSC_VER) && _MSC_VER < 1400)
#include <windows.h>
#endif
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define xstr(s) str(s)
#define str(s) #s

#define INI_NAME	    "Gestion des fichiers au format .ini"
#define INI_VERS_MAJ  1
#define INI_VERS_MIN  0
#define INI_VERS_BRCH 0
#define INI_ID		    INI_NAME " - Version " xstr(INI_VERS_MAJ) "." xstr(INI_VERS_MIN) "." xstr(INI_VERS_BRCH)

const char* INI_Identifier(void)
{
  return INI_ID;
}

int INI_Version(void)
{
  return INI_VERS_MAJ * 10000 + INI_VERS_MIN * 100 + INI_VERS_BRCH;
}

size_t INI_ReadIni(const char* sectionName, const char* keyName, const char* defaultValue, char* readValue, size_t maxSize, const char* fileName)
{
  assert(readValue);
  assert(maxSize);
  assert(sectionName && sectionName[0]);
  assert(keyName && keyName[0]);

  /* Lecture de la valeur */
  {
#if defined(__BORLANDC__) || (defined(_MSC_VER) && _MSC_VER < 1400)
    /* Si une fonction systeme permettant de lire les fichiers ini existe, on l'utilise */
    return (size_t)GetPrivateProfileString(sectionName, keyName, defaultValue, readValue, (DWORD)maxSize, fileName);
#else
    FILE* fp = NULL;
    bool isSectionFound = false;
    bool isKeyFound = false;
    char readData[BUFSIZ + 1] = "";
    char tmp[BUFSIZ + 1];
    char section[50 + 1] = "";
    char key[50 + 1] = "";

    /* La fonction est case-insensitive */
    STR_String2Lower(section, sectionName, sizeof section);
    STR_String2Lower(key, keyName, sizeof key);

    fp = fopen(fileName, "r");
    if(fp)
    {
      fseek(fp, 0L, SEEK_SET);

      /* recherche de la section */
      while(fgets(readData, sizeof readData - 1, fp) != NULL && isKeyFound == false)
      {
        /* suppression du '\n' */
        char* sep = strchr(readData, '\n');
        if(sep != NULL)
        {
          sep[0] = '\0';
        }

        /* La fonction est case-insensitive et les espaces ne sont pas significatifs */
        STR_Strip(readData, readData, sizeof readData);
        STR_String2Lower(readData, readData, sizeof readData);

        switch(readData[0])
        {
        case '\n':     /* Ligne vide */
        case ';':      /* Commentaire */
        case '#':      /* Commentaire */
          break;

        case '[':
          if(strncmp(section, &readData[1], strlen(section)) == 0 && readData[strlen(section) + 1] == ']')
          {
            /* la section est trouve */
            isSectionFound = true;
          }
          else
          {
            /* on se trouve dans une autre section */
            isSectionFound = false;
          }
          break;

        default:
          if(isSectionFound)
          {
            /* separation de la chaine */
            strcpy(tmp, &readData[strcspn(readData, "=") + 1]);
            STR_Strip(tmp, tmp, sizeof tmp);
            readData[strcspn(readData, "=")] = '\0';

            /* Les espaces ne sont pas significatifs */
            STR_Strip(readData, readData, sizeof readData);

            if(memcmp(readData, key, strlen(key)) == 0)
            {
              strncpy(readValue, tmp, maxSize - 1);
              readValue[maxSize - 1] = '\0';
              isKeyFound = true;
            }
          }
        }
      }

      /* la cle n'a pas ete trouve, on renvoie la valeur par defaut si elle existe */
      if(isKeyFound == false && defaultValue != NULL)
      {
        strncpy(readValue, defaultValue, maxSize - 1);
        readValue[maxSize - 1] = '\0';
      }
      else if(isKeyFound == false && defaultValue == NULL)
      {
        readValue[0] = '\0';
      }

      fclose(fp);
    }
    else
    {
      if(defaultValue)
      {
        strncpy(readValue, defaultValue, maxSize - 1);
        readValue[maxSize - 1] = '\0';
      }
      else
      {
        readValue[0] = '\0';
      }
    }

    return strlen(readValue);
#endif
  }
}

bool INI_WriteIni(const char* sectionName, const char* keyName, const char* valueToWrite, const char* fileName)
{
  assert(sectionName && sectionName[0]);
  assert(keyName && keyName[0]);
  assert(valueToWrite && valueToWrite[0]);
  assert(fileName && fileName[0]);

  /* Ecriture de la valeur */
  {
#if defined(__BORLANDC__) || (defined(_MSC_VER) && _MSC_VER < 1400)
    /* Si une fonction systeme permettant d'ecrire les fichiers ini existe, on l'utilise */
    return WritePrivateProfileString(sectionName, keyName, valueToWrite, fileName);
#else
    const char  provFileName[] = "./INI_GL_Prov.ini";

    FILE* dst = NULL;
    FILE* src = NULL;
    char section[50 + 1] = "";
    char key[50 + 1] = "";
    char readData[BUFSIZ + 1] = "";
    char tmp1[BUFSIZ + 1] = "";
    char tmp2[BUFSIZ + 1] = "";
    bool isSectionFound = false;
    bool exit = false;

    /* La fonction est case-insensitive */
    STR_String2Lower(section, sectionName, sizeof section);
    STR_String2Lower(key, keyName, sizeof key);

    dst = fopen(provFileName, "w");
    if(dst ==  NULL)
    {
      goto err;
    }

    src = fopen(fileName, "r");
    if(src ==  NULL)
    {
      goto err;
    }

    /* recherche de la section et ecriture avant la section dans le fichier temporaire */
    while(isSectionFound == false && fgets(readData, sizeof readData - 1, src))
    {
      /* La fonction est case-insensitive et les espaces ne sont pas significatifs */
      STR_Strip(tmp1, readData, sizeof tmp1);
      STR_String2Lower(tmp1, tmp1, sizeof tmp1);

      if(tmp1[0] == '[' && strncmp(section, &tmp1[1], strlen(section)) == 0 && tmp1[strlen(section) + 1] == ']')
      {
        /* la section est trouve */
        isSectionFound = true;
      }

      /* copie le buffer dans la destination */
      fputs(readData, dst);
    }

    /* si la section n'a pas ete trouve */
    if(!isSectionFound)
    {
      /* la section n'a pas ete trouvee et on se trouve donc en fin de fichier,
         on rajoute la nouvelle section ... */
      strcpy(tmp1, "\n[");
      strcat(tmp1, sectionName);
      strcat(tmp1, "]\n");
      fputs(tmp1, dst);

      /* ... la cle et la valeur */
      strcpy(tmp1, keyName);
      strcat(tmp1, "=");
      strcat(tmp1, valueToWrite);
      strcat(tmp1, "\n");
      fputs(tmp1, dst);
    }
    else
    {
      /* la section a ete trouve, on cherche la cle */
      while (exit == false)
      {
        if (fgets(readData, sizeof readData - 1, src) == NULL)
        {
          /* La cle n'a pas ete trouvee, on rajoute la nouvelle cle et la valeur */
          strcpy(tmp1, keyName);
          strcat(tmp1, "=");
          strcat(tmp1, valueToWrite);
          strcat(tmp1, "\n");
          fputs(tmp1, dst);
          exit = true;
        }
        else
        {
          if(readData[0] == '\n')
          {
            /* Il s'agit d'un saut de ligne, on n'inscrit rien afin de ne pas avoir de saut de ligne parasite */
            /* NOP */
          }
          else if(readData[0] == '[')
          {
            /* On rentrer dans une nouvelle section et la cle n'a pas ete trouvee dans, on rajoute la nouvelle cle et la valeur ... */
            strcpy(tmp1, keyName);
            strcat(tmp1, "=");
            strcat(tmp1, valueToWrite);
            strcat(tmp1, "\n\n");
            fputs(tmp1, dst);

            /* ... et ce que l'on vient de lire */
            fputs(readData, dst);
            exit = true;
          }
          else
          {
            /* On recupere la cle courante */
            strcpy(tmp1, readData);
            tmp1[strcspn(tmp1, "=")] = '\0';

            /* La fonction est case-insensitive et les espaces ne sont pas significatifs */
            STR_Strip(tmp2, tmp1, sizeof tmp2);
            STR_String2Lower(tmp2, tmp2, sizeof tmp2);

            if(memcmp(tmp2, key, strlen(key)) == 0)
            {
              /* La cle est trouve, on ecrit la nouvelle valeur */
              strcpy(tmp2, tmp1);
              strcat(tmp2, "=");
              strcat(tmp2, valueToWrite);
              strcat(tmp2, "\n");
              fputs(tmp2, dst);
              exit = true;
            }
            else
            {
              /* Ce n'est pas la bonne cle, on ecrit ce qui vient d'etre lu */
              fputs(readData, dst);
            }
          }
        }
      }

      /* on ecrit la fin du fichier */
      while(fgets(readData, sizeof(readData) - 1, src) != NULL)
      {
        fputs(readData, dst);
      }
    }

    if(dst)
    {
      fclose(dst), dst = NULL;
    }
    if(src)
    {
      fclose(src), src = NULL;
    }

    /* On recopie le fichier temporaire dans le .ini */
    remove(fileName);
    return rename(provFileName, fileName) == 0;

err:
  if(dst)
    {
      fclose(dst), dst = NULL;
    }
    if(src)
    {
      fclose(src), src = NULL;
    }
    return false;
#endif
  }
}
