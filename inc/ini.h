/**
 * @author Gregory Lerbret
 * @file
 * @brief Gestion des fichiers au format ini
 * @version 1.0.0
 * @copyright MIT license
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
 * @param[in] sectionName Nom de la section
 * @param[in] keyName Nom de la cle
 * @param[in] defaultValue Valeur par defaut
 * @param[out] readValue Valeur lue
 * @param[in] maxSize Taille maximale de la valeur
 * @param[in] fileName Nom du fichier .ini
 *
 * @return Nombre de caracteres lus
 */
size_t INI_ReadIni(const char* sectionName, const char* keyName, const char* defaultValue, char* readValue, size_t maxSize, const char* fileName);

/**
 * @brief Ecriture d'un element dans un fichier .ini
 *
 * @param[in] sectionName Nom de la section
 * @param[in] keyName Nom de la cle
 * @param[in] valueToWrite Valeur a inscrire
 * @param[in] fileName Nom du fichier .ini
 *
 * @return
 *  - INI_OK si l'ecriture c'est bien deroulee
 *  - INI_KO sinon
*/
INI_Res_e INI_WriteIni(const char* sectionName, const char* keyName, const char* valueToWrite, const char* fileName);

#ifdef __cplusplus
}
#endif

#endif
