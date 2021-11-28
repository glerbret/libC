#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"
#include "stack.h"
#include "test.h"

typedef struct
{
   char*       pcString;
   size_t      szSize;
} DupString_s;

int      TstStack(void)
{
   int            iResult = 0;
   size_t         szNbInser = 0;
   size_t         szIdx;
   stack_s*       pStack1;
   stack_s*       pStack2;
   stack_s*       pCloneStack1;
   stack_s*       pCloneStack2;
   STACK_Error_e  eError;
   const char*    pcData;

   /* Creation des donnees a inserer */
   const char*    apcString[] =
   {
      "chaine1",
      "chaine2"
   };

   printf("\nTest de \"%s\"\n", STACK_Identifier());

   /* Test de la fonction STACK_Init() */
   {
      pStack1 = STACK_Create(&eError);
      if(pStack1 == NULL || eError != STACK_NO_ERROR)
      {
         printf("(STACK_Create) Test creation d'une pile KO\n");
         return 1;
      }
      else
      {
         printf("(STACK_Create) Test creation d'une pile OK\n");
      }

      pStack2 = STACK_Create(&eError);
      if(pStack2 == NULL || eError != STACK_NO_ERROR)
      {
         printf("(STACK_Create) Test creation d'une pile KO\n");
         return 1;
      }
   }

   /* Test de la fonction STACK_IsEmpty() sur une pile vide */
   {
      if(STACK_IsEmpty(pStack1) == false)
      {
         printf("(STACK_IsEmpty) Test sur une pile vide KO\n");
         iResult=1;
      }
      else
      {
         printf("(STACK_IsEmpty) Test sur une pile vide OK\n");
      }
   }

   /* Test de la fonction STACK_Size() sur une pile vide */
   {
      if(STACK_Size(pStack1) != 0)
      {
         printf("(STACK_Size) Test sur une pile vide KO\n");
         iResult=1;
      }
      else
      {
         printf("(STACK_Size) Test sur une pile vide OK\n");
      }
   }

   /* Test de la fonction STACK_Push() */
   {
      for(szIdx = 0; szIdx < sizeof(apcString)/sizeof(apcString[0]); szIdx++)
      {
         if(STACK_Push(pStack1, apcString[szIdx], strlen(apcString[szIdx])+1) == STACK_NO_ERROR)
         {
            printf("(STACK_Push) Test d'insertion %lu OK\n", (unsigned long)szIdx);
            szNbInser++;
         }
         else
         {
            printf("(STACK_Push) Test d'insertion %lu KO\n", (unsigned long)szIdx);
            iResult = 1;
         }
      }
   }

   /* Test de la fonction STACK_IsEmpty() sur une pile non vide */
   {
      if(STACK_IsEmpty(pStack1) != false)
      {
         printf("(STACK_IsEmpty) Test sur une pile non vide KO\n");
         iResult=1;
      }
      else
      {
         printf("(STACK_IsEmpty) Test sur une pile non vide OK\n");
      }
   }

   /* Test de la fonction STACK_Size() sur une pile non vide */
   {
      if(STACK_Size(pStack1) != szNbInser)
      {
         printf("(STACK_Size) Test sur une pile non vide KO\n");
         iResult=1;
      }
      else
      {
         printf("(STACK_Size) Test sur une pile non vide OK\n");
      }
   }

   /* Test de la fonction STACK_Clone() */
   {
      pCloneStack1 = STACK_Clone(pStack1, &eError);
      if(pCloneStack1 == NULL || eError != STACK_NO_ERROR)
      {
         printf("(STACK_Clone) Test duplication d'une pile KO\n");
         pCloneStack1 = NULL;
         iResult = 1;
      }
      else
      {
         /* On verifie que tout semble bien se passer */
         if(STACK_IsEmpty(pCloneStack1) == false && STACK_Size(pCloneStack1) == szNbInser)
         {
            printf("(STACK_Clone) Test duplication d'une pile OK\n");
         }
         else
         {
            printf("(STACK_Clone) Test duplication d'une pile KO\n");
            iResult = 1;
         }
      }

      pCloneStack2 = STACK_Clone(pStack2, &eError);
      if(pCloneStack2 == NULL || eError != STACK_NO_ERROR)
      {
         printf("(STACK_Clone) Test duplication d'une pile vide KO\n");
         pCloneStack2 = NULL;
         iResult = 1;
      }
      else
      {
         /* On verifie que tout semble bien se passer */
         if(STACK_IsEmpty(pCloneStack2) == true && STACK_Size(pCloneStack2) == 0)
         {
            printf("(STACK_Clone) Test duplication d'une pile vide OK\n");
         }
         else
         {
            printf("(STACK_Clone) Test duplication d'une pile vide KO\n");
            iResult = 1;
         }
      }
   }

   /* Test de la fonction STACK_Peek() */
   {
      pcData = STACK_Peek(pCloneStack1, &eError);
      if(pcData == NULL || eError != STACK_NO_ERROR)
      {
         printf("(STACK_Peek) Test lecture d'une pile KO\n");
         iResult = 1;
      }
      else
      {
         if(strcmp(pcData, "chaine2") == 0)
         {
            printf("(STACK_Peek) Test lecture d'une pile OK\n");
         }
         else
         {
            printf("(STACK_Peek) Test lecture d'une pile KO\n");
            iResult = 1;
         }
      }

      pcData = STACK_Peek(pStack2, &eError);
      if(pcData == NULL &&  eError == STACK_EMPTY_STACK)
      {
         printf("(STACK_Peek) Test lecture d'une pile vide OK\n");
      }
      else
      {
         printf("(STACK_Peek) Test lecture d'une pile vide KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction STACK_Pop() */
   {
      pcData = STACK_Pop(pCloneStack1, &eError);
      if(pcData == NULL || eError != STACK_NO_ERROR)
      {
         printf("(STACK_Pop) Test depilement d'une pile KO\n");
         iResult = 1;
      }
      else
      {
         szNbInser--;
         if(strcmp(pcData, "chaine2") == 0 && STACK_Size(pCloneStack1) == szNbInser)
         {
            printf("(STACK_Pop) Test depilement d'une pile OK\n");
            free((void*)pcData), pcData = NULL;
         }
         else
         {
            printf("(STACK_Pop) Test depilement d'une pile KO\n");
            iResult = 1;
         }
      }

      pcData = STACK_Pop(pStack2, &eError);
      if(pcData == NULL &&  eError == STACK_EMPTY_STACK)
      {
         printf("(STACK_Pop) Test depilement d'une pile vide OK\n");
      }
      else
      {
         printf("(STACK_Pop) Test depilement d'une pile vide KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction STACK_Remove() */
   {
      eError = STACK_Remove(pCloneStack1);
      if(eError != STACK_NO_ERROR)
      {
         printf("(STACK_Remove) Test suppression d'un element d'une pile KO\n");
         iResult = 1;
      }
      else
      {
         szNbInser--;
         if(STACK_Size(pCloneStack1) == szNbInser)
         {
            printf("(STACK_Remove) Test suppression d'un element d'une pile OK\n");
         }
         else
         {
            printf("(STACK_Remove) Test suppression d'un element d'une pile KO\n");
            iResult = 1;
         }
      }

      eError = STACK_Remove(pStack2);
      if(eError == STACK_EMPTY_STACK)
      {
         printf("(STACK_Remove) Test depilement d'une pile vide OK\n");
      }
      else
      {
         printf("(STACK_Remove) Test depilement d'une pile vide KO\n");
         iResult = 1;
      }
   }

   /* Test de la fonction STACK_Destroy() */
   {
      STACK_Destroy(pStack1);
      STACK_Destroy(pStack2);
      STACK_Destroy(pCloneStack1);
      STACK_Destroy(pCloneStack2);

      printf("(STACK_Destroy) Test de destructon d'une pile OK\n");
   }

   return iResult;
}
