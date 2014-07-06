 #include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../struct.h"
#include "../plateau/plateau.h"
#include "graph.h"



/**
 * \fn struct graphe_global* init_graphe_global(struct tuile* tuile_depart)
 * \brief Fonction Initialisant le graph global représentant le plateau de jeu dans l'etat ou seul la premiere carte à été posé.
 *
 * \return graphe_global Pointeur vers le graphe global qui vient d'être initialisé.
 */
struct graphe_global* init_graphe_global(struct tuile* tuile_depart)
{
  assert(tuile_depart != NULL);
  
  struct graphe_global* graphe_global = malloc(sizeof(struct graphe_global));
  graphe_global->nb_arete = 0;
  graphe_global->nb_sommet = 0;
  graphe_global->id_sommet = malloc(sizeof(struct sommets)*NB_SOMMETS*NB_TYPE_SOMMETS);
  graphe_global->tab_successeurs = malloc(sizeof(struct sommet_successeurs)*NB_SOMMETS*NB_TYPE_SOMMETS);

  graphe_global->id_sommet[0] = tuile_depart->graphe->champs[0];
  graphe_global->id_sommet[0]->sommet_indice = 0;
  graphe_global->id_sommet[0]->type_sommet = _CHAMP;
  graphe_global->id_sommet[1] = tuile_depart->graphe->champs[1];
  graphe_global->id_sommet[1]->sommet_indice = 1;
  graphe_global->id_sommet[1]->type_sommet = _CHAMP;
  graphe_global->id_sommet[2] = tuile_depart->graphe->champs[2];
  graphe_global->id_sommet[2]->sommet_indice = 2;
  graphe_global->id_sommet[2]->type_sommet = _CHAMP;
  graphe_global->id_sommet[3] = tuile_depart->graphe->champs[3];
  graphe_global->id_sommet[3]->sommet_indice = 3;
  graphe_global->id_sommet[3]->type_sommet = _CHAMP;
  
  graphe_global->id_sommet[4] = tuile_depart->graphe->routes[0];
  graphe_global->id_sommet[4]->sommet_indice = 4;
  graphe_global->id_sommet[4]->type_sommet = _ROUTE;
  graphe_global->id_sommet[5] = tuile_depart->graphe->routes[2];
  graphe_global->id_sommet[5]->sommet_indice = 5;
  graphe_global->id_sommet[5]->type_sommet = _ROUTE;
  
  graphe_global->id_sommet[6] = tuile_depart->graphe->villes[3];
  graphe_global->id_sommet[6]->sommet_indice = 6;
  graphe_global->id_sommet[6]->type_sommet = _VILLE;
  graphe_global->id_sommet[6]->fin_element = COMPLET_ELEMENT;
  
  graphe_global->nb_sommet = 7;
  
  
  for (int i=0; i<NB_SOMMETS*NB_TYPE_SOMMETS-1; i++)
  {
    graphe_global->tab_successeurs[i] = malloc(sizeof(struct sommet_successeurs));
    graphe_global->tab_successeurs[i]->sommet = NULL;
    graphe_global->tab_successeurs[i]->suivant = NULL;
    graphe_global->tab_successeurs[i]->type_arete = _VIDE;
  }
  
  graphe_global->tab_successeurs[0]->sommet = tuile_depart->graphe->champs[3];
  graphe_global->tab_successeurs[0]->type_arete = _INTERNE;
  graphe_global->tab_successeurs[1]->sommet = tuile_depart->graphe->champs[2];
  graphe_global->tab_successeurs[1]->type_arete = _INTERNE;
  graphe_global->tab_successeurs[2]->sommet = tuile_depart->graphe->champs[1];
  graphe_global->tab_successeurs[2]->type_arete = _INTERNE;
  graphe_global->tab_successeurs[3]->sommet = tuile_depart->graphe->champs[0];
  graphe_global->tab_successeurs[3]->type_arete = _INTERNE;
  
  graphe_global->tab_successeurs[4]->sommet = tuile_depart->graphe->routes[2];
  graphe_global->tab_successeurs[4]->type_arete = _INTERNE;
  graphe_global->tab_successeurs[5]->sommet = tuile_depart->graphe->routes[0];
  graphe_global->tab_successeurs[5]->type_arete = _INTERNE;
  
  graphe_global->tab_successeurs[6] = NULL;
  
  graphe_global->nb_arete = 3;
  
  return graphe_global;
}

/**
 * \fn int free_successeur(struct sommet_successeurs* sommet_successeur)
 * \brief Fonction libérant la memoire correspondant à la liste chainé des successeurs
 * \param sommet_successeur Pointeur vers le debut de la structure sommet_successeur à liberer
 * \return int Correspond au succès ou l'echec de l'execution.
 */
int free_successeur(struct sommet_successeurs* sommet_successeur)
{
  
  
  struct sommet_successeurs* temp = sommet_successeur;
  while (temp != NULL)
  {
    struct sommet_successeurs* temp2 = temp->suivant;
    free(temp);
    temp = temp2;
  }
  return EXIT_SUCCESS;
}

/**
 * \fn free_graphe_global(struct graphe_global* graphe_global)
 * \brief Fonction libérant la memoire correspondant à une strucutre graphe globale
 * \param graphe_global Pointeur vers la structure graphe global à libérer
 * \return int Correspond au succès ou l'echec de l'execution.
 */
int free_graphe_global(struct graphe_global* graphe_global)
{
  assert(graphe_global != NULL);
  
  for (int i=0; i<graphe_global->nb_sommet; i++)
    free_successeur(graphe_global->tab_successeurs[i]);
  free(graphe_global->id_sommet);
  free(graphe_global->tab_successeurs);
  free(graphe_global);
  return EXIT_SUCCESS;
}

/**
 * \fn int ajout_sommet(struct graphe_global* graphe_global, struct sommets* nouv_sommet)
 * \brief Fonction ajoutant un sommet au graphe global en realouant de la memoire
 * \param graphe_global Pointeur vers la structure graphe global
 * \param nouv_sommet Pointeur vers la structure du sommet à ajouter
 * \return int Correspond au succès ou l'echec de l'execution.
 */
int ajout_sommet(struct graphe_global* graphe_global, struct sommets* nouv_sommet)
{
  assert(graphe_global != NULL);
  assert(nouv_sommet != NULL);
  
  graphe_global->id_sommet = realloc(graphe_global->id_sommet, sizeof(struct sommets)*(graphe_global->nb_sommet + 1));
  graphe_global->id_sommet[graphe_global->nb_sommet] = nouv_sommet;
  graphe_global->id_sommet[graphe_global->nb_sommet]->sommet_indice = graphe_global->nb_sommet;
  
  graphe_global->tab_successeurs = realloc(graphe_global->tab_successeurs, sizeof(struct sommet_successeurs)*(graphe_global->nb_sommet + 1));
  graphe_global->tab_successeurs[graphe_global->nb_sommet] = NULL;
  
  graphe_global->nb_sommet++;
  
  return EXIT_SUCCESS;
}

/**
 * \fn struct sommet_successeurs* dernier_successeur(struct sommet_successeurs* tete_liste)
 * \brief Fonction retournant un pointeur vers le dernier élément de la liste chainée de successeurs
 * \param tete_liste Pointeur vers la tete de la liste
 * \return temp Pointeur vers le dernier successeur de la liste chainée.
 */
struct sommet_successeurs* dernier_successeur(struct sommet_successeurs* tete_liste)
{
  assert(tete_liste != NULL);
  
  struct sommet_successeurs* temp = tete_liste;
  while (temp->suivant != NULL)
  {
    temp = temp->suivant;
  }
  return temp;
}


/**
 * \fn int ajout_succ_chaine(struct sommets* nouv_sommet, struct sommet_successeurs** sommet_successeurs, int sommet_ind, int type_arete)
 * \brief Fonction creant un successeur contenant le sommet passé en parametre  et qui l'ajoute au dernier successeur
 * \param nouv_sommet Pointeur vers la structure sommets du sommet à ajouter
 * \param sommet_successeurs Pointeur vers la tête de la liste chainée
 * \return int Correspond au succès ou l'echec de l'execution.
 */
int ajout_succ_chaine(struct sommets* nouv_sommet, struct sommet_successeurs** sommet_successeurs, int sommet_ind, int type_arete)
{
  assert(nouv_sommet != NULL);
  assert(sommet_successeurs != NULL);
    
  struct sommet_successeurs* nouv_succ = malloc(sizeof(struct sommet_successeurs));
  nouv_succ->sommet = nouv_sommet;
  nouv_succ->suivant = NULL;
  nouv_succ->type_arete = type_arete;
  
  if (sommet_successeurs[sommet_ind] ==NULL)
  {
    sommet_successeurs[sommet_ind] = nouv_succ;
  }
  else
  {
    struct sommet_successeurs* dernier_succ = dernier_successeur(sommet_successeurs[sommet_ind]);
    dernier_succ->suivant = nouv_succ;
  }
  
  return EXIT_SUCCESS;
}




/**
 * \fn int ajout_arete(struct graphe_global* graphe_global, struct sommets* sommet_src, struct sommets* sommet_dst, int type_arete)
 * \brief Fonction ajoutant une arête au graphe global en ajoutant un chainon à la liste de successeurs
 * \param graphe_global Pointeur vers la structure graphe global
 * \param sommet_src Pointeur vers la structure du sommet source
 * \param sommet_dst Pointeur vers la structure du sommet destination
 * \return int Correspond au succès ou l'echec de l'execution.
 */
int ajout_arete(struct graphe_global* graphe_global, struct sommets* sommet_src, struct sommets* sommet_dst, int type_arete)
{
  assert(graphe_global != NULL);
  assert(sommet_dst != NULL);
  assert(sommet_src != NULL);
  
  int sommet_src_indice = sommet_src->sommet_indice;
  int sommet_dst_indice = sommet_dst->sommet_indice;
  
  if ((sommet_dst_indice == EXIT_VERTICE_DO_NOT_EXIST) || (sommet_src_indice == EXIT_VERTICE_DO_NOT_EXIST))
    return EXIT_FAILURE;
  
  if ((ajout_succ_chaine(sommet_src, graphe_global->tab_successeurs, sommet_dst_indice, type_arete) == EXIT_FAILURE) || (ajout_succ_chaine(sommet_dst, graphe_global->tab_successeurs, sommet_src_indice, type_arete) == EXIT_FAILURE))
    return EXIT_FAILURE;
  
  graphe_global->nb_arete++;
  
  return EXIT_SUCCESS;
}


/**
 * \fn int ajouter_tuile_graphe_global(struct tuile*** plateau, struct graphe_global* graphe_global, struct tuile* tuile, int x, int y, char position)
 * \brief Fonction ajoutant des arretes entre la tuile que l'on vient de poser et le graphe globale, pour les sommets activées, pour un coté de la tuile
 * \param plateau Tableau de pointeur vers des structures tuiles qui correspondent aux tuiles déjà posées.
 * \param graphe_global Pointeur vers la structure graphe global
 * \param tuile Pointeur vers la structure tuile que l'on vient de poser
 * \param x Position x dans le tableau plateau où l'on veut placer la tuile
 * \param y Position y dans le tableau plateau où l'on veut placer la tuile
 * \param position Caractère donnant le coté de la tuile dont on veut relier les sommets au graphe globale.
 * \return int Correspond au succès ou l'echec de l'execution.
 */
int ajouter_tuile_graphe_global(struct tuile*** plateau, struct graphe_global* graphe_global, struct tuile* tuile, int x, int y, char position)
{
  assert(plateau != NULL);
  assert(graphe_global != NULL);
  assert(tuile != NULL);
  assert((x >= 0) && (x < LARGEUR_PLATEAU));
  assert((y >= 0) && (y < LARGEUR_PLATEAU));
  assert(position != '\0');
  
  int x_p;
  int y_p;
  int sommet_tuile;
  switch (position)
  {
    case 'h':
      x_p = x-1;
      y_p = y;
      sommet_tuile = 0;
      break;
      
    case 'b':
      x_p = x+1;
      y_p =y;
      sommet_tuile = 2;
      break;
      
    case 'g':
      x_p = x;
      y_p = y-1;
      sommet_tuile = 3;
      break;
      
    case 'd':
      x_p = x;
      y_p = y+1;
      sommet_tuile = 1;
      break;
      
    default:
      printf("La position à tester est manquante");
      return EXIT_FAILURE;
      break;
  }

  if (tuile->graphe->villes[sommet_tuile]->actif == 1)
  {
    ajout_arete(graphe_global, tuile->graphe->villes[sommet_tuile], plateau[x_p][y_p]->graphe->villes[(sommet_tuile+2) % NB_SOMMETS], _EXTERNE);
  }
  else
  {
    if ((tuile->graphe->champs[sommet_tuile]->actif == 1) && (tuile->graphe->champs[(sommet_tuile+1) % NB_SOMMETS]->actif == 1))
    {
      ajout_arete(graphe_global, tuile->graphe->champs[sommet_tuile], plateau[x_p][y_p]->graphe->champs[(sommet_tuile+3) % NB_SOMMETS], _EXTERNE);
      ajout_arete(graphe_global, tuile->graphe->champs[(sommet_tuile+1) % NB_SOMMETS], plateau[x_p][y_p]->graphe->champs[(((sommet_tuile+1) % NB_SOMMETS)+1) % NB_SOMMETS], _EXTERNE);
      if (tuile->graphe->routes[sommet_tuile]->actif == 1)
      {
        ajout_arete(graphe_global, tuile->graphe->routes[sommet_tuile], plateau[x_p][y_p]->graphe->routes[(sommet_tuile+2) % NB_SOMMETS], _EXTERNE);
      }
    }
    else
      return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}


/**
 * \fn int update_graphe_global(struct tuile*** plateau, struct graphe_global* graphe_global, struct tuile* tuile, int x, int y)
 * \brief Fonction ajoutant toutes les arretes entre la tuile que l'on vient de poser et le graphe globale, pour les sommets activées.
 * \param plateau Tableau de pointeur vers des structures tuiles qui correspondent aux tuiles déjà posées.
 * \param graphe_global Pointeur vers la structure graphe global
 * \param tuile Pointeur vers la structure tuile que l'on vient de poser
 * \param x Position x dans le tableau plateau où l'on veut placer la tuile
 * \param y Position y dans le tableau plateau où l'on veut placer la tuile
 * \return int Correspond au succès ou l'echec de l'execution.
 */
int update_graphe_global(struct tuile*** plateau, struct graphe_global* graphe_global, struct tuile* tuile, int x, int y)
{
  assert(plateau != NULL);
  assert(graphe_global != NULL);
  assert(tuile != NULL);
  assert((x >= 0) && (x < LARGEUR_PLATEAU));
  assert((y >= 0) && (y < LARGEUR_PLATEAU));
  int coeff[4][6] = {{0,0,0,1,2,3},{0,1,1,1,2,3},{0,1,2,2,2,3},{0,1,2,3,3,3}};
  
  for (int i=0; i<NB_SOMMETS; i++)
  {
    if (tuile->graphe->champs[i]->actif == 1)
    {
      ajout_sommet(graphe_global, tuile->graphe->champs[i]);
      tuile->graphe->champs[i]->type_sommet = _CHAMP;
    }
    if (tuile->graphe->routes[i]->actif == 1)
    {
      ajout_sommet(graphe_global, tuile->graphe->routes[i]);
      tuile->graphe->routes[i]->type_sommet = _ROUTE;
    }
    if (tuile->graphe->villes[i]->actif == 1)
    {
      ajout_sommet(graphe_global, tuile->graphe->villes[i]);
      tuile->graphe->villes[i]->type_sommet = _VILLE;
    }
  }
  
  for (int i=0; i<NB_SOMMETS; i++)
  {
    for (int j=i+1; j<NB_SOMMETS; j++)
    {
      if (tuile->graphe->mat_champs[i][j] == 1)
        ajout_arete(graphe_global, tuile->graphe->champs[i], tuile->graphe->champs[j], _INTERNE);
        
      if (tuile->graphe->mat_routes[i][j] == 1)
        ajout_arete(graphe_global, tuile->graphe->routes[i], tuile->graphe->routes[j], _INTERNE);
      
      if (tuile->graphe->mat_villes[i][j] == 1)
        ajout_arete(graphe_global, tuile->graphe->villes[i], tuile->graphe->villes[j], _INTERNE);
    }
  }
  
  for (int i=0; i<NB_SOMMETS; i++)
  {
    if ((tuile->graphe->routes[i]->actif == 1) && (tuile->graphe->mat_routes[coeff[i][0]][coeff[i][3]] == 0) && (tuile->graphe->mat_routes[coeff[i][1]][coeff[i][4]] == 0) && (tuile->graphe->mat_routes[coeff[i][2]][coeff[i][5]] == 0))
    {
      tuile->graphe->routes[i]->fin_element = COMPLET_ELEMENT;
    }
    else if ((tuile->graphe->villes[i]->actif == 1) && (tuile->graphe->mat_villes[coeff[i][0]][coeff[i][3]] == 0) && (tuile->graphe->mat_villes[coeff[i][1]][coeff[i][4]] == 0) && (tuile->graphe->mat_villes[coeff[i][2]][coeff[i][5]]) == 0)
    {
      tuile->graphe->villes[i]->fin_element = COMPLET_ELEMENT;
    }
  }
  
  char* positions = position_tuiles_voisines(plateau, x, y);
  for (int i=0; positions[i] != '\0'; i++)
  {
    if (ajouter_tuile_graphe_global(plateau, graphe_global, tuile, x, y, positions[i]) == EXIT_FAILURE)
      return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}



/**
 * \fn int parcourt_graphe_global(struct graphe_global* graphe_global, struct sommets* sommet, int* nb_tuile, int* nb_pion, int nb_fonctions_traitement, int (*fonctions_a_exec[])(struct sommet_successeurs*, struct sommet_successeurs**, int*, int*), int resultats_attendus[])
 * \brief Fonction parcourant le graphe global et appliquant a chaque sommet parcouru la fonction dont l'adresse est donnée en paramètre.
 * \param graphe_global Pointeur vers la structure graphe global
 * \param sommet Pointeur vers le sommet duquel on souhaite commencer le parcourt
 * \param (*fonction_a_exec)(struct sommet_successeurs*, int*) Pointeur vers la fonction à executer sur chaque sommets
 * \return int Correspond au succès ou l'echec de l'execution.
 */
int parcourt_graphe_global(struct graphe_global* graphe_global, struct sommets* sommet, int* nb_tuile, int* nb_pion, int nb_fonctions_traitement, int (*fonctions_a_exec[])(struct sommet_successeurs*, struct sommet_successeurs**, int*, int*), int resultats_attendus[])
{
  assert(sommet != NULL);
  assert(graphe_global != NULL);
  
  int sommet_indice = sommet->sommet_indice;
  if (sommet_indice == EXIT_VERTICE_DO_NOT_EXIST)
    return EXIT_FAILURE;
  
  sommet->parcourt_graphe = GRIS;
  
  if (graphe_global->tab_successeurs[sommet_indice] == NULL)
    return EXIT_NO_SUCCESSOR;

  
  struct sommet_successeurs temp_som_suc;
  temp_som_suc.sommet = sommet;
  temp_som_suc.suivant = NULL;
  temp_som_suc.type_arete = _INTERNE;
  for (int i=0; i<nb_fonctions_traitement; i++)
  {
    if ((*fonctions_a_exec[i])(&temp_som_suc, graphe_global->tab_successeurs, nb_tuile, nb_pion) != resultats_attendus[i])
      return EXIT_FAILURE;
  }
  
  
  struct sommet_successeurs* temp = graphe_global->tab_successeurs[sommet_indice];
  struct sommet_successeurs* temp_bak = NULL;
 
  while (temp != NULL)
  {
    if (temp->sommet->parcourt_graphe == BLANC)
    {
      for (int i=0; i<nb_fonctions_traitement; i++)
      {
        if ((*fonctions_a_exec[i])(temp, graphe_global->tab_successeurs, nb_tuile, nb_pion) != resultats_attendus[i])
          return EXIT_FAILURE;
      }
      if (parcourt_graphe_global(graphe_global, temp->sommet, nb_tuile, nb_pion, nb_fonctions_traitement, fonctions_a_exec, resultats_attendus) == EXIT_FAILURE)
        return EXIT_FAILURE;
    }
    temp_bak = temp;
    temp = temp->suivant;
  }
  
  sommet->parcourt_graphe = NOIR;
    
  return EXIT_SUCCESS;
}



/**
 * \fn int init_parcourt_graphe(struct graphe_global* graphe_global)
 * \brief Fonction initialisant l'indicateur de parcourt de chaque sommet à blanc
 * \param graphe_global Pointeur vers la structure graphe global
 * \return int Correspond au succès ou l'echec de l'execution.
 */
int init_parcourt_graphe(struct graphe_global* graphe_global)
{
  assert(graphe_global != NULL);
  
  for (int i=0; i<graphe_global->nb_sommet; i++)
  {
    graphe_global->id_sommet[i]->parcourt_graphe = BLANC;
  }
  return EXIT_SUCCESS;
}

