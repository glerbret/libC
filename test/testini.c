#include "ini.h"
#include "test.h"

#include <stdio.h>
#include <string.h>

typedef struct
{
    const char* section;
    const char* cle;
    const char* valeur;
} ini_s;

int TstIni(void)
{
    size_t idx;
    int result = 0;
    char readData[50];
    const char fileName[] = "./testini.ini";
    FILE* fp;

    printf("\nTest de \"%s\"\n", INI_Identifier());

    /* Test de la fonction INI_ReadIni */
    {
        const char defaultValue[] = "non";
        const char initFile[] = "[seCtion1]\nclE1=valeur1\ncLE2=valeur2\n";
        ini_s ini[] =
        {
            {"section1", "cle1", "valeur1"},
            {"section1", "cle3", "non"},
            {"section2", "cle1", "non"}
        };

        /* Creation du fichier de travail */
        fp = fopen(fileName, "w");
        if(fp == NULL)
        {
            printf("(INI_ReadIni) Echec ouverture fichier pour ecriture");
            return 1;
        }
        fputs(initFile, fp);
        fclose(fp);

        /* Test de l'absence de fichier */
        INI_ReadIni("section1", "cle1", defaultValue, readData, sizeof readData, "inexistant.ini");
        if(strcmp(readData, defaultValue) == 0)
        {
            printf("(INI_ReadIni) Test fichier absent OK\n");
        }
        else
        {
            printf("(INI_ReadIni) Test fichier absent KO\n");
            result = 1;
        }

        /* Test de l'absence de valeur par defaut */
        if(INI_ReadIni("section1", "cle1", NULL, readData, sizeof readData, "inexistant.ini") == 0)
        {
            printf("(INI_ReadIni) Test pas de valeur par defaut OK\n");
        }
        else
        {
            printf("(INI_ReadIni) Test pas de valeur par defaut KO\n");
            result = 1;
        }

        /* Test de l'absence de section */
        if(INI_ReadIni(NULL, "cle1", NULL, readData, sizeof readData, "inexistant.ini") == 0)
        {
            printf("(INI_ReadIni) Test absence section OK\n");
        }
        else
        {
            printf("(INI_ReadIni) Test absence section KO\n");
            result = 1;
        }

        /* Test de section vide */
        if(INI_ReadIni("", "cle1", NULL, readData, sizeof readData, "inexistant.ini") == 0)
        {
            printf("(INI_ReadIni) Test section vide OK\n");
        }
        else
        {
            printf("(INI_ReadIni) Test section vide KO\n");
            result = 1;
        }

        /* Test de l'absence de cle */
        if(INI_ReadIni("section1", NULL, NULL, readData, sizeof readData, "inexistant.ini") == 0)
        {
            printf("(INI_ReadIni) Test absence cle OK\n");
        }
        else
        {
            printf("(INI_ReadIni) Test absence cle KO\n");
            result = 1;
        }

        /* Test de cle vide */
        if(INI_ReadIni("section1", "", NULL, readData, sizeof readData, "inexistant.ini") == 0)
        {
            printf("(INI_ReadIni) Test cle vide OK\n");
        }
        else
        {
            printf("(INI_ReadIni) Test cle vide KO\n");
            result = 1;
        }

        /* Test d'absence de retour */
        if(INI_ReadIni("section1", "cle1", NULL, NULL, sizeof readData, "inexistant.ini") == 0)
        {
            printf("(INI_ReadIni) Test absence de retour OK\n");
        }
        else
        {
            printf("(INI_ReadIni) Test absence de retour KO\n");
            result = 1;
        }

        /* Test taille nulle */
        if(INI_ReadIni("section1", "cle1", NULL, readData, 0, "inexistant.ini") == 0)
        {
            printf("(INI_ReadIni) Test taille nulle OK\n");
        }
        else
        {
            printf("(INI_ReadIni) Test taille nulle KO\n");
            result = 1;
        }

        for(idx = 0; idx < (sizeof(ini) / sizeof(ini[0])); idx++)
        {
            INI_ReadIni(ini[idx].section, ini[idx].cle, defaultValue, readData, sizeof readData, fileName);
            if(strcmp(readData, ini[idx].valeur) == 0)
            {
                printf("(INI_ReadIni) Test %d OK\n", (int)(idx + 1));
            }
            else
            {
                printf("(INI_ReadIni) Test %d KO\n", (int)(idx + 1));
                result = 1;
            }
        }

        /* on remet tout en etat */
        remove(fileName);
    }

    /* Test de la fonction INI_WriteIni */
    {
        const char initFile[] = "[sectiOn1]\ncLe1=valeur1\n\n[section2]\ncle2=valeur2\n";
        int iState = 0;
        char* pcSep;

        /* Creation du fichier de travail */
        fp = fopen(fileName, "w");
        if(fp == NULL)
        {
            printf("(INI_WriteIni) Echec ouverture fichier pour ecriture");
            return 1;
        }
        fputs(initFile, fp);
        fclose(fp);

        /* Test de l'absence de section */
        if(INI_WriteIni(NULL, "cle1", "valeur_test", fileName) == INI_KO)
        {
            printf("(INI_WriteIni) Test absence section OK\n");
        }
        else
        {
            printf("(INI_WriteIni) Test absence section KO\n");
            result = 1;
        }

        /* Test de section vide */
        if(INI_WriteIni("", "cle1", "valeur_test", fileName) == INI_KO)
        {
            printf("(INI_WriteIni) Test section vide OK\n");
        }
        else
        {
            printf("(INI_WriteIni) Test section vide KO\n");
            result = 1;
        }

        /* Test de l'absence de cle */
        if(INI_WriteIni("section1", NULL, "valeur_test", fileName) == INI_KO)
        {
            printf("(INI_WriteIni) Test absence cle OK\n");
        }
        else
        {
            printf("(INI_WriteIni) Test absence cle KO\n");
            result = 1;
        }

        /* Test de cle vide */
        if(INI_WriteIni("section1", "", "valeur_test", fileName) == INI_KO)
        {
            printf("(INI_WriteIni) Test cle vide OK\n");
        }
        else
        {
            printf("(INI_WriteIni) Test cle vide KO\n");
            result = 1;
        }

        /* Test de l'absence de valeur */
        if(INI_WriteIni("section1", "cle1", NULL, fileName) == INI_KO)
        {
            printf("(INI_WriteIni) Test absence de valeur OK\n");
        }
        else
        {
            printf("(INI_WriteIni) Test absence de valeur KO\n");
            result = 1;
        }

        /* Test de cle vide */
        if(INI_WriteIni("section1", "cle1", "", fileName) == INI_KO)
        {
            printf("(INI_WriteIni) Test valeur vide OK\n");
        }
        else
        {
            printf("(INI_WriteIni) Test valeur vide KO\n");
            result = 1;
        }

        INI_WriteIni("section1", "cle1", "valeur1_modif", fileName);
        INI_WriteIni("section1", "cLe1bis", "vaLeur1bis", fileName);
        INI_WriteIni("section3", "clE3", "valeur3", fileName);

        fp = fopen(fileName, "r");
        if(fp == NULL)
        {
            printf("(INI_WriteIni) Echec ouverture fichier pour lecture");
            return 1;
        }

        /* Analyse du fichier */
        while(fgets(readData, sizeof readData, fp) != NULL)
        {
            /* On ne tient pas compte des lignes vide */
            if(readData[0] == '\n')
            {
                continue;
            }

            /* suppression du '\n' */
            pcSep = strchr(readData, '\n');
            if(pcSep != NULL)
            {
                pcSep[0] = '\0';
            }

            /* Verification des champs en foncion de l'etape */
            switch(iState)
            {
            case 0:
                if(strcmp(readData, "[sectiOn1]") != 0)
                {
                    result = 1;
                }
                break;

            case 1:
                if(strcmp(readData, "cLe1=valeur1_modif") != 0)
                {
                    result = 1;
                }
                break;

            case 2:
                if(strcmp(readData, "cLe1bis=vaLeur1bis") != 0)
                {
                    result = 1;
                }
                break;

            case 3:
                if(strcmp(readData, "[section2]") != 0)
                {
                    result = 1;
                }
                break;

            case 4:
                if(strcmp(readData, "cle2=valeur2") != 0)
                {
                    result = 1;
                }
                break;

            case 5:
                if(strcmp(readData, "[section3]") != 0)
                {
                    result = 1;
                }
                break;

            case 6:
                if(strcmp(readData, "clE3=valeur3") != 0)
                {
                    result = 1;
                }
                break;

            default:
                /* Si on arrive ici, il y a un probleme */
                result = 1;
                break;
            }

            iState++;
        }
        fclose(fp);

        if(result == 0)
        {
            printf("(INI_WriteIni) Test OK\n");
        }
        else
        {
            printf("(INI_WriteIni) Test KO\n");
        }

        /* on remet tout en etat */
        remove(fileName);
    }

    return result;
}
