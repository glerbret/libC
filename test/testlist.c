#include "bool.h"
#include "list.h"
#include "test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int TstCompar(const void* pData1, const void* pData2)
{
    return strcmp((const char*)pData1, (const char*)pData2);
}

int TstList(void)
{
    int iResult = 0;
    size_t szNbInser = 0;
    size_t szNbCloneInser = 0;
    list_s* pList1;
    list_s* pList2;
    list_s* pCloneList1;
    list_s* pCloneList2;
    LIST_Error_e eError;
    const char* pcData;
    const char* acChaine[] =
    {
        "Chaine1",
        "Chaine2",
        "Chaine3",
        "Chaine4",
        "Chaine5",
        "Chaine6",
        "Chaine7",
        "Chaine8"
    };
    const char* acChaineSearch[] =
    {
        "ChaineA",
        "ChaineB",
        "ChaineB",
        "ChaineB",
        "ChaineD",
        "ChaineB",
        "ChaineB",
        "ChaineB",
        "ChaineC"
    };

    printf("\nTest de \"%s\"\n", LIST_Identifier());

    /* Test de la fonction LIST_Init() */
    {
        pList1 = LIST_Create(NULL, &eError);
        if(pList1 == NULL || eError != LIST_NO_ERROR)
        {
            printf("(LIST_Create) Test creation d'une liste sans fonction de comparaison KO\n");
            return 1;
        }
        else
        {
            printf("(LIST_Create) Test creation d'une liste sans fonction de comparaison OK\n");
        }

        pList2 = LIST_Create(NULL, &eError);
        if(pList2 == NULL || eError != LIST_NO_ERROR)
        {
            printf("(LIST_Create) Test creation d'une liste avec fonction de comparaison KO\n");
            return 1;
        }
        else
        {
            printf("(LIST_Create) Test creation d'une liste avec fonction de comparaison OK\n");
        }
    }

    /* Test de la fonction LIST_IsEmpty() sur une liste vide */
    {
        if(LIST_IsEmpty(pList1) == false)
        {
            printf("(LIST_IsEmpty) Test sur une liste vide KO\n");
            iResult = 1;
        }
        else
        {
            printf("(LIST_IsEmpty) Test sur une liste vide OK\n");
        }
    }

    /* Test de la fonction LIST_Size() sur une liste vide */
    {
        if(LIST_Size(pList1) != 0)
        {
            printf("(LIST_Size) Test sur une liste vide KO\n");
            iResult = 1;
        }
        else
        {
            printf("(LIST_Size) Test sur une liste vide OK\n");
        }
    }

    /* Test de la fonction LIST_InsertFirst() */
    {
        if(LIST_InsertFirst(pList1, acChaine[szNbInser], strlen(acChaine[szNbInser]) + 1) == LIST_NO_ERROR)
        {
            printf("(LIST_InsertFirst) Test d'insertion OK\n");
            szNbInser++;
        }
        else
        {
            printf("(LIST_InsertFirst) Test d'insertion KO\n");
            iResult = 1;
        }

        if(LIST_InsertFirst(pList1, acChaine[szNbInser], strlen(acChaine[szNbInser]) + 1) == LIST_NO_ERROR)
        {
            printf("(LIST_InsertFirst) Test d'insertion OK\n");
            szNbInser++;
        }
        else
        {
            printf("(LIST_InsertFirst) Test d'insertion KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_InsertLast() */
    {
        if(LIST_InsertLast(pList1, acChaine[szNbInser], strlen(acChaine[szNbInser]) + 1) == LIST_NO_ERROR)
        {
            printf("(LIST_InsertLast) Test d'insertion OK\n");
            szNbInser++;
        }
        else
        {
            printf("(LIST_InsertLast) Test d'insertion KO\n");
            iResult = 1;
        }

        if(LIST_InsertLast(pList1, acChaine[szNbInser], strlen(acChaine[szNbInser]) + 1) == LIST_NO_ERROR)
        {
            printf("(LIST_InsertLast) Test d'insertion OK\n");
            szNbInser++;
        }
        else
        {
            printf("(LIST_InsertLast) Test d'insertion KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_InsertNext() */
    {
        /* On commence par se positionner au bon endroit */
        LIST_SeekPrev(pList1);
        LIST_SeekPrev(pList1);

        if(LIST_InsertNext(pList1, acChaine[szNbInser], strlen(acChaine[szNbInser]) + 1) == LIST_NO_ERROR)
        {
            printf("(LIST_InsertNext) Test d'insertion OK\n");
            szNbInser++;
        }
        else
        {
            printf("(LIST_InsertNext) Test d'insertion KO\n");
            iResult = 1;
        }

        /* On se repositionner au bon endroit */
        if(LIST_SeekPrev(pList1) != LIST_NO_ERROR)
        {
            printf("Test module list_s KO : pb deplacement\n");
            return 1;
        }

        if(LIST_InsertNext(pList1, acChaine[szNbInser], strlen(acChaine[szNbInser]) + 1) == LIST_NO_ERROR)
        {
            printf("(LIST_InsertNext) Test d'insertion OK\n");
            szNbInser++;
        }
        else
        {
            printf("(LIST_InsertNext) Test d'insertion KO\n");
            iResult = 1;
        }

        /* On se repositionner au bon endroit */
        if(LIST_SeekPrev(pList1) != LIST_NO_ERROR)
        {
            printf("Test module list_s KO : pb deplacement\n");
            return 1;
        }
    }

    /* Test de la fonction LIST_InsertPrev() */
    {
        if(LIST_InsertPrev(pList1, acChaine[szNbInser], strlen(acChaine[szNbInser]) + 1) == LIST_NO_ERROR)
        {
            printf("(LIST_InsertPrev) Test d'insertion OK\n");
            szNbInser++;
        }
        else
        {
            printf("(LIST_InsertPrev) Test d'insertion KO\n");
            iResult = 1;
        }

        /* On se repositionner au bon endroit */
        if(LIST_SeekNext(pList1) != LIST_NO_ERROR)
        {
            printf("Test module list_s KO : pb deplacement\n");
            return 1;
        }

        if(LIST_InsertPrev(pList1, acChaine[szNbInser], strlen(acChaine[szNbInser]) + 1) == LIST_NO_ERROR)
        {
            printf("(LIST_InsertPrev) Test d'insertion OK\n");
            szNbInser++;
        }
        else
        {
            printf("(LIST_InsertPrev) Test d'insertion KO\n");
            iResult = 1;
        }

        /* On se repositionner au bon endroit */
        if(LIST_SeekNext(pList1) != LIST_NO_ERROR)
        {
            printf("Test module list_s KO : pb deplacement\n");
            return 1;
        }
    }

    /* Test de la fonction LIST_IsEmpty() sur une liste non vide */
    {
        if(LIST_IsEmpty(pList1) == true)
        {
            printf("(LIST_IsEmpty) Test sur une liste non vide KO\n");
            iResult = 1;
        }
        else
        {
            printf("(LIST_IsEmpty) Test sur une liste non vide OK\n");
        }
    }

    /* Test de la fonction LIST_Size() sur une liste non vide */
    {
        if(LIST_Size(pList1) != szNbInser)
        {
            printf("(LIST_Size) Test sur une liste non vide KO\n");
            iResult = 1;
        }
        else
        {
            printf("(LIST_Size) Test sur une liste vide OK\n");
        }
    }

    /* Test de la fonction LIST_ReadCurrent() */
    {
        pcData = LIST_ReadCurrent(pList1, &eError);
        if(pcData == NULL || eError != LIST_NO_ERROR)
        {
            printf("(LIST_ReadCurrent) Test lecture de l'element courant d'une liste KO\n");
            iResult = 1;
        }
        else
        {
            if(strcmp(pcData, "Chaine1") == 0)
            {
                printf("(LIST_ReadCurrent) Test lecture de l'element courant d'une liste OK\n");
            }
            else
            {
                printf("(LIST_ReadCurrent) Test lecture de l'element courant d'une liste KO\n");
                iResult = 1;
            }
        }

        pcData = LIST_ReadCurrent(pList2, &eError);
        if(pcData == NULL && eError == LIST_EMPTY_LIST)
        {
            printf("(LIST_ReadCurrent) Test lecture de l'element courant d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_ReadCurrent) Test lecture de l'element courant d'une liste vide KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_ReadFirst() */
    {
        pcData = LIST_ReadFirst(pList1, &eError);
        if(pcData == NULL || eError != LIST_NO_ERROR)
        {
            printf("(LIST_ReadFirst) Test lecture du premier element d'une liste KO\n");
            iResult = 1;
        }
        else
        {
            if(strcmp(pcData, "Chaine2") == 0)
            {
                printf("(LIST_ReadFirst) Test lecture du premier element d'une liste OK\n");
            }
            else
            {
                printf("(LIST_ReadFirst) Test lecture du premier element d'une liste KO\n");
                iResult = 1;
            }
        }

        pcData = LIST_ReadFirst(pList2, &eError);
        if(pcData == NULL && eError == LIST_EMPTY_LIST)
        {
            printf("(LIST_ReadFirst) Test lecture du premier element d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_ReadFirst) Test lecture du premier element d'une liste vide KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_ReadLast() */
    {
        pcData = LIST_ReadLast(pList1, &eError);
        if(pcData == NULL || eError != LIST_NO_ERROR)
        {
            printf("(LIST_ReadLast) Test lecture du dernier element d'une liste KO\n");
            iResult = 1;
        }
        else
        {
            if(strcmp(pcData, "Chaine4") == 0)
            {
                printf("(LIST_ReadLast) Test lecture du dernier element d'une liste OK\n");
            }
            else
            {
                printf("(LIST_ReadLast) Test lecture du dernier element d'une liste KO\n");
                iResult = 1;
            }
        }

        pcData = LIST_ReadLast(pList2, &eError);
        if(pcData == NULL && eError == LIST_EMPTY_LIST)
        {
            printf("(LIST_ReadLast) Test lecture du dernier element d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_ReadLast) Test lecture du dernier element d'une liste vide KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_ReadNext() */
    {
        pcData = LIST_ReadNext(pList1, &eError);
        if(pcData == NULL || eError != LIST_NO_ERROR)
        {
            printf("(LIST_ReadNext) Test lecture de l'element suivant d'une liste KO\n");
            iResult = 1;
        }
        else
        {
            if(strcmp(pcData, "Chaine6") == 0)
            {
                printf("(LIST_ReadNext) Test lecture de l'element suivant d'une liste OK\n");
            }
            else
            {
                printf("(LIST_ReadNext) Test lecture de l'element suivant d'une liste KO\n");
                iResult = 1;
            }
        }

        pcData = LIST_ReadNext(pList2, &eError);
        if(pcData == NULL && eError == LIST_EMPTY_LIST)
        {
            printf("(LIST_ReadNext) Test lecture de l'element suivant d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_ReadNext) Test lecture de l'element suivant d'une liste vide KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_ReadPrev() */
    {
        pcData = LIST_ReadPrev(pList1, &eError);
        if(pcData == NULL || eError != LIST_NO_ERROR)
        {
            printf("(LIST_ReadPrev) Test lecture de l'element precedent d'une liste KO\n");
            iResult = 1;
        }
        else
        {
            if(strcmp(pcData, "Chaine8") == 0)
            {
                printf("(LIST_ReadPrev) Test lecture de l'element precedent d'une liste OK\n");
            }
            else
            {
                printf("(LIST_ReadPrev) Test lecture de l'element precedent d'une liste KO\n");
                iResult = 1;
            }
        }

        pcData = LIST_ReadNext(pList2, &eError);
        if(pcData == NULL && eError == LIST_EMPTY_LIST)
        {
            printf("(LIST_ReadPrev) Test lecture de l'element precedent d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_ReadPrev) Test lecture de l'element precedent d'une liste vide KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_SeekFirst() */
    {
        if(LIST_SeekFirst(pList1) != LIST_NO_ERROR)
        {
            printf("(LIST_SeekFirst) Test de deplacement vers le premier element d'une liste KO\n");
            iResult = 1;
        }
        else
        {
            pcData = LIST_ReadCurrent(pList1, &eError);
            if(pcData != NULL && eError == LIST_NO_ERROR && strcmp(pcData, "Chaine2") == 0)
            {
                printf("(LIST_SeekFirst) Test de deplacement vers le premier element d'une liste OK\n");
            }
            else
            {
                printf("(LIST_SeekFirst) Test de deplacement vers le premier element d'une liste KO\n");
                iResult = 1;
            }
        }

        if(LIST_SeekFirst(pList2) == LIST_EMPTY_LIST)
        {
            printf("(LIST_SeekFirst) Test de deplacement vers le premier element d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_SeekFirst) Test de deplacement vers le premier element d'une liste vide KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_SeekLast() */
    {
        if(LIST_SeekLast(pList1) != LIST_NO_ERROR)
        {
            printf("(LIST_SeekLast) Test de deplacement vers le dernier element d'une liste KO\n");
            iResult = 1;
        }
        else
        {
            pcData = LIST_ReadCurrent(pList1, &eError);
            if(pcData != NULL && eError == LIST_NO_ERROR && strcmp(pcData, "Chaine4") == 0)
            {
                printf("(LIST_SeekLast) Test de deplacement vers le dernier element d'une liste OK\n");
            }
            else
            {
                printf("(LIST_SeekLast) Test de deplacement vers le dernier element d'une liste KO\n");
                iResult = 1;
            }
        }

        if(LIST_SeekLast(pList2) == LIST_EMPTY_LIST)
        {
            printf("(LIST_SeekLast) Test de deplacement vers le dernier element d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_SeekLast) Test de deplacement vers le dernier element d'une liste vide KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_SeekPrev() */
    {
        if(LIST_SeekPrev(pList1) != LIST_NO_ERROR)
        {
            printf("(LIST_SeekPrev) Test de deplacement vers l'element precedent d'une liste KO\n");
            iResult = 1;
        }
        else
        {
            pcData = LIST_ReadCurrent(pList1, &eError);
            if(pcData != NULL && eError == LIST_NO_ERROR && strcmp(pcData, "Chaine3") == 0)
            {
                printf("(LIST_SeekPrev) Test de deplacement vers l'element precedent d'une liste OK\n");
            }
            else
            {
                printf("(LIST_SeekPrev) Test de deplacement vers ll'element precedent d'une liste KO\n");
                iResult = 1;
            }
        }

        if(LIST_SeekPrev(pList2) == LIST_EMPTY_LIST)
        {
            printf("(LIST_SeekPrev) Test de deplacement vers l'element precedent d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_SeekPrev) Test de deplacement vers l'element precedent d'une liste vide KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_SeekNext() */
    {
        if(LIST_SeekNext(pList1) != LIST_NO_ERROR)
        {
            printf("(LIST_SeekNext) Test de deplacement vers l'element suivant d'une liste KO\n");
            iResult = 1;
        }
        else
        {
            pcData = LIST_ReadCurrent(pList1, &eError);
            if(pcData != NULL && eError == LIST_NO_ERROR && strcmp(pcData, "Chaine4") == 0)
            {
                printf("(LIST_SeekNext) Test de deplacement vers l'element suivant d'une liste OK\n");
            }
            else
            {
                printf("(LIST_SeekNext) Test de deplacement vers l'element suivant d'une liste KO\n");
                iResult = 1;
            }
        }

        if(LIST_SeekNext(pList2) == LIST_EMPTY_LIST)
        {
            printf("(LIST_SeekNext) Test de deplacement vers l'element suivant d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_SeekNext) Test de deplacement vers l'element suivant d'une liste vide KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_IsHead() */
    {
        if(LIST_IsHead(pList1) == false)
        {
            LIST_SeekFirst(pList1);
            if(LIST_IsHead(pList1) == true)
            {
                printf("(LIST_IsHead) Test sur une liste non vide OK\n");
            }
            else
            {
                printf("(LIST_IsHead) Test sur une liste non vide KO\n");
                iResult = 1;
            }
        }
        else
        {
            printf("(LIST_IsHead) Test sur une liste non vide KO\n");
            iResult = 1;
        }

        if(LIST_IsHead(pList2) == false)
        {
            printf("(LIST_IsHead) Test sur une liste vide OK\n");
        }
        else
        {
            printf("(LIST_IsHead) Test sur une liste vide KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_IsTail() */
    {
        if(LIST_IsTail(pList1) == false)
        {
            LIST_SeekLast(pList1);
            if(LIST_IsTail(pList1) == true)
            {
                printf("(LIST_IsTail) Test sur une liste non vide OK\n");
            }
            else
            {
                printf("(LIST_IsTail) Test sur une liste non vide KO\n");
                iResult = 1;
            }
        }
        else
        {
            printf("(LIST_IsTail) Test sur une liste non vide KO\n");
            iResult = 1;
        }

        if(LIST_IsTail(pList2) == false)
        {
            printf("(LIST_IsTail) Test sur une liste vide OK\n");
        }
        else
        {
            printf("(LIST_IsTail) Test sur une liste vide KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_Clone() */
    {
        pCloneList1 = LIST_Clone(pList1, &eError);
        if(pCloneList1 == NULL || eError != LIST_NO_ERROR)
        {
            printf("(LIST_Clone) Test duplication d'une liste KO\n");
            iResult = 1;
        }
        else
        {
            /* On verifie que tout semble bien se passer */
            if(LIST_IsEmpty(pCloneList1) == false && LIST_Size(pCloneList1) == szNbInser)
            {
                printf("(LIST_Clone) Test duplication d'une liste OK\n");
                szNbCloneInser = szNbInser;
            }
            else
            {
                printf("(LIST_Clone) Test duplication d'une liste KO\n");
                iResult = 1;
            }
        }

        pCloneList2 = LIST_Clone(pList2, &eError);
        if(pCloneList2 == NULL || eError != LIST_NO_ERROR)
        {
            printf("(LIST_Clone) Test duplication d'une liste vide KO\n");
            pCloneList2 = NULL;
            iResult = 1;
        }
        else
        {
            /* On verifie que tout semble bien se passer */
            if(LIST_IsEmpty(pCloneList2) == true && LIST_Size(pCloneList2) == 0)
            {
                printf("(LIST_Clone) Test duplication d'une liste vide OK\n");
            }
            else
            {
                printf("(LIST_Clone) Test duplication d'une liste vide KO\n");
                iResult = 1;
            }
        }
    }

    /* Test de la fonction LIST_GetFirst() */
    {
        pcData = LIST_GetFirst(pCloneList1, &eError);
        if(pcData == NULL || eError != LIST_NO_ERROR)
        {
            printf("(LIST_GetFirst) Test lecture du premier element d'une liste KO\n");
            iResult = 1;
        }
        else
        {
            szNbCloneInser --;
            if(strcmp(pcData, "Chaine2") == 0)
            {
                printf("(LIST_GetFirst) Test lecture du premier element d'une liste OK\n");
                free((void*)pcData), pcData = NULL;
            }
            else
            {
                printf("(LIST_GetFirst) Test lecture du premier element d'une liste KO\n");
                iResult = 1;
            }
        }

        pcData = LIST_GetFirst(pCloneList2, &eError);
        if(pcData == NULL && eError == LIST_EMPTY_LIST)
        {
            printf("(LIST_GetFirst) Test lecture du premier element d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_GetFirst) Test lecture du premier element d'une liste vide KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_GetLast() */
    {
        pcData = LIST_GetLast(pCloneList1, &eError);
        if(pcData == NULL || eError != LIST_NO_ERROR)
        {
            printf("(LIST_GetLast) Test lecture du dernier element d'une liste KO\n");
            iResult = 1;
        }
        else
        {
            szNbCloneInser --;
            if(strcmp(pcData, "Chaine4") == 0)
            {
                printf("(LIST_GetLast) Test lecture du dernier element d'une liste OK\n");
                free((void*)pcData), pcData = NULL;
            }
            else
            {
                printf("(LIST_GetLast) Test lecture du dernier element d'une liste KO\n");
                iResult = 1;
            }
        }

        pcData = LIST_GetLast(pCloneList2, &eError);
        if(pcData == NULL && eError == LIST_EMPTY_LIST)
        {
            printf("(LIST_GetLast) Test lecture du dernier element d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_GetLast) Test lecture du dernier element d'une liste vide KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_GetCurrent() */
    {
        /* On se positionne sur le bon element */
        LIST_SeekFirst(pCloneList1);
        LIST_SeekNext(pCloneList1);
        LIST_SeekNext(pCloneList1);

        pcData = LIST_GetCurrent(pCloneList1, &eError);
        if(pcData == NULL || eError != LIST_NO_ERROR)
        {
            printf("(LIST_GetCurrent) Test lecture d'une liste KO\n");
            iResult = 1;
        }
        else
        {
            szNbCloneInser --;
            if(strcmp(pcData, "Chaine1") == 0)
            {
                printf("(LIST_GetCurrent) Test lecture d'une liste OK\n");
            }
            else
            {
                printf("(LIST_GetCurrent) Test lecture d'une liste KO\n");
                iResult = 1;
            }
        }

        pcData = LIST_GetCurrent(pCloneList2, &eError);
        if(pcData == NULL && eError == LIST_EMPTY_LIST)
        {
            printf("(LIST_GetCurrent) Test lecture d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_GetCurrent) Test lecture d'une liste vide KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_GetNext() */
    {
        pcData = LIST_GetNext(pCloneList1, &eError);
        if(pcData == NULL || eError != LIST_NO_ERROR)
        {
            printf("(LIST_GetNext) Test lecture d'une liste KO\n");
            iResult = 1;
        }
        else
        {
            szNbCloneInser --;
            if(strcmp(pcData, "Chaine5") == 0)
            {
                printf("(LIST_GetNext) Test lecture d'une liste OK\n");
            }
            else
            {
                printf("(LIST_GetNext) Test lecture d'une liste KO\n");
                iResult = 1;
            }
        }

        pcData = LIST_GetNext(pCloneList2, &eError);
        if(pcData == NULL && eError == LIST_EMPTY_LIST)
        {
            printf("(LIST_GetNext) Test lecture d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_GetNext) Test lecture d'une liste vide KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_GetPrev() */
    {
        pcData = LIST_GetPrev(pCloneList1, &eError);
        if(pcData == NULL || eError != LIST_NO_ERROR)
        {
            printf("(LIST_GetPrev) Test lecture d'une liste KO\n");
            iResult = 1;
        }
        else
        {
            szNbCloneInser --;
            if(strcmp(pcData, "Chaine8") == 0)
            {
                printf("(LIST_GetPrev) Test lecture d'une liste OK\n");
                free((void*)pcData), pcData = NULL;
            }
            else
            {
                printf("(LIST_GetPrev) Test lecture d'une liste KO\n");
                iResult = 1;
            }
        }

        pcData = LIST_GetPrev(pCloneList2, &eError);
        if(pcData == NULL && eError == LIST_EMPTY_LIST)
        {
            printf("(LIST_GetPrev) Test lecture d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_GetPrev) Test lecture d'une liste vide KO\n");
            iResult = 1;
        }
    }

    /* On verifie que les elements ont bien ete enleve */
    {
        if(LIST_Size(pCloneList1) != szNbCloneInser)
        {
            printf("(LIST_GetXXXX) La taille de la liste est incorrecte\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_RemoveFirst() */
    {
        eError = LIST_RemoveFirst(pList1);
        if(eError != LIST_NO_ERROR)
        {
            printf("(LIST_RemoveFirst) Test suppression dans une liste KO\n");
            iResult = 1;
        }
        else
        {
            szNbInser --;
            printf("(LIST_RemoveFirst) Test suppression dans une liste OK\n");
        }

        eError = LIST_RemoveFirst(pCloneList2);
        if(eError == LIST_EMPTY_LIST)
        {
            printf("(LIST_RemoveFirst) Test suppression dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveFirst) Test suppression dans une liste KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_RemoveLast() */
    {
        eError = LIST_RemoveLast(pList1);
        if(eError != LIST_NO_ERROR)
        {
            printf("(LIST_RemoveLast) Test suppression dans une liste KO\n");
            iResult = 1;
        }
        else
        {
            szNbInser --;
            printf("(LIST_RemoveLast) Test suppression dans une liste OK\n");
        }

        eError = LIST_RemoveLast(pCloneList2);
        if(eError == LIST_EMPTY_LIST)
        {
            printf("(LIST_RemoveLast) Test suppression dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveLast) Test suppression dans une liste KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_RemoveCurrent() */
    {
        /* On se positionne sur le bon element */
        LIST_SeekFirst(pList1);
        LIST_SeekNext(pList1);
        LIST_SeekNext(pList1);

        eError = LIST_RemoveCurrent(pList1);
        if(eError != LIST_NO_ERROR)
        {
            printf("(LIST_RemoveCurrent) Test suppression dans une liste KO\n");
            iResult = 1;
        }
        else
        {
            szNbInser --;
            printf("(LIST_RemoveCurrent) Test suppression dans une liste OK\n");
        }

        eError = LIST_RemoveCurrent(pCloneList2);
        if(eError == LIST_EMPTY_LIST)
        {
            printf("(LIST_RemoveCurrent) Test suppression dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveCurrent) Test suppression dans une liste KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_RemoveNext() */
    {
        eError = LIST_RemoveNext(pList1);
        if(eError != LIST_NO_ERROR)
        {
            printf("(LIST_RemoveNext) Test suppression dans une liste KO\n");
            iResult = 1;
        }
        else
        {
            szNbInser --;
            printf("(LIST_RemoveNext) Test suppression dans une liste OK\n");
        }

        eError = LIST_RemoveNext(pCloneList2);
        if(eError == LIST_EMPTY_LIST)
        {
            printf("(LIST_RemoveNext) Test suppression dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveNext) Test suppression dans une liste KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_RemovePrev() */
    {
        eError = LIST_RemovePrev(pList1);
        if(eError != LIST_NO_ERROR)
        {
            printf("(LIST_RemovePrev) Test suppression dans une liste KO\n");
            iResult = 1;
        }
        else
        {
            szNbInser --;
            printf("(LIST_RemovePrev) Test suppression dans une liste OK\n");
        }

        eError = LIST_RemovePrev(pCloneList2);
        if(eError == LIST_EMPTY_LIST)
        {
            printf("(LIST_RemovePrev) Test suppression dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemovePrev) Test suppression dans une liste KO\n");
            iResult = 1;
        }
    }

    /* On verifie que les elements ont bien ete enleve */
    {
        if(LIST_Size(pList1) != szNbInser)
        {
            printf("(LIST_RemoveXXXX) La taille de la liste est incorrecte\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_Destroy() */
    {
        LIST_Destroy(pList1);
        LIST_Destroy(pList2);
        LIST_Destroy(pCloneList1);
        LIST_Destroy(pCloneList2);

        printf("(LIST_Destroy) Test de destruction d'une liste OK\n");
    }

    /* Creation des listes de test pour la recherche */
    {
        pList1 = LIST_Create(NULL, &eError);
        pList2 = LIST_Create(NULL, &eError);
        if(pList1 == NULL || pList2 == NULL)
        {
            printf("Test module liste : pb creations liste de test\n");
            return 1;
        }

        for(szNbInser = 0; szNbInser < sizeof(acChaineSearch) / sizeof(acChaineSearch[0]); szNbInser++)
        {
            if(LIST_InsertLast(pList1, acChaineSearch[szNbInser], strlen(acChaineSearch[szNbInser]) + 1) != LIST_NO_ERROR)
            {
                printf("Test module liste : pb creations liste de test\n");
                return 1;
            }
        }

        pCloneList1 = LIST_Clone(pList1, &eError);
        if(pCloneList1 == NULL || eError != LIST_NO_ERROR)
        {
            printf("Test module liste : pb creations liste de test\n");
            iResult = 1;
        }

        szNbCloneInser = szNbInser;

        LIST_SeekFirst(pList1);
        LIST_SeekNext(pList1);
        LIST_SeekNext(pList1);
        LIST_SeekNext(pList1);
        LIST_SeekNext(pList1);

        LIST_SeekFirst(pCloneList1);
        LIST_SeekNext(pCloneList1);
        LIST_SeekNext(pCloneList1);
        LIST_SeekNext(pCloneList1);
        LIST_SeekNext(pCloneList1);
    }

    /* Test de la fonction LIST_SetCmp() */
    {
        LIST_SetCmp(pList1, TstCompar);
        printf("(LIST_SetCmp) Initialisation de la fonction de comparaison OK\n");
    }

    /* Test de la fonction LIST_SearchData() */
    {
        if(LIST_SearchData(pList1, "ChaineB") == LIST_NO_ERROR)
        {
            printf("(LIST_SearchData) Test de recherche dans une liste OK\n");
        }
        else
        {
            printf("(LIST_SearchData) Test de recherche dans une liste KO\n");
            iResult = 1;
        }

        if(LIST_SearchData(pList1, "ChaineA") == LIST_CELL_NOT_FOUND)
        {
            printf("(LIST_SearchData) Test de recherche d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(LIST_SearchData) Test de recherche d'un element non present dans une liste KO\n");
            iResult = 1;
        }

        if(LIST_SearchData(pList2, "ChaineB") == LIST_EMPTY_LIST)
        {
            printf("(LIST_SearchData) Test de recherche dans une liste vide OK\n");
        }
        else
        {
            printf("(LIST_SearchData) Test de recherche dans une liste vide KO\n");
            iResult = 1;
        }

        if(LIST_SearchData(pCloneList1, "ChaineB") == LIST_NO_COMP_FONCTION)
        {
            printf("(LIST_SearchData) Test de recherche dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(LIST_SearchData) Test de recherche dans une liste sans comparateur KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_SearchDataFct() */
    {
        if(LIST_SearchDataFct(pList1, "ChaineB", TstCompar) == LIST_NO_ERROR)
        {
            printf("(LIST_SearchDataFct) Test de recherche dans une liste OK\n");
        }
        else
        {
            printf("(LIST_SearchDataFct) Test de recherche dans une liste KO\n");
            iResult = 1;
        }

        if(LIST_SearchDataFct(pList1, "ChaineA", TstCompar) == LIST_CELL_NOT_FOUND)
        {
            printf("(LIST_SearchDataFct) Test de recherche d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(LIST_SearchDataFct) Test de recherche d'un element non present dans une liste KO\n");
            iResult = 1;
        }

        if(LIST_SearchDataFct(pList2, "ChaineB", TstCompar) == LIST_EMPTY_LIST)
        {
            printf("(LIST_SearchDataFct) Test de recherche dans une liste vide OK\n");
        }
        else
        {
            printf("(LIST_SearchDataFct) Test de recherche dans une liste vide KO\n");
            iResult = 1;
        }

        if(LIST_SearchDataFct(pCloneList1, "ChaineB", TstCompar) == LIST_NO_ERROR)
        {
            printf("(LIST_SearchDataFct) Test de recherche dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(LIST_SearchDataFct) Test de recherche dans une liste sans comparateur KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_SearchDataRev() */
    {
        if(LIST_SearchDataRev(pList1, "ChaineD") == LIST_NO_ERROR)
        {
            printf("(LIST_SearchDataRev) Test de recherche dans une liste OK\n");
        }
        else
        {
            printf("(LIST_SearchDataRev) Test de recherche dans une liste KO\n");
            iResult = 1;
        }

        if(LIST_SearchDataRev(pList1, "ChaineC") == LIST_CELL_NOT_FOUND)
        {
            printf("(LIST_SearchDataRev) Test de recherche d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(LIST_SearchDataRev) Test de recherche d'un element non present dans une liste KO\n");
            iResult = 1;
        }

        if(LIST_SearchDataRev(pList2, "ChaineD") == LIST_EMPTY_LIST)
        {
            printf("(LIST_SearchDataRev) Test de recherche dans une liste vide OK\n");
        }
        else
        {
            printf("(LIST_SearchDataRev) Test de recherche dans une liste vide KO\n");
            iResult = 1;
        }

        if(LIST_SearchDataRev(pCloneList1, "ChaineD") == LIST_NO_COMP_FONCTION)
        {
            printf("(LIST_SearchDataRev) Test de recherche dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(LIST_SearchDataRev) Test de recherche dans une liste sans comparateur KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_SearchDataRevFct() */
    {
        if(LIST_SearchDataRevFct(pList1, "ChaineD", TstCompar) == LIST_NO_ERROR)
        {
            printf("(LIST_SearchDataRevFct) Test de recherche dans une liste OK\n");
        }
        else
        {
            printf("(LIST_SearchDataRevFct) Test de recherche dans une liste KO\n");
            iResult = 1;
        }

        if(LIST_SearchDataRevFct(pList1, "ChaineC", TstCompar) == LIST_CELL_NOT_FOUND)
        {
            printf("(LIST_SearchDataRevFct) Test de recherche d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(LIST_SearchDataRevFct) Test de recherche d'un element non present dans une liste KO\n");
            iResult = 1;
        }

        if(LIST_SearchDataRevFct(pList2, "ChaineD", TstCompar) == LIST_EMPTY_LIST)
        {
            printf("(LIST_SearchDataRevFct) Test de recherche dans une liste vide OK\n");
        }
        else
        {
            printf("(LIST_SearchDataRevFct) Test de recherche dans une liste vide KO\n");
            iResult = 1;
        }

        if(LIST_SearchDataRevFct(pCloneList1, "ChaineD", TstCompar) == LIST_NO_ERROR)
        {
            printf("(LIST_SearchDataRevFct) Test de recherche dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(LIST_SearchDataRevFct) Test de recherche dans une liste sans comparateur KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_RemoveData() */
    {
        if(LIST_RemoveData(pList1, "ChaineB") == LIST_NO_ERROR)
        {
            printf("(LIST_RemoveData) Test de suppression dans une liste OK\n");
            szNbInser--;
        }
        else
        {
            printf("(LIST_RemoveData) Test de suppression dans une liste KO\n");
            iResult = 1;
        }

        if(LIST_RemoveData(pList1, "ChaineA") == LIST_CELL_NOT_FOUND)
        {
            printf("(LIST_RemoveData) Test de suppression d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveData) Test de suppression d'un element non present dans une liste KO\n");
            iResult = 1;
        }

        if(LIST_RemoveData(pList2, "ChaineB") == LIST_EMPTY_LIST)
        {
            printf("(LIST_RemoveData) Test de suppression dans une liste vide OK\n");
        }
        else
        {
            printf("(LIST_RemoveData) Test de suppression dans une liste vide KO\n");
            iResult = 1;
        }

        if(LIST_RemoveData(pCloneList1, "ChaineB") == LIST_NO_COMP_FONCTION)
        {
            printf("(LIST_RemoveData) Test de suppression dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(LIST_RemoveData) Test de suppression dans une liste sans comparateur KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_RemoveDataFct() */
    {
        if(LIST_RemoveDataFct(pList1, "ChaineB", TstCompar) == LIST_NO_ERROR)
        {
            printf("(LIST_RemoveDataFct) Test de suppression dans une liste OK\n");
            szNbInser--;
        }
        else
        {
            printf("(LIST_RemoveDataFct) Test de suppression dans une liste KO\n");
            iResult = 1;
        }

        if(LIST_RemoveDataFct(pList1, "ChaineA", TstCompar) == LIST_CELL_NOT_FOUND)
        {
            printf("(LIST_RemoveDataFct) Test de suppression d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveDataFct) Test de suppression d'un element non present dans une liste KO\n");
            iResult = 1;
        }

        if(LIST_RemoveDataFct(pList2, "ChaineB", TstCompar) == LIST_EMPTY_LIST)
        {
            printf("(LIST_RemoveDataFct) Test de suppression dans une liste vide OK\n");
        }
        else
        {
            printf("(LIST_RemoveDataFct) Test de suppression dans une liste vide KO\n");
            iResult = 1;
        }

        if(LIST_RemoveDataFct(pCloneList1, "ChaineB", TstCompar) == LIST_NO_ERROR)
        {
            printf("(LIST_RemoveDataFct) Test de suppression dans une liste sans comparateur OK\n");
            szNbCloneInser--;
        }
        else
        {
            printf("(LIST_RemoveDataFct) Test de suppression dans une liste sans comparateur KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_RemoveDataRev() */
    {
        if(LIST_RemoveDataRev(pList1, "ChaineB") == LIST_NO_ERROR)
        {
            printf("(LIST_RemoveDataRev) Test de suppression dans une liste OK\n");
            szNbInser--;
        }
        else
        {
            printf("(LIST_RemoveDataRev) Test de suppression dans une liste KO\n");
            iResult = 1;
        }

        if(LIST_RemoveDataRev(pList1, "ChaineC") == LIST_CELL_NOT_FOUND)
        {
            printf("(LIST_RemoveDataRev) Test de suppression d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveDataRev) Test de suppression d'un element non present dans une liste KO\n");
            iResult = 1;
        }

        if(LIST_RemoveDataRev(pList2, "ChaineB") == LIST_EMPTY_LIST)
        {
            printf("(LIST_RemoveDataRev) Test de suppression dans une liste vide OK\n");
        }
        else
        {
            printf("(LIST_RemoveDataRev) Test de suppression dans une liste vide KO\n");
            iResult = 1;
        }

        if(LIST_RemoveDataRev(pCloneList1, "ChaineB") == LIST_NO_COMP_FONCTION)
        {
            printf("(LIST_RemoveDataRev) Test de suppression dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(LIST_RemoveDataRev) Test de suppression dans une liste sans comparateur KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_RemoveDataRevFct() */
    {
        if(LIST_RemoveDataRevFct(pList1, "ChaineB", TstCompar) == LIST_NO_ERROR)
        {
            printf("(LIST_RemoveDataRevFct) Test de suppression dans une liste OK\n");
            szNbInser--;
        }
        else
        {
            printf("(LIST_RemoveDataRevFct) Test de suppression dans une liste KO\n");
            iResult = 1;
        }

        if(LIST_RemoveDataRevFct(pList1, "ChaineC", TstCompar) == LIST_CELL_NOT_FOUND)
        {
            printf("(LIST_RemoveDataRevFct) Test de suppression d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveDataRevFct) Test de suppression d'un element non present dans une liste KO\n");
            iResult = 1;
        }

        if(LIST_RemoveDataRevFct(pList2, "ChaineB", TstCompar) == LIST_EMPTY_LIST)
        {
            printf("(LIST_RemoveDataRevFct) Test de suppression dans une liste vide OK\n");
        }
        else
        {
            printf("(LIST_RemoveDataRevFct) Test de suppression dans une liste vide KO\n");
            iResult = 1;
        }

        if(LIST_RemoveDataRevFct(pCloneList1, "ChaineB", TstCompar) == LIST_NO_ERROR)
        {
            printf("(LIST_RemoveDataRevFct) Test de suppression dans une liste sans comparateur OK\n");
            szNbCloneInser--;
        }
        else
        {
            printf("(LIST_RemoveDataRevFct) Test de suppression dans une liste sans comparateur KO\n");
            iResult = 1;
        }
    }

    /* On verifie que les elements ont bien ete enleve */
    {
        if(LIST_Size(pList1) != szNbInser)
        {
            printf("(LIST_RemoveDataXXXX) La taille de la liste pList1 est incorrecte\n");
            iResult = 1;
        }


        if(LIST_Size(pCloneList1) != szNbCloneInser)
        {
            printf("(LIST_RemoveDataXXXX) La taille de la liste pCloneList1 est incorrecte\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_RemoveAllData() */
    {
        if(LIST_RemoveAllData(pList1, "ChaineB") == LIST_NO_ERROR)
        {
            printf("(LIST_RemoveAllData) Test de suppression dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveAllData) Test de suppression dans une liste KO\n");
            iResult = 1;
        }

        if(LIST_RemoveAllData(pList1, "ChaineZ") == LIST_NO_ERROR)
        {
            printf("(LIST_RemoveAllData) Test de suppression d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveAllData) Test de suppression d'un element non present dans une liste KO\n");
            iResult = 1;
        }

        if(LIST_RemoveAllData(pList2, "ChaineB") == LIST_EMPTY_LIST)
        {
            printf("(LIST_RemoveAllData) Test de suppression dans une liste vide OK\n");
        }
        else
        {
            printf("(LIST_RemoveAllData) Test de suppression dans une liste vide KO\n");
            iResult = 1;
        }

        if(LIST_RemoveAllData(pCloneList1, "ChaineB") == LIST_NO_COMP_FONCTION)
        {
            printf("(LIST_RemoveAllData) Test de suppression dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(LIST_RemoveAllData) Test de suppression dans une liste sans comparateur KO\n");
            iResult = 1;
        }
    }

    /* Test de la fonction LIST_RemoveDataFct() */
    {
        if(LIST_RemoveAllDataFct(pList1, "ChaineB", TstCompar) == LIST_NO_ERROR)
        {
            printf("(LIST_RemoveAllDataFct) Test de suppression dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveAllDataFct) Test de suppression dans une liste KO\n");
            iResult = 1;
        }

        if(LIST_RemoveAllDataFct(pList1, "ChaineZ", TstCompar) == LIST_NO_ERROR)
        {
            printf("(LIST_RemoveAllDataFct) Test de suppression d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveAllDataFct) Test de suppression d'un element non present dans une liste KO\n");
            iResult = 1;
        }

        if(LIST_RemoveAllDataFct(pList2, "ChaineB", TstCompar) == LIST_EMPTY_LIST)
        {
            printf("(LIST_RemoveAllDataFct) Test de suppression dans une liste vide OK\n");
        }
        else
        {
            printf("(LIST_RemoveAllDataFct) Test de suppression dans une liste vide KO\n");
            iResult = 1;
        }

        if(LIST_RemoveAllDataFct(pCloneList1, "ChaineB", TstCompar) == LIST_NO_ERROR)
        {
            printf("(LIST_RemoveAllDataFct) Test de suppression dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(LIST_RemoveAllDataFct) Test de suppression dans une liste sans comparateur KO\n");
            iResult = 1;
        }
    }

    /* On verifie que les elements ont bien ete enleve */
    {
        if(LIST_Size(pList1) != 3)
        {
            printf("(LIST_RemoveAllDataXXXX) La taille de la liste pList1 est incorrecte\n");
            iResult = 1;
        }

        if(LIST_Size(pCloneList1) != 3)
        {
            printf("(LIST_RemoveAllDataXXXX) La taille de la liste pCloneList1 est incorrecte\n");
            iResult = 1;
        }
    }

    /* Desctruction des listes */
    {
        LIST_Destroy(pList1);
        LIST_Destroy(pList2);
        LIST_Destroy(pCloneList1);
    }

    return iResult;
}
