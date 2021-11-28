/**
 * @author Gregory Lerbret
 * @file
 * @brief Gestion des options en ligne de commande
 * @date 13/04/2005
 * @version 1.0.0
 */

#ifndef GL_OPT_H
#define GL_OPT_H

/**
 * @brief Flag de traitement des options
 */
typedef enum
{
    /// @brief Fonctionnement nominal
    OPT_FLG_NORM,
    /// @brief Remise a 0 du compteur
    OPT_FLG_RESET
} OPT_Flag_e;

/**
 * @brief Resultat de traitement des options
 */
typedef enum
{
    /// @brief Fin d'analyse des options
    OPT_END = -1
} OPT_Res_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @return Identifiant du module (nom et version)
 */
const char* OPT_Identifier(void);

/**
 * @return Version du module
 */
int OPT_Version(void);

/**
 * @brief Analyse des options fournis au programme
 *        A chaque appel, la fonction retourne une des options geres
 *
 * @param[in] iNbArg Nombre d'arguments fournis au programme
 * @param[in] pacArg Arguments fournis au programme
 * @param[out] pcData Donnee liee a l'argument
 * @param[in] pcOpt Liste des options a traiter (une option suivi de : indique que l'option accepte des donnees)
 * @param[in] iFlag Flag de traitement (OPT_FLG_RESET remet a 0 le compteur, l'analyse recommence au premier argument)
 *
 * @return
 *  - La position de l'option si une option est trouvee
 *  - OPT_END sinon
 */
int OPT_GetOpt(int iNbArg, const char *pacArg[], const char **pcData, const char* pcOpt, int iFlag);

#ifdef __cplusplus
}
#endif

#endif
