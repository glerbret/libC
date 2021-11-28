/**
 * @author Gregory Lerbret
 * @file
 * @brief Gestion des fichiers au format ini
 * @date 06/04/2005
 * @version 1.0.0
 */

#ifndef GL_INI_H
#define GL_INI_H

#include <stddef.h>

/**
 * @brief Resultat des traitement sur un fichier .ini
 */
typedef enum
{
    /// @brief Le traitement a reussi
    INI_OK,
    /// @brief Le traitement a echoue
    INI_KO
} INI_Res_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @return Identifiant du module (nom et version)
 */
const char* INI_Identifier(void);

/**
 * @return Version du module
 */
int INI_Version(void);

/**
 * @brief Lecture d'un element dans un fichier .ini
 *
 * @param[in] pcSectionName Nom de la section
 * @param[in] pcKeyName Nom de la cle
 * @param[in] pcDefault Valeur par defaut
 * @param[out] pcReturnedString Valeur lue
 * @param[in] szSize Taille maximale de la valeur
 * @param[in] pcFileName Nom du fichier .ini
 *
 * @return Nombre de caracteres lus
 */
size_t INI_ReadIni(const char* pcSectionName, const char* pcKeyName, const char* pcDefault, char* pcReturnedString, size_t szSize, const char* pcFileName);

/**
 * @brief Ecriture d'un element dans un fichier .ini
 *
 * @param[in] pcSectionName Nom de la section
 * @param[in] pcKeyName Nom de la cle
 * @param[in] pcWriteString Valeur a inscrire
 * @param[in] pcFileName Nom du fichier .ini
 *
 * @return
 *  - INI_OK si l'ecriture c'est bien deroulee
 *  - INI_KO sinon
*/
INI_Res_e      INI_WriteIni(const char* pcSectionName, const char* pcKeyName, const char* pcWriteString, const char* pcFileName);

#ifdef __cplusplus
}
#endif

#endif
