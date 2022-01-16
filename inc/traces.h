/**
 * @file
 * @brief Fichier de traces.
 * @version 1.0.0.
 * @copyright MIT license.
 * @author Gregory Lerbret.
 */

#ifndef GL_TRACE_H
#define GL_TRACE_H

/// @cond
/**
 * @brief Niveau de trace.
 */
typedef enum
{
#define GEN(a, b) \
   TRACE_ ## a,
#include "traces.gen"
#undef GEN
    TRACE_dummy

} TRACE_Niveau_e;
/// @endcond

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @return Identifiant du module (nom et version).
 */
const char* TRACE_Identifier(void);

/**
 * @return Version du module.
 */
int TRACE_Version(void);

/**
 * @brief Ajoute une trace dans le fichier LogXXXX (XXXXX represente la date du jour).
 *
 * @param[in] level   Niveau de la trace.
 * @param[in] format  Format de la trace.
 */
void TRACE_ReportTrace(TRACE_Niveau_e level, const char* format, ... );

#ifdef __cplusplus
}
#endif

#endif
