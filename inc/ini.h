/**
 * @author Gregory Lerbret
 * @file
 * @brief Gestion des fichiers au format ini
 * @version 1.0.0
 * @copyright MIT license
 */

#ifndef GL_INI_H
#define GL_INI_H

#include "bool.h"

#include <stddef.h>

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
 *
 * @pre readValue n'est pas NULL
 * @pre maxSize n'est pas nulle
 * @pre sectionName n'est pas NULL ni vide
 * @pre keyName n'est pas NULL ni vide
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
 *  - true si l'ecriture c'est bien deroulee
 *  - false sinon
 *
 * @pre sectionName n'est pas NULL ni vide
 * @pre keyName n'est pas NULL ni vide
 * @pre valueToWrite n'est pas NULL ni vide
 * @pre fileName n'est pas NULL ni vide
 */
bool INI_WriteIni(const char* sectionName, const char* keyName, const char* valueToWrite, const char* fileName);

#ifdef __cplusplus
}
#endif

#endif
