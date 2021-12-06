/**
 * @author Gregory Lerbret
 * @brief Gestion des fichiers au format ini
 * @version 1.0.0
 * @copyright MIT license
 */

#include "ini.h"
#include "str.h"
#include "bool.h"

#if defined(__BORLANDC__) || (defined(_MSC_VER) && _MSC_VER < 1400)
#include <windows.h>
#endif
#include <string.h>
#include <stdio.h>

#define xstr(s) str(s)
#define str(s) #s

#define INI_NAME	    "Gestion des fichiers au format .ini"
#define INI_VERS_MAJ    1
#define INI_VERS_MIN    0
#define INI_VERS_BRCH   0
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
    /* Verification des conditions initiales */
    {
        if(readValue == NULL  || maxSize == 0)
        {
            return 0;
        }

        if(sectionName == NULL || sectionName[0] == '\0' || keyName == NULL || keyName[0] == '\0')
        {
            readValue[0] = '\0';
            return 0;
        }
    }

    /* Lecture de la valeur */
    {
#if defined(__BORLANDC__) || (defined(_MSC_VER) && _MSC_VER < 1400)
        /* Si une fonction systeme permettant de lire les fichiers ini existe, on l'utilise */
        return (size_t)GetPrivateProfileString(sectionName, keyName, defaultValue, readValue, (DWORD)maxSize, fileName);
#else
        FILE* fp = NULL;
        int isSectionFound = 0;
        int isKeyFound = 0;
        char readData[BUFSIZ + 1] = "";
        char tmp[BUFSIZ + 1];
        char section[50 + 1] = "";
        char key[50 + 1] = "";
        char* sep;

        /* La fonction est case-insensitive */
        STR_String2Lower(section, sectionName, sizeof section);
        STR_String2Lower(key, keyName, sizeof key);

        fp = fopen(fileName, "r");
        if (fp == NULL)
        {
            if (defaultValue != NULL)
            {
                strncpy(readValue, defaultValue, maxSize - 1);
                readValue[maxSize - 1] = '\0';
            }
            else
            {
                readValue[0] = '\0';
            }
        }
        else
        {
            fseek(fp, 0L, SEEK_SET);

            /* recherche de la section */
            while (fgets(readData, sizeof readData - 1, fp) != NULL && isKeyFound == 0)
            {
                /* suppression du '\n' */
                sep = strchr(readData, '\n');
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
                    if (strncmp(section, &readData[1], strlen(section)) == 0 && readData[strlen(section) + 1] == ']')
                    {
                        /* la section est trouve */
                        isSectionFound = 1;
                    }
                    else
                    {
                        /* on se trouve dans une autre section */
                        isSectionFound = 0;
                    }
                    break;

                default:
                    if(isSectionFound == 1)
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
                            isKeyFound = 1;
                        }
                    }
                }
            }

            /* la cle n'a pas ete trouve, on renvoie la valeur par defaut si elle existe */
            if (isKeyFound == 0 && defaultValue != NULL)
            {
                strncpy(readValue, defaultValue, maxSize - 1);
                readValue[maxSize - 1] = '\0';
            }
            else if (isKeyFound == 0 && defaultValue == NULL)
            {
                readValue[0] = '\0';
            }

            fclose(fp);
        }
        return strlen(readValue);
#endif
    }
}

INI_Res_e INI_WriteIni(const char* sectionName, const char* keyName, const char* valueToWrite, const char* fileName)
{
    /* Verification des conditions initiales */
    if(sectionName == NULL || sectionName[0] == '\0'  ||
       keyName == NULL || keyName[0] == '\0'          ||
       valueToWrite == NULL || valueToWrite[0] == '\0'  ||
       fileName == NULL || fileName[0] == '\0')
    {
        return INI_KO;
    }

    /* Ecriture de la valeur */
    {
#if defined(__BORLANDC__) || (defined(_MSC_VER) && _MSC_VER < 1400)
        /* Si une fonction systeme permettant d'ecrire les fichiers ini existe, on l'utilise */
        if(WritePrivateProfileString(sectionName, keyName, valueToWrite, fileName) == true)
        {
            return INI_OK;
        }
        else
        {
            return INI_KO;
        }
#else
        const char  acProvFileName[] = "./INI_GL_Prov.ini";

        FILE* dst = NULL;
        FILE* src = NULL;
        char section[50 + 1] = "";
        char key[50 + 1] = "";
        char readData[BUFSIZ + 1] = "";
        char tmp1[BUFSIZ + 1] = "";
        char tmp2[BUFSIZ + 1] = "";
        int isSectionFound = 0;
        bool exit = false;
        INI_Res_e result = INI_OK;

        /* La fonction est case-insensitive */
        STR_String2Lower(section, sectionName, sizeof section);
        STR_String2Lower(key, keyName, sizeof key);

        dst = fopen(acProvFileName, "w");
        if(dst ==  NULL)
        {
            result = INI_KO;
        }

        src = fopen(fileName, "r");
        if(src ==  NULL)
        {
            result = INI_KO;
        }

        if(result == INI_OK)
        {
            /* recherche de la section et ecriture avant la section dans le fichier temporaire */
            while(isSectionFound == 0 && fgets(readData, sizeof readData - 1, src) != NULL)
            {
                /* La fonction est case-insensitive et les espaces ne sont pas significatifs */
                STR_Strip(tmp1, readData, sizeof tmp1);
                STR_String2Lower(tmp1, tmp1, sizeof tmp1);

                if(tmp1[0] == '[' && strncmp(section, &tmp1[1], strlen(section)) == 0 && tmp1[strlen(section) + 1] == ']')
                {
                    /* la section est trouve */
                    isSectionFound = 1;
                }

                /* copie le buffer dans la destination */
                fputs(readData, dst);
            }

            /* si la section n'a pas ete trouve */
            if(isSectionFound == 0)
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
                            /* On rcupere la cle courante */
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
        }

        if(dst != NULL)
        {
            fclose(dst), dst = NULL;
        }
        if(src != NULL)
        {
            fclose(src), src = NULL;
        }

        /* On recopie le fichier temporaire dans le .ini */
        if(result == INI_OK)
        {
            remove(fileName);
            if(rename(acProvFileName, fileName) != 0)
            {
                result = INI_KO;
            }
        }

        return result;
#endif
    }
}
