/**
   \author Grégory Lerbret
   \file luhn.h
   \brief Calcul et de controle des cles de Luhn.<br>
   \date 04/04/2005
   \version 1.0.0
*/

#ifndef GL_LUHN_H
#define GL_LUHN_H

/**
   \enum LUHN_Res_e
   \brief Resultat de la verification de la cle de Luhn
*/
typedef enum
{
/**
   \brief La cle de Luhn est correcte.
*/
   LUHN_OK,
/**
   \brief La cle de Luhn est incorrecte.
*/
   LUHN_KO
} LUHN_Res_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
   \fn const char* LUHN_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char* LUHN_Identifier(void);

/**
   \fn int LUHN_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int         LUHN_Version(void);

/**
   \fn char LUHN_CalculalteLuhnKey(const char* pcNumber)
   \brief Calcul de la cle de Luhn.
   \param[in] pcNumber le numero dont on veut calculer la cle de Luhn
   \return la cle de Luhn sous sa forme ASCII.
*/
char        LUHN_CalculalteLuhnKey(const char* pcNumber);

/**
   \fn LUHN_Res_e LUHN_CheckLuhnKey(const char* pcNumber)
   \brief Verification de la cle de Luhn.
   \param[in] pcNumber le numero a verifier
   \return  LUHN_OK pour une cle de Luhn correcte.<br>
            LUHN_KO sinon
*/
LUHN_Res_e  LUHN_CheckLuhnKey(const char* pcNumber);

#ifdef __cplusplus
}
#endif

#endif
