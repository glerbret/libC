#include "bool.h"
#include "queue.h"
#include "test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int TstQueue(void)
{
  int result = 0;
  size_t nbInser = 0;
  queue_s* queue1;
  queue_s* queue2;
  queue_s* cloneQueue1;
  queue_s* cloneQueue2;

  printf("\nTest de \"%s\"\n", QUEUE_Identifier());

  /* Test de la fonction QUEUE_Init() */
  {
    queue1 = QUEUE_Create();
    if(queue1 == NULL)
    {
      printf("(QUEUE_Create) Test creation d'une file KO\n");
      return 1;
    }
    else
    {
      printf("(QUEUE_Create) Test creation d'une file OK\n");
    }

    queue2 = QUEUE_Create();
    if(queue2 == NULL)
    {
      printf("(QUEUE_Create) Test creation d'une file KO\n");
      return 1;
    }
  }

  /* Test de la fonction QUEUE_IsEmpty() sur une file vide */
  {
    if(QUEUE_IsEmpty(queue1) == false)
    {
      printf("(QUEUE_IsEmpty) Test sur une file vide KO\n");
      result = 1;
    }
    else
    {
      printf("(QUEUE_IsEmpty) Test sur une file vide OK\n");
    }
  }

  /* Test de la fonction QUEUE_Size() sur une file vide */
  {
    if(QUEUE_Size(queue1) != 0)
    {
      printf("(QUEUE_Size) Test sur une file vide KO\n");
      result = 1;
    }
    else
    {
      printf("(QUEUE_Size) Test sur une file vide OK\n");
    }
  }

  /* Test de la fonction QUEUE_Enqueue() */
  {
    const char* strings[] =
    {
      "chaine1",
      "chaine2"
    };

    for(size_t idx = 0; idx < sizeof(strings) / sizeof(strings[0]); idx++)
    {
      if(QUEUE_Enqueue(queue1, strings[idx], strlen(strings[idx]) + 1) == QUEUE_NO_ERROR)
      {
        printf("(QUEUE_Enqueue) Test d'insertion %lu OK\n", (unsigned long)idx);
        nbInser++;
      }
      else
      {
        printf("(QUEUE_Enqueue) Test d'insertion %lu KO\n", (unsigned long)idx);
        result = 1;
      }
    }
  }

  /* Test de la fonction QUEUE_IsEmpty() sur une file non vide */
  {
    if(QUEUE_IsEmpty(queue1) != false)
    {
      printf("(QUEUE_IsEmpty) Test sur une file non vide KO\n");
      result = 1;
    }
    else
    {
      printf("(QUEUE_IsEmpty) Test sur une file non vide OK\n");
    }
  }

  /* Test de la fonction QUEUE_Size() sur une file non vide */
  {
    if(QUEUE_Size(queue1) != nbInser)
    {
      printf("(QUEUE_Size) Test sur une file non vide KO\n");
      result = 1;
    }
    else
    {
      printf("(QUEUE_Size) Test sur une file non vide OK\n");
    }
  }

  /* Test de la fonction QUEUE_Clone() */
  {
    cloneQueue1 = QUEUE_Clone(queue1);
    if(cloneQueue1 == NULL)
    {
      printf("(QUEUE_Clone) Test duplication d'une file KO\n");
      cloneQueue1 = NULL;
      result = 1;
    }
    else
    {
      /* On verifie que tout semble bien se passer */
      if(QUEUE_IsEmpty(cloneQueue1) == false && QUEUE_Size(cloneQueue1) == nbInser)
      {
        printf("(QUEUE_Clone) Test duplication d'une file OK\n");
      }
      else
      {
        printf("(QUEUE_Clone) Test duplication d'une file KO\n");
        result = 1;
      }
    }

    cloneQueue2 = QUEUE_Clone(queue2);
    if(cloneQueue2 == NULL)
    {
      printf("(QUEUE_Clone) Test duplication d'une file vide KO\n");
      cloneQueue2 = NULL;
      result = 1;
    }
    else
    {
      /* On verifie que tout semble bien se passer */
      if(QUEUE_IsEmpty(cloneQueue2) == true && QUEUE_Size(cloneQueue2) == 0)
      {
        printf("(QUEUE_Clone) Test duplication d'une file vide OK\n");
      }
      else
      {
        printf("(QUEUE_Clone) Test duplication d'une file vide KO\n");
        result = 1;
      }
    }
  }

  /* Test de la fonction QUEUE_Peek() */
  {
    const char* data = QUEUE_Peek(cloneQueue1);
    if(data == NULL)
    {
      printf("(QUEUE_Peek) Test lecture d'une file KO\n");
      result = 1;
    }
    else
    {
      if(strcmp(data, "chaine1") == 0)
      {
        printf("(QUEUE_Peek) Test lecture d'une file OK\n");
      }
      else
      {
        printf("(QUEUE_Peek) Test lecture d'une file KO\n");
        result = 1;
      }
    }

    data = QUEUE_Peek(queue2);
    if(data == NULL)
    {
      printf("(QUEUE_Peek) Test lecture d'une file vide OK\n");
    }
    else
    {
      printf("(QUEUE_Peek) Test lecture d'une file vide KO\n");
      result = 1;
    }
  }

  /* Test de la fonction QUEUE_Dequeue() */
  {
    const char* data = QUEUE_Dequeue(cloneQueue1);
    if(data == NULL)
    {
      printf("(QUEUE_Dequeue) Test depilement d'une file KO\n");
      result = 1;
    }
    else
    {
      nbInser--;
      if(strcmp(data, "chaine1") == 0 && QUEUE_Size(cloneQueue1) == nbInser)
      {
        printf("(QUEUE_Dequeue) Test depilement d'une file OK\n");
        free((void*)data), data = NULL;
      }
      else
      {
        printf("(QUEUE_Dequeue) Test depilement d'une file KO\n");
        result = 1;
      }
    }

    data = QUEUE_Dequeue(queue2);
    if(data == NULL)
    {
      printf("(QUEUE_Dequeue) Test depilement d'une file vide OK\n");
    }
    else
    {
      printf("(QUEUE_Dequeue) Test depilement d'une file vide KO\n");
      result = 1;
    }
  }

  /* Test de la fonction QUEUE_Remove() */
  {
    if(QUEUE_Remove(cloneQueue1) != QUEUE_NO_ERROR)
    {
      printf("(QUEUE_Remove) Test suppression d'un element d'une file KO\n");
      result = 1;
    }
    else
    {
      nbInser--;
      if(QUEUE_Size(cloneQueue1) == nbInser)
      {
        printf("(QUEUE_Remove) Test suppression d'un element d'une file OK\n");
      }
      else
      {
        printf("(QUEUE_Remove) Test suppression d'un element d'une file KO\n");
        result = 1;
      }
    }

    if(QUEUE_Remove(queue2) == QUEUE_EMPTY_QUEUE)
    {
      printf("(QUEUE_Remove) Test suppression d'une file vide OK\n");
    }
    else
    {
      printf("(QUEUE_Remove) Test suppression d'une file vide KO\n");
      result = 1;
    }
  }

  /* Test de la fonction QUEUE_Destroy() */
  {
    QUEUE_Destroy(queue1);
    QUEUE_Destroy(queue2);
    QUEUE_Destroy(cloneQueue1);
    QUEUE_Destroy(cloneQueue2);

    printf("(QUEUE_Destroy) Test de destructon d'une file OK\n");
  }

  return result;
}
