/**
   \author Grégory Lerbret
   \file processus.c
   \brief   Gestion des processus.<br>
            Ce fichier fournie une interface uniforme pour la gestion des processus encapsulant les appels aux fonctions systemes
            dependates de la cible.<br>
   \date 20/08/2008
   \version 1.0.0
*/

#include <stdio.h>
#include "processus.h"

#ifdef WIN32
   #include <process.h>
#else
   #include <sys\unistd.h>
#endif

#define xstr(s) str(s)
#define str(s) #s

#define PROCESS_NAME       "Gestion des processus"
#define PROCESS_VERS_MAJ   1
#define PROCESS_VERS_MIN   0
#define PROCESS_VERS_BRCH  0
#define PROCESS_ID         PROCESS_NAME " - Version " xstr(PROCESS_VERS_MAJ) "." xstr(PROCESS_VERS_MIN) "." xstr(PROCESS_VERS_BRCH)

/**
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char* PROCESS_Identifier(void)
{
   return PROCESS_ID;
}

/**
   \brief Version du module.
   \return La version du module.
*/
int PROCESS_Version(void)
{
   return PROCESS_VERS_MAJ*10000 + PROCESS_VERS_MIN*100 + PROCESS_VERS_BRCH;
}

/**
   \brief Obtention de l'identifiant du processus.
   \return L'identifiant du processus.
*/
pid_t PROCESS_getpid(void)
{
#if (defined(_MSC_VER) && _MSC_VER >= 1400)
/* Comilateur Visual C++ posterieur a la version 8,
   la fonction _getpid() permet d'obtenir l'identifiant du processus. */
   return _getpid();
#else
/* Sinon, il est possible d'utiliser la fonction POSIX getpid() */
   return getpid();
#endif
}
