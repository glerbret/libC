/**
 * @author Gregory Lerbret
 * @brief Gestion des chaines de caracteres
 * @date 06/04/2005
 * @version 1.0.0
 */

#include "str.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define xstr(s) str(s)
#define str(s) #s

#define STR_NAME	    "Gestion des chaines de caracteres"
#define STR_VERS_MAJ    1
#define STR_VERS_MIN    0
#define STR_VERS_BRCH   0
#define STR_ID		    STR_NAME " - Version " xstr(STR_VERS_MAJ) "." xstr(STR_VERS_MIN) "." xstr(STR_VERS_BRCH)

const char* STR_Identifier(void)
{
    return STR_ID;
}

int STR_Version(void)
{
    return STR_VERS_MAJ * 10000 + STR_VERS_MIN * 100 + STR_VERS_BRCH;
}

char* STR_DelChar(char* pcDst, const char* pcSrc, size_t szLgDst, char cChar2Delete)
{
    /* Verification des conditions initiales */
    if(pcDst == NULL || pcSrc == NULL || szLgDst == 0)
    {
        return NULL;
    }

    for(; *pcSrc != '\0' && szLgDst > 1; pcSrc++)
    {
        if(*pcSrc != cChar2Delete)
        {
            /* Le caractere courant doit etre conserve */
            *pcDst = *pcSrc;
            pcDst++;
            szLgDst--;
        }
    }

    /* Une chaine se termine par un 0 */
    *pcDst = '\0';
    return pcDst;
}

char* STR_Strip(char* pcDst, const char* pcSrc, size_t szLgDst)
{
    char* pcSavDst = pcDst;

    /* Verification des conditions initiales */
    if(pcDst == NULL || pcSrc == NULL || szLgDst == 0)
    {
        return NULL;
    }

    /* Recherche du premier caractere non blanc de la chaine */
    for(; isspace(*pcSrc) != 0 && *pcSrc != '\0'; pcSrc++)
    {
        /* NOP */
    }

    /* Suppression des espaces superlus en debut de chaine */
    for(; *pcSrc != '\0' && szLgDst > 1; pcSrc++, szLgDst--, pcDst++)
    {
        *pcDst = *pcSrc;
    }

    /* Suppression des espaces superlus en fin de chaine
       Si rien n'a ete copie dans la chaine resultante (chaine initiale ne
       contenant que des espaces ou longueur de la chaine resultante de 1),
       on ne fait rien */
    for(; pcSavDst != pcDst && isspace(*(pcDst - 1)) != 0; pcDst--)
    {
        /* NOP */
    }

    /* Une chaine se termine par un 0 */
    *pcDst = '\0';
    return pcSavDst;
}

char* STR_String2Lower(char* pcDst, const char* pcSrc, size_t szLgDst)
{
    /* Verication des conditions intiales */
    if(pcDst == NULL || pcSrc == NULL || szLgDst == 0)
    {
        return NULL;
    }

    /* Parcours iteratif de la chaine de caractere avec conversion en minuscule */
    for(; *pcSrc != '\0' && szLgDst > 1; szLgDst--, pcDst++, pcSrc++)
    {
        *pcDst = (char)tolower(*pcSrc);
    }

    /* Une chaine se termine par un 0 */
    *pcDst = '\0';
    return pcDst;
}

char* STR_String2Upper(char* pcDst, const char* pcSrc, size_t szLgDst)
{
    /* Verication des conditions intiales */
    if(pcDst == NULL || pcSrc == NULL || szLgDst == 0)
    {
        return NULL;
    }

    /* Parcours iteratif de la chaine de caractere avec conversion en majuscule */
    for(; *pcSrc != '\0' && szLgDst > 1; szLgDst--, pcDst++, pcSrc++)
    {
        *pcDst = (char)toupper(*pcSrc);
    }

    /* Une chaine se termine par un 0 */
    *pcDst = '\0';
    return pcDst;
}

char* STR_LeftPadding(char* pcDst, const char* pcSrc, size_t szLgDst, char cPaddingChar)
{
    size_t szLgSrc;

    /* Verification des conditions initiales */
    if(pcDst == NULL || pcSrc == NULL || szLgDst == 0)
    {
        return NULL;
    }

    szLgSrc = strlen(pcSrc);

    if(szLgSrc >= szLgDst)
    {
        /* La chaine intiale est trop longue, on tronque */
        memcpy(pcDst, pcSrc, szLgDst - 1);
    }
    else
    {
        /* On remplit le buffer avec le caractere de padding ... */
        memset(pcDst, cPaddingChar, szLgDst - 1);

        /* ... et on copie la chaine initiale a la bonne position */
        memcpy(pcDst + szLgDst - szLgSrc - 1, pcSrc, szLgSrc);
    }

    /* Une chaine se termine par un 0 */
    pcDst[szLgDst - 1] = '\0';
    return pcDst;
}

char* STR_RightPadding(char* pcDst, const char* pcSrc, size_t szLgDst, char cPaddingChar)
{
    size_t szLgSrc;

    /* Verification des conditions initiales */
    if(pcDst == NULL || pcSrc == NULL || szLgDst == 0)
    {
        return NULL;
    }

    szLgSrc = strlen(pcSrc);

    if(szLgSrc >= szLgDst)
    {
        /* La chaine intiale est trop longue, on tronque */
        memcpy(pcDst, pcSrc, szLgDst - 1);
    }
    else
    {
        /* On remplit le buffer avec le caractere de padding ... */
        memset(pcDst, cPaddingChar, szLgDst - 1);

        /* ... et on copie la chaine initiale a la bonne position */
        memcpy(pcDst, pcSrc, szLgSrc);
    }

    /* Une chaine se termine par un 0 */
    pcDst[szLgDst - 1] = '\0';
    return pcDst;
}

char* STR_Center(char* pcDst, const char* pcSrc, size_t szLgDst, char cPaddingChar)
{
    size_t szLgSrc;

    /* Verification des conditions initiales */
    if(pcDst == NULL || pcSrc == NULL || szLgDst == 0)
    {
        return NULL;
    }

    szLgSrc = strlen(pcSrc);

    if(szLgSrc >= szLgDst)
    {
        /* La chaine intiale est trop longue, on tronque */
        memcpy(pcDst, pcSrc, szLgDst - 1);
    }
    else
    {
        /* On remplit le buffer avec le caractere de padding ... */
        memset(pcDst, cPaddingChar, szLgDst - 1);

        /* ... et on copie la chaine initiale a la bonne position */
        memcpy(pcDst + ((szLgDst - 1 - szLgSrc) / 2), pcSrc, szLgSrc);
    }

    /* Une chaine se termine par un 0 */
    pcDst[szLgDst - 1] = '\0';
    return pcDst;
}

char* STR_StrDup(const char* pcSrc)
{
    char* pcDst = malloc(strlen(pcSrc) + 1);
    if(pcDst != NULL)
    {
        strcpy(pcDst, pcSrc);
    }

    return pcDst;
}
