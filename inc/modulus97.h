/**
   \author Grégory Lerbret
   \file modulus97.h
   \brief Calcul et de controle des modulo 97.<br>
   \date 07/05/2007
   \version 1.0.0
*/

#ifndef GL_MODULUS97_H
#define GL_MODULUS97_H

/**
   \enum MOD97_Res_e
   \brief Resultat de la verification du modulo 97
*/
typedef enum
{
/**
   \brief Le modulo 97 est correct.
*/
   MOD97_OK,
/**
   \brief Le modulo 97 est incorrect.
*/
   MOD97_KO
} MOD97_Res_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
   \fn const char* MOD97_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char* MOD97_Identifier(void);

/**
   \fn int MOD97_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int         MOD97_Version(void);

/**
   \fn MOD97_Res_e MOD97_CheckRIBKey(const char* pcNumber)
   \brief Verification de la validite d'un RIB.
   \param[in] pcNumber le numero de RIB complet (y comprit la cle).
   \return  MOD97_OK si le RIB est correct.<br>
            MOD97_KO sinon.
*/
MOD97_Res_e MOD97_CheckRIBKey(const char* pcNumber);

/**
   \fn int MOD97_CalculateRIBKey(const char* pcNumber)
   \brief Calcul de la cle d'un RIB.
   \param[in] pcNumber le numero de RIB sans la cle.
   \return la cle RIB.
*/
int         MOD97_CalculateRIBKey(const char* pcNumber);

/**
   \fn MOD97_Res_e MOD97_CheckNIRKey(const char* pcNumber, int iKey)
   \brief Verification de la validite d'un NIR (Numero de Securite Sociale).
   \param[in] pcNumber le numero de NIR sans la cle.
   \param[in] iKey la cle du NIR.
   \return  MOD97_OK si le NIR est correct.<br>
            MOD97_KO sinon.
*/
MOD97_Res_e MOD97_CheckNIRKey(const char* pcNumber, int iKey);

/**
   \fn int MOD97_CalculateNIRKey(const char* pcNumber)
   \brief Calcul de la cle d'un NIR (numero de Securite Sociale).
   \param[in] pcNumber le numero de NIR sans la cle.
   \return la cle NIR.
*/
int         MOD97_CalculateNIRKey(const char* pcNumber);

/**
   \fn MOD97_Res_e MOD97_CheckReducedMod97Key(const char* pcNumber, int iKey)
   \brief Verification de la validite d'un modulo 97 reduit.
   \param[in] pcNumber le numero a verifier (cle non comprise).
   \param[in] iKey la cle du numero.
   \return  MOD97_OK si le numero est correct.<br>
            MOD97_KO sinon
*/
MOD97_Res_e MOD97_CheckReducedMod97Key(const char* pcNumber, int iKey);

/**
   \fn int MOD97_CalculateReducedMod97Key(const char* pcNumber)
   \brief Calcul d'un modulo 97 reduit.
   \param[in] pcNumber le numero sur lequel calculer la cle.
   \return la cle.
*/
int         MOD97_CalculateReducedMod97Key(const char* pcNumber);

/**
   \fn MOD97_Res_e MOD97_CheckRLMCKey(const char* pcNumber)
   \brief Verification de la validite d'une cle RLMC (cle de cheque).
   \param[in] pcNumber le numero du cheque suivi de la cle.
   \return  MOD97_OK si la cle RLMC est correct.<br>
            MOD97_KO sinon.
*/
MOD97_Res_e MOD97_CheckRLMCKey(const char* pcNumber);

/**
   \fn int MOD97_CalculateRLMCKey(const char* pcNumber)
   \brief Calcul de la cle RLMC (cle de cheque.
   \param[in] pcNumber le numero du cheque.
   \return la cle RLMC.
*/
int         MOD97_CalculateRLMCKey(const char* pcNumber);

#ifdef __cplusplus
}
#endif

#endif
