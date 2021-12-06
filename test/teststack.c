#include "stack.h"
#include "bool.h"
#include "test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int TstStack(void)
{
    int result = 0;
    size_t nbInser = 0;
    size_t idx;
    stack_s* stack1;
    stack_s* stack2;
    stack_s* cloneStack1;
    stack_s* cloneStack2;
    STACK_Error_e error;
    const char* data;

    /* Creation des donnees a inserer */
    const char* strings[] =
    {
        "chaine1",
        "chaine2"
    };

    printf("\nTest de \"%s\"\n", STACK_Identifier());

    /* Test de la fonction STACK_Init() */
    {
        stack1 = STACK_Create(&error);
        if(stack1 == NULL || error != STACK_NO_ERROR)
        {
            printf("(STACK_Create) Test creation d'une pile KO\n");
            return 1;
        }
        else
        {
            printf("(STACK_Create) Test creation d'une pile OK\n");
        }

        stack2 = STACK_Create(&error);
        if(stack2 == NULL || error != STACK_NO_ERROR)
        {
            printf("(STACK_Create) Test creation d'une pile KO\n");
            return 1;
        }
    }

    /* Test de la fonction STACK_IsEmpty() sur une pile vide */
    {
        if(STACK_IsEmpty(stack1) == false)
        {
            printf("(STACK_IsEmpty) Test sur une pile vide KO\n");
            result = 1;
        }
        else
        {
            printf("(STACK_IsEmpty) Test sur une pile vide OK\n");
        }
    }

    /* Test de la fonction STACK_Size() sur une pile vide */
    {
        if(STACK_Size(stack1) != 0)
        {
            printf("(STACK_Size) Test sur une pile vide KO\n");
            result = 1;
        }
        else
        {
            printf("(STACK_Size) Test sur une pile vide OK\n");
        }
    }

    /* Test de la fonction STACK_Push() */
    {
        for(idx = 0; idx < sizeof(strings) / sizeof(strings[0]); idx++)
        {
            if(STACK_Push(stack1, strings[idx], strlen(strings[idx]) + 1) == STACK_NO_ERROR)
            {
                printf("(STACK_Push) Test d'insertion %lu OK\n", (unsigned long)idx);
                nbInser++;
            }
            else
            {
                printf("(STACK_Push) Test d'insertion %lu KO\n", (unsigned long)idx);
                result = 1;
            }
        }
    }

    /* Test de la fonction STACK_IsEmpty() sur une pile non vide */
    {
        if(STACK_IsEmpty(stack1) != false)
        {
            printf("(STACK_IsEmpty) Test sur une pile non vide KO\n");
            result = 1;
        }
        else
        {
            printf("(STACK_IsEmpty) Test sur une pile non vide OK\n");
        }
    }

    /* Test de la fonction STACK_Size() sur une pile non vide */
    {
        if(STACK_Size(stack1) != nbInser)
        {
            printf("(STACK_Size) Test sur une pile non vide KO\n");
            result = 1;
        }
        else
        {
            printf("(STACK_Size) Test sur une pile non vide OK\n");
        }
    }

    /* Test de la fonction STACK_Clone() */
    {
        cloneStack1 = STACK_Clone(stack1, &error);
        if(cloneStack1 == NULL || error != STACK_NO_ERROR)
        {
            printf("(STACK_Clone) Test duplication d'une pile KO\n");
            cloneStack1 = NULL;
            result = 1;
        }
        else
        {
            /* On verifie que tout semble bien se passer */
            if(STACK_IsEmpty(cloneStack1) == false && STACK_Size(cloneStack1) == nbInser)
            {
                printf("(STACK_Clone) Test duplication d'une pile OK\n");
            }
            else
            {
                printf("(STACK_Clone) Test duplication d'une pile KO\n");
                result = 1;
            }
        }

        cloneStack2 = STACK_Clone(stack2, &error);
        if(cloneStack2 == NULL || error != STACK_NO_ERROR)
        {
            printf("(STACK_Clone) Test duplication d'une pile vide KO\n");
            cloneStack2 = NULL;
            result = 1;
        }
        else
        {
            /* On verifie que tout semble bien se passer */
            if(STACK_IsEmpty(cloneStack2) == true && STACK_Size(cloneStack2) == 0)
            {
                printf("(STACK_Clone) Test duplication d'une pile vide OK\n");
            }
            else
            {
                printf("(STACK_Clone) Test duplication d'une pile vide KO\n");
                result = 1;
            }
        }
    }

    /* Test de la fonction STACK_Peek() */
    {
        data = STACK_Peek(cloneStack1, &error);
        if(data == NULL || error != STACK_NO_ERROR)
        {
            printf("(STACK_Peek) Test lecture d'une pile KO\n");
            result = 1;
        }
        else
        {
            if(strcmp(data, "chaine2") == 0)
            {
                printf("(STACK_Peek) Test lecture d'une pile OK\n");
            }
            else
            {
                printf("(STACK_Peek) Test lecture d'une pile KO\n");
                result = 1;
            }
        }

        data = STACK_Peek(stack2, &error);
        if(data == NULL &&  error == STACK_EMPTY_STACK)
        {
            printf("(STACK_Peek) Test lecture d'une pile vide OK\n");
        }
        else
        {
            printf("(STACK_Peek) Test lecture d'une pile vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction STACK_Pop() */
    {
        data = STACK_Pop(cloneStack1, &error);
        if(data == NULL || error != STACK_NO_ERROR)
        {
            printf("(STACK_Pop) Test depilement d'une pile KO\n");
            result = 1;
        }
        else
        {
            nbInser--;
            if(strcmp(data, "chaine2") == 0 && STACK_Size(cloneStack1) == nbInser)
            {
                printf("(STACK_Pop) Test depilement d'une pile OK\n");
                free((void*)data), data = NULL;
            }
            else
            {
                printf("(STACK_Pop) Test depilement d'une pile KO\n");
                result = 1;
            }
        }

        data = STACK_Pop(stack2, &error);
        if(data == NULL &&  error == STACK_EMPTY_STACK)
        {
            printf("(STACK_Pop) Test depilement d'une pile vide OK\n");
        }
        else
        {
            printf("(STACK_Pop) Test depilement d'une pile vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction STACK_Remove() */
    {
        error = STACK_Remove(cloneStack1);
        if(error != STACK_NO_ERROR)
        {
            printf("(STACK_Remove) Test suppression d'un element d'une pile KO\n");
            result = 1;
        }
        else
        {
            nbInser--;
            if(STACK_Size(cloneStack1) == nbInser)
            {
                printf("(STACK_Remove) Test suppression d'un element d'une pile OK\n");
            }
            else
            {
                printf("(STACK_Remove) Test suppression d'un element d'une pile KO\n");
                result = 1;
            }
        }

        error = STACK_Remove(stack2);
        if(error == STACK_EMPTY_STACK)
        {
            printf("(STACK_Remove) Test depilement d'une pile vide OK\n");
        }
        else
        {
            printf("(STACK_Remove) Test depilement d'une pile vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction STACK_Destroy() */
    {
        STACK_Destroy(stack1);
        STACK_Destroy(stack2);
        STACK_Destroy(cloneStack1);
        STACK_Destroy(cloneStack2);

        printf("(STACK_Destroy) Test de destructon d'une pile OK\n");
    }

    return result;
}
