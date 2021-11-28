/**
   \author Grégory Lerbret
   \file traces.h
   \brief Fichier de traces.<br>
   \date 07/04/2005
   \version 1.0.0
*/

#ifndef GL_TRACE_H
#define GL_TRACE_H

/**
   \enum TRACE_Niveau_e
   \brief Niveau de trace.
*/
typedef enum
{

#define GEN(a, b) \
   TRACE_ ## a,
#include "traces.gen"
#undef GEN
   TRACE_dummy
} TRACE_Niveau_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
   \fn const char* TRACE_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char* TRACE_Identifier(void);

/**
   \fn int TRACE_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int         TRACE_Version(void);

/**
   \fn void TRACE_ReportTrace(TRACE_Niveau_e eNiveau, const char *pcFormat, ... )
   \brief Ajout d'une trace dans le fichier LogXXXX (XXXXX represente la date du jour).
   \param[in] eNiveau Le niveau de la trace
   \param[in] pcFormat Le format de la trace
*/
void        TRACE_ReportTrace(TRACE_Niveau_e eNiveau, const char *pcFormat, ... );

#ifdef __cplusplus
}
#endif

#endif
