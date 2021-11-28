/**
   \author Grégory Lerbret
   \file processus.h
   \brief   Gestion des processus.<br>
            Ce fichier fournie une interface uniforme pour la gestion des processus encapsulant les appels aux fonctions systemes
            dependates de la cible.<br>
   \date 20/08/2008
   \version 1.0.0
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
   \fn const char* PROCESS_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char* PROCESS_Identifier(void);

/**
   \fn int PROCESS_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int         PROCESS_Version(void);

/**
   \fn  pid_t PROCESS_getpid(void)
   \brief Obtention de l'identifiant du processus.
   \return L'identifiant du processus.
*/
pid_t       PROCESS_getpid(void);

#ifdef __cplusplus
}
#endif

#endif
