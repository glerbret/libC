#include "modulus97.h"
#include "test.h"
#include "bool.h"

#include <stdio.h>
#include <string.h>

typedef struct
{
  const char* number;
  int         key;
} modulo97_s;

int TstModulus97(void)
{
  const char* ribOK[] =
  {
    "14506020305210889900045"
  };
  const char* ribKO[] =
  {
    "14506020305210889900048"
  };
  modulo97_s calculatedRib[] =
  {
    {"145060203052108899000",  45}
  };
  modulo97_s nirOK[] =
  {
    {"1781142218207", 63}
  };
  modulo97_s nirKO[] =
  {
    {"1781148218207", 63}
  };
  modulo97_s calculatedNir[] =
  {
    {"1781142218207", 63}
  };
  modulo97_s reducedOK[] =
  {
    {"12345",   4}
  };
  modulo97_s reducedKO[] =
  {
    {"12345",   8}
  };
  modulo97_s calculatedReduced[] =
  {
    {"12345",   4}
  };
  const char* rlmcOK[] =
  {
    "667954504201450690805210889900090"
  };
  const char* rlmcKO[] =
  {
    "667954504201450690805210889900012"
  };
  modulo97_s calculatedRlmc[] =
  {
    {"6679545042014506908052108899000",  90}
  };
  int result = 0;

  printf("\nTest de \"%s\"\n", MOD97_Identifier());

  /* test de la fonction de verification RIB sur des numeros corrects */
  for(size_t idx = 0; idx < (sizeof(ribOK) / sizeof(ribOK[0])); idx++)
  {
    if(MOD97_CheckRIBKey(ribOK[idx]))
    {
      printf("(MOD97_CheckRIBKey) test validite RIB numero correct %d OK\n", (int)(idx + 1));
    }
    else
    {
      printf("(MOD97_CheckRIBKey) test validite RIB numero correct %d KO\n", (int)(idx + 1));
      result = 1;
    }
  }

  /* test de la fonction de verification RIB sur des numeros incorrects */
  for(size_t idx = 0; idx < (sizeof(ribKO) / sizeof(ribKO[0])); idx++)
  {
    if(MOD97_CheckRIBKey(ribKO[idx]))
    {
      printf("(MOD97_CheckRIBKey) test validite RIB numero errone %d KO\n", (int)(idx + 1));
      result = 1;
    }
    else
    {
      printf("(MOD97_CheckRIBKey) test validite RIB numero errone %d OK\n", (int)(idx + 1));
    }
  }

  /* test de la fonction de calcul de RIB*/
  for(size_t idx = 0; idx < (sizeof(calculatedRib) / sizeof(calculatedRib[0])); idx++)
  {
    if(MOD97_CalculateRIBKey(calculatedRib[idx].number) == calculatedRib[idx].key)
    {
      printf("(MOD97_CalculateRIBKey) test calcul RIB %d OK\n", (int)(idx + 1));
    }
    else
    {
      printf("(MOD97_CalculateRIBKey) test calcul RIB %d KO", (int)(idx + 1));
      result = 1;
    }
  }

  /* test de la fonction de verification NIR sur des numeros corrects */
  for(size_t idx = 0; idx < (sizeof(nirOK) / sizeof(nirOK[0])); idx++)
  {
    if(MOD97_CheckNIRKey(nirOK[idx].number, nirOK[idx].key))
    {
      printf("(MOD97_CheckNIRKey) test validite NIR numero correct %d OK\n", (int)(idx + 1));
    }
    else
    {
      printf("(MOD97_CheckNIRKey) test validite NIR numero correct %d KO\n", (int)(idx + 1));
      result = 1;
    }
  }

  /* test de la fonction de verification NIR sur des numeros incorrects */
  for(size_t idx = 0; idx < (sizeof(nirKO) / sizeof(nirKO[0])); idx++)
  {
    if(MOD97_CheckNIRKey(nirKO[idx].number, nirKO[idx].key))
    {
      printf("(MOD97_CheckNIRKey) test validite NIR numero errone %d KO\n", (int)(idx + 1));
      result = 1;
    }
    else
    {
      printf("(MOD97_CheckNIRKey) test validite NIR numero errone %d OK\n", (int)(idx + 1));
    }
  }

  /* test de la fonction de calcul de NIR*/
  for(size_t idx = 0; idx < (sizeof(calculatedNir) / sizeof(calculatedNir[0])); idx++)
  {
    if(MOD97_CalculateNIRKey(calculatedNir[idx].number) == calculatedNir[idx].key)
    {
      printf("(MOD97_CalculateNIRKey) test calcul NIR %d OK\n", (int)(idx + 1));
    }
    else
    {
      printf("(MOD97_CalculateNIRKey) test calcul NIR %d KO", (int)(idx + 1));
      result = 1;
    }
  }

  /* test de la fonction de verification modulo 97 reduit sur des numeros corrects */
  for(size_t idx = 0; idx < (sizeof(reducedOK) / sizeof(reducedOK[0])); idx++)
  {
    if(MOD97_CheckReducedMod97Key(reducedOK[idx].number, reducedOK[idx].key))
    {
      printf("(MOD97_CheckReducedMod97Key) test validite numero correct %d OK\n", (int)(idx + 1));
    }
    else
    {
      printf("(MOD97_CheckReducedMod97Key) test validite numero correct %d KO\n", (int)(idx + 1));
      result = 1;
    }
  }

  /* test de la fonction de verification NIR sur des numeros incorrects */
  for(size_t idx = 0; idx < (sizeof(reducedKO) / sizeof(reducedKO[0])); idx++)
  {
    if(MOD97_CheckReducedMod97Key(reducedKO[idx].number, reducedKO[idx].key))
    {
      printf("(MOD97_CheckReducedMod97Key) test validite numero errone %d KO\n", (int)(idx + 1));
      result = 1;
    }
    else
    {
      printf("(MOD97_CheckReducedMod97Key) test validite numero errone %d OK\n", (int)(idx + 1));
    }
  }

  /* test de la fonction de calcul de NIR*/
  for(size_t idx = 0; idx < (sizeof(calculatedReduced) / sizeof(calculatedReduced[0])); idx++)
  {
    if(MOD97_CalculateReducedMod97Key(calculatedReduced[idx].number) == calculatedReduced[idx].key)
    {
      printf("(MOD97_CalculateReducedMod97Key) test calcul %d OK\n", (int)(idx + 1));
    }
    else
    {
      printf("(MOD97_CalculateReducedMod97Key) test calcul %d KO", (int)(idx + 1));
      result = 1;
    }
  }

  /* test de la fonction de verification RLMC sur des numeros corrects */
  for(size_t idx = 0; idx < (sizeof(rlmcOK) / sizeof(rlmcOK[0])); idx++)
  {
    if(MOD97_CheckRLMCKey(rlmcOK[idx]))
    {
      printf("(MOD97_CheckRLMCKey) test validite RLMC numero correct %d OK\n", (int)(idx + 1));
    }
    else
    {
      printf("(MOD97_CheckRLMCKey) test validite RLMC numero correct %d KO\n", (int)(idx + 1));
      result = 1;
    }
  }

  /* test de la fonction de verification RLMC sur des numeros incorrects */
  for(size_t idx = 0; idx < (sizeof(rlmcKO) / sizeof(rlmcKO[0])); idx++)
  {
    if(MOD97_CheckRLMCKey(rlmcKO[idx]))
    {
      printf("(MOD97_CheckRLMCKey) test validite RLMC numero errone %d KO\n", (int)(idx + 1));
      result = 1;
    }
    else
    {
      printf("(MOD97_CheckRLMCKey) test validite RLMC numero errone %d OK\n", (int)(idx + 1));
    }
  }

  /* test de la fonction de calcul de RLMC*/
  for(size_t idx = 0; idx < (sizeof(calculatedRlmc) / sizeof(calculatedRlmc[0])); idx++)
  {
    if(MOD97_CalculateRLMCKey(calculatedRlmc[idx].number) == calculatedRlmc[idx].key)
    {
      printf("(MOD97_CalculateRLMCKey) test calcul RLMC %d OK\n", (int)(idx + 1));
    }
    else
    {
      printf("(MOD97_CalculateRLMCKey) test calcul RLMC %d KO", (int)(idx + 1));
      result = 1;
    }
  }

  return result;
}
