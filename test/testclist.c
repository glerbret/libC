#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"
#include "clist.h"
#include "test.h"

static int TstCompar(const void* pData1, const void* pData2)
{
   return strcmp((const char*)pData1, (const char*)pData2);
}

int      TstCList(void)
{
   int            iResult = 0;
   size_t         szNbInser = 0;
   size_t         szNbCloneInser = 0;
   clist_s*       pList1;
   clist_s*       pList2;
   clist_s*       pCloneList1;
   clist_s*       pCloneList2;
   CLIST_Error_e  eError;
   const char*    pcData;
   const char*    acChaine[]=
   {
      "Chaine1",
      "Chaine2",
      "Chaine3",
      "Chaine4",
      "Chaine5",
      "Chaine6"
   };
   const char*    acChaineSearch[]=
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
      pList1 = CLIST_Create(NULL, &eError);
      if(pList1 == NULL || eError != CLIST_NO_ERROR)
      {
         printf("(CLIST_Create) Test creation d'une liste sans fonction de comparaison KO\n");
         return 1;
      }
      else
      {
         printf("(CLIST_Create) Test creation d'une liste sans fonction de comparaison OK\n");
      }

      pList2 = CLIST_Create(NULL, &eError);
      if(pList2 == NULL || eError != CLIST_NO_ERROR)
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
      if(CLIST_IsEmpty(pList1) == false)
      {
         printf("(CLIST_IsEmpty) Test sur une liste vide KO\n");
         iResult=1;
      }
      else
      {
         printf("(CLIST_IsEmpty) Test sur une liste vide OK\n");
      }
   }

   /* Test de la fonction CLIST_Size() sur une liste vide */
   {
      if(CLIST_Size(pList1) != 0)
      {
         printf("(CLIST_Size) Test sur une liste vide KO\n");
         iResult=1;
      }
      else
      {
         printf("(CLIST_Size) Test sur une liste vide OK\n");
      }
   }

   /* Test de la fonction CLIST_InsertFirst() */
   {
      if(CLIST_InsertFirst(pList1, acChaine[szNbInser], strlen(acChaine[szNbInser])+1) == CLIST_NO_ERROR)
      {
         printf("(CLIST_InsertFirst) Test d'insertion OK\n");
         szNbInser++;
      }
      else
      {
         printf("(CLIST_InsertFirst) Test d'insertion KO\n");
         iResult = 1;
      }

      if(CLIST_InsertFirst(pList1, acChaine[szNbInser], strlen(acChaine[szNbInser])+1) == CLIST_NO_ERROR)
      {
         printf("(CLIST_InsertFirst) Test d'insertion OK\n");
         szNbInser++;
      }
      else
      {
         printf("(CLIST_InsertFirst) Test d'insertion KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_InsertNext() */
   {
      if(CLIST_InsertNext(pList1, acChaine[szNbInser], strlen(acChaine[szNbInser])+1) == CLIST_NO_ERROR)
      {
         printf("(CLIST_InsertNext) Test d'insertion OK\n");
         szNbInser++;
      }
      else
      {
         printf("(CLIST_InsertNext) Test d'insertion KO\n");
         iResult = 1;
      }

      if(CLIST_InsertNext(pList1, acChaine[szNbInser], strlen(acChaine[szNbInser])+1) == CLIST_NO_ERROR)
      {
         printf("(CLIST_InsertNext) Test d'insertion OK\n");
         szNbInser++;
      }
      else
      {
         printf("(CLIST_InsertNext) Test d'insertion KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_InsertPrev() */
   {
      if(CLIST_InsertPrev(pList1, acChaine[szNbInser], strlen(acChaine[szNbInser])+1) == CLIST_NO_ERROR)
      {
         printf("(CLIST_InsertPrev) Test d'insertion OK\n");
         szNbInser++;
      }
      else
      {
         printf("(CLIST_InsertPrev) Test d'insertion KO\n");
         iResult = 1;
      }

      if(CLIST_InsertPrev(pList1, acChaine[szNbInser], strlen(acChaine[szNbInser])+1) == CLIST_NO_ERROR)
      {
         printf("(CLIST_InsertPrev) Test d'insertion OK\n");
         szNbInser++;
      }
      else
      {
         printf("(CLIST_InsertPrev) Test d'insertion KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_IsEmpty() sur une liste non vide */
   {
      if(CLIST_IsEmpty(pList1) == true)
      {
         printf("(CLIST_IsEmpty) Test sur une liste non vide KO\n");
         iResult=1;
      }
      else
      {
         printf("(CLIST_IsEmpty) Test sur une liste non vide OK\n");
      }
   }

   /* Test de la fonction CLIST_Size() sur une liste non vide */
   {
      if(CLIST_Size(pList1) != szNbInser)
      {
         printf("(CLIST_Size) Test sur une liste non vide KO\n");
         iResult=1;
      }
      else
      {
         printf("(CLIST_Size) Test sur une liste vide OK\n");
      }
   }

   /* Test de la fonction CLIST_ReadCurrent() */
   {
      pcData = CLIST_ReadCurrent(pList1, &eError);
      if(pcData == NULL || eError != CLIST_NO_ERROR)
      {
         printf("(CLIST_ReadCurrent) Test lecture de l'element courant d'une liste KO\n");
         iResult = 1;
      }
      else
      {
         if(strcmp(pcData, "Chaine6") == 0)
         {
            printf("(CLIST_ReadCurrent) Test lecture de l'element courant d'une liste OK\n");
         }
         else
         {
            printf("(CLIST_ReadCurrent) Test lecture de l'element courant d'une liste KO\n");
            iResult = 1;
         }
      }

      pcData = CLIST_ReadCurrent(pList2, &eError);
      if(pcData == NULL && eError == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_ReadCurrent) Test lecture de l'element courant d'une liste vide OK\n");
      }
      else
      {
         printf("(CLIST_ReadCurrent) Test lecture de l'element courant d'une liste vide KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction LIST_ReadFirst() */
   {
      pcData = CLIST_ReadFirst(pList1, &eError);
      if(pcData == NULL || eError != CLIST_NO_ERROR)
      {
         printf("(CLIST_ReadFirst) Test lecture du premier element d'une liste KO\n");
         iResult = 1;
      }
      else
      {
         if(strcmp(pcData, "Chaine2") == 0)
         {
            printf("(CLIST_ReadFirst) Test lecture du premier element d'une liste OK\n");
         }
         else
         {
            printf("(CLIST_ReadFirst) Test lecture du premier element d'une liste KO\n");
            iResult = 1;
         }
      }

      pcData = CLIST_ReadFirst(pList2, &eError);
      if(pcData == NULL && eError == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_ReadFirst) Test lecture du premier element d'une liste vide OK\n");
      }
      else
      {
         printf("(CLIST_ReadFirst) Test lecture du premier element d'une liste vide KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction LIST_ReadNext() */
   {
      pcData = CLIST_ReadNext(pList1, &eError);
      if(pcData == NULL || eError != CLIST_NO_ERROR)
      {
         printf("(CLIST_ReadNext) Test lecture de l'element suivant d'une liste KO\n");
         iResult = 1;
      }
      else
      {
         if(strcmp(pcData, "Chaine5") == 0)
         {
            printf("(CLIST_ReadNext) Test lecture de l'element suivant d'une liste OK\n");
         }
         else
         {
            printf("(CLIST_ReadNext) Test lecture de l'element suivant d'une liste KO\n");
            iResult = 1;
         }
      }

      pcData = CLIST_ReadNext(pList2, &eError);
      if(pcData == NULL && eError == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_ReadNext) Test lecture de l'element suivant d'une liste vide OK\n");
      }
      else
      {
         printf("(CLIST_ReadNext) Test lecture de l'element suivant d'une liste vide KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_ReadPrev() */
   {
      pcData = CLIST_ReadPrev(pList1, &eError);
      if(pcData == NULL || eError != CLIST_NO_ERROR)
      {
         printf("(CLIST_ReadPrev) Test lecture de l'element precedent d'une liste KO\n");
         iResult = 1;
      }
      else
      {
         if(strcmp(pcData, "Chaine3") == 0)
         {
            printf("(CLIST_ReadPrev) Test lecture de l'element precedent d'une liste OK\n");
         }
         else
         {
            printf("(CLIST_ReadPrev) Test lecture de l'element precedent d'une liste KO\n");
            iResult = 1;
         }
      }

      pcData = CLIST_ReadNext(pList2, &eError);
      if(pcData == NULL && eError == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_ReadPrev) Test lecture de l'element precedent d'une liste vide OK\n");
      }
      else
      {
         printf("(CLIST_ReadPrev) Test lecture de l'element precedent d'une liste vide KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_SeekFirst() */
   {
      if(CLIST_SeekFirst(pList1) != CLIST_NO_ERROR)
      {
         printf("(CLIST_SeekFirst) Test de deplacement vers le premier element d'une liste KO\n");
         iResult = 1;
      }
      else
      {
         pcData = CLIST_ReadCurrent(pList1, &eError);
         if(pcData != NULL && eError == CLIST_NO_ERROR && strcmp(pcData, "Chaine2") == 0)
         {
            printf("(CLIST_SeekFirst) Test de deplacement vers le premier element d'une liste OK\n");
         }
         else
         {
            printf("(CLIST_SeekFirst) Test de deplacement vers le premier element d'une liste KO\n");
            iResult = 1;
         }
      }

      if(CLIST_SeekFirst(pList2) == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_SeekFirst) Test de deplacement vers le premier element d'une liste vide OK\n");
      }
      else
      {
         printf("(CLIST_SeekFirst) Test de deplacement vers le premier element d'une liste vide KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_SeekPrev() */
   {
      if(CLIST_SeekPrev(pList1) != CLIST_NO_ERROR)
      {
         printf("(CLIST_SeekPrev) Test de deplacement vers l'element precedent d'une liste KO\n");
         iResult = 1;
      }
      else
      {
         pcData = CLIST_ReadCurrent(pList1, &eError);
         if(pcData != NULL && eError == CLIST_NO_ERROR && strcmp(pcData, "Chaine1") == 0)
         {
            printf("(CLIST_SeekPrev) Test de deplacement vers l'element precedent d'une liste OK\n");
         }
         else
         {
            printf("(CLIST_SeekPrev) Test de deplacement vers ll'element precedent d'une liste KO\n");
            iResult = 1;
         }
      }

      if(CLIST_SeekPrev(pList2) == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_SeekPrev) Test de deplacement vers l'element precedent d'une liste vide OK\n");
      }
      else
      {
         printf("(CLIST_SeekPrev) Test de deplacement vers l'element precedent d'une liste vide KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_SeekNext() */
   {
      if(CLIST_SeekNext(pList1) != CLIST_NO_ERROR)
      {
         printf("(CLIST_SeekNext) Test de deplacement vers l'element suivant d'une liste KO\n");
         iResult = 1;
      }
      else
      {
         pcData = CLIST_ReadCurrent(pList1, &eError);
         if(pcData != NULL && eError == CLIST_NO_ERROR && strcmp(pcData, "Chaine2") == 0)
         {
            printf("(CLIST_SeekNext) Test de deplacement vers l'element suivant d'une liste OK\n");
         }
         else
         {
            printf("(CLIST_SeekNext) Test de deplacement vers l'element suivant d'une liste KO\n");
            iResult = 1;
         }
      }

      if(CLIST_SeekNext(pList2) == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_SeekNext) Test de deplacement vers l'element suivant d'une liste vide OK\n");
      }
      else
      {
         printf("(CLIST_SeekNext) Test de deplacement vers l'element suivant d'une liste vide KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_IsHead() */
   {
      /* on se positionne au bon endroit */
      CLIST_SeekNext(pList1);

      if(CLIST_IsHead(pList1) == false)
      {
         CLIST_SeekFirst(pList1);
         if(CLIST_IsHead(pList1) == true)
         {
            printf("(CLIST_IsHead) Test sur une liste non vide OK\n");
         }
         else
         {
            printf("(CLIST_IsHead) Test sur une liste non vide KO\n");
            iResult = 1;
         }
      }
      else
      {
         printf("(CLIST_IsHead) Test sur une liste non vide KO\n");
         iResult = 1;
      }

      if(CLIST_IsHead(pList2) == false)
      {
         printf("(CLIST_IsHead) Test sur une liste vide OK\n");
      }
      else
      {
         printf("(CLIST_IsHead) Test sur une liste vide KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_Clone() */
   {
      pCloneList1 = CLIST_Clone(pList1, &eError);
      if(pCloneList1 == NULL || eError != CLIST_NO_ERROR)
      {
         printf("(CLIST_Clone) Test duplication d'une liste KO\n");
         iResult = 1;
      }
      else
      {
         /* On verifie que tout semble bien se passer */
         if(CLIST_IsEmpty(pCloneList1) == false && CLIST_Size(pCloneList1) == szNbInser)
         {
            printf("(CLIST_Clone) Test duplication d'une liste OK\n");
            szNbCloneInser = szNbInser;
         }
         else
         {
            printf("(CLIST_Clone) Test duplication d'une liste KO\n");
            iResult = 1;
         }
      }

      pCloneList2 = CLIST_Clone(pList2, &eError);
      if(pCloneList2 == NULL || eError != CLIST_NO_ERROR)
      {
         printf("(CLIST_Clone) Test duplication d'une liste vide KO\n");
         pCloneList2 = NULL;
         iResult = 1;
      }
      else
      {
         /* On verifie que tout semble bien se passer */
         if(CLIST_IsEmpty(pCloneList2) == true && CLIST_Size(pCloneList2) == 0)
         {
            printf("(CLIST_Clone) Test duplication d'une liste vide OK\n");
         }
         else
         {
            printf("(CLIST_Clone) Test duplication d'une liste vide KO\n");
            iResult = 1;
         }
      }
   }

   /* Test de la fonction CLIST_GetFirst() */
   {
      pcData = CLIST_GetFirst(pCloneList1, &eError);
      if(pcData == NULL || eError != CLIST_NO_ERROR)
      {
         printf("(CLIST_GetFirst) Test lecture du premier element d'une liste KO\n");
         iResult = 1;
      }
      else
      {
         szNbCloneInser --;
         if(strcmp(pcData, "Chaine2") == 0)
         {
            printf("(CLIST_GetFirst) Test lecture du premier element d'une liste OK\n");
            free((void*)pcData), pcData = NULL;
         }
         else
         {
            printf("(CLIST_GetFirst) Test lecture du premier element d'une liste KO\n");
            iResult = 1;
         }
      }

      pcData = CLIST_GetFirst(pCloneList2, &eError);
      if(pcData == NULL && eError == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_GetFirst) Test lecture du premier element d'une liste vide OK\n");
      }
      else
      {
         printf("(CLIST_GetFirst) Test lecture du premier element d'une liste vide KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_GetCurrent() */
   {
      pcData = CLIST_GetCurrent(pCloneList1, &eError);
      if(pcData == NULL || eError != CLIST_NO_ERROR)
      {
         printf("(CLIST_GetCurrent) Test lecture d'une liste KO\n");
         iResult = 1;
      }
      else
      {
         szNbCloneInser --;
         if(strcmp(pcData, "Chaine3") == 0)
         {
            printf("(CLIST_GetCurrent) Test lecture d'une liste OK\n");
         }
         else
         {
            printf("(CLIST_GetCurrent) Test lecture d'une liste KO\n");
            iResult = 1;
         }
      }

      pcData = CLIST_GetCurrent(pCloneList2, &eError);
      if(pcData == NULL && eError == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_GetCurrent) Test lecture d'une liste vide OK\n");
      }
      else
      {
         printf("(CLIST_GetCurrent) Test lecture d'une liste vide KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_GetNext() */
   {
      pcData = CLIST_GetNext(pCloneList1, &eError);
      if(pcData == NULL || eError != CLIST_NO_ERROR)
      {
         printf("(CLIST_GetNext) Test lecture d'une liste KO\n");
         iResult = 1;
      }
      else
      {
         szNbCloneInser --;
         if(strcmp(pcData, "Chaine5") == 0)
         {
            printf("(CLIST_GetNext) Test lecture d'une liste OK\n");
         }
         else
         {
            printf("(CLIST_GetNext) Test lecture d'une liste KO\n");
            iResult = 1;
         }
      }

      pcData = CLIST_GetNext(pCloneList2, &eError);
      if(pcData == NULL && eError == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_GetNext) Test lecture d'une liste vide OK\n");
      }
      else
      {
         printf("(CLIST_GetNext) Test lecture d'une liste vide KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_GetPrev() */
   {
      pcData = CLIST_GetPrev(pCloneList1, &eError);
      if(pcData == NULL || eError != CLIST_NO_ERROR)
      {
         printf("(CLIST_GetPrev) Test lecture d'une liste KO\n");
         iResult = 1;
      }
      else
      {
         szNbCloneInser --;
         if(strcmp(pcData, "Chaine1") == 0)
         {
            printf("(CLIST_GetPrev) Test lecture d'une liste OK\n");
         }
         else
         {
            printf("(CLIST_GetPrev) Test lecture d'une liste KO\n");
            iResult = 1;
         }
      }

      pcData = CLIST_GetPrev(pCloneList2, &eError);
      if(pcData == NULL && eError == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_GetPrev) Test lecture d'une liste vide OK\n");
      }
      else
      {
         printf("(CLIST_GetPrev) Test lecture d'une liste vide KO\n");
         iResult = 1;
      }
   }

   /* On verifie que les elements ont bien ete enleve */
   {
      if(CLIST_Size(pCloneList1) != szNbCloneInser)
      {
         printf("(CLIST_GetXXXX) La taille de la liste est incorrecte\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_RemoveFirst() */
   {
      /* on se positionne au bon endroit */
      CLIST_SeekFirst(pList1);

      eError = CLIST_RemoveFirst(pList1);
      if(eError != CLIST_NO_ERROR)
      {
         printf("(CLIST_RemoveFirst) Test suppression dans une liste KO\n");
         iResult = 1;
      }
      else
      {
         szNbInser --;
         printf("(CLIST_RemoveFirst) Test suppression dans une liste OK\n");
      }

      eError = CLIST_RemoveFirst(pCloneList2);
      if(eError == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_RemoveFirst) Test suppression dans une liste OK\n");
      }
      else
      {
         printf("(CLIST_RemoveFirst) Test suppression dans une liste KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_RemoveCurrent() */
   {
      eError = CLIST_RemoveCurrent(pList1);
      if(eError != CLIST_NO_ERROR)
      {
         printf("(CLIST_RemoveCurrent) Test suppression dans une liste KO\n");
         iResult = 1;
      }
      else
      {
         szNbInser --;
         printf("(CLIST_RemoveCurrent) Test suppression dans une liste OK\n");
      }

      eError = CLIST_RemoveCurrent(pCloneList2);
      if(eError == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_RemoveCurrent) Test suppression dans une liste OK\n");
      }
      else
      {
         printf("(CLIST_RemoveCurrent) Test suppression dans une liste KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_RemoveNext() */
   {
      eError = CLIST_RemoveNext(pList1);
      if(eError != CLIST_NO_ERROR)
      {
         printf("(CLIST_RemoveNext) Test suppression dans une liste KO\n");
         iResult = 1;
      }
      else
      {
         szNbInser --;
         printf("(CLIST_RemoveNext) Test suppression dans une liste OK\n");
      }

      eError = CLIST_RemoveNext(pCloneList2);
      if(eError == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_RemoveNext) Test suppression dans une liste OK\n");
      }
      else
      {
         printf("(CLIST_RemoveNext) Test suppression dans une liste KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_RemovePrev() */
   {
      eError = CLIST_RemovePrev(pList1);
      if(eError != CLIST_NO_ERROR)
      {
         printf("(CLIST_RemovePrev) Test suppression dans une liste KO\n");
         iResult = 1;
      }
      else
      {
         szNbInser --;
         printf("(CLIST_RemovePrev) Test suppression dans une liste OK\n");
      }

      eError = CLIST_RemovePrev(pCloneList2);
      if(eError == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_RemovePrev) Test suppression dans une liste OK\n");
      }
      else
      {
         printf("(CLIST_RemovePrev) Test suppression dans une liste KO\n");
         iResult = 1;
      }
   }

   /* On verifie que les elements ont bien ete enleve */
   {
      if(CLIST_Size(pList1) != szNbInser)
      {
         printf("(CLIST_RemoveXXXX) La taille de la liste est incorrecte\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_Destroy() */
   {
      CLIST_Destroy(pList1);
      CLIST_Destroy(pList2);
      CLIST_Destroy(pCloneList1);
      CLIST_Destroy(pCloneList2);

      printf("(CLIST_Destroy) Test de destruction d'une liste OK\n");
   }

   /* Creation des listes de test pour la recherche */
   {
      pList1 = CLIST_Create(NULL, &eError);
      pList2 = CLIST_Create(NULL, &eError);
      if(pList1 == NULL || pList2 == NULL)
      {
         printf("Test module liste circulaire : pb creations liste de test\n");
         return 1;
      }

      for(szNbInser=0; szNbInser<sizeof(acChaineSearch)/sizeof(acChaineSearch[0]); szNbInser++)
      {
         if(CLIST_InsertNext(pList1, acChaineSearch[szNbInser], strlen(acChaineSearch[szNbInser])+1) != CLIST_NO_ERROR)
         {
            printf("Test module liste circulaire : pb creations liste de test\n");
            return 1;
         }
      }

      pCloneList1 = CLIST_Clone(pList1, &eError);
      if(pCloneList1 == NULL || eError != CLIST_NO_ERROR)
      {
         printf("Test module liste circulaire : pb creations liste de test\n");
         iResult = 1;
      }

      szNbCloneInser = szNbInser;

      CLIST_SeekFirst(pList1);
      CLIST_SeekNext(pList1);
      CLIST_SeekNext(pList1);
      CLIST_SeekNext(pList1);
      CLIST_SeekNext(pList1);

      CLIST_SeekFirst(pCloneList1);
      CLIST_SeekNext(pCloneList1);
      CLIST_SeekNext(pCloneList1);
      CLIST_SeekNext(pCloneList1);
      CLIST_SeekNext(pCloneList1);
   }


   /* Test de la fonction CLIST_SetCmp() */
   {
      CLIST_SetCmp(pList1, TstCompar);
      printf("(CLIST_SetCmp) Initialisation de la fonction de comparaison OK\n");
   }

   /* Test de la fonction CLIST_SearchData() */
   {
      if(CLIST_SearchData(pList1, "ChaineB") == CLIST_NO_ERROR)
      {
         printf("(CLIST_SearchData) Test de recherche dans une liste OK\n");
      }
      else
      {
         printf("(CLIST_SearchData) Test de recherche dans une liste KO\n");
         iResult = 1;
      }

      if(CLIST_SearchData(pList1, "ChaineZ") == CLIST_CELL_NOT_FOUND)
      {
         printf("(CLIST_SearchData) Test de recherche d'un element non present dans une liste OK\n");
      }
      else
      {
         printf("(CLIST_SearchData) Test de recherche d'un element non present dans une liste KO\n");
         iResult = 1;
      }

      if(CLIST_SearchData(pList2, "ChaineB") == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_SearchData) Test de recherche dans une liste vide OK\n");
      }
      else
      {
         printf("(CLIST_SearchData) Test de recherche dans une liste vide KO\n");
         iResult = 1;
      }

      if(CLIST_SearchData(pCloneList1, "ChaineB") == CLIST_NO_COMP_FONCTION)
      {
         printf("(CLIST_SearchData) Test de recherche dans une liste sans comparateur OK\n");
      }
      else
      {
         printf("(CLIST_SearchData) Test de recherche dans une liste sans comparateur KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_SearchDataFct() */
   {
      if(CLIST_SearchDataFct(pList1, "ChaineB", TstCompar) == CLIST_NO_ERROR)
      {
         printf("(CLIST_SearchDataFct) Test de recherche dans une liste OK\n");
      }
      else
      {
         printf("(CLIST_SearchDataFct) Test de recherche dans une liste KO\n");
         iResult = 1;
      }

      if(CLIST_SearchDataFct(pList1, "ChaineZ", TstCompar) == CLIST_CELL_NOT_FOUND)
      {
         printf("(CLIST_SearchDataFct) Test de recherche d'un element non present dans une liste OK\n");
      }
      else
      {
         printf("(CLIST_SearchDataFct) Test de recherche d'un element non present dans une liste KO\n");
         iResult = 1;
      }

      if(CLIST_SearchDataFct(pList2, "ChaineB", TstCompar) == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_SearchDataFct) Test de recherche dans une liste vide OK\n");
      }
      else
      {
         printf("(CLIST_SearchDataFct) Test de recherche dans une liste vide KO\n");
         iResult = 1;
      }

      if(CLIST_SearchDataFct(pCloneList1, "ChaineB", TstCompar) == CLIST_NO_ERROR)
      {
         printf("(CLIST_SearchDataFct) Test de recherche dans une liste sans comparateur OK\n");
      }
      else
      {
         printf("(CLIST_SearchDataFct) Test de recherche dans une liste sans comparateur KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_SearchDataRev() */
   {
      if(CLIST_SearchDataRev(pList1, "ChaineC") == CLIST_NO_ERROR)
      {
         printf("(CLIST_SearchDataRev) Test de recherche dans une liste OK\n");
      }
      else
      {
         printf("(CLIST_SearchDataRev) Test de recherche dans une liste KO\n");
         iResult = 1;
      }

      if(CLIST_SearchDataRev(pList1, "ChaineZ") == CLIST_CELL_NOT_FOUND)
      {
         printf("(CLIST_SearchDataRev) Test de recherche d'un element non present dans une liste OK\n");
      }
      else
      {
         printf("(CLIST_SearchDataRev) Test de recherche d'un element non present dans une liste KO\n");
         iResult = 1;
      }

      if(CLIST_SearchDataRev(pList2, "ChaineD") == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_SearchDataRev) Test de recherche dans une liste vide OK\n");
      }
      else
      {
         printf("(CLIST_SearchDataRev) Test de recherche dans une liste vide KO\n");
         iResult = 1;
      }

      if(CLIST_SearchDataRev(pCloneList1, "ChaineD") == CLIST_NO_COMP_FONCTION)
      {
         printf("(CLIST_SearchDataRev) Test de recherche dans une liste sans comparateur OK\n");
      }
      else
      {
         printf("(CLIST_SearchDataRev) Test de recherche dans une liste sans comparateur KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_SearchDataRevFct() */
   {
      if(CLIST_SearchDataRevFct(pList1, "ChaineC", TstCompar) == CLIST_NO_ERROR)
      {
         printf("(CLIST_SearchDataRevFct) Test de recherche dans une liste OK\n");
      }
      else
      {
         printf("(CLIST_SearchDataRevFct) Test de recherche dans une liste KO\n");
         iResult = 1;
      }

      if(CLIST_SearchDataRevFct(pList1, "ChaineZ", TstCompar) == CLIST_CELL_NOT_FOUND)
      {
         printf("(CLIST_SearchDataRevFct) Test de recherche d'un element non present dans une liste OK\n");
      }
      else
      {
         printf("(CLIST_SearchDataRevFct) Test de recherche d'un element non present dans une liste KO\n");
         iResult = 1;
      }

      if(CLIST_SearchDataRevFct(pList2, "ChaineD", TstCompar) == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_SearchDataRevFct) Test de recherche dans une liste vide OK\n");
      }
      else
      {
         printf("(CLIST_SearchDataRevFct) Test de recherche dans une liste vide KO\n");
         iResult = 1;
      }

      if(CLIST_SearchDataRevFct(pCloneList1, "ChaineD", TstCompar) == CLIST_NO_ERROR)
      {
         printf("(CLIST_SearchDataRevFct) Test de recherche dans une liste sans comparateur OK\n");
      }
      else
      {
         printf("(CLIST_SearchDataRevFct) Test de recherche dans une liste sans comparateur KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_RemoveData() */
   {
      if(CLIST_RemoveData(pList1, "ChaineB") == CLIST_NO_ERROR)
      {
         printf("(CLIST_RemoveData) Test de suppression dans une liste OK\n");
         szNbInser--;
      }
      else
      {
         printf("(CLIST_RemoveData) Test de suppression dans une liste KO\n");
         iResult = 1;
      }

      if(CLIST_RemoveData(pList1, "ChaineZ") == CLIST_CELL_NOT_FOUND)
      {
         printf("(CLIST_RemoveData) Test de suppression d'un element non present dans une liste OK\n");
      }
      else
      {
         printf("(CLIST_RemoveData) Test de suppression d'un element non present dans une liste KO\n");
         iResult = 1;
      }

      if(CLIST_RemoveData(pList2, "ChaineB") == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_RemoveData) Test de suppression dans une liste vide OK\n");
      }
      else
      {
         printf("(CLIST_RemoveData) Test de suppression dans une liste vide KO\n");
         iResult = 1;
      }

      if(CLIST_RemoveData(pCloneList1, "ChaineB") == CLIST_NO_COMP_FONCTION)
      {
         printf("(CLIST_RemoveData) Test de suppression dans une liste sans comparateur OK\n");
      }
      else
      {
         printf("(CLIST_RemoveData) Test de suppression dans une liste sans comparateur KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_RemoveDataFct() */
   {
      if(CLIST_RemoveDataFct(pList1, "ChaineB", TstCompar) == CLIST_NO_ERROR)
      {
         printf("(CLIST_RemoveDataFct) Test de suppression dans une liste OK\n");
         szNbInser--;
      }
      else
      {
         printf("(CLIST_RemoveDataFct) Test de suppression dans une liste KO\n");
         iResult = 1;
      }

      if(CLIST_RemoveDataFct(pList1, "ChaineZ", TstCompar) == CLIST_CELL_NOT_FOUND)
      {
         printf("(CLIST_RemoveDataFct) Test de suppression d'un element non present dans une liste OK\n");
      }
      else
      {
         printf("(CLIST_RemoveDataFct) Test de suppression d'un element non present dans une liste KO\n");
         iResult = 1;
      }

      if(CLIST_RemoveDataFct(pList2, "ChaineB", TstCompar) == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_RemoveDataFct) Test de suppression dans une liste vide OK\n");
      }
      else
      {
         printf("(CLIST_RemoveDataFct) Test de suppression dans une liste vide KO\n");
         iResult = 1;
      }

      if(CLIST_RemoveDataFct(pCloneList1, "ChaineB", TstCompar) == CLIST_NO_ERROR)
      {
         printf("(CLIST_RemoveDataFct) Test de suppression dans une liste sans comparateur OK\n");
         szNbCloneInser--;
      }
      else
      {
         printf("(CLIST_RemoveDataFct) Test de suppression dans une liste sans comparateur KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_RemoveDataRev() */
   {
      if(CLIST_RemoveDataRev(pList1, "ChaineB") == CLIST_NO_ERROR)
      {
         printf("(CLIST_RemoveDataRev) Test de suppression dans une liste OK\n");
         szNbInser--;
      }
      else
      {
         printf("(CLIST_RemoveDataRev) Test de suppression dans une liste KO\n");
         iResult = 1;
      }

      if(CLIST_RemoveDataRev(pList1, "ChaineZ") == CLIST_CELL_NOT_FOUND)
      {
         printf("(CLIST_RemoveDataRev) Test de suppression d'un element non present dans une liste OK\n");
      }
      else
      {
         printf("(CLIST_RemoveDataRev) Test de suppression d'un element non present dans une liste KO\n");
         iResult = 1;
      }

      if(CLIST_RemoveDataRev(pList2, "ChaineB") == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_RemoveDataRev) Test de suppression dans une liste vide OK\n");
      }
      else
      {
         printf("(CLIST_RemoveDataRev) Test de suppression dans une liste vide KO\n");
         iResult = 1;
      }

      if(CLIST_RemoveDataRev(pCloneList1, "ChaineB") == CLIST_NO_COMP_FONCTION)
      {
         printf("(CLIST_RemoveDataRev) Test de suppression dans une liste sans comparateur OK\n");
      }
      else
      {
         printf("(CLIST_RemoveDataRev) Test de suppression dans une liste sans comparateur KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_RemoveDataRevFct() */
   {
      if(CLIST_RemoveDataRevFct(pList1, "ChaineB", TstCompar) == CLIST_NO_ERROR)
      {
         printf("(CLIST_RemoveDataRevFct) Test de suppression dans une liste OK\n");
         szNbInser--;
      }
      else
      {
         printf("(CLIST_RemoveDataRevFct) Test de suppression dans une liste KO\n");
         iResult = 1;
      }

      if(CLIST_RemoveDataRevFct(pList1, "ChaineZ", TstCompar) == CLIST_CELL_NOT_FOUND)
      {
         printf("(CLIST_RemoveDataRevFct) Test de suppression d'un element non present dans une liste OK\n");
      }
      else
      {
         printf("(CLIST_RemoveDataRevFct) Test de suppression d'un element non present dans une liste KO\n");
         iResult = 1;
      }

      if(CLIST_RemoveDataRevFct(pList2, "ChaineB", TstCompar) == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_RemoveDataRevFct) Test de suppression dans une liste vide OK\n");
      }
      else
      {
         printf("(CLIST_RemoveDataRevFct) Test de suppression dans une liste vide KO\n");
         iResult = 1;
      }

      if(CLIST_RemoveDataRevFct(pCloneList1, "ChaineB", TstCompar) == CLIST_NO_ERROR)
      {
         printf("(CLIST_RemoveDataRevFct) Test de suppression dans une liste sans comparateur OK\n");
         szNbCloneInser--;
      }
      else
      {
         printf("(CLIST_RemoveDataRevFct) Test de suppression dans une liste sans comparateur KO\n");
         iResult = 1;
      }
   }

   /* On verifie que les elements ont bien ete enleve */
   {
      if(CLIST_Size(pList1) != szNbInser)
      {
         printf("(CLIST_RemoveDataXXXX) La taille de la liste pList1 est incorrecte\n");
         iResult = 1;
      }


      if(CLIST_Size(pCloneList1) != szNbCloneInser)
      {
         printf("(CLIST_RemoveDataXXXX) La taille de la liste pCloneList1 est incorrecte\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_RemoveAllData() */
   {
      if(CLIST_RemoveAllData(pList1, "ChaineB") == CLIST_NO_ERROR)
      {
         printf("(CLIST_RemoveAllData) Test de suppression dans une liste OK\n");
      }
      else
      {
         printf("(CLIST_RemoveAllData) Test de suppression dans une liste KO\n");
         iResult = 1;
      }

      if(CLIST_RemoveAllData(pList1, "ChaineZ") == CLIST_NO_ERROR)
      {
         printf("(CLIST_RemoveAllData) Test de suppression d'un element non present dans une liste OK\n");
      }
      else
      {
         printf("(CLIST_RemoveAllData) Test de suppression d'un element non present dans une liste KO\n");
         iResult = 1;
      }

      if(CLIST_RemoveAllData(pList2, "ChaineB") == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_RemoveAllData) Test de suppression dans une liste vide OK\n");
      }
      else
      {
         printf("(CLIST_RemoveAllData) Test de suppression dans une liste vide KO\n");
         iResult = 1;
      }

      if(CLIST_RemoveAllData(pCloneList1, "ChaineB") == CLIST_NO_COMP_FONCTION)
      {
         printf("(CLIST_RemoveAllData) Test de suppression dans une liste sans comparateur OK\n");
      }
      else
      {
         printf("(CLIST_RemoveAllData) Test de suppression dans une liste sans comparateur KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction CLIST_RemoveDataFct() */
   {
      if(CLIST_RemoveAllDataFct(pList1, "ChaineB", TstCompar) == CLIST_NO_ERROR)
      {
         printf("(CLIST_RemoveAllDataFct) Test de suppression dans une liste OK\n");
      }
      else
      {
         printf("(CLIST_RemoveAllDataFct) Test de suppression dans une liste KO\n");
         iResult = 1;
      }

      if(CLIST_RemoveAllDataFct(pList1, "ChaineZ", TstCompar) == CLIST_NO_ERROR)
      {
         printf("(CLIST_RemoveAllDataFct) Test de suppression d'un element non present dans une liste OK\n");
      }
      else
      {
         printf("(CLIST_RemoveAllDataFct) Test de suppression d'un element non present dans une liste KO\n");
         iResult = 1;
      }

      if(CLIST_RemoveAllDataFct(pList2, "ChaineB", TstCompar) == CLIST_EMPTY_LIST)
      {
         printf("(CLIST_RemoveAllDataFct) Test de suppression dans une liste vide OK\n");
      }
      else
      {
         printf("(CLIST_RemoveAllDataFct) Test de suppression dans une liste vide KO\n");
         iResult = 1;
      }

      if(CLIST_RemoveAllDataFct(pCloneList1, "ChaineB", TstCompar) == CLIST_NO_ERROR)
      {
         printf("(CLIST_RemoveAllDataFct) Test de suppression dans une liste sans comparateur OK\n");
      }
      else
      {
         printf("(CLIST_RemoveAllDataFct) Test de suppression dans une liste sans comparateur KO\n");
         iResult = 1;
      }
   }

   /* On verifie que les elements ont bien ete enleve */
   {
      if(CLIST_Size(pList1) != 3)
      {
         printf("(CLIST_RemoveAllDataXXXX) La taille de la liste pList1 est incorrecte\n");
         iResult = 1;
      }

      if(CLIST_Size(pCloneList1) != 3)
      {
         printf("(CLIST_RemoveAllDataXXXX) La taille de la liste pCloneList1 est incorrecte\n");
         iResult = 1;
      }
   }

   /* Desctruction des listes */
   {
      CLIST_Destroy(pList1);
      CLIST_Destroy(pList2);
      CLIST_Destroy(pCloneList1);
   }

   return iResult;
}
