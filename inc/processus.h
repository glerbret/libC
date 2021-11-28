/**
 * @author Gregory Lerbret
 * @file
 * @brief Gestion des processus
 *        Ce fichier fournie une interface uniforme pour la gestion des processus encapsulant les appels aux fonctions systemes
 *        dependantes de la cible
 * @date 20/08/2008
 * @version 1.0.0
 */

#ifndef GL_PROCESSUS_H
#define GL_PROCESSUS_H

#ifdef WIN32
#include <process.h>
#else
#include <sys\unistd.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @return Identifiant du module (nom et version)
 */
const char* PROCESS_Identifier(void);

/**
 * @return Version du module
 */
int PROCESS_Version(void);

/**
 * @return Identifiant du processus
 */
pid_t PROCESS_getpid(void);

#ifdef __cplusplus
}
#endif

#endif
