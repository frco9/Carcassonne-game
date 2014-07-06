#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../struct.h"
#include "../graphe/graph.h"
#include "regles.h"


/**
 * \fn int est_pion(struct sommet_successeurs* sommet_successeurs, struct sommet_successeurs** tab_successeur,int* nb_tuiles, int* tot_pions)
 * \brief Fonction utilisée pour chaque sommet afin de verifier la présence du pion d'un des deux joueurs
 * \param struct sommet_successeurs* sommet_successeurs Pointeur vers la strucure sommet_successeur qui contient le sommet à verifier
 * \param struct sommet_successeurs** tab_successeur Tableau de pointeur vers des structures sommet_successeurs** Inutile dans cette fonction
 * \param int* nb_tuiles Pointeur vers un entier contenant le nombre de tuiles parcourues au moment de l'execution. Inutilisé ici.
 * \param int* tot_pions Pointeur vers un entier contenant le nombre de partisan trouvés dans le graphe en cours de parcourt.
 * \return int Correspond au succes de l'execution
 */
int est_pion(struct sommet_successeurs* sommet_successeurs, struct sommet_successeurs** tab_successeur,int* nb_tuiles, int* tot_pions)
{
  assert(sommet_successeurs != NULL);
  assert(sommet_successeurs->sommet != NULL);
  
  if (sommet_successeurs->sommet->pion == PARTISAN_BLEU)
    *tot_pions += 10;
  else if (sommet_successeurs->sommet->pion == PARTISAN_ROUGE)
    *tot_pions += 1;
  return EXIT_SUCCESS;
}


/**
 * \fn int est_route_champ_complet(struct sommet_successeurs* sommet_successeurs, struct sommet_successeurs** tab_successeur, int* nb_tuiles, int* nb_pions)
 * \brief Fonction utilisée pour chaque sommet permettant de verifier si une construction (route et ville) est fermée, terminée.
 * \param struct sommet_successeurs* sommet_successeurs Pointeur vers la strucure sommet_successeur qui contient le sommet à verifier
 * \param struct sommet_successeurs** tab_successeur Tableau de pointeur vers des structures sommet_successeurs**. Permet d'acceder au type de l'arete et donc de savoir si l'on passe à une autre tuile.
 * \param int* nb_tuiles Pointeur vers un entier contenant le nombre de tuiles parcourues au moment de l'execution.
 * \param int* tot_pions Pointeur vers un entier contenant le nombre de partisan trouvés dans le graphe en cours de parcourt. Inutilisé ici.
 * \return int Correspond au succes de l'execution
 */
int est_route_champ_complet(struct sommet_successeurs* sommet_successeurs, struct sommet_successeurs** tab_successeur, int* nb_tuiles, int* nb_pions)
{
  assert(sommet_successeurs != NULL);
  assert(sommet_successeurs->sommet != NULL);
  assert(tab_successeur != NULL);
  
  
  if ((sommet_successeurs->sommet->fin_element == COMPLET_ELEMENT) || (dernier_successeur(tab_successeur[sommet_successeurs->sommet->sommet_indice])->type_arete == _EXTERNE))
  {
    if (sommet_successeurs->type_arete == _EXTERNE)
      *nb_tuiles = *nb_tuiles + 1;
    return EXIT_SUCCESS;
  }
  

  return EXIT_FAILURE;
}


/**
 * \fn int marquer_sommet_termine(struct sommet_successeurs* sommet_successeurs, struct sommet_successeurs** tab_successeur, int* nb_tuiles, int* nb_pions)
 * \brief Fonction activant le champ contruct_complet du sommet donné en paramètre et qui est cencé appartenir à une construction terminée.
 * \param struct sommet_successeurs* sommet_successeurs Pointeur vers la strucure sommet_successeur qui contient le sommet à verifier
 * \param struct sommet_successeurs** tab_successeur Tableau de pointeur vers des structures sommet_successeurs**. Inutilisé ici.
 * \param int* nb_tuiles Pointeur vers un entier contenant le nombre de tuiles parcourues au moment de l'execution. Inutilisé ici.
 * \param int* tot_pions Pointeur vers un entier contenant le nombre de partisan trouvés dans le graphe en cours de parcourt. Inutilisé ici.
 * \return int Correspond au succes de l'execution
 */
int marquer_sommet_termine(struct sommet_successeurs* sommet_successeurs, struct sommet_successeurs** tab_successeur, int* nb_tuiles, int* nb_pions)
{
  assert(sommet_successeurs != NULL);
  assert(sommet_successeurs->sommet != NULL);
  
  if (sommet_successeurs->sommet->construct_complet == NO_COMPLET_ELEMENT)
  {
    sommet_successeurs->sommet->construct_complet = COMPLET_ELEMENT;
  }
  
  return EXIT_SUCCESS;
}


/**
 * \fn int supprimer_pion(struct sommet_successeurs* sommet_successeurs, struct sommet_successeurs** tab_successeur, int* nb_tuiles, int* nb_pions)
 * \brief Fonction supprimant le pion du sommet donné en paramètre et qui est cencé appartenir à une construction terminée.
 * \param struct sommet_successeurs* sommet_successeurs Pointeur vers la strucure sommet_successeur qui contient le sommet à verifier
 * \param struct sommet_successeurs** tab_successeur Tableau de pointeur vers des structures sommet_successeurs**. Inutilisé ici.
 * \param int* nb_tuiles Pointeur vers un entier contenant le nombre de tuiles parcourues au moment de l'execution. Inutilisé ici.
 * \param int* tot_pions Pointeur vers un entier contenant le nombre de partisan trouvés dans le graphe en cours de parcourt. Inutilisé ici.
 * \return int Correspond au succes de l'execution
 */
int supprimer_pion(struct sommet_successeurs* sommet_successeurs, struct sommet_successeurs** tab_successeur, int* nb_tuiles, int* nb_pions)
{
  assert(sommet_successeurs != NULL);
  assert(sommet_successeurs->sommet != NULL);
  
  if (sommet_successeurs->sommet->pion != 0)
  {
    sommet_successeurs->sommet->pion = 0;
  }
  
  return EXIT_SUCCESS;
}


/**
 * \fn int calcul_score_pions(int nb_tot_pions, int nb_tuiles, int type, struct joueurs* joueurs)
 * \brief Fonction determinant le nombre de points à attribuer au bon joueur en fonction du nombre de pions present et de leur appartenance, du nombre de tuiles et du type de construction achevée.
 * \param int nb_tot_pions Nombre de partisan trouvés lors du parcourt du graphe.
 * \param int nb_tuiles Nombre de tuiles parcourues.
 * \param int type Points correspondant au type de construction achevée (ville:2, route:1) par tuiles.
 * \param struct joueurs* joueurs Pointeur vers la structure contenant le joueur courant et les deux joueurs et toute leurs données de jeu.
 * \return int Correspond au succes de l'execution
 */
int calcul_score_pions(int nb_tot_pions, int nb_tuiles, int type, struct joueurs* joueurs)
{
  int nb_pion_bleu = nb_tot_pions/10;
  int nb_pion_rouge = nb_tot_pions - (nb_tot_pions/10)*10;
  if (nb_pion_bleu > nb_pion_rouge)
  {
    joueurs->bleu->score += type*nb_tuiles;
    joueurs->bleu->nb_partisans += nb_pion_bleu;
  }
  else if (nb_pion_bleu < nb_pion_rouge)
  {
    joueurs->rouge->score += type * nb_tuiles;
    joueurs->rouge->nb_partisans += nb_pion_rouge;
  }
  else
  {
    joueurs->bleu->score += (type * nb_tuiles)/2;
    joueurs->bleu->nb_partisans += nb_pion_bleu;
    joueurs->rouge->score += (type * nb_tuiles)/2;
    joueurs->rouge->nb_partisans += nb_pion_rouge;
  }
  return EXIT_SUCCESS;
}

/**
 * \fn int poser_pion(struct graphe_global* graphe_global, struct joueur* joueur, struct sommets* sommet)
 * \brief Fonction permettant de poser un pion et verifiant qu'il est possible de le poser
 * \param graphe_global Pointeur vers la structure graphe global
 * \param struct tuile* tuile Pointeur vers la tuile qui vient d'être posée et qui termine une structure.
 * \param struct joueurs* joueurs Pointeur vers la structure contenant le joueur courant et les deux joueurs et toute leurs données de jeu.
 * \return int Correspond au succès ou l'echec de l'execution.
 */
int compter_points_ville_route(struct graphe_global* graphe_global, struct tuile* tuile, struct joueurs* joueurs)
{
  assert(graphe_global != NULL);
  int nb_tuiles = 1;
  int nb_tot_pions = 0;
  int (*fonctions_a_exec[])(struct sommet_successeurs*, struct sommet_successeurs**, int*, int*) = {&est_route_champ_complet, &est_pion, &supprimer_pion, &marquer_sommet_termine};
  int resultats[] = {EXIT_SUCCESS, EXIT_SUCCESS, EXIT_SUCCESS, EXIT_SUCCESS};
  
  for (int i=0; i<NB_SOMMETS; i++)
  {
    if ((tuile->graphe->villes[i]->actif == 1) && (graphe_global->tab_successeurs[tuile->graphe->villes[i]->sommet_indice] != NULL) && (tuile->graphe->villes[i]->construct_complet == NO_COMPLET_ELEMENT))
    {
      nb_tuiles = 1;
      nb_tot_pions = 0;
      init_parcourt_graphe(graphe_global);
      if (parcourt_graphe_global(graphe_global, tuile->graphe->villes[i], &nb_tuiles, &nb_tot_pions, 1, fonctions_a_exec, resultats) == EXIT_SUCCESS)
      {
        fonctions_a_exec[0] = &marquer_sommet_termine;
        init_parcourt_graphe(graphe_global);
        parcourt_graphe_global(graphe_global, tuile->graphe->villes[i], &nb_tuiles, &nb_tot_pions, 3, fonctions_a_exec, resultats);
        if (nb_tot_pions != 0)
          calcul_score_pions(nb_tot_pions, nb_tuiles, 2, joueurs);
        fonctions_a_exec[0] = &est_route_champ_complet;
      }
    }
    
    if ((tuile->graphe->routes[i]->actif == 1) && (graphe_global->tab_successeurs[tuile->graphe->routes[i]->sommet_indice] != NULL) && (tuile->graphe->routes[i]->construct_complet == NO_COMPLET_ELEMENT))
    {
      nb_tuiles = 1;
      nb_tot_pions = 0;
      init_parcourt_graphe(graphe_global);
      if (parcourt_graphe_global(graphe_global, tuile->graphe->routes[i], &nb_tuiles, &nb_tot_pions, 1, fonctions_a_exec, resultats) == EXIT_SUCCESS)
      {
        fonctions_a_exec[0] = &marquer_sommet_termine;
        init_parcourt_graphe(graphe_global);
        parcourt_graphe_global(graphe_global, tuile->graphe->routes[i], &nb_tuiles, &nb_tot_pions, 3, fonctions_a_exec, resultats);
        if (nb_tot_pions != 0)
          calcul_score_pions(nb_tot_pions, nb_tuiles, 1, joueurs);
        fonctions_a_exec[0] = &est_route_champ_complet;
      }
    }
  }
  
  return EXIT_SUCCESS;
}


/**
 * \fn int est_poser_pion_possi(struct graphe_global* graphe_global, struct sommets* sommet)
 * \brief Fonction initialisant le parcourt du graphe en vu d'un test sur la presence d'un pion
 * \param graphe_global Pointeur vers la structure graphe global
 * \param sommet Pointeur vers le sommet duquel on souhaite commencer le parcourt
 * \return int Correspond au succès ou l'echec de l'execution.
 */
int est_poser_pion_possi(struct graphe_global* graphe_global, struct sommets* sommet)
{
  assert(sommet != NULL);
  assert(graphe_global != NULL);
  int tot_pions = 0;
  int nb_tuile = 0;
  int (*fonctions_a_exec[])(struct sommet_successeurs*, struct sommet_successeurs**, int*, int*) = {&est_pion};
  int resultat[] = {EXIT_SUCCESS};
  
  init_parcourt_graphe(graphe_global);
  int parcourt_result = parcourt_graphe_global(graphe_global, sommet, &nb_tuile, &tot_pions, 1, fonctions_a_exec, resultat);
  if ((parcourt_result == EXIT_NO_SUCCESSOR) || (tot_pions == 0))
  {
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}


/**
 * \fn int poser_pion(struct graphe_global* graphe_global, struct joueur* joueur, struct sommets* sommet)
 * \brief Fonction permettant de poser un pion et verifiant qu'il est possible de le poser
 * \param graphe_global Pointeur vers la structure graphe global
 * \param struct joueurs* joueurs Pointeur vers la structure contenant le joueur courant et les deux joueurs et toute leurs données de jeu.
 * \param sommet Pointeur vers le sommet sur lequel on souhaite poser le pion
 * \return int Correspond au succès ou l'echec de l'execution.
 */
int poser_pion(struct graphe_global* graphe_global, struct joueurs* joueurs, struct sommets* sommet)
{
  assert(sommet != NULL);
  assert(graphe_global != NULL);
  
  if (sommet->pion == 0)
  {
    if (est_poser_pion_possi(graphe_global, sommet) == EXIT_SUCCESS)
    {
      sommet->pion = joueurs->courant->pion;
      joueurs->courant->nb_partisans -= 1;
      return EXIT_SUCCESS;
    }
  }
  return EXIT_FAILURE;
}


/**
 * \fn struct joueurs* initialise_joueurs(void)
 * \brief Fonction allouant et initialisant la memoire de la structure joueurs et des structures joueur qu'elle contient.
* \return struct joueurs* Pointeur vers la structure qui vient d'être aloué.
 */
struct joueurs* initialise_joueurs(void)
{
  
  struct joueurs* joueurs = malloc(sizeof(struct joueurs));
  struct joueur* courant = NULL;
  struct joueur* bleu = malloc(sizeof(struct joueur));
  bleu->nb_partisans = 10;
  bleu->score = 0;
  bleu->pion = PARTISAN_BLEU;
  
  struct joueur* rouge = malloc(sizeof(struct joueur));
  rouge->nb_partisans = 10;
  rouge->score = 0;
  rouge->pion = PARTISAN_ROUGE;
  
  joueurs->rouge = rouge;
  joueurs->bleu = bleu;
  joueurs->courant = courant;
  
  return joueurs;
}

/**
 * \fn int free_joueurs(struct joueurs* joueurs)
 * \brief Fonction libérant la memoire alloué du pointeur donné en paramètre et de ses sous structures.
 * \param struct joueurs* joueurs Pointeur vers la structure joueurs à liberer
 * \return int Correspond au succès ou l'echec de l'execution.
 */
int free_joueurs(struct joueurs* joueurs)
{
  assert(joueurs != NULL);
  
  free(joueurs->bleu);
  free(joueurs->rouge);
  free(joueurs);
  return EXIT_SUCCESS;
}


/**
 * \fn int a_qui_le_tour(struct joueurs* joueurs)
 * \brief Fonction changeant le joueur courant.
 * \param struct joueurs* joueurs Pointeur vers la structure joueurs
 * \return int Correspond au succès ou l'echec de l'execution.
 */
int a_qui_le_tour(struct joueurs* joueurs)
{
  if (joueurs->courant == joueurs->bleu)
    joueurs->courant = joueurs->rouge;
  else
    joueurs->courant = joueurs->bleu;
  return EXIT_SUCCESS;
}