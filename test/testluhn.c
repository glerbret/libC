#include "luhn.h"
#include "test.h"
#include "bool.h"

#include <stdio.h>
#include <string.h>

typedef struct
{
  const char* number;
  char        key;
} carte_s;

int TstLuhn(void)
{
  const char* numTest[] =
  {
    "67030403669228008",
    "4972880061065935"
  };
  const char* numTestKO[] =
  {
    "67030403569228008",
    "4972880021065935"
  };
  carte_s testCard[] =
  {
    {"6703040366922800", '8'},
    {"497288006106593",  '5'}
  };
  int result = 0;

  printf("\nTest de \"%s\"\n", LUHN_Identifier());

  /* test de la fonction de verification sur des numeros corrects */
  for(size_t idx = 0; idx < (sizeof(numTest) / sizeof(numTest[0])); idx++)
  {
    if(LUHN_CheckLuhnKey(numTest[idx]))
    {
      printf("(LUHN_CheckLuhnKey) test validite numero correct %d OK\n", (int)(idx + 1));
    }
    else
    {
      printf("(LUHN_CheckLuhnKey) test validite numero correct %d KO\n", (int)(idx + 1));
      result = 1;
    }
  }

  /* test de la fonction de verification sur des numeros incorrects */
  for(size_t idx = 0; idx < (sizeof(numTestKO) / sizeof(numTestKO[0])); idx++)
  {
    if(LUHN_CheckLuhnKey(numTestKO[idx]))
    {
      printf("(LUHN_CheckLuhnKey) test validite numero errone %d KO\n", (int)(idx + 1));
      result = 1;
    }
    else
    {
      printf("(LUHN_CheckLuhnKey) test validite numero errone %d OK\n", (int)(idx + 1));
    }
  }

  /* test de la fonction de calcul */
  for(size_t idx = 0; idx < (sizeof(testCard) / sizeof(testCard[0])); idx++)
  {
    if(LUHN_CalculateLuhnKey(testCard[idx].number) == testCard[idx].key)
    {
      printf("(LUHN_CalculateLuhnKey) test calcul %d OK\n", (int)(idx + 1));
    }
    else
    {
      printf("(LUHN_CalculateLuhnKey) test calcul %d KO", (int)(idx + 1));
      result = 1;
    }
  }

  return result;
}
