#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "../src/struct.h"
#include "../src/logique/tuiles/tuiles.h"
#include "../src/logique/plateau/plateau.h"


int test_est_compatible_routes()
{
  
  struct tuile*** plateau = initialise_plateau(LARGEUR_PLATEAU);
  struct tuile* tuiles[NB_TUILES];
	for(int i=0;i<NB_TUILES;i++)
	{
		tuiles[i]=NULL;
	}
  tuile_parseur(tuiles, "tuiles.txt");

  
  plateau[72][72] = tuiles[1];
  plateau[71][73] = tuiles[14];
  plateau[72][74] = tuiles[5];
  plateau[73][73] = tuiles[15];
  
  assert(est_compatible_routes(plateau, tuiles[5], 72, 73, 'h') == EXIT_VERTICES_ACTIVATED);
  assert(est_compatible_routes(plateau, tuiles[5], 72, 73, 'b') == EXIT_VERTICES_ACTIVATED);
  assert(est_compatible_routes(plateau, tuiles[5], 72, 73, 'g') == EXIT_VERTICES_ACTIVATED);
  assert(est_compatible_routes(plateau, tuiles[5], 72, 73, 'd') == EXIT_VERTICES_ACTIVATED);
  
  assert(est_compatible_routes(plateau, tuiles[10], 72, 73, 'h') == EXIT_VERTICES_DIFFERENT);
  assert(est_compatible_routes(plateau, tuiles[10], 72, 73, 'b') == EXIT_VERTICES_DIFFERENT);
  assert(est_compatible_routes(plateau, tuiles[10], 72, 73, 'g') == EXIT_VERTICES_DIFFERENT);
  assert(est_compatible_routes(plateau, tuiles[10], 72, 73, 'd') == EXIT_VERTICES_DIFFERENT);
  
  assert(est_compatible_routes(plateau, tuiles[8], 72, 73, 'h') == EXIT_VERTICES_ACTIVATED);
  assert(est_compatible_routes(plateau, tuiles[8], 72, 73, 'b') == EXIT_VERTICES_ACTIVATED);
  assert(est_compatible_routes(plateau, tuiles[8], 72, 73, 'g') == EXIT_VERTICES_DIFFERENT);
  assert(est_compatible_routes(plateau, tuiles[8], 72, 73, 'd') == EXIT_VERTICES_ACTIVATED);
  
  assert(est_compatible_routes(plateau, tuiles[15], 72, 73, 'h') == EXIT_VERTICES_ACTIVATED);
  assert(est_compatible_routes(plateau, tuiles[15], 72, 73, 'b') == EXIT_VERTICES_DIFFERENT);
  assert(est_compatible_routes(plateau, tuiles[15], 72, 73, 'g') == EXIT_VERTICES_DIFFERENT);
  assert(est_compatible_routes(plateau, tuiles[15], 72, 73, 'd') == EXIT_VERTICES_ACTIVATED);
  
  assert(est_compatible_routes(plateau, tuiles[16], 72, 73, 'h') == EXIT_VERTICES_DIFFERENT);
  assert(est_compatible_routes(plateau, tuiles[16], 72, 73, 'b') == EXIT_VERTICES_ACTIVATED);
  assert(est_compatible_routes(plateau, tuiles[16], 72, 73, 'g') == EXIT_VERTICES_DIFFERENT);
  assert(est_compatible_routes(plateau, tuiles[16], 72, 73, 'd') == EXIT_VERTICES_ACTIVATED);
  
  
  plateau[72][72] = tuiles[14];
  plateau[71][73] = tuiles[13];
  plateau[72][74] = tuiles[6];
  plateau[73][73] = tuiles[16];
  
  assert(est_compatible_routes(plateau, tuiles[3], 72, 73, 'h') == EXIT_VERTICES_DESACTIVATED);
  assert(est_compatible_routes(plateau, tuiles[3], 72, 73, 'b') == EXIT_VERTICES_DESACTIVATED);
  assert(est_compatible_routes(plateau, tuiles[3], 72, 73, 'g') == EXIT_VERTICES_DESACTIVATED);
  assert(est_compatible_routes(plateau, tuiles[3], 72, 73, 'd') == EXIT_VERTICES_DESACTIVATED);
  
  assert(est_compatible_routes(plateau, tuiles[12], 72, 73, 'h') == EXIT_VERTICES_DESACTIVATED);
  assert(est_compatible_routes(plateau, tuiles[12], 72, 73, 'b') == EXIT_VERTICES_DESACTIVATED);
  assert(est_compatible_routes(plateau, tuiles[12], 72, 73, 'g') == EXIT_VERTICES_DESACTIVATED);
  assert(est_compatible_routes(plateau, tuiles[12], 72, 73, 'd') == EXIT_VERTICES_DESACTIVATED);
  
  assert(est_compatible_routes(plateau, tuiles[8], 72, 73, 'h') == EXIT_VERTICES_DIFFERENT);
  assert(est_compatible_routes(plateau, tuiles[8], 72, 73, 'b') == EXIT_VERTICES_DIFFERENT);
  assert(est_compatible_routes(plateau, tuiles[8], 72, 73, 'g') == EXIT_VERTICES_DESACTIVATED);
  assert(est_compatible_routes(plateau, tuiles[8], 72, 73, 'd') == EXIT_VERTICES_DIFFERENT);
  
  assert(est_compatible_routes(plateau, tuiles[5], 72, 73, 'h') == EXIT_VERTICES_DIFFERENT);
  assert(est_compatible_routes(plateau, tuiles[5], 72, 73, 'b') == EXIT_VERTICES_DIFFERENT);
  assert(est_compatible_routes(plateau, tuiles[5], 72, 73, 'g') == EXIT_VERTICES_DIFFERENT);
  assert(est_compatible_routes(plateau, tuiles[5], 72, 73, 'd') == EXIT_VERTICES_DIFFERENT);

  
  free_plateau(plateau, LARGEUR_PLATEAU);
  free_tuiles(tuiles);
  
  return EXIT_SUCCESS;
}



int test_est_compatible_villes()
{
  
  struct tuile*** plateau = initialise_plateau(LARGEUR_PLATEAU);
  struct tuile* tuiles[NB_TUILES];
  for(int i=0;i<NB_TUILES;i++)
  {
    tuiles[i]=NULL;
  }
  tuile_parseur(tuiles, "tuiles.txt");


  plateau[10][15] = tuiles[0];
  plateau[11][14] = tuiles[13];
  plateau[11][16] = tuiles[3];
  plateau[12][15] = tuiles[10];
  
  assert(est_compatible_villes(plateau, tuiles[17], 11, 15, 'h') == EXIT_VERTICES_ACTIVATED);
  assert(est_compatible_villes(plateau, tuiles[17], 11, 15, 'b') == EXIT_VERTICES_ACTIVATED);
  assert(est_compatible_villes(plateau, tuiles[17], 11, 15, 'g') == EXIT_VERTICES_DESACTIVATED);
  assert(est_compatible_villes(plateau, tuiles[17], 11, 15, 'd') == EXIT_VERTICES_DESACTIVATED);
  
  assert(est_compatible_villes(plateau, tuiles[9], 11, 15, 'h') == EXIT_VERTICES_ACTIVATED);
  assert(est_compatible_villes(plateau, tuiles[9], 11, 15, 'b') == EXIT_VERTICES_ACTIVATED);
  assert(est_compatible_villes(plateau, tuiles[9], 11, 15, 'g') == EXIT_VERTICES_DIFFERENT);
  assert(est_compatible_villes(plateau, tuiles[9], 11, 15, 'd') == EXIT_VERTICES_DIFFERENT);
  
  assert(est_compatible_villes(plateau, tuiles[14], 11, 15, 'h') == EXIT_VERTICES_DIFFERENT);
  assert(est_compatible_villes(plateau, tuiles[14], 11, 15, 'b') == EXIT_VERTICES_DIFFERENT);
  assert(est_compatible_villes(plateau, tuiles[14], 11, 15, 'g') == EXIT_VERTICES_DIFFERENT);
  assert(est_compatible_villes(plateau, tuiles[14], 11, 15, 'd') == EXIT_VERTICES_DESACTIVATED);
  
  assert(est_compatible_villes(plateau, tuiles[12], 11, 15, 'h') == EXIT_VERTICES_ACTIVATED);
  assert(est_compatible_villes(plateau, tuiles[12], 11, 15, 'b') == EXIT_VERTICES_DIFFERENT);
  assert(est_compatible_villes(plateau, tuiles[12], 11, 15, 'g') == EXIT_VERTICES_DIFFERENT);
  assert(est_compatible_villes(plateau, tuiles[12], 11, 15, 'd') == EXIT_VERTICES_DESACTIVATED);

  
  free_plateau(plateau, LARGEUR_PLATEAU);
  free_tuiles(tuiles);
  
  return EXIT_SUCCESS;
}


int test_tuiles_compatibles()
{
  
  struct tuile*** plateau = initialise_plateau(LARGEUR_PLATEAU);
  struct tuile* tuiles[NB_TUILES];
  for(int i=0;i<NB_TUILES;i++)
  {
    tuiles[i]=NULL;
  }
  tuile_parseur(tuiles, "tuiles.txt");


  plateau[10][15] = tuiles[0];
  plateau[11][14] = tuiles[13];
  plateau[11][16] = tuiles[3];
  plateau[12][15] = tuiles[10];
  
  assert(tuiles_compatibles(plateau, tuiles[17], 11, 15) == EXIT_COMPATIBLE);
  assert(tuiles_compatibles(plateau, tuiles[9], 11, 15) == EXIT_NOT_COMPATIBLE);
  
  plateau[42][21] = tuiles[0];
  assert(tuiles_compatibles(plateau, tuiles[9], 43, 21) == EXIT_COMPATIBLE);
  plateau[43][21] = tuiles[9];
  assert(tuiles_compatibles(plateau, tuiles[2], 42, 20) == EXIT_COMPATIBLE);
  plateau[42][20] = tuiles[2];
  assert(tuiles_compatibles(plateau, tuiles[3], 43, 20) == EXIT_NOT_COMPATIBLE);
  assert(tuiles_compatibles(plateau, tuiles[3], 42, 22) == EXIT_COMPATIBLE);
  plateau[42][22] = tuiles[3];
  assert(tuiles_compatibles(plateau, tuiles[13], 43, 22) == EXIT_COMPATIBLE);
  plateau[43][22] = tuiles[13];
  assert(tuiles_compatibles(plateau, tuiles[4], 44, 22) == EXIT_COMPATIBLE);
  plateau[44][22] = tuiles[4];
  assert(tuiles_compatibles(plateau, tuiles[8], 45, 22) == EXIT_COMPATIBLE);
  plateau[45][22] = tuiles[8];
  assert(tuiles_compatibles(plateau, tuiles[6], 46, 22) == EXIT_COMPATIBLE);
  plateau[46][22] = tuiles[6];
  assert(tuiles_compatibles(plateau, tuiles[16], 47, 22) == EXIT_COMPATIBLE);
  plateau[47][22] = tuiles[16];
  assert(tuiles_compatibles(plateau, tuiles[5], 46, 23) == EXIT_COMPATIBLE);
  plateau[46][23] = tuiles[5];
  assert(tuiles_compatibles(plateau, tuiles[5], 47, 23) == EXIT_COMPATIBLE);
  plateau[47][23] = tuiles[5];
  assert(tuiles_compatibles(plateau, tuiles[5], 45, 23) == EXIT_COMPATIBLE);
  plateau[45][23] = tuiles[5];
  assert(tuiles_compatibles(plateau, tuiles[17], 44, 21) == EXIT_COMPATIBLE);
  plateau[44][21] = tuiles[17];
  assert(tuiles_compatibles(plateau, tuiles[12], 45, 21) == EXIT_COMPATIBLE);
  plateau[45][21] = tuiles[12];
  assert(tuiles_compatibles(plateau, tuiles[9], 45, 20) == EXIT_COMPATIBLE);
  plateau[45][20] = tuiles[9];
  assert(tuiles_compatibles(plateau, tuiles[12], 46, 20) == EXIT_COMPATIBLE);
  plateau[46][20] = tuiles[12];
  assert(tuiles_compatibles(plateau, tuiles[13], 46, 21) == EXIT_NOT_COMPATIBLE);
  assert(tuiles_compatibles(plateau, tuiles[3], 46, 21) == EXIT_COMPATIBLE);
  plateau[46][21] = tuiles[3];
  
  
  free_plateau(plateau, LARGEUR_PLATEAU);
  free_tuiles(tuiles);
  
  return EXIT_SUCCESS;
}

int test_poser_tuile()
{
  
  struct tuile*** plateau = initialise_plateau(LARGEUR_PLATEAU);
  struct tuile* tuiles[NB_TUILES];
  for(int i=0;i<NB_TUILES;i++)
  {
    tuiles[i]=NULL;
  }
  tuile_parseur(tuiles, "tuiles.txt");


  plateau[10][15] = tuiles[0];
  plateau[11][14] = tuiles[13];
  plateau[11][16] = tuiles[3];
  plateau[12][15] = tuiles[10];
  
  assert(poser_tuile(plateau, tuiles[17], 11, 15) == EXIT_SUCCESS);
  assert(plateau[11][15] == tuiles[17]);
  
  assert(plateau[42][21] == tuiles[0]);
  assert(poser_tuile(plateau, tuiles[9], 43, 21) == EXIT_SUCCESS);
  assert(plateau[43][21] == tuiles[9]);
  assert(poser_tuile(plateau, tuiles[2], 42, 20) == EXIT_SUCCESS);
  assert(plateau[42][20] == tuiles[2]);
  assert(poser_tuile(plateau, tuiles[3], 43, 20) == EXIT_FAILURE);
  assert(plateau[43][20] == NULL);
  assert(poser_tuile(plateau, tuiles[3], 42, 22) == EXIT_SUCCESS);
  assert(plateau[42][22] == tuiles[3]);
  assert(poser_tuile(plateau, tuiles[13], 43, 22) == EXIT_SUCCESS);
  assert(plateau[43][22] == tuiles[13]);
  assert(poser_tuile(plateau, tuiles[4], 44, 22) == EXIT_SUCCESS);
  assert(plateau[44][22] == tuiles[4]);
  assert(poser_tuile(plateau, tuiles[8], 45, 22) == EXIT_SUCCESS);
  assert(plateau[45][22] == tuiles[8]);
  assert(poser_tuile(plateau, tuiles[6], 46, 22) == EXIT_SUCCESS);
  assert(plateau[46][22] == tuiles[6]);
  assert(poser_tuile(plateau, tuiles[16], 47, 22) == EXIT_SUCCESS);
  assert(plateau[47][22] == tuiles[16]);
  assert(poser_tuile(plateau, tuiles[5], 46, 23) == EXIT_SUCCESS);
  assert(plateau[46][23] == tuiles[5]);
  assert(poser_tuile(plateau, tuiles[5], 47, 23) == EXIT_SUCCESS);
  assert(plateau[47][23] == tuiles[5]);
  assert(poser_tuile(plateau, tuiles[5], 45, 23) == EXIT_SUCCESS);
  assert(plateau[45][23] == tuiles[5]);
  assert(poser_tuile(plateau, tuiles[17], 44, 21) == EXIT_SUCCESS);
  assert(plateau[44][21] == tuiles[17]);
  assert(poser_tuile(plateau, tuiles[12], 45, 21) == EXIT_SUCCESS);
  assert(plateau[45][21] == tuiles[12]);
  assert(poser_tuile(plateau, tuiles[9], 45, 20) == EXIT_SUCCESS);
  assert(plateau[45][20] == tuiles[9]);
  assert(poser_tuile(plateau, tuiles[12], 46, 20) == EXIT_SUCCESS);
  assert(plateau[46][20] == tuiles[12]);
  assert(poser_tuile(plateau, tuiles[13], 46, 21) == EXIT_FAILURE);
  assert(plateau[46][21] == NULL);
  assert(poser_tuile(plateau, tuiles[3], 46, 21) == EXIT_SUCCESS);
  assert(plateau[46][21] == tuiles[3]);

  
  
  free_plateau(plateau, LARGEUR_PLATEAU);
  free_tuiles(tuiles);
  
  return EXIT_SUCCESS;
}


int test_update_pioche()
{
  struct tuile* tuiles[NB_TUILES];
  for(int i=0;i<NB_TUILES;i++)
  {
    tuiles[i]=NULL;
  }
  tuile_parseur(tuiles, "tuiles.txt");
  struct pioche* pioche = init_pioche();
  for (int i=0;i<72;i++)
  {
    assert(update_pioche(pioche, tuiles) != EXIT_ANY_TILE_AVAILLABLE);
  }
  assert(update_pioche(pioche, tuiles) == EXIT_ANY_TILE_AVAILLABLE);
  return EXIT_SUCCESS;
}


int test_init_pioche()
{
  struct pioche* pioche = NULL;
  pioche = init_pioche();
  assert(pioche != NULL);
  for (int i=0; i<NB_TUILES; i++)
  {
    assert(pioche->nb_carte[i] == 0);
  }
  assert(pioche->tuile_pioche == NULL);
  
  return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
  time_t t;
  /* Intializes random number generator */
  srand((unsigned) time(&t));
  
  test_init_pioche();
  test_update_pioche();
  test_est_compatible_routes();
  test_est_compatible_villes();
  test_tuiles_compatibles();
  printf("Aucune erreur détectée\n"); 

	return 1;
}
 