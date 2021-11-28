/**
   \author Grégory Lerbret
   \file modulus97.c
   \brief Calcul et de controle des modulo 97.<br>
   \date 04/04/2005
   \version 1.0.0
*/

#include <stdio.h>
#include <string.h>
#include "modulus97.h"

#define xstr(s) str(s)
#define str(s) #s

#define MOD97_NAME	      "Calcul des modulo 97"
#define MOD97_VERS_MAJ     1
#define MOD97_VERS_MIN     0
#define MOD97_VERS_BRCH    0
#define MOD97_ID           MOD97_NAME " - Version " xstr(MOD97_VERS_MAJ) "." xstr(MOD97_VERS_MIN) "." xstr(MOD97_VERS_BRCH)

/**
   \brief Calcul du modulo 97 du nombre fournit en argument.
   \param[in] pcNumber le numero sur lequel calculer le modulo 97.
   \return le modulo 97.
*/
static int MOD97_CalculateModulus97(const char* pcNumber)
{
   size_t   szIdx;
   size_t   szLen;
   int      iModulus;

   /* Longueur du nombre */
   szLen = strlen(pcNumber);

   /* Calcul du modulo */
   for(szIdx = 0, iModulus = 0; szIdx < szLen; szIdx++)
   {
      iModulus = ((iModulus * 10) + (pcNumber[szIdx] - '0')) % 97;
   }

   return iModulus;
}

/**
   \brief Calcul du modulo 97 reduit du nombre fournit en argument.
   \param[in] pcNumber le numero sur lequel calculer le modulo 97 reduit
   \return le modulo 97 reduit.
*/
static int MOD97_CalculateReducedModulus97(const char* pcNumber)
{
   int   iModulus97;
   int   iReducesModulus97;
   int   iR0;
   int   iR1;

   /* Calcul du modulo 97 */
   iModulus97 = MOD97_CalculateModulus97(pcNumber);

   /* Reduction du modulo 97 */
   iR0               = iModulus97 % 10;
   iR1               = iModulus97 / 10;
   iReducesModulus97 = (iR1 + 2*iR0) % 10;

   return iReducesModulus97;
}

/**
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char* MOD97_Identifier(void)
{
   return MOD97_ID;
}

/**
   \brief Version du module.
   \return La version du module.
*/
int MOD97_Version(void)
{
   return MOD97_VERS_MAJ*10000 + MOD97_VERS_MIN*100 + MOD97_VERS_BRCH;
}

/**
   \brief Verification de la validite d'un RIB.
   \param[in] pcNumber le numero de RIB complet (y comprit la cle).
   \return  MOD97_OK si le RIB est correct.<br>
            MOD97_KO sinon.
*/
MOD97_Res_e MOD97_CheckRIBKey(const char* pcNumber)
{
   if(MOD97_CalculateModulus97(pcNumber) == 0)
   {
      return MOD97_OK;
   }
   else
   {
      return MOD97_KO;
   }
}

/**
   \brief Calcul de la cle d'un RIB.
   \param[in] pcNumber le numero de RIB sans la cle.
   \return la cle RIB.
*/
int MOD97_CalculateRIBKey(const char* pcNumber)
{
   int   iModulus97;

   /* Calcul du modulo des donnees presente */
   iModulus97 = MOD97_CalculateModulus97(pcNumber);

   /* Calcul de la cle */
   iModulus97 = (iModulus97 * 100) % 97;
   iModulus97 = 97 - iModulus97;

   return iModulus97;
}

/**
   \brief Verification de la validite d'un NIR (Numero de Securite Sociale).
   \param[in] pcNumber le numero de NIR sans la cle.
   \param[in] iKey la cle du NIR.
   \return  MOD97_OK si le NIR est correct.<br>
            MOD97_KO sinon.
*/
MOD97_Res_e MOD97_CheckNIRKey(const char* pcNumber, int iKey)
{
   int   iModulus97;

   iModulus97 = MOD97_CalculateModulus97(pcNumber);

   if(iModulus97 + iKey == 97)
   {
      return MOD97_OK;
   }
   else
   {
      return MOD97_KO;
   }
}

/**
   \brief Calcul de la cle d'un NIR (numero de Securite Sociale).
   \param[in] pcNumber le numero de NIR sans la cle.
   \return la cle NIR.
*/
int MOD97_CalculateNIRKey(const char* pcNumber)
{
   int   iModulus97;

   /* Calcul du modulo des donnees presente    */
   iModulus97 = MOD97_CalculateModulus97(pcNumber);

   /* Calcul de la cle */
   iModulus97 = 97 - iModulus97;

   return iModulus97;
}

/**
   \brief Verification de la validite d'un modulo 97 reduit.
   \param[in] pcNumber le numero a verifier (cle non comprise).
   \param[in] iKey la cle du numero.
   \return  MOD97_OK si le numero est correct.<br>
            MOD97_KO sinon
*/
MOD97_Res_e MOD97_CheckReducedMod97Key(const char* pcNumber, int iKey)
{
   if(MOD97_CalculateReducedModulus97(pcNumber) == iKey)
   {
      return MOD97_OK;
   }
   else
   {
      return MOD97_KO;
   }
}

/**
   \brief Calcul d'un modulo 97 reduit.
   \param[in] pcNumber le numero sur lequel calculer la cle.
   \return la cle.
*/
int MOD97_CalculateReducedMod97Key(const char* pcNumber)
{
   return MOD97_CalculateReducedModulus97(pcNumber);
}

/**
   \brief Verification de la validite d'une cle RLMC (cle de cheque).
   \param[in] pcNumber le numero du cheque suivi de la cle.
   \return  MOD97_OK si la cle RLMC est correct.<br>
            MOD97_KO sinon.
*/
MOD97_Res_e MOD97_CheckRLMCKey(const char* pcNumber)
{
   if(MOD97_CalculateModulus97(pcNumber) == 0)
   {
      return MOD97_OK;
   }
   else
   {
      return MOD97_KO;
   }
}

/**
   \brief Calcul de la cle RLMC (cle de cheque.
   \param[in] pcNumber le numero du cheque.
   \return la cle RLMC.
*/
int MOD97_CalculateRLMCKey(const char* pcNumber)
{
   int   iModulus97;

   /* Calcul du modulo des donnees presente */
   iModulus97 = MOD97_CalculateModulus97(pcNumber);

   /* Calcul de la cle */
   iModulus97 = (iModulus97 * 100) % 97;
   iModulus97 = 97 - iModulus97;

   return iModulus97;
}
