/**
   \author Grégory Lerbret
   \file luhn.c
   \brief Calcul et de controle des cles de Luhn.<br>
   \date 04/04/2005
   \version 1.0.0
*/

#include <stdio.h>
#include <string.h>
#include "luhn.h"

#define xstr(s) str(s)
#define str(s) #s

#define LUHN_NAME	         "Calcul des cles de Luhn"
#define LUHN_VERS_MAJ      1
#define LUHN_VERS_MIN      0
#define LUHN_VERS_BRCH     0
#define LUHN_ID		      LUHN_NAME " - Version " xstr(LUHN_VERS_MAJ) "." xstr(LUHN_VERS_MIN) "." xstr(LUHN_VERS_BRCH)

// TODO revoir le passage de iDouble dans LUHN_CalculateLuhnSum. Plutôt une info cle presente/non presente
// TODO Preciser contrainte : ce sont des chaînes de caracteres
// TODO LUHN_CalculalteLuhnKey ==> LUHN_CalculateLuhnKey
// TODO Dans LUHN_CalculalteLuhnKey pourquoi utiliser un char et non un int ?

/**
   \fn static int LUHN_CalculateLuhnSum(const char* pcNumber, int iDouble)
   \brief Calcul de la somme en suivant l'algorithme de cle de Luhn.
   \param[in] pcNumber le numero sur lequel appliquer l'algorithme de cle de Luhn
   \param[in] iDouble indique s'il faut doubler ou non le dernier caractere
   \return la somme calculee.
*/
static int LUHN_CalculateLuhnSum(const char* pcNumber, int iDouble)
{
   int      iIdx;
   int      iValue;
   int      iSum  = 0;

   for(iIdx = (int)strlen(pcNumber)-1; iIdx >= 0; iIdx--)
   {
      iValue = (pcNumber[iIdx] - '0') * iDouble;
      if (iValue >= 10)
      {
         iValue = (iValue % 10) + 1;
      }
      iSum += iValue;
      iDouble = (iDouble == 2 ? 1 : 2);
   }
   return iSum;
}

/**
   \fn const char* LUHN_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char* LUHN_Identifier(void)
{
   return LUHN_ID;
}

/**
   \fn int LUHN_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int LUHN_Version(void)
{
   return LUHN_VERS_MAJ*10000 + LUHN_VERS_MIN*100 + LUHN_VERS_BRCH;
}

/**
   \fn char LUHN_CalculalteLuhnKey(const char* pcNumber)
   \brief Calcul de la cle de Luhn.
   \param[in] pcNumber le numero dont on veut calculer la cle de Luhn
   \return la cle de Luhn sous sa forme ASCII.
*/
char LUHN_CalculalteLuhnKey(const char* pcNumber)
{
   char     cLuhn;

   cLuhn=(char)(10 - (LUHN_CalculateLuhnSum(pcNumber, 2) % 10));
   if(cLuhn == 10)
   {
      cLuhn = 0;
   }
   return (char)(cLuhn + '0');
}

/**
   \fn LUHN_Res_e LUHN_CheckLuhnKey(const char* pcNumber)
   \brief Verification de la cle de Luhn.
   \param[in] pcNumber le numero a verifier
   \return  LUHN_OK pour une cle de Luhn correcte.<br>
            LUHN_KO sinon
*/
LUHN_Res_e LUHN_CheckLuhnKey(const char* pcNumber)
{
   if((LUHN_CalculateLuhnSum(pcNumber, 1) % 10) == 0)
   {
      return LUHN_OK;
   }
   else
   {
      return LUHN_KO;
   }
}
