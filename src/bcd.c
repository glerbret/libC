/**
 * @author Grégory Lerbret
 * @brief Gestion de nombres au format BCD.<br>
 * @date 14/12/2005
 * @version 1.0.0
 */

#include "bcd.h"

#define xstr(s) str(s)
#define str(s) #s

#define BCD_NAME        "Gestion des nombres au format BCD"
#define BCD_VERS_MAJ    1
#define BCD_VERS_MIN    0
#define BCD_VERS_BRCH   0
#define BCD_ID  BCD_NAME " - Version " xstr(BCD_VERS_MAJ) "." xstr(BCD_VERS_MIN) "." xstr(BCD_VERS_BRCH)

/**
 * @return Identifiant du module (nom et version).
 */
const char* BCD_Identifier(void)
{
    return BCD_ID;
}

/**
   \fn int BCD_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int BCD_Version(void)
{
   return BCD_VERS_MAJ*10000 + BCD_VERS_MIN*100 + BCD_VERS_BRCH;
}

/**
   \fn BCD_Res_e BCD_ConvBCD2Ascii(char* pcAscii, const unsigned char* pcBCD, size_t szNbDigit)
   \brief Conversion d'un nombre au format BCD vers sa representation textuelle.
   \param[out] pcAscii la chaine de caracteres representant le nombre
   \param[in] pcBCD le nombre au format BCD
   \param[in] szNbDigit la taille du nombre (en digits)
   \return  BCD_OK en cas de succes.<br>
            BCD_CONV_ERROR encas d'erreur.
*/
BCD_Res_e BCD_ConvBCD2Ascii(char* pcAscii, const unsigned char* pcBCD, size_t szNbDigit)
{
   size_t   szIndexASCII   = 0;
   size_t   szIndexBCD     = 0;

   /* Verification des conditions initiales */
   if(pcAscii == NULL || pcBCD == NULL || szNbDigit == 0)
   {
      return BCD_CONV_ERROR;
   }

   /* Si la taille du nombre est impaire, le premier caractere ne conient q'un seul
      digit (dans le quartet de poid faible) */
   if((szNbDigit % 2) != 0)
   {
      pcAscii[0] = (char)((pcBCD[0] & 0x0F) + '0');
      szNbDigit--;
      szIndexASCII++;
      szIndexBCD++;
   }

   for(; szIndexASCII < szNbDigit; szIndexASCII += 2, szIndexBCD++)
   {
      pcAscii[szIndexASCII]      = (char)(((pcBCD[szIndexBCD] >> 4) & 0x0F) + '0');
      pcAscii[szIndexASCII + 1]  = (char)((pcBCD[szIndexBCD] & 0x0F) + '0');
   }

   return BCD_OK;
}

/**
   \fn BCD_Res_e BCD_Res_e BCD_ConvAscii2BCD(unsigned char* pcBCD, const char* pcAscii, size_t szNbDigit)
   \brief Conversion de la representation textuelle d'un nombre vers sa representation BCD.
   \param[out] pcBCD le nombre au format BCD
   \param[in] pcAscii la chaine de caracteres representant le nombre
   \param[in] szNbDigit la taille du nombre (en digit)
   \return  BCD_OK en cas de succes.<br>
            BCD_CONV_ERROR encas d'erreur.
*/
BCD_Res_e BCD_ConvAscii2BCD(unsigned char* pcBCD, const char* pcAscii, size_t szNbDigit)
{
   size_t   szIndex;

   /* Verification des conditions initiales */
   if(pcAscii == NULL || pcBCD == NULL || szNbDigit == 0)
   {
      return BCD_CONV_ERROR;
   }

   if((szNbDigit % 2) != 0)
   {
      pcBCD[0] = (char)(pcAscii[0] - '0');
      for(szIndex = 1; szIndex < (szNbDigit + 1) / 2; szIndex++)
      {
         pcBCD[szIndex] = (char)(((pcAscii[szIndex * 2 - 1] - '0') << 4) + (pcAscii[szIndex * 2] - '0'));
      }
   }
   else
   {
      for(szIndex = 0; szIndex < (szNbDigit + 1) / 2; szIndex++)
      {
         pcBCD[szIndex] = (char)(((pcAscii[szIndex * 2] - '0') << 4) + (pcAscii[szIndex * 2 + 1] - '0'));
      }
   }

   return BCD_OK;
}
