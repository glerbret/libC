#include "date.h"
#include "test.h"

#include <stdio.h>
#include <string.h>

int TstDate(void)
{
    int result = 0;
    char date[10];
    char entered[5];

    printf("\nTest de \"%s\"\n", DATE_Identifier());

    /* test de la fonction DATE_GetTodayDate */
    if(DATE_GetTodayDate(date, sizeof date, "%Y%m%d") == DATE_OK)
    {
        printf("la date %s est elle bien celle du jour (format AAAAMMJJ) (o/n)? ", date);
        fflush(stdout);
        fgets(entered, sizeof entered, stdin);
        if(entered[0] == 'o' || entered[0] == 'O')
        {
            printf("(DATE_GetTodayDate) test 1 OK\n");
        }
        else
        {
            printf("(DATE_GetTodayDate) test 1 KO\n");
            result = 1;
        }
    }
    else
    {
        printf("(DATE_GetTodayDate) test 1 KO\n");
        result = 1;
    }

    if(DATE_GetTodayDate(date, sizeof date, "%d%m%Y") == DATE_OK)
    {
        printf("la date %s est elle bien celle du jour (format JJMMAAAA) (o/n)? ", date);
        fflush(stdout);
        fgets(entered, sizeof entered, stdin);
        if(entered[0] == 'o' || entered[0] == 'O')
        {
            printf("(DATE_GetTodayDate) test 2 OK\n");
        }
        else
        {
            printf("(DATE_GetTodayDate) test 2 KO\n");
            result = 1;
        }
    }
    else
    {
        printf("(DATE_GetTodayDate) test 2 KO\n");
        result = 1;
    }

    return result;
}
