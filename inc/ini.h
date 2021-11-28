/**
   \author Grégory Lerbret
   \file ini.h
   \brief Gestion des fichiers au format ini.<br>
   \date 06/04/2005
   \version 1.0.0
*/

#ifndef GL_INI_H
#define GL_INI_H

/**
   \enum INI_Res_e
   \brief Resultat des traitement sur un fichier .ini
*/
typedef enum
{
/**
   \brief Le traitement a reussi
*/
   INI_OK,
/**
   \brief Le traitement a echoue
*/
   INI_KO
} INI_Res_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
   \fn const char* INI_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char*    INI_Identifier(void);

/**
   \fn int INI_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int            INI_Version(void);

/**
   \fn unsigned int INI_ReadIni(const char* pcSectionName, const char* pcKeyName, const char* pcDefault, char* pcReturnedString, size_t szSize, const char* pcFileName)
   \brief Lecture d'un element dans un fichier .ini.
   \param[in] pcSectionName le nom de la section
   \param[in] pcKeyName le nom de la cle
   \param[in] pcDefault la valeur par defaut
   \param[out] pcReturnedString la valeur lue
   \param[in] szSize la taille maximale de la valeur
   \param[in] pcFileName le nom du fichier .ini
   \return le nombre de caracteres lus
*/
size_t         INI_ReadIni(const char* pcSectionName, const char* pcKeyName, const char* pcDefault, char* pcReturnedString, size_t szSize, const char* pcFileName);

/**
   \fn INI_Res_e INI_WriteIni(const char* pcSectionName, const char* pcKeyName, const char* pcWriteString, const char* pcFileName)
   \brief Ecriture d'un element dans un fichier .ini.
   \param[in] pcSectionName le nom de la section
   \param[in] pcKeyName le nom de la cle
   \param[in] pcWriteString la valeur a inscrire
   \param[in] pcFileName le nom du fichier .ini
   \return  INI_OK si l'ecriture c'est bien deroulee.<br>
            INI_KO sinon.
*/
INI_Res_e      INI_WriteIni(const char* pcSectionName, const char* pcKeyName, const char* pcWriteString, const char* pcFileName);

#ifdef __cplusplus
}
#endif

#endif
