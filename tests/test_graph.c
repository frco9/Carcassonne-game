#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "../src/struct.h"
#include "../src/logique/tuiles/graph_tuiles.h"
#include "../src/logique/tuiles/tuiles.h"
#include "../src/logique/regles/regles.c"
#include "../src/logique/plateau/plateau.h"
#include "../src/logique/graphe/graph.h"


int test_graphe_global()
{
  
  struct tuile*** plateau = initialise_plateau(LARGEUR_PLATEAU);
  
  struct tuile* tuiles[NB_TUILES];
  for(int i=0;i<NB_TUILES;i++)
  {
    tuiles[i]=NULL;
  }
  tuile_parseur(tuiles, "tuiles.txt");
  
  struct tuile* tuile_14 = init_tuile();
  dupliquer_tuiles(tuiles[14], tuile_14);
  plateau[10][15] = tuile_14;
  struct tuile* tuile_18 = init_tuile();
  dupliquer_tuiles(tuiles[18], tuile_18);
  plateau[11][15] = tuile_18;
  
  struct graphe_global* graphe_global = init_graphe_global(tuile_14);


  
  assert(graphe_global->nb_sommet == 7);
  assert(graphe_global->nb_arete == 3);
  
  assert(graphe_global->id_sommet[0] == tuile_14->graphe->champs[0]);
  assert(graphe_global->id_sommet[1] == tuile_14->graphe->champs[1]);
  assert(graphe_global->id_sommet[2] == tuile_14->graphe->champs[2]);
  assert(graphe_global->id_sommet[3] == tuile_14->graphe->champs[3]);
  assert(graphe_global->id_sommet[4] == tuile_14->graphe->routes[0]);
  assert(graphe_global->id_sommet[5] == tuile_14->graphe->routes[2]);
  assert(graphe_global->id_sommet[6] == tuile_14->graphe->villes[3]);
  
  assert(graphe_global->tab_successeurs[0]->sommet == tuile_14->graphe->champs[3]);
  assert(graphe_global->tab_successeurs[3]->sommet == tuile_14->graphe->champs[0]);
  assert(graphe_global->tab_successeurs[1]->sommet == tuile_14->graphe->champs[2]);
  assert(graphe_global->tab_successeurs[2]->sommet == tuile_14->graphe->champs[1]);
  
  assert(graphe_global->tab_successeurs[4]->sommet == tuile_14->graphe->routes[2]);
  assert(graphe_global->tab_successeurs[5]->sommet == tuile_14->graphe->routes[0]);
  

  update_graphe_global(plateau, graphe_global, tuile_18, 11, 15);
  
  assert(graphe_global->nb_sommet == 14);
  assert(graphe_global->nb_arete == 9);
  
  assert(graphe_global->id_sommet[7] == tuile_18->graphe->champs[0]);
  assert(graphe_global->id_sommet[9] == tuile_18->graphe->champs[1]);
  assert(graphe_global->id_sommet[11] == tuile_18->graphe->champs[2]);
  assert(graphe_global->id_sommet[8] == tuile_18->graphe->routes[0]);
  assert(graphe_global->id_sommet[10] == tuile_18->graphe->routes[1]);
  assert(graphe_global->id_sommet[12] == tuile_18->graphe->villes[2]);
  assert(graphe_global->id_sommet[13] == tuile_18->graphe->villes[3]);
  
  assert(graphe_global->tab_successeurs[7]->sommet == tuile_18->graphe->champs[2]);
  assert(graphe_global->tab_successeurs[11]->sommet == tuile_18->graphe->champs[0]);
  
  assert(graphe_global->tab_successeurs[8]->sommet == tuile_18->graphe->routes[1]);
  assert(graphe_global->tab_successeurs[10]->sommet == tuile_18->graphe->routes[0]);
  
  assert(graphe_global->tab_successeurs[12]->sommet == tuile_18->graphe->villes[3]);
  assert(graphe_global->tab_successeurs[13]->sommet == tuile_18->graphe->villes[2]);
  
  assert(graphe_global->tab_successeurs[3]->suivant->sommet == tuile_18->graphe->champs[0]);
  assert(graphe_global->tab_successeurs[2]->suivant->sommet == tuile_18->graphe->champs[1]);
  assert(graphe_global->tab_successeurs[5]->suivant->sommet == tuile_18->graphe->routes[0]);
  
  
  free_plateau(plateau, LARGEUR_PLATEAU);
  free_graphe_global(graphe_global);
  
  
  
  
  plateau = initialise_plateau(LARGEUR_PLATEAU);
  struct pioche* pioche = init_pioche();
  
  tuile_14 = init_tuile();
  dupliquer_tuiles(tuiles[14], tuile_14);
  struct tuile* tuile_6 = init_tuile();
  dupliquer_tuiles(tuiles[6], tuile_6);
  struct tuile* tuile_8 = init_tuile();
  dupliquer_tuiles(tuiles[8], tuile_8);
  
  plateau[20][25] = tuile_14;
  
  pioche->tuile_pioche = tuile_6;
  tuile_rotation(pioche, 'd');
  plateau[19][25] = pioche->tuile_pioche;
  
    
  graphe_global = init_graphe_global(tuile_14);
  
  update_graphe_global(plateau, graphe_global, tuile_6, 19, 25);
  
  
  assert(graphe_global->nb_sommet == 13);
  assert(graphe_global->nb_arete == 9);
  
  assert(graphe_global->id_sommet[12] == tuile_6->graphe->champs[3]);
  assert(graphe_global->id_sommet[10] == tuile_6->graphe->champs[2]);
  assert(graphe_global->id_sommet[8]  == tuile_6->graphe->champs[1]);
  
  assert(graphe_global->id_sommet[9]  == tuile_6->graphe->routes[1]);
  assert(graphe_global->id_sommet[11] == tuile_6->graphe->routes[2]);
  
  //Arêtes inter-tuiles
  assert(graphe_global->tab_successeurs[11]->sommet == tuile_6->graphe->routes[1]);
  assert(graphe_global->tab_successeurs[9]->sommet  == tuile_6->graphe->routes[2]);
  
  assert(graphe_global->tab_successeurs[12]->sommet         == tuile_6->graphe->champs[0]);
  assert(graphe_global->tab_successeurs[7]->suivant->sommet == tuile_6->graphe->champs[3]);//double successeur
  assert(graphe_global->tab_successeurs[8]->sommet          == tuile_6->graphe->champs[0]);
  
  //Arêtes entre tuiles
  assert(graphe_global->tab_successeurs[10]->sommet          == tuile_14->graphe->champs[1]);
  assert(graphe_global->tab_successeurs[12]->suivant->sommet == tuile_14->graphe->champs[0]);
  assert(graphe_global->tab_successeurs[0]->suivant->sommet  == tuile_6->graphe->champs[3]);
  assert(graphe_global->tab_successeurs[11]->suivant->sommet == tuile_14->graphe->routes[0]);
  assert(graphe_global->tab_successeurs[4]->suivant->sommet  == tuile_6->graphe->routes[2]);
  
  pioche->tuile_pioche = tuile_8;
  tuile_rotation(pioche, 'd');
  plateau[19][26] = pioche->tuile_pioche;

  update_graphe_global(plateau, graphe_global, tuile_8, 19, 26);

  
  assert(graphe_global->nb_sommet == 20);
  assert(graphe_global->nb_arete == 13);
  
  assert(graphe_global->id_sommet[13] == tuile_8->graphe->champs[0]);
  assert(graphe_global->id_sommet[18] == tuile_8->graphe->champs[3]);
  assert(graphe_global->id_sommet[14] == tuile_8->graphe->champs[1]);
  assert(graphe_global->id_sommet[16] == tuile_8->graphe->champs[2]);
  
  assert(graphe_global->id_sommet[19] == tuile_8->graphe->routes[3]);
  assert(graphe_global->id_sommet[17] == tuile_8->graphe->routes[2]);
  assert(graphe_global->id_sommet[15] == tuile_8->graphe->routes[1]);
  
  //Arêtes inter-tuiles
  assert(graphe_global->tab_successeurs[13]->sommet == tuile_8->graphe->champs[1]);
  assert(graphe_global->tab_successeurs[14]->sommet == tuile_8->graphe->champs[0]);
  
  //Arêtes entre tuiles
  assert(graphe_global->tab_successeurs[13]->suivant->sommet == tuile_6->graphe->champs[1]);
  assert(graphe_global->tab_successeurs[8]->suivant->sommet  == tuile_8->graphe->champs[0]);
  assert(graphe_global->tab_successeurs[19]->sommet          == tuile_6->graphe->routes[1]);
  assert(graphe_global->tab_successeurs[9]->suivant->sommet  == tuile_8->graphe->routes[3]);
  assert(graphe_global->tab_successeurs[18]->sommet          == tuile_6->graphe->champs[2]);
  assert(graphe_global->tab_successeurs[10]->suivant->sommet == tuile_8->graphe->champs[3]);
  
  
  
  free_plateau(plateau, LARGEUR_PLATEAU);
  free_tuiles(tuiles);
  free_graphe_global(graphe_global);
  
  
  
  return EXIT_SUCCESS;
}


int test_parcourt_graphe_global()
{
  
  struct tuile*** plateau = initialise_plateau(LARGEUR_PLATEAU);
  
  struct tuile* tuiles[NB_TUILES];
  for(int i=0;i<NB_TUILES;i++)
  {
    tuiles[i]=NULL;
  }
  tuile_parseur(tuiles, "tuiles.txt");
  
  struct tuile* tuile_14 = init_tuile();
  dupliquer_tuiles(tuiles[14], tuile_14);
  plateau[10][15] = tuile_14;
  struct tuile* tuile_18 = init_tuile();
  dupliquer_tuiles(tuiles[18], tuile_18);
  plateau[11][15] = tuile_18;
  
  struct graphe_global* graphe_global = init_graphe_global(tuile_14);
  
  update_graphe_global(plateau, graphe_global, tuile_18, 11, 15);
  
  init_parcourt_graphe(graphe_global);
  for (int i=0; i<graphe_global->nb_sommet; i++)
  {
    assert(graphe_global->id_sommet[i]->parcourt_graphe == BLANC);
  }
  parcourt_graphe_global(graphe_global, tuile_14->graphe->champs[0], &est_pion);
  assert(graphe_global->id_sommet[0]->parcourt_graphe == NOIR);
  assert(graphe_global->id_sommet[3]->parcourt_graphe == NOIR);
  assert(graphe_global->id_sommet[7]->parcourt_graphe == NOIR);
  assert(graphe_global->id_sommet[11]->parcourt_graphe == NOIR);
  
  init_parcourt_graphe(graphe_global);
  parcourt_graphe_global(graphe_global, tuile_14->graphe->champs[1], &est_pion);
  assert(graphe_global->id_sommet[1]->parcourt_graphe == NOIR);
  assert(graphe_global->id_sommet[2]->parcourt_graphe == NOIR);
  assert(graphe_global->id_sommet[9]->parcourt_graphe == NOIR);
  assert(graphe_global->id_sommet[11]->parcourt_graphe == BLANC);
  
  init_parcourt_graphe(graphe_global);
  parcourt_graphe_global(graphe_global, tuile_14->graphe->routes[0], &est_pion);
  assert(graphe_global->id_sommet[4]->parcourt_graphe == NOIR);
  assert(graphe_global->id_sommet[5]->parcourt_graphe == NOIR);
  assert(graphe_global->id_sommet[8]->parcourt_graphe == NOIR);
  assert(graphe_global->id_sommet[10]->parcourt_graphe == NOIR);
  assert(graphe_global->id_sommet[0]->parcourt_graphe == BLANC);
  assert(graphe_global->id_sommet[11]->parcourt_graphe == BLANC);
  
  free_plateau(plateau, LARGEUR_PLATEAU);
  free_tuiles(tuiles);
  free_graphe_global(graphe_global);
  
  return EXIT_SUCCESS;
}

int test_poser_pion()
{
  struct tuile*** plateau = initialise_plateau(LARGEUR_PLATEAU);
  
  struct tuile* tuiles[NB_TUILES];
  for(int i=0;i<NB_TUILES;i++)
  {
    tuiles[i]=NULL;
  }
  tuile_parseur(tuiles, "tuiles.txt");
  
  struct tuile* tuile_14 = init_tuile();
  dupliquer_tuiles(tuiles[14], tuile_14);
  plateau[10][15] = tuile_14;
  struct tuile* tuile_18 = init_tuile();
  dupliquer_tuiles(tuiles[18], tuile_18);
  plateau[11][15] = tuile_18;
  
  struct graphe_global* graphe_global = init_graphe_global(tuile_14);
  
  update_graphe_global(plateau, graphe_global, tuile_18, 11, 15);

  assert(tuile_18->graphe->routes[0]->pion == 0);
  assert(poser_pion(graphe_global, tuile_18->graphe->routes[0]) == EXIT_SUCCESS);
  assert(tuile_18->graphe->routes[0]->pion == 1);
  assert(poser_pion(graphe_global, tuile_18->graphe->routes[0]) == EXIT_FAILURE);
  
  free_plateau(plateau, LARGEUR_PLATEAU);
  free_tuiles(tuiles);
  free_graphe_global(graphe_global);
  
  return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
  time_t t;
  /* Intializes random number generator */
  srand((unsigned) time(&t));
  test_graphe_global();
  test_parcourt_graphe_global();
  test_poser_pion();
  printf("Aucune erreur détectée\n");
  
	return 1;
}
