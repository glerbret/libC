#include "bool.h"
#include "clist.h"
#include "test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int TstCompar(const void* data1, const void* data2)
{
    return strcmp((const char*)data1, (const char*)data2);
}

int TstCList(void)
{
    int result = 0;
    size_t nbInser = 0;
    size_t nbCloneInser = 0;
    clist_s* list1;
    clist_s* list2;
    clist_s* cloneList1;
    clist_s* cloneList2;
    CLIST_Error_e error;
    const char* data;
    const char* string[] =
    {
        "Chaine1",
        "Chaine2",
        "Chaine3",
        "Chaine4",
        "Chaine5",
        "Chaine6"
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

    printf("\nTest de \"%s\"\n", CLIST_Identifier());

    /* Test de la fonction CLIST_Init() */
    {
        list1 = CLIST_Create(NULL, &error);
        if(list1 == NULL || error != CLIST_NO_ERROR)
        {
            printf("(CLIST_Create) Test creation d'une liste sans fonction de comparaison KO\n");
            return 1;
        }
        else
        {
            printf("(CLIST_Create) Test creation d'une liste sans fonction de comparaison OK\n");
        }

        list2 = CLIST_Create(NULL, &error);
        if(list2 == NULL || error != CLIST_NO_ERROR)
        {
            printf("(CLIST_Create) Test creation d'une liste avec fonction de comparaison KO\n");
            return 1;
        }
        else
        {
            printf("(CLIST_Create) Test creation d'une liste avec fonction de comparaison OK\n");
        }
    }

    /* Test de la fonction CLIST_IsEmpty() sur une liste vide */
    {
        if(CLIST_IsEmpty(list1) == false)
        {
            printf("(CLIST_IsEmpty) Test sur une liste vide KO\n");
            result = 1;
        }
        else
        {
            printf("(CLIST_IsEmpty) Test sur une liste vide OK\n");
        }
    }

    /* Test de la fonction CLIST_Size() sur une liste vide */
    {
        if(CLIST_Size(list1) != 0)
        {
            printf("(CLIST_Size) Test sur une liste vide KO\n");
            result = 1;
        }
        else
        {
            printf("(CLIST_Size) Test sur une liste vide OK\n");
        }
    }

    /* Test de la fonction CLIST_InsertFirst() */
    {
        if(CLIST_InsertFirst(list1, string[nbInser], strlen(string[nbInser]) + 1) == CLIST_NO_ERROR)
        {
            printf("(CLIST_InsertFirst) Test d'insertion OK\n");
            nbInser++;
        }
        else
        {
            printf("(CLIST_InsertFirst) Test d'insertion KO\n");
            result = 1;
        }

        if(CLIST_InsertFirst(list1, string[nbInser], strlen(string[nbInser]) + 1) == CLIST_NO_ERROR)
        {
            printf("(CLIST_InsertFirst) Test d'insertion OK\n");
            nbInser++;
        }
        else
        {
            printf("(CLIST_InsertFirst) Test d'insertion KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_InsertNext() */
    {
        if(CLIST_InsertNext(list1, string[nbInser], strlen(string[nbInser]) + 1) == CLIST_NO_ERROR)
        {
            printf("(CLIST_InsertNext) Test d'insertion OK\n");
            nbInser++;
        }
        else
        {
            printf("(CLIST_InsertNext) Test d'insertion KO\n");
            result = 1;
        }

        if(CLIST_InsertNext(list1, string[nbInser], strlen(string[nbInser]) + 1) == CLIST_NO_ERROR)
        {
            printf("(CLIST_InsertNext) Test d'insertion OK\n");
            nbInser++;
        }
        else
        {
            printf("(CLIST_InsertNext) Test d'insertion KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_InsertPrev() */
    {
        if(CLIST_InsertPrev(list1, string[nbInser], strlen(string[nbInser]) + 1) == CLIST_NO_ERROR)
        {
            printf("(CLIST_InsertPrev) Test d'insertion OK\n");
            nbInser++;
        }
        else
        {
            printf("(CLIST_InsertPrev) Test d'insertion KO\n");
            result = 1;
        }

        if(CLIST_InsertPrev(list1, string[nbInser], strlen(string[nbInser]) + 1) == CLIST_NO_ERROR)
        {
            printf("(CLIST_InsertPrev) Test d'insertion OK\n");
            nbInser++;
        }
        else
        {
            printf("(CLIST_InsertPrev) Test d'insertion KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_IsEmpty() sur une liste non vide */
    {
        if(CLIST_IsEmpty(list1) == true)
        {
            printf("(CLIST_IsEmpty) Test sur une liste non vide KO\n");
            result = 1;
        }
        else
        {
            printf("(CLIST_IsEmpty) Test sur une liste non vide OK\n");
        }
    }

    /* Test de la fonction CLIST_Size() sur une liste non vide */
    {
        if(CLIST_Size(list1) != nbInser)
        {
            printf("(CLIST_Size) Test sur une liste non vide KO\n");
            result = 1;
        }
        else
        {
            printf("(CLIST_Size) Test sur une liste vide OK\n");
        }
    }

    /* Test de la fonction CLIST_ReadCurrent() */
    {
        data = CLIST_ReadCurrent(list1, &error);
        if(data == NULL || error != CLIST_NO_ERROR)
        {
            printf("(CLIST_ReadCurrent) Test lecture de l'element courant d'une liste KO\n");
            result = 1;
        }
        else
        {
            if(strcmp(data, "Chaine6") == 0)
            {
                printf("(CLIST_ReadCurrent) Test lecture de l'element courant d'une liste OK\n");
            }
            else
            {
                printf("(CLIST_ReadCurrent) Test lecture de l'element courant d'une liste KO\n");
                result = 1;
            }
        }

        data = CLIST_ReadCurrent(list2, &error);
        if(data == NULL && error == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_ReadCurrent) Test lecture de l'element courant d'une liste vide OK\n");
        }
        else
        {
            printf("(CLIST_ReadCurrent) Test lecture de l'element courant d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_ReadFirst() */
    {
        data = CLIST_ReadFirst(list1, &error);
        if(data == NULL || error != CLIST_NO_ERROR)
        {
            printf("(CLIST_ReadFirst) Test lecture du premier element d'une liste KO\n");
            result = 1;
        }
        else
        {
            if(strcmp(data, "Chaine2") == 0)
            {
                printf("(CLIST_ReadFirst) Test lecture du premier element d'une liste OK\n");
            }
            else
            {
                printf("(CLIST_ReadFirst) Test lecture du premier element d'une liste KO\n");
                result = 1;
            }
        }

        data = CLIST_ReadFirst(list2, &error);
        if(data == NULL && error == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_ReadFirst) Test lecture du premier element d'une liste vide OK\n");
        }
        else
        {
            printf("(CLIST_ReadFirst) Test lecture du premier element d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction LIST_ReadNext() */
    {
        data = CLIST_ReadNext(list1, &error);
        if(data == NULL || error != CLIST_NO_ERROR)
        {
            printf("(CLIST_ReadNext) Test lecture de l'element suivant d'une liste KO\n");
            result = 1;
        }
        else
        {
            if(strcmp(data, "Chaine5") == 0)
            {
                printf("(CLIST_ReadNext) Test lecture de l'element suivant d'une liste OK\n");
            }
            else
            {
                printf("(CLIST_ReadNext) Test lecture de l'element suivant d'une liste KO\n");
                result = 1;
            }
        }

        data = CLIST_ReadNext(list2, &error);
        if(data == NULL && error == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_ReadNext) Test lecture de l'element suivant d'une liste vide OK\n");
        }
        else
        {
            printf("(CLIST_ReadNext) Test lecture de l'element suivant d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_ReadPrev() */
    {
        data = CLIST_ReadPrev(list1, &error);
        if(data == NULL || error != CLIST_NO_ERROR)
        {
            printf("(CLIST_ReadPrev) Test lecture de l'element precedent d'une liste KO\n");
            result = 1;
        }
        else
        {
            if(strcmp(data, "Chaine3") == 0)
            {
                printf("(CLIST_ReadPrev) Test lecture de l'element precedent d'une liste OK\n");
            }
            else
            {
                printf("(CLIST_ReadPrev) Test lecture de l'element precedent d'une liste KO\n");
                result = 1;
            }
        }

        data = CLIST_ReadNext(list2, &error);
        if(data == NULL && error == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_ReadPrev) Test lecture de l'element precedent d'une liste vide OK\n");
        }
        else
        {
            printf("(CLIST_ReadPrev) Test lecture de l'element precedent d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_SeekFirst() */
    {
        if(CLIST_SeekFirst(list1) != CLIST_NO_ERROR)
        {
            printf("(CLIST_SeekFirst) Test de deplacement vers le premier element d'une liste KO\n");
            result = 1;
        }
        else
        {
            data = CLIST_ReadCurrent(list1, &error);
            if(data != NULL && error == CLIST_NO_ERROR && strcmp(data, "Chaine2") == 0)
            {
                printf("(CLIST_SeekFirst) Test de deplacement vers le premier element d'une liste OK\n");
            }
            else
            {
                printf("(CLIST_SeekFirst) Test de deplacement vers le premier element d'une liste KO\n");
                result = 1;
            }
        }

        if(CLIST_SeekFirst(list2) == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_SeekFirst) Test de deplacement vers le premier element d'une liste vide OK\n");
        }
        else
        {
            printf("(CLIST_SeekFirst) Test de deplacement vers le premier element d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_SeekPrev() */
    {
        if(CLIST_SeekPrev(list1) != CLIST_NO_ERROR)
        {
            printf("(CLIST_SeekPrev) Test de deplacement vers l'element precedent d'une liste KO\n");
            result = 1;
        }
        else
        {
            data = CLIST_ReadCurrent(list1, &error);
            if(data != NULL && error == CLIST_NO_ERROR && strcmp(data, "Chaine1") == 0)
            {
                printf("(CLIST_SeekPrev) Test de deplacement vers l'element precedent d'une liste OK\n");
            }
            else
            {
                printf("(CLIST_SeekPrev) Test de deplacement vers ll'element precedent d'une liste KO\n");
                result = 1;
            }
        }

        if(CLIST_SeekPrev(list2) == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_SeekPrev) Test de deplacement vers l'element precedent d'une liste vide OK\n");
        }
        else
        {
            printf("(CLIST_SeekPrev) Test de deplacement vers l'element precedent d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_SeekNext() */
    {
        if(CLIST_SeekNext(list1) != CLIST_NO_ERROR)
        {
            printf("(CLIST_SeekNext) Test de deplacement vers l'element suivant d'une liste KO\n");
            result = 1;
        }
        else
        {
            data = CLIST_ReadCurrent(list1, &error);
            if(data != NULL && error == CLIST_NO_ERROR && strcmp(data, "Chaine2") == 0)
            {
                printf("(CLIST_SeekNext) Test de deplacement vers l'element suivant d'une liste OK\n");
            }
            else
            {
                printf("(CLIST_SeekNext) Test de deplacement vers l'element suivant d'une liste KO\n");
                result = 1;
            }
        }

        if(CLIST_SeekNext(list2) == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_SeekNext) Test de deplacement vers l'element suivant d'une liste vide OK\n");
        }
        else
        {
            printf("(CLIST_SeekNext) Test de deplacement vers l'element suivant d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_IsHead() */
    {
        /* on se positionne au bon endroit */
        CLIST_SeekNext(list1);

        if(CLIST_IsHead(list1) == false)
        {
            CLIST_SeekFirst(list1);
            if(CLIST_IsHead(list1) == true)
            {
                printf("(CLIST_IsHead) Test sur une liste non vide OK\n");
            }
            else
            {
                printf("(CLIST_IsHead) Test sur une liste non vide KO\n");
                result = 1;
            }
        }
        else
        {
            printf("(CLIST_IsHead) Test sur une liste non vide KO\n");
            result = 1;
        }

        if(CLIST_IsHead(list2) == false)
        {
            printf("(CLIST_IsHead) Test sur une liste vide OK\n");
        }
        else
        {
            printf("(CLIST_IsHead) Test sur une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_Clone() */
    {
        cloneList1 = CLIST_Clone(list1, &error);
        if(cloneList1 == NULL || error != CLIST_NO_ERROR)
        {
            printf("(CLIST_Clone) Test duplication d'une liste KO\n");
            result = 1;
        }
        else
        {
            /* On verifie que tout semble bien se passer */
            if(CLIST_IsEmpty(cloneList1) == false && CLIST_Size(cloneList1) == nbInser)
            {
                printf("(CLIST_Clone) Test duplication d'une liste OK\n");
                nbCloneInser = nbInser;
            }
            else
            {
                printf("(CLIST_Clone) Test duplication d'une liste KO\n");
                result = 1;
            }
        }

        cloneList2 = CLIST_Clone(list2, &error);
        if(cloneList2 == NULL || error != CLIST_NO_ERROR)
        {
            printf("(CLIST_Clone) Test duplication d'une liste vide KO\n");
            cloneList2 = NULL;
            result = 1;
        }
        else
        {
            /* On verifie que tout semble bien se passer */
            if(CLIST_IsEmpty(cloneList2) == true && CLIST_Size(cloneList2) == 0)
            {
                printf("(CLIST_Clone) Test duplication d'une liste vide OK\n");
            }
            else
            {
                printf("(CLIST_Clone) Test duplication d'une liste vide KO\n");
                result = 1;
            }
        }
    }

    /* Test de la fonction CLIST_GetFirst() */
    {
        data = CLIST_GetFirst(cloneList1, &error);
        if(data == NULL || error != CLIST_NO_ERROR)
        {
            printf("(CLIST_GetFirst) Test lecture du premier element d'une liste KO\n");
            result = 1;
        }
        else
        {
            nbCloneInser --;
            if(strcmp(data, "Chaine2") == 0)
            {
                printf("(CLIST_GetFirst) Test lecture du premier element d'une liste OK\n");
                free((void*)data), data = NULL;
            }
            else
            {
                printf("(CLIST_GetFirst) Test lecture du premier element d'une liste KO\n");
                result = 1;
            }
        }

        data = CLIST_GetFirst(cloneList2, &error);
        if(data == NULL && error == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_GetFirst) Test lecture du premier element d'une liste vide OK\n");
        }
        else
        {
            printf("(CLIST_GetFirst) Test lecture du premier element d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_GetCurrent() */
    {
        data = CLIST_GetCurrent(cloneList1, &error);
        if(data == NULL || error != CLIST_NO_ERROR)
        {
            printf("(CLIST_GetCurrent) Test lecture d'une liste KO\n");
            result = 1;
        }
        else
        {
            nbCloneInser --;
            if(strcmp(data, "Chaine3") == 0)
            {
                printf("(CLIST_GetCurrent) Test lecture d'une liste OK\n");
            }
            else
            {
                printf("(CLIST_GetCurrent) Test lecture d'une liste KO\n");
                result = 1;
            }
        }

        data = CLIST_GetCurrent(cloneList2, &error);
        if(data == NULL && error == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_GetCurrent) Test lecture d'une liste vide OK\n");
        }
        else
        {
            printf("(CLIST_GetCurrent) Test lecture d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_GetNext() */
    {
        data = CLIST_GetNext(cloneList1, &error);
        if(data == NULL || error != CLIST_NO_ERROR)
        {
            printf("(CLIST_GetNext) Test lecture d'une liste KO\n");
            result = 1;
        }
        else
        {
            nbCloneInser --;
            if(strcmp(data, "Chaine5") == 0)
            {
                printf("(CLIST_GetNext) Test lecture d'une liste OK\n");
            }
            else
            {
                printf("(CLIST_GetNext) Test lecture d'une liste KO\n");
                result = 1;
            }
        }

        data = CLIST_GetNext(cloneList2, &error);
        if(data == NULL && error == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_GetNext) Test lecture d'une liste vide OK\n");
        }
        else
        {
            printf("(CLIST_GetNext) Test lecture d'une liste vide KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_GetPrev() */
    {
        data = CLIST_GetPrev(cloneList1, &error);
        if(data == NULL || error != CLIST_NO_ERROR)
        {
            printf("(CLIST_GetPrev) Test lecture d'une liste KO\n");
            result = 1;
        }
        else
        {
            nbCloneInser --;
            if(strcmp(data, "Chaine1") == 0)
            {
                printf("(CLIST_GetPrev) Test lecture d'une liste OK\n");
            }
            else
            {
                printf("(CLIST_GetPrev) Test lecture d'une liste KO\n");
                result = 1;
            }
        }

        data = CLIST_GetPrev(cloneList2, &error);
        if(data == NULL && error == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_GetPrev) Test lecture d'une liste vide OK\n");
        }
        else
        {
            printf("(CLIST_GetPrev) Test lecture d'une liste vide KO\n");
            result = 1;
        }
    }

    /* On verifie que les elements ont bien ete enleve */
    {
        if(CLIST_Size(cloneList1) != nbCloneInser)
        {
            printf("(CLIST_GetXXXX) La taille de la liste est incorrecte\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_RemoveFirst() */
    {
        /* on se positionne au bon endroit */
        CLIST_SeekFirst(list1);

        error = CLIST_RemoveFirst(list1);
        if(error != CLIST_NO_ERROR)
        {
            printf("(CLIST_RemoveFirst) Test suppression dans une liste KO\n");
            result = 1;
        }
        else
        {
            nbInser --;
            printf("(CLIST_RemoveFirst) Test suppression dans une liste OK\n");
        }

        error = CLIST_RemoveFirst(cloneList2);
        if(error == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_RemoveFirst) Test suppression dans une liste OK\n");
        }
        else
        {
            printf("(CLIST_RemoveFirst) Test suppression dans une liste KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_RemoveCurrent() */
    {
        error = CLIST_RemoveCurrent(list1);
        if(error != CLIST_NO_ERROR)
        {
            printf("(CLIST_RemoveCurrent) Test suppression dans une liste KO\n");
            result = 1;
        }
        else
        {
            nbInser --;
            printf("(CLIST_RemoveCurrent) Test suppression dans une liste OK\n");
        }

        error = CLIST_RemoveCurrent(cloneList2);
        if(error == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_RemoveCurrent) Test suppression dans une liste OK\n");
        }
        else
        {
            printf("(CLIST_RemoveCurrent) Test suppression dans une liste KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_RemoveNext() */
    {
        error = CLIST_RemoveNext(list1);
        if(error != CLIST_NO_ERROR)
        {
            printf("(CLIST_RemoveNext) Test suppression dans une liste KO\n");
            result = 1;
        }
        else
        {
            nbInser --;
            printf("(CLIST_RemoveNext) Test suppression dans une liste OK\n");
        }

        error = CLIST_RemoveNext(cloneList2);
        if(error == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_RemoveNext) Test suppression dans une liste OK\n");
        }
        else
        {
            printf("(CLIST_RemoveNext) Test suppression dans une liste KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_RemovePrev() */
    {
        error = CLIST_RemovePrev(list1);
        if(error != CLIST_NO_ERROR)
        {
            printf("(CLIST_RemovePrev) Test suppression dans une liste KO\n");
            result = 1;
        }
        else
        {
            nbInser --;
            printf("(CLIST_RemovePrev) Test suppression dans une liste OK\n");
        }

        error = CLIST_RemovePrev(cloneList2);
        if(error == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_RemovePrev) Test suppression dans une liste OK\n");
        }
        else
        {
            printf("(CLIST_RemovePrev) Test suppression dans une liste KO\n");
            result = 1;
        }
    }

    /* On verifie que les elements ont bien ete enleve */
    {
        if(CLIST_Size(list1) != nbInser)
        {
            printf("(CLIST_RemoveXXXX) La taille de la liste est incorrecte\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_Destroy() */
    {
        CLIST_Destroy(list1);
        CLIST_Destroy(list2);
        CLIST_Destroy(cloneList1);
        CLIST_Destroy(cloneList2);

        printf("(CLIST_Destroy) Test de destruction d'une liste OK\n");
    }

    /* Creation des listes de test pour la recherche */
    {
        list1 = CLIST_Create(NULL, &error);
        list2 = CLIST_Create(NULL, &error);
        if(list1 == NULL || list2 == NULL)
        {
            printf("Test module liste circulaire : pb creations liste de test\n");
            return 1;
        }

        for(nbInser = 0; nbInser < sizeof(searchedString) / sizeof(searchedString[0]); nbInser++)
        {
            if(CLIST_InsertNext(list1, searchedString[nbInser], strlen(searchedString[nbInser]) + 1) != CLIST_NO_ERROR)
            {
                printf("Test module liste circulaire : pb creations liste de test\n");
                return 1;
            }
        }

        cloneList1 = CLIST_Clone(list1, &error);
        if(cloneList1 == NULL || error != CLIST_NO_ERROR)
        {
            printf("Test module liste circulaire : pb creations liste de test\n");
            result = 1;
        }

        nbCloneInser = nbInser;

        CLIST_SeekFirst(list1);
        CLIST_SeekNext(list1);
        CLIST_SeekNext(list1);
        CLIST_SeekNext(list1);
        CLIST_SeekNext(list1);

        CLIST_SeekFirst(cloneList1);
        CLIST_SeekNext(cloneList1);
        CLIST_SeekNext(cloneList1);
        CLIST_SeekNext(cloneList1);
        CLIST_SeekNext(cloneList1);
    }


    /* Test de la fonction CLIST_SetCmp() */
    {
        CLIST_SetCmp(list1, TstCompar);
        printf("(CLIST_SetCmp) Initialisation de la fonction de comparaison OK\n");
    }

    /* Test de la fonction CLIST_SearchData() */
    {
        if(CLIST_SearchData(list1, "ChaineB") == CLIST_NO_ERROR)
        {
            printf("(CLIST_SearchData) Test de recherche dans une liste OK\n");
        }
        else
        {
            printf("(CLIST_SearchData) Test de recherche dans une liste KO\n");
            result = 1;
        }

        if(CLIST_SearchData(list1, "ChaineZ") == CLIST_CELL_NOT_FOUND)
        {
            printf("(CLIST_SearchData) Test de recherche d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(CLIST_SearchData) Test de recherche d'un element non present dans une liste KO\n");
            result = 1;
        }

        if(CLIST_SearchData(list2, "ChaineB") == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_SearchData) Test de recherche dans une liste vide OK\n");
        }
        else
        {
            printf("(CLIST_SearchData) Test de recherche dans une liste vide KO\n");
            result = 1;
        }

        if(CLIST_SearchData(cloneList1, "ChaineB") == CLIST_NO_COMP_FONCTION)
        {
            printf("(CLIST_SearchData) Test de recherche dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(CLIST_SearchData) Test de recherche dans une liste sans comparateur KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_SearchDataFct() */
    {
        if(CLIST_SearchDataFct(list1, "ChaineB", TstCompar) == CLIST_NO_ERROR)
        {
            printf("(CLIST_SearchDataFct) Test de recherche dans une liste OK\n");
        }
        else
        {
            printf("(CLIST_SearchDataFct) Test de recherche dans une liste KO\n");
            result = 1;
        }

        if(CLIST_SearchDataFct(list1, "ChaineZ", TstCompar) == CLIST_CELL_NOT_FOUND)
        {
            printf("(CLIST_SearchDataFct) Test de recherche d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(CLIST_SearchDataFct) Test de recherche d'un element non present dans une liste KO\n");
            result = 1;
        }

        if(CLIST_SearchDataFct(list2, "ChaineB", TstCompar) == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_SearchDataFct) Test de recherche dans une liste vide OK\n");
        }
        else
        {
            printf("(CLIST_SearchDataFct) Test de recherche dans une liste vide KO\n");
            result = 1;
        }

        if(CLIST_SearchDataFct(cloneList1, "ChaineB", TstCompar) == CLIST_NO_ERROR)
        {
            printf("(CLIST_SearchDataFct) Test de recherche dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(CLIST_SearchDataFct) Test de recherche dans une liste sans comparateur KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_SearchDataRev() */
    {
        if(CLIST_SearchDataRev(list1, "ChaineC") == CLIST_NO_ERROR)
        {
            printf("(CLIST_SearchDataRev) Test de recherche dans une liste OK\n");
        }
        else
        {
            printf("(CLIST_SearchDataRev) Test de recherche dans une liste KO\n");
            result = 1;
        }

        if(CLIST_SearchDataRev(list1, "ChaineZ") == CLIST_CELL_NOT_FOUND)
        {
            printf("(CLIST_SearchDataRev) Test de recherche d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(CLIST_SearchDataRev) Test de recherche d'un element non present dans une liste KO\n");
            result = 1;
        }

        if(CLIST_SearchDataRev(list2, "ChaineD") == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_SearchDataRev) Test de recherche dans une liste vide OK\n");
        }
        else
        {
            printf("(CLIST_SearchDataRev) Test de recherche dans une liste vide KO\n");
            result = 1;
        }

        if(CLIST_SearchDataRev(cloneList1, "ChaineD") == CLIST_NO_COMP_FONCTION)
        {
            printf("(CLIST_SearchDataRev) Test de recherche dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(CLIST_SearchDataRev) Test de recherche dans une liste sans comparateur KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_SearchDataRevFct() */
    {
        if(CLIST_SearchDataRevFct(list1, "ChaineC", TstCompar) == CLIST_NO_ERROR)
        {
            printf("(CLIST_SearchDataRevFct) Test de recherche dans une liste OK\n");
        }
        else
        {
            printf("(CLIST_SearchDataRevFct) Test de recherche dans une liste KO\n");
            result = 1;
        }

        if(CLIST_SearchDataRevFct(list1, "ChaineZ", TstCompar) == CLIST_CELL_NOT_FOUND)
        {
            printf("(CLIST_SearchDataRevFct) Test de recherche d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(CLIST_SearchDataRevFct) Test de recherche d'un element non present dans une liste KO\n");
            result = 1;
        }

        if(CLIST_SearchDataRevFct(list2, "ChaineD", TstCompar) == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_SearchDataRevFct) Test de recherche dans une liste vide OK\n");
        }
        else
        {
            printf("(CLIST_SearchDataRevFct) Test de recherche dans une liste vide KO\n");
            result = 1;
        }

        if(CLIST_SearchDataRevFct(cloneList1, "ChaineD", TstCompar) == CLIST_NO_ERROR)
        {
            printf("(CLIST_SearchDataRevFct) Test de recherche dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(CLIST_SearchDataRevFct) Test de recherche dans une liste sans comparateur KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_RemoveData() */
    {
        if(CLIST_RemoveData(list1, "ChaineB") == CLIST_NO_ERROR)
        {
            printf("(CLIST_RemoveData) Test de suppression dans une liste OK\n");
            nbInser--;
        }
        else
        {
            printf("(CLIST_RemoveData) Test de suppression dans une liste KO\n");
            result = 1;
        }

        if(CLIST_RemoveData(list1, "ChaineZ") == CLIST_CELL_NOT_FOUND)
        {
            printf("(CLIST_RemoveData) Test de suppression d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(CLIST_RemoveData) Test de suppression d'un element non present dans une liste KO\n");
            result = 1;
        }

        if(CLIST_RemoveData(list2, "ChaineB") == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_RemoveData) Test de suppression dans une liste vide OK\n");
        }
        else
        {
            printf("(CLIST_RemoveData) Test de suppression dans une liste vide KO\n");
            result = 1;
        }

        if(CLIST_RemoveData(cloneList1, "ChaineB") == CLIST_NO_COMP_FONCTION)
        {
            printf("(CLIST_RemoveData) Test de suppression dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(CLIST_RemoveData) Test de suppression dans une liste sans comparateur KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_RemoveDataFct() */
    {
        if(CLIST_RemoveDataFct(list1, "ChaineB", TstCompar) == CLIST_NO_ERROR)
        {
            printf("(CLIST_RemoveDataFct) Test de suppression dans une liste OK\n");
            nbInser--;
        }
        else
        {
            printf("(CLIST_RemoveDataFct) Test de suppression dans une liste KO\n");
            result = 1;
        }

        if(CLIST_RemoveDataFct(list1, "ChaineZ", TstCompar) == CLIST_CELL_NOT_FOUND)
        {
            printf("(CLIST_RemoveDataFct) Test de suppression d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(CLIST_RemoveDataFct) Test de suppression d'un element non present dans une liste KO\n");
            result = 1;
        }

        if(CLIST_RemoveDataFct(list2, "ChaineB", TstCompar) == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_RemoveDataFct) Test de suppression dans une liste vide OK\n");
        }
        else
        {
            printf("(CLIST_RemoveDataFct) Test de suppression dans une liste vide KO\n");
            result = 1;
        }

        if(CLIST_RemoveDataFct(cloneList1, "ChaineB", TstCompar) == CLIST_NO_ERROR)
        {
            printf("(CLIST_RemoveDataFct) Test de suppression dans une liste sans comparateur OK\n");
            nbCloneInser--;
        }
        else
        {
            printf("(CLIST_RemoveDataFct) Test de suppression dans une liste sans comparateur KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_RemoveDataRev() */
    {
        if(CLIST_RemoveDataRev(list1, "ChaineB") == CLIST_NO_ERROR)
        {
            printf("(CLIST_RemoveDataRev) Test de suppression dans une liste OK\n");
            nbInser--;
        }
        else
        {
            printf("(CLIST_RemoveDataRev) Test de suppression dans une liste KO\n");
            result = 1;
        }

        if(CLIST_RemoveDataRev(list1, "ChaineZ") == CLIST_CELL_NOT_FOUND)
        {
            printf("(CLIST_RemoveDataRev) Test de suppression d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(CLIST_RemoveDataRev) Test de suppression d'un element non present dans une liste KO\n");
            result = 1;
        }

        if(CLIST_RemoveDataRev(list2, "ChaineB") == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_RemoveDataRev) Test de suppression dans une liste vide OK\n");
        }
        else
        {
            printf("(CLIST_RemoveDataRev) Test de suppression dans une liste vide KO\n");
            result = 1;
        }

        if(CLIST_RemoveDataRev(cloneList1, "ChaineB") == CLIST_NO_COMP_FONCTION)
        {
            printf("(CLIST_RemoveDataRev) Test de suppression dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(CLIST_RemoveDataRev) Test de suppression dans une liste sans comparateur KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_RemoveDataRevFct() */
    {
        if(CLIST_RemoveDataRevFct(list1, "ChaineB", TstCompar) == CLIST_NO_ERROR)
        {
            printf("(CLIST_RemoveDataRevFct) Test de suppression dans une liste OK\n");
            nbInser--;
        }
        else
        {
            printf("(CLIST_RemoveDataRevFct) Test de suppression dans une liste KO\n");
            result = 1;
        }

        if(CLIST_RemoveDataRevFct(list1, "ChaineZ", TstCompar) == CLIST_CELL_NOT_FOUND)
        {
            printf("(CLIST_RemoveDataRevFct) Test de suppression d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(CLIST_RemoveDataRevFct) Test de suppression d'un element non present dans une liste KO\n");
            result = 1;
        }

        if(CLIST_RemoveDataRevFct(list2, "ChaineB", TstCompar) == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_RemoveDataRevFct) Test de suppression dans une liste vide OK\n");
        }
        else
        {
            printf("(CLIST_RemoveDataRevFct) Test de suppression dans une liste vide KO\n");
            result = 1;
        }

        if(CLIST_RemoveDataRevFct(cloneList1, "ChaineB", TstCompar) == CLIST_NO_ERROR)
        {
            printf("(CLIST_RemoveDataRevFct) Test de suppression dans une liste sans comparateur OK\n");
            nbCloneInser--;
        }
        else
        {
            printf("(CLIST_RemoveDataRevFct) Test de suppression dans une liste sans comparateur KO\n");
            result = 1;
        }
    }

    /* On verifie que les elements ont bien ete enleve */
    {
        if(CLIST_Size(list1) != nbInser)
        {
            printf("(CLIST_RemoveDataXXXX) La taille de la liste list1 est incorrecte\n");
            result = 1;
        }


        if(CLIST_Size(cloneList1) != nbCloneInser)
        {
            printf("(CLIST_RemoveDataXXXX) La taille de la liste cloneList1 est incorrecte\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_RemoveAllData() */
    {
        if(CLIST_RemoveAllData(list1, "ChaineB") == CLIST_NO_ERROR)
        {
            printf("(CLIST_RemoveAllData) Test de suppression dans une liste OK\n");
        }
        else
        {
            printf("(CLIST_RemoveAllData) Test de suppression dans une liste KO\n");
            result = 1;
        }

        if(CLIST_RemoveAllData(list1, "ChaineZ") == CLIST_NO_ERROR)
        {
            printf("(CLIST_RemoveAllData) Test de suppression d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(CLIST_RemoveAllData) Test de suppression d'un element non present dans une liste KO\n");
            result = 1;
        }

        if(CLIST_RemoveAllData(list2, "ChaineB") == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_RemoveAllData) Test de suppression dans une liste vide OK\n");
        }
        else
        {
            printf("(CLIST_RemoveAllData) Test de suppression dans une liste vide KO\n");
            result = 1;
        }

        if(CLIST_RemoveAllData(cloneList1, "ChaineB") == CLIST_NO_COMP_FONCTION)
        {
            printf("(CLIST_RemoveAllData) Test de suppression dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(CLIST_RemoveAllData) Test de suppression dans une liste sans comparateur KO\n");
            result = 1;
        }
    }

    /* Test de la fonction CLIST_RemoveDataFct() */
    {
        if(CLIST_RemoveAllDataFct(list1, "ChaineB", TstCompar) == CLIST_NO_ERROR)
        {
            printf("(CLIST_RemoveAllDataFct) Test de suppression dans une liste OK\n");
        }
        else
        {
            printf("(CLIST_RemoveAllDataFct) Test de suppression dans une liste KO\n");
            result = 1;
        }

        if(CLIST_RemoveAllDataFct(list1, "ChaineZ", TstCompar) == CLIST_NO_ERROR)
        {
            printf("(CLIST_RemoveAllDataFct) Test de suppression d'un element non present dans une liste OK\n");
        }
        else
        {
            printf("(CLIST_RemoveAllDataFct) Test de suppression d'un element non present dans une liste KO\n");
            result = 1;
        }

        if(CLIST_RemoveAllDataFct(list2, "ChaineB", TstCompar) == CLIST_EMPTY_LIST)
        {
            printf("(CLIST_RemoveAllDataFct) Test de suppression dans une liste vide OK\n");
        }
        else
        {
            printf("(CLIST_RemoveAllDataFct) Test de suppression dans une liste vide KO\n");
            result = 1;
        }

        if(CLIST_RemoveAllDataFct(cloneList1, "ChaineB", TstCompar) == CLIST_NO_ERROR)
        {
            printf("(CLIST_RemoveAllDataFct) Test de suppression dans une liste sans comparateur OK\n");
        }
        else
        {
            printf("(CLIST_RemoveAllDataFct) Test de suppression dans une liste sans comparateur KO\n");
            result = 1;
        }
    }

    /* On verifie que les elements ont bien ete enleve */
    {
        if(CLIST_Size(list1) != 3)
        {
            printf("(CLIST_RemoveAllDataXXXX) La taille de la liste list1 est incorrecte\n");
            result = 1;
        }

        if(CLIST_Size(cloneList1) != 3)
        {
            printf("(CLIST_RemoveAllDataXXXX) La taille de la liste cloneList1 est incorrecte\n");
            result = 1;
        }
    }

    /* Desctruction des listes */
    {
        CLIST_Destroy(list1);
        CLIST_Destroy(list2);
        CLIST_Destroy(cloneList1);
    }

    return result;
}
