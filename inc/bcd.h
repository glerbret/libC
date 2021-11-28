/**
   \author Grégory Lerbret
   \file bcd.h
   \brief Gestion de nombres au format BCD.<br>
   \date 14/12/2005
   \version 1.0.0
*/

#ifndef GL_BCD_H
#define GL_BCD_H

#include <stddef.h>

/**
   \enum BCD_Res_e
   \brief Resultat des traitements sur le nombres au format BCD
*/
typedef enum
{
/**
   \brief pas d'erreur
*/
   BCD_OK,
/**
   \brief echec de conversion d'un nombre BCD
*/
   BCD_CONV_ERROR
} BCD_Res_e;

#ifdef __cplusplus
extern "C"
{
#endif
/**
   \fn const char* BCD_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char* BCD_Identifier(void);

/**
   \fn int BCD_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int         BCD_Version(void);

/**
   \fn BCD_Res_e BCD_ConvBCD2Ascii(char* pcAscii, const unsigned char* pcBCD, size_t szNbDigit)
   \brief Conversion d'un nombre au format BCD vers sa representation textuelle.
   \param[out] pcAscii la chaine de caracteres representant le nombre
   \param[in] pcBCD le nombre au format BCD
   \param[in] szNbDigit la taille du nombre (en digits)
   \return  BCD_OK en cas de succes.<br>
            BCD_CONV_ERROR en cas d'erreur
*/
BCD_Res_e   BCD_ConvBCD2Ascii(char* pcAscii, const unsigned char* pcBCD, size_t szNbDigit);

/**
   \fn BCD_Res_e BCD_Res_e BCD_ConvAscii2BCD(unsigned char* pcBCD, const char* pcAscii, size_t szNbDigit)
   \brief Conversion de la representation textuelle d'un nombre vers sa representation BCD.
   \param[out] pcBCD le nombre au format BCD
   \param[in] pcAscii la chaine de caracteres representant le nombre
   \param[in] szNbDigit la taille du nombre (en digit)
   \return  BCD_OK en cas de succes.<br>
            BCD_CONV_ERROR encas d'erreur.
*/
BCD_Res_e   BCD_ConvAscii2BCD(unsigned char* pcBCD, const char* pcAscii, size_t szNbDigit);

#ifdef __cplusplus
}
#endif

#endif
