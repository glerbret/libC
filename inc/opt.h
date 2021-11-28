/**
   \author Grégory Lerbret
   \file opt.h
   \brief Gestion des options en ligne de commande.<br>
   \date 13/04/2005
   \version 1.0.0
*/

#ifndef GL_OPT_H
#define GL_OPT_H

/**
   \enum OPT_Flag_e
   \brief Flag de traitement des options.
*/
typedef enum
{
/**
   \brief Fonctionnement nominal.
*/
   OPT_FLG_NORM,
/**
   \brief Remise a 0 du compteur.
*/
   OPT_FLG_RESET
} OPT_Flag_e;

/**
   \enum OPT_Res_e
   \brief Resultat de traitement des options.
*/
typedef enum
{
/**
   \brief Fin d'analye des options.
*/
   OPT_END=-1
} OPT_Res_e;

#ifdef __cplusplus
extern "C"
{
#endif

/**
   \fn const char* OPT_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char* OPT_Identifier(void);

/**
   \fn int OPT_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int         OPT_Version(void);

/**
   \fn int OPT_GetOpt(int iNbArg, const char *pacArg[], const char **pcData, const char* pcOpt, int iFlag)
   \brief   Analyse des options fournis au programme.<br>
            A chaque appel, la fonction retourne une des options geres.
   \param[in] iNbArg le nombre d'arguments fournis au programme.
   \param[in] pacArg les arguments fournis au programme.
   \param[out] pcData la donnee liee a l'argument.
   \param[in] pcOpt la liste des options a traiter (une option suivi de : indique que l'option accepte des donnees).
   \param[in] iFlag flag de traitement (OPT_FLG_RESET remet a 0 le compteur, l'analyse recommence au premier argument).
   \return  La position de l'option si une option est trouvee.<br>
            OPT_END sinon
*/
int         OPT_GetOpt(int iNbArg, const char *pacArg[], const char **pcData, const char* pcOpt, int iFlag);

#ifdef __cplusplus
}
#endif

#endif
