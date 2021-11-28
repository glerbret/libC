#include "bool.h"
#include "queue.h"
#include "test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char*   pcString;
    size_t  szSize;
} DupString_s;

int TstQueue(void)
{
    int iResult = 0;
    size_t szNbInser = 0;
    size_t szIdx;
    queue_s* pQueue1;
    queue_s* pQueue2;
    queue_s* pCloneQueue1;
    queue_s* pCloneQueue2;
    QUEUE_Error_e eError;
    const char* pcData;

    /* Creation des donnees a inserer */
    const char* apcString[] =
    {
        "chaine1",
        "chaine2"
    };

    printf("\nTest de \"%s\"\n", QUEUE_Identifier());

    /* Test de la fonction QUEUE_Init() */
    {
        pQueue1 = QUEUE_Create(&eError);
        if(pQueue1 == NULL || eError != QUEUE_NO_ERROR)
        {
            printf("(QUEUE_Create) Test creation d'une file KO\n");
            return 1;
        }
        else
        {
            printf("(QUEUE_Create) Test creation d'une file OK\n");
        }

        pQueue2 = QUEUE_Create(&eError);
        if(pQueue2 == NULL || eError != QUEUE_NO_ERROR)
        {
            printf("(QUEUE_Create) Test creation d'une file KO\n");
            return 1;
        }
    }

    /* Test de la fonction QUEUE_IsEmpty() sur une file vide */
    {
        if(QUEUE_IsEmpty(pQueue1) == false)
        {
            printf("(QUEUE_IsEmpty) Test sur une file vide KO\n");
            iResult = 1;
        }
        else
        {
            printf("(QUEUE_IsEmpty) Test sur une file vide OK\n");
        }
    }

    /* Test de la fonction QUEUE_Size() sur une file vide */
    {
        if(QUEUE_Size(pQueue1) != 0)
        {
            printf("(QUEUE_Size) Test sur une file vide KO\n");
            iResult = 1;
        }
        else
        {
            printf("(QUEUE_Size) Test sur une file vide OK\n");
        }
    }

    /* Test de la fonction QUEUE_Enqueue() */
    {
        for(szIdx = 0; szIdx < sizeof(apcString) / sizeof(apcString[0]); szIdx++)
        {
            if(QUEUE_Enqueue(pQueue1, apcString[szIdx], strlen(apcString[szIdx]) + 1) == QUEUE_NO_ERROR)
            {
                printf("(QUEUE_Enqueue) Test d'insertion %lu OK\n", (unsigned long)szIdx);
                szNbInser++;
            }
            else
            {
                printf("(QUEUE_Enqueue) Test d'insertion %lu KO\n", (unsigned long)szIdx);
                iResult = 1;
            }
        }
    }

    /* Test de la fonction QUEUE_IsEmpty() sur une file non vide */
    {
        if(QUEUE_IsEmpty(pQueue1) != false)
        {
            printf("(QUEUE_IsEmpty) Test sur une file non vide KO\n");
            iResult = 1;
        }
        else
        {
            printf("(QUEUE_IsEmpty) Test sur une file non vide OK\n");
        }
    }

    /* Test de la fonction QUEUE_Size() sur une file non vide */
    {
        if(QUEUE_Size(pQueue1) != szNbInser)
        {
            printf("(QUEUE_Size) Test sur une file non vide KO\n");
            iResult = 1;
        }
        else
        {
            printf("(QUEUE_Size) Test sur une file non vide OK\n");
        }
    }

    /* Test de la fonction QUEUE_Clone() */
    {
        pCloneQueue1 = QUEUE_Clone(pQueue1, &eError);
        if(pCloneQueue1 == NULL || eError != QUEUE_NO_ERROR)
        {
            printf("(QUEUE_Clone) Test duplication d'une file KO\n");
            pCloneQueue1 = NULL;
            iResult = 1;
        }
        else
        {
            /* On verifie que tout semble bien se passer */
            if(QUEUE_IsEmpty(pCloneQueue1) == false && QUEUE_Size(pCloneQueue1) == szNbInser)
            {
                printf("(QUEUE_Clone) Test duplication d'une file OK\n");
            }
            else
            {
                printf("(QUEUE_Clone) Test duplication d'une file KO\n");
                iResult = 1;
            }
        }

        pCloneQueue2 = QUEUE_Clone(pQueue2, &eError);
        if(pCloneQueue2 == NULL || eError != QUEUE_NO_ERROR)
        {
            printf("(QUEUE_Clone) Test duplication d'une file vide KO\n");
            pCloneQueue2 = NULL;
            iResult = 1;
        }
        else
        {
            /* On verifie que tout semble bien se passer */
            if(QUEUE_IsEmpty(pCloneQueue2) == true && QUEUE_Size(pCloneQueue2) == 0)
            {
                printf("(QUEUE_Clone) Test duplication d'une file vide OK\n");
            }
            else
            {
                printf("(QUEUE_Clone) Test duplication d'une file vide KO\n");
                iResult = 1;
            }
        }
    }

    /* Test de la fonction QUEUE_Peek() */
    {
        pcData = QUEUE_Peek(pCloneQueue1, &eError);
        if(pcData == NULL || eError != QUEUE_NO_ERROR)
        {
            printf("(QUEUE_Peek) Test lecture d'une file KO\n");
            iResult = 1;
        }
        else
        {
            if(strcmp(pcData, "chaine1") == 0)
            {
                printf("(QUEUE_Peek) Test lecture d'une file OK\n");
            }
            else
            {
                printf("(QUEUE_Peek) Test lecture d'une file KO\n");
                iResult = 1;
            }
        }

        pcData = QUEUE_Peek(pQueue2, &eError);
        if(pcData == NULL &&  eError == QUEUE_EMPTY_QUEUE)
        {
            printf("(QUEUE_Peek) Test lecture d'une file vide OK\n");
        }
        else
        {
            printf("(QUEUE_Peek) Test lecture d'une file vide KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction QUEUE_Dequeue() */
    {
        pcData = QUEUE_Dequeue(pCloneQueue1, &eError);
        if(pcData == NULL || eError != QUEUE_NO_ERROR)
        {
            printf("(QUEUE_Dequeue) Test depilement d'une file KO\n");
            iResult = 1;
        }
        else
        {
            szNbInser--;
            if(strcmp(pcData, "chaine1") == 0 && QUEUE_Size(pCloneQueue1) == szNbInser)
            {
                printf("(QUEUE_Dequeue) Test depilement d'une file OK\n");
                free((void*)pcData), pcData = NULL;
            }
            else
            {
                printf("(QUEUE_Dequeue) Test depilement d'une file KO\n");
                iResult = 1;
            }
        }

        pcData = QUEUE_Dequeue(pQueue2, &eError);
        if(pcData == NULL &&  eError == QUEUE_EMPTY_QUEUE)
        {
            printf("(QUEUE_Dequeue) Test depilement d'une file vide OK\n");
        }
        else
        {
            printf("(QUEUE_Dequeue) Test depilement d'une file vide KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction QUEUE_Remove() */
    {
        eError = QUEUE_Remove(pCloneQueue1);
        if(eError != QUEUE_NO_ERROR)
        {
            printf("(QUEUE_Remove) Test suppression d'un element d'une file KO\n");
            iResult = 1;
        }
        else
        {
            szNbInser--;
            if(QUEUE_Size(pCloneQueue1) == szNbInser)
            {
                printf("(QUEUE_Remove) Test suppression d'un element d'une file OK\n");
            }
            else
            {
                printf("(QUEUE_Remove) Test suppression d'un element d'une file KO\n");
                iResult = 1;
            }
        }

        eError = QUEUE_Remove(pQueue2);
        if(eError == QUEUE_EMPTY_QUEUE)
        {
            printf("(QUEUE_Remove) Test suppression d'une file vide OK\n");
        }
        else
        {
            printf("(QUEUE_Remove) Test suppression d'une file vide KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction QUEUE_Destroy() */
    {
        QUEUE_Destroy(pQueue1);
        QUEUE_Destroy(pQueue2);
        QUEUE_Destroy(pCloneQueue1);
        QUEUE_Destroy(pCloneQueue2);

        printf("(QUEUE_Destroy) Test de destructon d'une file OK\n");
    }

    return iResult;
}
