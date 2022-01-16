/**
 * @brief Calcul et de controle des modulo 97.
 * @version 1.0.0.
 * @copyright MIT license.
 * @author Gregory Lerbret.
 */

#include "modulus97.h"
#include "bool.h"

#include <stdio.h>
#include <string.h>

#define xstr(s) str(s)
#define str(s) #s

#define MOD97_NAME	    "Calcul des modulo 97"
#define MOD97_VERS_MAJ  1
#define MOD97_VERS_MIN  0
#define MOD97_VERS_BRCH 0
#define MOD97_ID        MOD97_NAME " - Version " xstr(MOD97_VERS_MAJ) "." xstr(MOD97_VERS_MIN) "." xstr(MOD97_VERS_BRCH)

static int MOD97_CalculateModulus97(const char* number)
{
  int modulus = 0;

  /* Longueur du nombre */
  const size_t len = strlen(number);

  /* Calcul du modulo */
  for(size_t idx = 0; idx < len; idx++)
  {
    modulus = ((modulus * 10) + (number[idx] - '0')) % 97;
  }

  return modulus;
}

static int MOD97_CalculateReducedModulus97(const char* number)
{
  /* Calcul du modulo 97 */
  const int modulus97 = MOD97_CalculateModulus97(number);

  /* Reduction du modulo 97 */
  const int r0 = modulus97 % 10;
  const int r1 = modulus97 / 10;
  return (r1 + 2 * r0) % 10;
}

const char* MOD97_Identifier(void)
{
  return MOD97_ID;
}

int MOD97_Version(void)
{
  return MOD97_VERS_MAJ * 10000 + MOD97_VERS_MIN * 100 + MOD97_VERS_BRCH;
}

bool MOD97_CheckRIBKey(const char* number)
{
  return MOD97_CalculateModulus97(number) == 0;
}

int MOD97_CalculateRIBKey(const char* number)
{
  /* Calcul du modulo des donnees presente */
  int modulus97 = MOD97_CalculateModulus97(number);

  /* Calcul de la cle */
  modulus97 = (modulus97 * 100) % 97;
  modulus97 = 97 - modulus97;

  return modulus97;
}

bool MOD97_CheckNIRKey(const char* number, int key)
{
  const int modulus97 = MOD97_CalculateModulus97(number);
  return modulus97 + key == 97;
}

int MOD97_CalculateNIRKey(const char* number)
{
  /* Calcul du modulo des donnees presente    */
  int modulus97 = MOD97_CalculateModulus97(number);

  /* Calcul de la cle */
  modulus97 = 97 - modulus97;

  return modulus97;
}

bool MOD97_CheckReducedMod97Key(const char* number, int key)
{
  return MOD97_CalculateReducedModulus97(number) == key;
}

int MOD97_CalculateReducedMod97Key(const char* number)
{
  return MOD97_CalculateReducedModulus97(number);
}

bool MOD97_CheckRLMCKey(const char* number)
{
  return MOD97_CalculateModulus97(number) == 0;
}

int MOD97_CalculateRLMCKey(const char* number)
{
  /* Calcul du modulo des donnees presente */
  int modulus97 = MOD97_CalculateModulus97(number);

  /* Calcul de la cle */
  modulus97 = (modulus97 * 100) % 97;
  modulus97 = 97 - modulus97;

  return modulus97;
}
