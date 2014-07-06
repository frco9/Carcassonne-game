#include <stdio.h>
#include <assert.h>
#include "../../struct.h"
#include "graph_tuiles.h"

/**
 * \fn struct sommets* init_sommet()
 * \brief Fonction Initialisant un sommet
 *
 * \return sommets Pointeur vers le sommet qui vient d'être initialisé.
 */
struct sommets* init_sommet()
{
  struct sommets* sommets = malloc(sizeof(struct sommets));
  sommets->actif = 0;
  sommets->pion = 0;
  sommets->parcourt_graphe = BLANC;
  sommets->sommet_indice = EXIT_VERTICE_DO_NOT_EXIST;
  sommets->fin_element = NO_COMPLET_ELEMENT;
  sommets->type_sommet = _VIDE;
  sommets->construct_complet = NO_COMPLET_ELEMENT;
  return sommets;
}


/**
 * \fn int free_sommet(struct sommets* sommet)
 * \brief Fonction libérant la memoire correspondant à une strucutre sommet
 * \param sommet Pointeur vers la structure sommets à libérer
 * \return int Correspond au succès ou l'echec de l'execution.
 */
int free_sommet(struct sommets* sommet)
{
  assert(sommet != NULL);
  
  free(sommet);
  return EXIT_SUCCESS;
}

/**
 * \fn struct graphe* init_graphe()
 * \brief Fonction Initialisant un graphe
 *
 * \return graphe Pointeur vers le graphe qui vient d'être initialisé.
 */
struct graphe* init_graphe()
{
  int i,j;
  struct graphe* graphe = malloc(sizeof(struct graphe));
  for(i=0;i<NB_SOMMETS;i++)
  {
    struct sommets* champ = init_sommet();
    struct sommets* route = init_sommet();
    struct sommets* ville = init_sommet();
    graphe->champs[i] = champ;
    graphe->routes[i] = route;
    graphe->villes[i] = ville;
  }
  for(i=0;i<NB_SOMMETS;i++)
  {
    for(j=0;j<NB_SOMMETS;j++)
    {
      graphe->mat_champs[i][j] = 0;
      graphe->mat_routes[i][j] = 0;
      graphe->mat_villes[i][j] = 0;
    }
  }
  graphe->monaster = 0;
  graphe->pion_monaster = 0;
  
  return graphe;
}

/**
 * \fn int free_graphe(struct graphe* graphe)
 * \brief Fonction libérant la memoire correspondant à une strucutre graphe
 * \param graphe Pointeur vers la structure graphe à libérer
 * \return int Correspond au succès ou l'echec de l'execution.
 */
int free_graphe(struct graphe* graphe)
{
  assert(graphe != NULL);
  
  for (int i=0;i<NB_SOMMETS;i++)
  {
    free_sommet(graphe->champs[i]);
    free_sommet(graphe->routes[i]);
    free_sommet(graphe->villes[i]);
  }
  free(graphe);
  return EXIT_SUCCESS;
}



