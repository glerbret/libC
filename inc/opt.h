/**
 * @file
 * @brief Gestion des options en ligne de commande.
 * @version 1.0.0.
 * @copyright MIT license.
 * @author Gregory Lerbret.
 */

#ifndef GL_OPT_H
#define GL_OPT_H

/**
 * @brief Flag de traitement des options.
 */
typedef enum
{
  /// @brief Fonctionnement nominal.
  OPT_FLG_NORM,
  /// @brief Remise a 0 du compteur.
  OPT_FLG_RESET
} OPT_Flag_e;

/**
 * @brief Resultat de traitement des options.
 */
typedef enum
{
  /// @brief Fin d'analyse des options.
  OPT_END = -1
} OPT_Res_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @return Identifiant du module (nom et version).
 */
const char* OPT_Identifier(void);

/**
 * @return Version du module.
 */
int OPT_Version(void);

/**
 * @brief Analyse les options fournis au programme.
 *
 * @param[in] argc    Nombre d'arguments fournis au programme.
 * @param[in] argv    Arguments fournis au programme.
 * @param[out] data   Donnee liee a l'argument.
 * @param[in] opt     Liste des options a traiter (une option suivi de : indique que l'option accepte des donnees).
 * @param[in] flags   Flag de traitement (OPT_FLG_RESET remet a 0 le compteur, l'analyse recommence au premier argument).
 *
 * @return La position de l'option si une option est trouvee.
 * @return OPT_END sinon.
 *
 * @note A chaque appel, la fonction retourne une des options geres.
 */
int OPT_GetOpt(int argc, const char *argv[], const char **data, const char* opt, int flags);

#ifdef __cplusplus
}
#endif

#endif
