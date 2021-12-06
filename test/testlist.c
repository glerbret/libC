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
    int result = 0;
    size_t nbInser = 0;
    size_t nbCloneInser = 0;
    list_s* list1;
    list_s* list2;
    list_s* cloneList1;
    list_s* cloneList2;
    LIST_Error_e error;
    const char* data;
    const char* string[] =
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
    const char* searchedString[] =
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
        list1 = LIST_Create(NULL, &error);
        if(list1 == NULL || error != LIST_NO_ERROR)
        {
            printf("(LIST_Create) Test creation d'une liste sans fonction de comparaison KO\n");
            return 1;
        }
        else
        {
            printf("(LIST_Create) Test creation d'une liste sans fonction de comparaison OK\n");
        }

        list2 = LIST_Create(NULL, &error);
        if(list2 == NULL || error != LIST_NO_ERROR)
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
        if(LIST_IsEmpty(list1) == false)
        {
            printf("(LIST_IsEmpty) Test sur une liste vide KO\n");
            result = 1;
        }
        else
        {
            printf("(LIST_IsEmpty) Test sur une liste vide OK\n");
        }
    }

    /* Test de la fonction LIST_Size() sur une liste vide */
    {
        if(LIST_Size(list1) != 0)
        {
            printf("(LIST_Size) Test sur une liste vide KO\n");
            result = 1;
        }
        else
        {
            printf("(LIST_Size) Test sur une liste vide OK\n");
        }
    }

    /* Test de la fonction LIST_InsertFirst() */
    {
        if(LIST_InsertFirst(list1, string[nbInser], strlen(string[nbInser]) + 1) == LIST_NO_ERROR)
        {
            printf("(LIST_InsertFirst) Test d'insertion OK\n");
            nbInser++;
        }
        else
        {
            printf("(LIST_InsertFirst) Test d'insertion KO\n");
            result = 1;
        }

        if(LIST_InsertFirst(list1, string[nbInser], strlen(string[nbInser]) + 1) == LIST_NO_ERROR)
        {
            printf("(LIST_InsertFirst) Test d'insertion OK\n");
            nbInser++;
        }
        else
        {
            printf("(LIST_InsertFirst) Test d'insertion KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_InsertLast() */
    {
        if(LIST_InsertLast(list1, string[nbInser], strlen(string[nbInser]) + 1) == LIST_NO_ERROR)
        {
            printf("(LIST_InsertLast) Test d'insertion OK\n");
            nbInser++;
        }
        else
        {
            printf("(LIST_InsertLast) Test d'insertion KO\n");
            result = 1;
        }

        if(LIST_InsertLast(list1, string[nbInser], strlen(string[nbInser]) + 1) == LIST_NO_ERROR)
        {
            printf("(LIST_InsertLast) Test d'insertion OK\n");
            nbInser++;
        }
        else
        {
            printf("(LIST_InsertLast) Test d'insertion KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_InsertNext() */
    {
        /* On commence par se positionner au bon endroit */
        LIST_SeekPrev(list1);
        LIST_SeekPrev(list1);

        if(LIST_InsertNext(list1, string[nbInser], strlen(string[nbInser]) + 1) == LIST_NO_ERROR)
        {
            printf("(LIST_InsertNext) Test d'insertion OK\n");
            nbInser++;
        }
        else
        {
            printf("(LIST_InsertNext) Test d'insertion KO\n");
            result = 1;
        }

        /* On se repositionner au bon endroit */
        if(LIST_SeekPrev(list1) != LIST_NO_ERROR)
        {
            printf("Test module list_s KO : pb deplacement\n");
            return 1;
        }

        if(LIST_InsertNext(list1, string[nbInser], strlen(string[nbInser]) + 1) == LIST_NO_ERROR)
        {
            printf("(LIST_InsertNext) Test d'insertion OK\n");
            nbInser++;
        }
        else
        {
            printf("(LIST_InsertNext) Test d'insertion KO\n");
            result = 1;
        }

        /* On se repositionner au bon endroit */
        if(LIST_SeekPrev(list1) != LIST_NO_ERROR)
        {
            printf("Test module list_s KO : pb deplacement\n");
            return 1;
        }
    }

    /* Test de la fonction LIST_InsertPrev() */
    {
        if(LIST_InsertPrev(list1, string[nbInser], strlen(string[nbInser]) + 1) == LIST_NO_ERROR)
        {
            printf("(LIST_InsertPrev) Test d'insertion OK\n");
            nbInser++;
        }
        else
        {
            printf("(LIST_InsertPrev) Test d'insertion KO\n");
            result = 1;
        }

        /* On se repositionner au bon endroit */
        if(LIST_SeekNext(list1) != LIST_NO_ERROR)
        {
            printf("Test module list_s KO : pb deplacement\n");
            return 1;
        }

        if(LIST_InsertPrev(list1, string[nbInser], strlen(string[nbInser]) + 1) == LIST_NO_ERROR)
        {
            printf("(LIST_InsertPrev) Test d'insertion OK\n");
            nbInser++;
        }
        else
        {
            printf("(LIST_InsertPrev) Test d'insertion KO\n");
            result = 1;
        }

        /* On se repositionner au bon endroit */
        if(LIST_SeekNext(list1) != LIST_NO_ERROR)
        {
            printf("Test module list_s KO : pb deplacement\n");
            return 1;
        }
    }

    /* Test de la fonction LIST_IsEmpty() sur une liste non vide */
    {
        if(LIST_IsEmpty(list1) == true)
        {
            printf("(LIST_IsEmpty) Test sur une liste non vide KO\n");
            result = 1;
        }
        else
        {
            printf("(LIST_IsEmpty) Test sur une liste non vide OK\n");
        }
    }

    /* Test de la fonction LIST_Size() sur une liste non vide */
    {
        if(LIST_Size(list1) != nbInser)
        {
            printf("(LIST_Size) Test sur une liste non vide KO\n");
            result = 1;
        }
        else
        {
            printf("(LIST_Size) Test sur une liste vide OK\n");
        }
    }

    /* Test de la fonction LIST_ReadCurrent() */
    {
        data = LIST_ReadCurrent(list1, &error);
        if(data == NULL || error != LIST_NO_ERROR)
        {
            printf("(LIST_ReadCurrent) Test lecture de l'element courant d'une liste KO\n");
            result = 1;
        }
        else
        {
            if(strcmp(data, "Chaine1") == 0)
            {
                printf("(LIST_ReadCurrent) Test lecture de l'element courant d'une liste OK\n");
            }
            else
            {
                printf("(LIST_ReadCurrent) Test lecture de l'element courant d'une liste KO\n");
                result = 1;
            }
        }

        data = LIST_ReadCurrent(list2, &error);
        if(data == NULL && error == LIST_EMPTY_LIST)
        {
            printf("(LIST_ReadCurrent) Test lecture de l'element courant d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_ReadCurrent) Test lecture de l'element courant d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_ReadFirst() */
    {
        data = LIST_ReadFirst(list1, &error);
        if(data == NULL || error != LIST_NO_ERROR)
        {
            printf("(LIST_ReadFirst) Test lecture du premier element d'une liste KO\n");
            result = 1;
        }
        else
        {
            if(strcmp(data, "Chaine2") == 0)
            {
                printf("(LIST_ReadFirst) Test lecture du premier element d'une liste OK\n");
            }
            else
            {
                printf("(LIST_ReadFirst) Test lecture du premier element d'une liste KO\n");
                result = 1;
            }
        }

        data = LIST_ReadFirst(list2, &error);
        if(data == NULL && error == LIST_EMPTY_LIST)
        {
            printf("(LIST_ReadFirst) Test lecture du premier element d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_ReadFirst) Test lecture du premier element d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_ReadLast() */
    {
        data = LIST_ReadLast(list1, &error);
        if(data == NULL || error != LIST_NO_ERROR)
        {
            printf("(LIST_ReadLast) Test lecture du dernier element d'une liste KO\n");
            result = 1;
        }
        else
        {
            if(strcmp(data, "Chaine4") == 0)
            {
                printf("(LIST_ReadLast) Test lecture du dernier element d'une liste OK\n");
            }
            else
            {
                printf("(LIST_ReadLast) Test lecture du dernier element d'une liste KO\n");
                result = 1;
            }
        }

        data = LIST_ReadLast(list2, &error);
        if(data == NULL && error == LIST_EMPTY_LIST)
        {
            printf("(LIST_ReadLast) Test lecture du dernier element d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_ReadLast) Test lecture du dernier element d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_ReadNext() */
    {
        data = LIST_ReadNext(list1, &error);
        if(data == NULL || error != LIST_NO_ERROR)
        {
            printf("(LIST_ReadNext) Test lecture de l'element suivant d'une liste KO\n");
            result = 1;
        }
        else
        {
            if(strcmp(data, "Chaine6") == 0)
            {
                printf("(LIST_ReadNext) Test lecture de l'element suivant d'une liste OK\n");
            }
            else
            {
                printf("(LIST_ReadNext) Test lecture de l'element suivant d'une liste KO\n");
                result = 1;
            }
        }

        data = LIST_ReadNext(list2, &error);
        if(data == NULL && error == LIST_EMPTY_LIST)
        {
            printf("(LIST_ReadNext) Test lecture de l'element suivant d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_ReadNext) Test lecture de l'element suivant d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_ReadPrev() */
    {
        data = LIST_ReadPrev(list1, &error);
        if(data == NULL || error != LIST_NO_ERROR)
        {
            printf("(LIST_ReadPrev) Test lecture de l'element precedent d'une liste KO\n");
            result = 1;
        }
        else
        {
            if(strcmp(data, "Chaine8") == 0)
            {
                printf("(LIST_ReadPrev) Test lecture de l'element precedent d'une liste OK\n");
            }
            else
            {
                printf("(LIST_ReadPrev) Test lecture de l'element precedent d'une liste KO\n");
                result = 1;
            }
        }

        data = LIST_ReadNext(list2, &error);
        if(data == NULL && error == LIST_EMPTY_LIST)
        {
            printf("(LIST_ReadPrev) Test lecture de l'element precedent d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_ReadPrev) Test lecture de l'element precedent d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_SeekFirst() */
    {
        if(LIST_SeekFirst(list1) != LIST_NO_ERROR)
        {
            printf("(LIST_SeekFirst) Test de deplacement vers le premier element d'une liste KO\n");
            result = 1;
        }
        else
        {
            data = LIST_ReadCurrent(list1, &error);
            if(data != NULL && error == LIST_NO_ERROR && strcmp(data, "Chaine2") == 0)
            {
                printf("(LIST_SeekFirst) Test de deplacement vers le premier element d'une liste OK\n");
            }
            else
            {
                printf("(LIST_SeekFirst) Test de deplacement vers le premier element d'une liste KO\n");
                result = 1;
            }
        }

        if(LIST_SeekFirst(list2) == LIST_EMPTY_LIST)
        {
            printf("(LIST_SeekFirst) Test de deplacement vers le premier element d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_SeekFirst) Test de deplacement vers le premier element d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_SeekLast() */
    {
        if(LIST_SeekLast(list1) != LIST_NO_ERROR)
        {
            printf("(LIST_SeekLast) Test de deplacement vers le dernier element d'une liste KO\n");
            result = 1;
        }
        else
        {
            data = LIST_ReadCurrent(list1, &error);
            if(data != NULL && error == LIST_NO_ERROR && strcmp(data, "Chaine4") == 0)
            {
                printf("(LIST_SeekLast) Test de deplacement vers le dernier element d'une liste OK\n");
            }
            else
            {
                printf("(LIST_SeekLast) Test de deplacement vers le dernier element d'une liste KO\n");
                result = 1;
            }
        }

        if(LIST_SeekLast(list2) == LIST_EMPTY_LIST)
        {
            printf("(LIST_SeekLast) Test de deplacement vers le dernier element d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_SeekLast) Test de deplacement vers le dernier element d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_SeekPrev() */
    {
        if(LIST_SeekPrev(list1) != LIST_NO_ERROR)
        {
            printf("(LIST_SeekPrev) Test de deplacement vers l'element precedent d'une liste KO\n");
            result = 1;
        }
        else
        {
            data = LIST_ReadCurrent(list1, &error);
            if(data != NULL && error == LIST_NO_ERROR && strcmp(data, "Chaine3") == 0)
            {
                printf("(LIST_SeekPrev) Test de deplacement vers l'element precedent d'une liste OK\n");
            }
            else
            {
                printf("(LIST_SeekPrev) Test de deplacement vers ll'element precedent d'une liste KO\n");
                result = 1;
            }
        }

        if(LIST_SeekPrev(list2) == LIST_EMPTY_LIST)
        {
            printf("(LIST_SeekPrev) Test de deplacement vers l'element precedent d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_SeekPrev) Test de deplacement vers l'element precedent d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_SeekNext() */
    {
        if(LIST_SeekNext(list1) != LIST_NO_ERROR)
        {
            printf("(LIST_SeekNext) Test de deplacement vers l'element suivant d'une liste KO\n");
            result = 1;
        }
        else
        {
            data = LIST_ReadCurrent(list1, &error);
            if(data != NULL && error == LIST_NO_ERROR && strcmp(data, "Chaine4") == 0)
            {
                printf("(LIST_SeekNext) Test de deplacement vers l'element suivant d'une liste OK\n");
            }
            else
            {
                printf("(LIST_SeekNext) Test de deplacement vers l'element suivant d'une liste KO\n");
                result = 1;
            }
        }

        if(LIST_SeekNext(list2) == LIST_EMPTY_LIST)
        {
            printf("(LIST_SeekNext) Test de deplacement vers l'element suivant d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_SeekNext) Test de deplacement vers l'element suivant d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_IsHead() */
    {
        if(LIST_IsHead(list1) == false)
        {
            LIST_SeekFirst(list1);
            if(LIST_IsHead(list1) == true)
            {
                printf("(LIST_IsHead) Test sur une liste non vide OK\n");
            }
            else
            {
                printf("(LIST_IsHead) Test sur une liste non vide KO\n");
                result = 1;
            }
        }
        else
        {
            printf("(LIST_IsHead) Test sur une liste non vide KO\n");
            result = 1;
        }

        if(LIST_IsHead(list2) == false)
        {
            printf("(LIST_IsHead) Test sur une liste vide OK\n");
        }
        else
        {
            printf("(LIST_IsHead) Test sur une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_IsTail() */
    {
        if(LIST_IsTail(list1) == false)
        {
            LIST_SeekLast(list1);
            if(LIST_IsTail(list1) == true)
            {
                printf("(LIST_IsTail) Test sur une liste non vide OK\n");
            }
            else
            {
                printf("(LIST_IsTail) Test sur une liste non vide KO\n");
                result = 1;
            }
        }
        else
        {
            printf("(LIST_IsTail) Test sur une liste non vide KO\n");
            result = 1;
        }

        if(LIST_IsTail(list2) == false)
        {
            printf("(LIST_IsTail) Test sur une liste vide OK\n");
        }
        else
        {
            printf("(LIST_IsTail) Test sur une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_Clone() */
    {
        cloneList1 = LIST_Clone(list1, &error);
        if(cloneList1 == NULL || error != LIST_NO_ERROR)
        {
            printf("(LIST_Clone) Test duplication d'une liste KO\n");
            result = 1;
        }
        else
        {
            /* On verifie que tout semble bien se passer */
            if(LIST_IsEmpty(cloneList1) == false && LIST_Size(cloneList1) == nbInser)
            {
                printf("(LIST_Clone) Test duplication d'une liste OK\n");
                nbCloneInser = nbInser;
            }
            else
            {
                printf("(LIST_Clone) Test duplication d'une liste KO\n");
                result = 1;
            }
        }

        cloneList2 = LIST_Clone(list2, &error);
        if(cloneList2 == NULL || error != LIST_NO_ERROR)
        {
            printf("(LIST_Clone) Test duplication d'une liste vide KO\n");
            cloneList2 = NULL;
            result = 1;
        }
        else
        {
            /* On verifie que tout semble bien se passer */
            if(LIST_IsEmpty(cloneList2) == true && LIST_Size(cloneList2) == 0)
            {
                printf("(LIST_Clone) Test duplication d'une liste vide OK\n");
            }
            else
            {
                printf("(LIST_Clone) Test duplication d'une liste vide KO\n");
                result = 1;
            }
        }
    }

    /* Test de la fonction LIST_GetFirst() */
    {
        data = LIST_GetFirst(cloneList1, &error);
        if(data == NULL || error != LIST_NO_ERROR)
        {
            printf("(LIST_GetFirst) Test lecture du premier element d'une liste KO\n");
            result = 1;
        }
        else
        {
            nbCloneInser --;
            if(strcmp(data, "Chaine2") == 0)
            {
                printf("(LIST_GetFirst) Test lecture du premier element d'une liste OK\n");
                free((void*)data), data = NULL;
            }
            else
            {
                printf("(LIST_GetFirst) Test lecture du premier element d'une liste KO\n");
                result = 1;
            }
        }

        data = LIST_GetFirst(cloneList2, &error);
        if(data == NULL && error == LIST_EMPTY_LIST)
        {
            printf("(LIST_GetFirst) Test lecture du premier element d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_GetFirst) Test lecture du premier element d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_GetLast() */
    {
        data = LIST_GetLast(cloneList1, &error);
        if(data == NULL || error != LIST_NO_ERROR)
        {
            printf("(LIST_GetLast) Test lecture du dernier element d'une liste KO\n");
            result = 1;
        }
        else
        {
            nbCloneInser --;
            if(strcmp(data, "Chaine4") == 0)
            {
                printf("(LIST_GetLast) Test lecture du dernier element d'une liste OK\n");
                free((void*)data), data = NULL;
            }
            else
            {
                printf("(LIST_GetLast) Test lecture du dernier element d'une liste KO\n");
                result = 1;
            }
        }

        data = LIST_GetLast(cloneList2, &error);
        if(data == NULL && error == LIST_EMPTY_LIST)
        {
            printf("(LIST_GetLast) Test lecture du dernier element d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_GetLast) Test lecture du dernier element d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_GetCurrent() */
    {
        /* On se positionne sur le bon element */
        LIST_SeekFirst(cloneList1);
        LIST_SeekNext(cloneList1);
        LIST_SeekNext(cloneList1);

        data = LIST_GetCurrent(cloneList1, &error);
        if(data == NULL || error != LIST_NO_ERROR)
        {
            printf("(LIST_GetCurrent) Test lecture d'une liste KO\n");
            result = 1;
        }
        else
        {
            nbCloneInser --;
            if(strcmp(data, "Chaine1") == 0)
            {
                printf("(LIST_GetCurrent) Test lecture d'une liste OK\n");
            }
            else
            {
                printf("(LIST_GetCurrent) Test lecture d'une liste KO\n");
                result = 1;
            }
        }

        data = LIST_GetCurrent(cloneList2, &error);
        if(data == NULL && error == LIST_EMPTY_LIST)
        {
            printf("(LIST_GetCurrent) Test lecture d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_GetCurrent) Test lecture d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_GetNext() */
    {
        data = LIST_GetNext(cloneList1, &error);
        if(data == NULL || error != LIST_NO_ERROR)
        {
            printf("(LIST_GetNext) Test lecture d'une liste KO\n");
            result = 1;
        }
        else
        {
            nbCloneInser --;
            if(strcmp(data, "Chaine5") == 0)
            {
                printf("(LIST_GetNext) Test lecture d'une liste OK\n");
            }
            else
            {
                printf("(LIST_GetNext) Test lecture d'une liste KO\n");
                result = 1;
            }
        }

        data = LIST_GetNext(cloneList2, &error);
        if(data == NULL && error == LIST_EMPTY_LIST)
        {
            printf("(LIST_GetNext) Test lecture d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_GetNext) Test lecture d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_GetPrev() */
    {
        data = LIST_GetPrev(cloneList1, &error);
        if(data == NULL || error != LIST_NO_ERROR)
        {
            printf("(LIST_GetPrev) Test lecture d'une liste KO\n");
            result = 1;
        }
        else
        {
            nbCloneInser --;
            if(strcmp(data, "Chaine8") == 0)
            {
                printf("(LIST_GetPrev) Test lecture d'une liste OK\n");
                free((void*)data), data = NULL;
            }
            else
            {
                printf("(LIST_GetPrev) Test lecture d'une liste KO\n");
                result = 1;
            }
        }

        data = LIST_GetPrev(cloneList2, &error);
        if(data == NULL && error == LIST_EMPTY_LIST)
        {
            printf("(LIST_GetPrev) Test lecture d'une liste vide OK\n");
        }
        else
        {
            printf("(LIST_GetPrev) Test lecture d'une liste vide KO\n");
            result = 1;
        }
    }

    /* On verifie que les elements ont bien ete enleve */
    {
        if(LIST_Size(cloneList1) != nbCloneInser)
        {
            printf("(LIST_GetXXXX) La taille de la liste est incorrecte\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_RemoveFirst() */
    {
        error = LIST_RemoveFirst(list1);
        if(error != LIST_NO_ERROR)
        {
            printf("(LIST_RemoveFirst) Test suppression dans une liste KO\n");
            result = 1;
        }
        else
        {
            nbInser --;
            printf("(LIST_RemoveFirst) Test suppression dans une liste OK\n");
        }

        error = LIST_RemoveFirst(cloneList2);
        if(error == LIST_EMPTY_LIST)
        {
            printf("(LIST_RemoveFirst) Test suppression dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveFirst) Test suppression dans une liste KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_RemoveLast() */
    {
        error = LIST_RemoveLast(list1);
        if(error != LIST_NO_ERROR)
        {
            printf("(LIST_RemoveLast) Test suppression dans une liste KO\n");
            result = 1;
        }
        else
        {
            nbInser --;
            printf("(LIST_RemoveLast) Test suppression dans une liste OK\n");
        }

        error = LIST_RemoveLast(cloneList2);
        if(error == LIST_EMPTY_LIST)
        {
            printf("(LIST_RemoveLast) Test suppression dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveLast) Test suppression dans une liste KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_RemoveCurrent() */
    {
        /* On se positionne sur le bon element */
        LIST_SeekFirst(list1);
        LIST_SeekNext(list1);
        LIST_SeekNext(list1);

        error = LIST_RemoveCurrent(list1);
        if(error != LIST_NO_ERROR)
        {
            printf("(LIST_RemoveCurrent) Test suppression dans une liste KO\n");
            result = 1;
        }
        else
        {
            nbInser --;
            printf("(LIST_RemoveCurrent) Test suppression dans une liste OK\n");
        }

        error = LIST_RemoveCurrent(cloneList2);
        if(error == LIST_EMPTY_LIST)
        {
            printf("(LIST_RemoveCurrent) Test suppression dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveCurrent) Test suppression dans une liste KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_RemoveNext() */
    {
        error = LIST_RemoveNext(list1);
        if(error != LIST_NO_ERROR)
        {
            printf("(LIST_RemoveNext) Test suppression dans une liste KO\n");
            result = 1;
        }
        else
        {
            nbInser --;
            printf("(LIST_RemoveNext) Test suppression dans une liste OK\n");
        }

        error = LIST_RemoveNext(cloneList2);
        if(error == LIST_EMPTY_LIST)
        {
            printf("(LIST_RemoveNext) Test suppression dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveNext) Test suppression dans une liste KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_RemovePrev() */
    {
        error = LIST_RemovePrev(list1);
        if(error != LIST_NO_ERROR)
        {
            printf("(LIST_RemovePrev) Test suppression dans une liste KO\n");
            result = 1;
        }
        else
        {
            nbInser --;
            printf("(LIST_RemovePrev) Test suppression dans une liste OK\n");
        }

        error = LIST_RemovePrev(cloneList2);
        if(error == LIST_EMPTY_LIST)
        {
            printf("(LIST_RemovePrev) Test suppression dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemovePrev) Test suppression dans une liste KO\n");
            result = 1;
        }
    }

    /* On verifie que les elements ont bien ete enleve */
    {
        if(LIST_Size(list1) != nbInser)
        {
            printf("(LIST_RemoveXXXX) La taille de la liste est incorrecte\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_Destroy() */
    {
        LIST_Destroy(list1);
        LIST_Destroy(list2);
        LIST_Destroy(cloneList1);
        LIST_Destroy(cloneList2);

        printf("(LIST_Destroy) Test de destruction d'une liste OK\n");
    }

    /* Creation des listes de test pour la recherche */
    {
        list1 = LIST_Create(NULL, &error);
        list2 = LIST_Create(NULL, &error);
        if(list1 == NULL || list2 == NULL)
        {
            printf("Test module liste : pb creations liste de test\n");
            return 1;
        }

        for(nbInser = 0; nbInser < sizeof(searchedString) / sizeof(searchedString[0]); nbInser++)
        {
            if(LIST_InsertLast(list1, searchedString[nbInser], strlen(searchedString[nbInser]) + 1) != LIST_NO_ERROR)
            {
                printf("Test module liste : pb creations liste de test\n");
                return 1;
            }
        }

        cloneList1 = LIST_Clone(list1, &error);
        if(cloneList1 == NULL || error != LIST_NO_ERROR)
        {
            printf("Test module liste : pb creations liste de test\n");
            result = 1;
        }

        nbCloneInser = nbInser;

        LIST_SeekFirst(list1);
        LIST_SeekNext(list1);
        LIST_SeekNext(list1);
        LIST_SeekNext(list1);
        LIST_SeekNext(list1);

        LIST_SeekFirst(cloneList1);
        LIST_SeekNext(cloneList1);
        LIST_SeekNext(cloneList1);
        LIST_SeekNext(cloneList1);
        LIST_SeekNext(cloneList1);
    }

    /* Test de la fonction LIST_SetCmp() */
    {
        LIST_SetCmp(list1, TstCompar);
        printf("(LIST_SetCmp) Initialisation de la fonction de comparaison OK\n");
    }

    /* Test de la fonction LIST_SearchData() */
    {
        if(LIST_SearchData(list1, "ChaineB") == LIST_NO_ERROR)
        {
            printf("(LIST_SearchData) Test de recherche dans une liste OK\n");
        }
        else
        {
            printf("(LIST_SearchData) Test de recherche dans une liste KO\n");
            result = 1;
        }

        if(LIST_SearchData(list1, "ChaineA") == LIST_CELL_NOT_FOUND)
        {
            printf("(LIST_SearchData) Test de recherche d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(LIST_SearchData) Test de recherche d'un element non present dans une liste KO\n");
            result = 1;
        }

        if(LIST_SearchData(list2, "ChaineB") == LIST_EMPTY_LIST)
        {
            printf("(LIST_SearchData) Test de recherche dans une liste vide OK\n");
        }
        else
        {
            printf("(LIST_SearchData) Test de recherche dans une liste vide KO\n");
            result = 1;
        }

        if(LIST_SearchData(cloneList1, "ChaineB") == LIST_NO_COMP_FONCTION)
        {
            printf("(LIST_SearchData) Test de recherche dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(LIST_SearchData) Test de recherche dans une liste sans comparateur KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_SearchDataFct() */
    {
        if(LIST_SearchDataFct(list1, "ChaineB", TstCompar) == LIST_NO_ERROR)
        {
            printf("(LIST_SearchDataFct) Test de recherche dans une liste OK\n");
        }
        else
        {
            printf("(LIST_SearchDataFct) Test de recherche dans une liste KO\n");
            result = 1;
        }

        if(LIST_SearchDataFct(list1, "ChaineA", TstCompar) == LIST_CELL_NOT_FOUND)
        {
            printf("(LIST_SearchDataFct) Test de recherche d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(LIST_SearchDataFct) Test de recherche d'un element non present dans une liste KO\n");
            result = 1;
        }

        if(LIST_SearchDataFct(list2, "ChaineB", TstCompar) == LIST_EMPTY_LIST)
        {
            printf("(LIST_SearchDataFct) Test de recherche dans une liste vide OK\n");
        }
        else
        {
            printf("(LIST_SearchDataFct) Test de recherche dans une liste vide KO\n");
            result = 1;
        }

        if(LIST_SearchDataFct(cloneList1, "ChaineB", TstCompar) == LIST_NO_ERROR)
        {
            printf("(LIST_SearchDataFct) Test de recherche dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(LIST_SearchDataFct) Test de recherche dans une liste sans comparateur KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_SearchDataRev() */
    {
        if(LIST_SearchDataRev(list1, "ChaineD") == LIST_NO_ERROR)
        {
            printf("(LIST_SearchDataRev) Test de recherche dans une liste OK\n");
        }
        else
        {
            printf("(LIST_SearchDataRev) Test de recherche dans une liste KO\n");
            result = 1;
        }

        if(LIST_SearchDataRev(list1, "ChaineC") == LIST_CELL_NOT_FOUND)
        {
            printf("(LIST_SearchDataRev) Test de recherche d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(LIST_SearchDataRev) Test de recherche d'un element non present dans une liste KO\n");
            result = 1;
        }

        if(LIST_SearchDataRev(list2, "ChaineD") == LIST_EMPTY_LIST)
        {
            printf("(LIST_SearchDataRev) Test de recherche dans une liste vide OK\n");
        }
        else
        {
            printf("(LIST_SearchDataRev) Test de recherche dans une liste vide KO\n");
            result = 1;
        }

        if(LIST_SearchDataRev(cloneList1, "ChaineD") == LIST_NO_COMP_FONCTION)
        {
            printf("(LIST_SearchDataRev) Test de recherche dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(LIST_SearchDataRev) Test de recherche dans une liste sans comparateur KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_SearchDataRevFct() */
    {
        if(LIST_SearchDataRevFct(list1, "ChaineD", TstCompar) == LIST_NO_ERROR)
        {
            printf("(LIST_SearchDataRevFct) Test de recherche dans une liste OK\n");
        }
        else
        {
            printf("(LIST_SearchDataRevFct) Test de recherche dans une liste KO\n");
            result = 1;
        }

        if(LIST_SearchDataRevFct(list1, "ChaineC", TstCompar) == LIST_CELL_NOT_FOUND)
        {
            printf("(LIST_SearchDataRevFct) Test de recherche d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(LIST_SearchDataRevFct) Test de recherche d'un element non present dans une liste KO\n");
            result = 1;
        }

        if(LIST_SearchDataRevFct(list2, "ChaineD", TstCompar) == LIST_EMPTY_LIST)
        {
            printf("(LIST_SearchDataRevFct) Test de recherche dans une liste vide OK\n");
        }
        else
        {
            printf("(LIST_SearchDataRevFct) Test de recherche dans une liste vide KO\n");
            result = 1;
        }

        if(LIST_SearchDataRevFct(cloneList1, "ChaineD", TstCompar) == LIST_NO_ERROR)
        {
            printf("(LIST_SearchDataRevFct) Test de recherche dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(LIST_SearchDataRevFct) Test de recherche dans une liste sans comparateur KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_RemoveData() */
    {
        if(LIST_RemoveData(list1, "ChaineB") == LIST_NO_ERROR)
        {
            printf("(LIST_RemoveData) Test de suppression dans une liste OK\n");
            nbInser--;
        }
        else
        {
            printf("(LIST_RemoveData) Test de suppression dans une liste KO\n");
            result = 1;
        }

        if(LIST_RemoveData(list1, "ChaineA") == LIST_CELL_NOT_FOUND)
        {
            printf("(LIST_RemoveData) Test de suppression d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveData) Test de suppression d'un element non present dans une liste KO\n");
            result = 1;
        }

        if(LIST_RemoveData(list2, "ChaineB") == LIST_EMPTY_LIST)
        {
            printf("(LIST_RemoveData) Test de suppression dans une liste vide OK\n");
        }
        else
        {
            printf("(LIST_RemoveData) Test de suppression dans une liste vide KO\n");
            result = 1;
        }

        if(LIST_RemoveData(cloneList1, "ChaineB") == LIST_NO_COMP_FONCTION)
        {
            printf("(LIST_RemoveData) Test de suppression dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(LIST_RemoveData) Test de suppression dans une liste sans comparateur KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_RemoveDataFct() */
    {
        if(LIST_RemoveDataFct(list1, "ChaineB", TstCompar) == LIST_NO_ERROR)
        {
            printf("(LIST_RemoveDataFct) Test de suppression dans une liste OK\n");
            nbInser--;
        }
        else
        {
            printf("(LIST_RemoveDataFct) Test de suppression dans une liste KO\n");
            result = 1;
        }

        if(LIST_RemoveDataFct(list1, "ChaineA", TstCompar) == LIST_CELL_NOT_FOUND)
        {
            printf("(LIST_RemoveDataFct) Test de suppression d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveDataFct) Test de suppression d'un element non present dans une liste KO\n");
            result = 1;
        }

        if(LIST_RemoveDataFct(list2, "ChaineB", TstCompar) == LIST_EMPTY_LIST)
        {
            printf("(LIST_RemoveDataFct) Test de suppression dans une liste vide OK\n");
        }
        else
        {
            printf("(LIST_RemoveDataFct) Test de suppression dans une liste vide KO\n");
            result = 1;
        }

        if(LIST_RemoveDataFct(cloneList1, "ChaineB", TstCompar) == LIST_NO_ERROR)
        {
            printf("(LIST_RemoveDataFct) Test de suppression dans une liste sans comparateur OK\n");
            nbCloneInser--;
        }
        else
        {
            printf("(LIST_RemoveDataFct) Test de suppression dans une liste sans comparateur KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_RemoveDataRev() */
    {
        if(LIST_RemoveDataRev(list1, "ChaineB") == LIST_NO_ERROR)
        {
            printf("(LIST_RemoveDataRev) Test de suppression dans une liste OK\n");
            nbInser--;
        }
        else
        {
            printf("(LIST_RemoveDataRev) Test de suppression dans une liste KO\n");
            result = 1;
        }

        if(LIST_RemoveDataRev(list1, "ChaineC") == LIST_CELL_NOT_FOUND)
        {
            printf("(LIST_RemoveDataRev) Test de suppression d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveDataRev) Test de suppression d'un element non present dans une liste KO\n");
            result = 1;
        }

        if(LIST_RemoveDataRev(list2, "ChaineB") == LIST_EMPTY_LIST)
        {
            printf("(LIST_RemoveDataRev) Test de suppression dans une liste vide OK\n");
        }
        else
        {
            printf("(LIST_RemoveDataRev) Test de suppression dans une liste vide KO\n");
            result = 1;
        }

        if(LIST_RemoveDataRev(cloneList1, "ChaineB") == LIST_NO_COMP_FONCTION)
        {
            printf("(LIST_RemoveDataRev) Test de suppression dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(LIST_RemoveDataRev) Test de suppression dans une liste sans comparateur KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_RemoveDataRevFct() */
    {
        if(LIST_RemoveDataRevFct(list1, "ChaineB", TstCompar) == LIST_NO_ERROR)
        {
            printf("(LIST_RemoveDataRevFct) Test de suppression dans une liste OK\n");
            nbInser--;
        }
        else
        {
            printf("(LIST_RemoveDataRevFct) Test de suppression dans une liste KO\n");
            result = 1;
        }

        if(LIST_RemoveDataRevFct(list1, "ChaineC", TstCompar) == LIST_CELL_NOT_FOUND)
        {
            printf("(LIST_RemoveDataRevFct) Test de suppression d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveDataRevFct) Test de suppression d'un element non present dans une liste KO\n");
            result = 1;
        }

        if(LIST_RemoveDataRevFct(list2, "ChaineB", TstCompar) == LIST_EMPTY_LIST)
        {
            printf("(LIST_RemoveDataRevFct) Test de suppression dans une liste vide OK\n");
        }
        else
        {
            printf("(LIST_RemoveDataRevFct) Test de suppression dans une liste vide KO\n");
            result = 1;
        }

        if(LIST_RemoveDataRevFct(cloneList1, "ChaineB", TstCompar) == LIST_NO_ERROR)
        {
            printf("(LIST_RemoveDataRevFct) Test de suppression dans une liste sans comparateur OK\n");
            nbCloneInser--;
        }
        else
        {
            printf("(LIST_RemoveDataRevFct) Test de suppression dans une liste sans comparateur KO\n");
            result = 1;
        }
    }

    /* On verifie que les elements ont bien ete enleve */
    {
        if(LIST_Size(list1) != nbInser)
        {
            printf("(LIST_RemoveDataXXXX) La taille de la liste list1 est incorrecte\n");
            result = 1;
        }


        if(LIST_Size(cloneList1) != nbCloneInser)
        {
            printf("(LIST_RemoveDataXXXX) La taille de la liste cloneList1 est incorrecte\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_RemoveAllData() */
    {
        if(LIST_RemoveAllData(list1, "ChaineB") == LIST_NO_ERROR)
        {
            printf("(LIST_RemoveAllData) Test de suppression dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveAllData) Test de suppression dans une liste KO\n");
            result = 1;
        }

        if(LIST_RemoveAllData(list1, "ChaineZ") == LIST_NO_ERROR)
        {
            printf("(LIST_RemoveAllData) Test de suppression d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveAllData) Test de suppression d'un element non present dans une liste KO\n");
            result = 1;
        }

        if(LIST_RemoveAllData(list2, "ChaineB") == LIST_EMPTY_LIST)
        {
            printf("(LIST_RemoveAllData) Test de suppression dans une liste vide OK\n");
        }
        else
        {
            printf("(LIST_RemoveAllData) Test de suppression dans une liste vide KO\n");
            result = 1;
        }

        if(LIST_RemoveAllData(cloneList1, "ChaineB") == LIST_NO_COMP_FONCTION)
        {
            printf("(LIST_RemoveAllData) Test de suppression dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(LIST_RemoveAllData) Test de suppression dans une liste sans comparateur KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_RemoveDataFct() */
    {
        if(LIST_RemoveAllDataFct(list1, "ChaineB", TstCompar) == LIST_NO_ERROR)
        {
            printf("(LIST_RemoveAllDataFct) Test de suppression dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveAllDataFct) Test de suppression dans une liste KO\n");
            result = 1;
        }

        if(LIST_RemoveAllDataFct(list1, "ChaineZ", TstCompar) == LIST_NO_ERROR)
        {
            printf("(LIST_RemoveAllDataFct) Test de suppression d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(LIST_RemoveAllDataFct) Test de suppression d'un element non present dans une liste KO\n");
            result = 1;
        }

        if(LIST_RemoveAllDataFct(list2, "ChaineB", TstCompar) == LIST_EMPTY_LIST)
        {
            printf("(LIST_RemoveAllDataFct) Test de suppression dans une liste vide OK\n");
        }
        else
        {
            printf("(LIST_RemoveAllDataFct) Test de suppression dans une liste vide KO\n");
            result = 1;
        }

        if(LIST_RemoveAllDataFct(cloneList1, "ChaineB", TstCompar) == LIST_NO_ERROR)
        {
            printf("(LIST_RemoveAllDataFct) Test de suppression dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(LIST_RemoveAllDataFct) Test de suppression dans une liste sans comparateur KO\n");
            result = 1;
        }
    }

    /* On verifie que les elements ont bien ete enleve */
    {
        if(LIST_Size(list1) != 3)
        {
            printf("(LIST_RemoveAllDataXXXX) La taille de la liste list1 est incorrecte\n");
            result = 1;
        }

        if(LIST_Size(cloneList1) != 3)
        {
            printf("(LIST_RemoveAllDataXXXX) La taille de la liste cloneList1 est incorrecte\n");
            result = 1;
        }
    }

    /* Desctruction des listes */
    {
        LIST_Destroy(list1);
        LIST_Destroy(list2);
        LIST_Destroy(cloneList1);
    }

    return result;
}
