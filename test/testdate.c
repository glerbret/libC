#include "date.h"
#include "test.h"

#include <stdio.h>
#include <string.h>

int TstDate(void)
{
    int iResult = 0;
    char acDate[10];
    char acEntered[5];

    printf("\nTest de \"%s\"\n", DATE_Identifier());

    /* test de la fonction DATE_GetTodayDate */
    if(DATE_GetTodayDate(acDate, sizeof acDate, "%Y%m%d") == DATE_OK)
    {
        printf("la date %s est elle bien celle du jour (format AAAAMMJJ) (o/n)? ", acDate);
        fflush(stdout);
        fgets(acEntered, sizeof acEntered, stdin);
        if(acEntered[0] == 'o' || acEntered[0] == 'O')
        {
            printf("(DATE_GetTodayDate) test 1 OK\n");
        }
        else
        {
            printf("(DATE_GetTodayDate) test 1 KO\n");
            iResult = 1;
        }
    }
    else
    {
        printf("(DATE_GetTodayDate) test 1 KO\n");
        iResult = 1;
    }

    if(DATE_GetTodayDate(acDate, sizeof acDate, "%d%m%Y") == DATE_OK)
    {
        printf("la date %s est elle bien celle du jour (format JJMMAAAA) (o/n)? ", acDate);
        fflush(stdout);
        fgets(acEntered, sizeof acEntered, stdin);
        if(acEntered[0] == 'o' || acEntered[0] == 'O')
        {
            printf("(DATE_GetTodayDate) test 2 OK\n");
        }
        else
        {
            printf("(DATE_GetTodayDate) test 2 KO\n");
            iResult = 1;
        }
    }
    else
    {
        printf("(DATE_GetTodayDate) test 2 KO\n");
        iResult = 1;
    }

    return iResult;
}
