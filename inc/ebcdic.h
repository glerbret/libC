/**
   \author Grégory Lerbret
   \file bcd.h
   \brief Gestion du chaset EBCDIC.<br>
   \date 14/12/2005
   \version 1.0.0
*/

#ifndef GL_EBCDIC_H
#define GL_EBCDIC_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
   \fn const char* EBCDIC_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char* EBCDIC_Identifier(void);

/**
   \fn int EBCDIC_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int         EBCDIC_Version(void);

/**
   \fn int EBCDIC_ConvertASCII2EBCDIC(int iASCII)
   \brief Conversion ASCI vers EBCDIC.
   \param[in] iASCII le caractere au format ASCII
   \return Le caractere au format EBCDIC.
*/
int         EBCDIC_ConvertASCII2EBCDIC(int iASCII);

/**
   \fn int EBCDIC_ConvertEBCDIC2ASCII(int iEBCDIC)
   \brief Conversion EBCDIC vers ASCII.
   \param[in] iEBCDIC le caractere au format EBCDIC
   \return Le caractere au format ASCII.
*/
int         EBCDIC_ConvertEBCDIC2ASCII(int iEBCDIC);

#ifdef __cplusplus
}
#endif

#endif
