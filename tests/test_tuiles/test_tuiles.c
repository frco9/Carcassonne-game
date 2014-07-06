#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../src/struct.h"
#include "../../src/logique/tuiles/tuiles.h"
#include "../../src/logique/tuiles/graph_tuiles.h"
#include "../../src/logique/graphe/graph.h"


int test_tuiles_parseur()
{
  struct tuile* tuiles[NB_TUILES];
  for(int i=0;i<NB_TUILES;i++)
    {
      tuiles[i]=NULL;
    }
  
  for(int i=0;i<NB_TUILES;i++)
    {
      assert(tuiles[i]==NULL);
    }
  assert(tuile_parseur(tuiles, "unknw") == EXIT_FAILURE);
  
  assert(tuile_parseur(tuiles, "tuiles_err1.txt") == EXIT_FAILURE);
  for(int i=0;i<NB_TUILES;i++)
    {
      assert(tuiles[i]==NULL);
    }
  
  assert(tuile_parseur(tuiles, "tuiles_err2.txt") == EXIT_FAILURE);
  for(int i=0;i<NB_TUILES;i++)
    {
      assert(tuiles[i]==NULL);
    }
  
  assert(tuile_parseur(tuiles, "tuiles_err3.txt") == EXIT_FAILURE);
  for(int i=0;i<NB_TUILES;i++)
    {
      assert(tuiles[i]==NULL);
    }
  
  assert(tuile_parseur(tuiles, "tuiles_err4.txt") == EXIT_FAILURE);
  for(int i=0;i<NB_TUILES;i++)
    {
      assert(tuiles[i]==NULL);
    }
  
  assert(tuile_parseur(tuiles, "tuiles_err5.txt") == EXIT_SUCCESS);
  free_tuiles(tuiles);
  for(int i=0;i<NB_TUILES;i++)
    {
      assert(tuiles[i]==NULL);
    }
  
  assert(tuile_parseur(tuiles, "tuiles_err6.txt") == EXIT_FAILURE);
  for(int i=0;i<NB_TUILES;i++)
    {
      assert(tuiles[i]==NULL);
    }
  
  assert(tuile_parseur(tuiles, "tuiles_err7.txt") == EXIT_FAILURE);
  for(int i=0;i<NB_TUILES;i++)
    {
      assert(tuiles[i]==NULL);
    }
  
  assert(tuile_parseur(tuiles, "tuiles_err8.txt") == EXIT_FAILURE);
  for(int i=0;i<NB_TUILES;i++)
    {
      assert(tuiles[i]==NULL);
    }
  
  assert(tuile_parseur(tuiles, "tuiles_err9.txt") == EXIT_FAILURE);
  for(int i=0;i<NB_TUILES;i++)
    {
      assert(tuiles[i]==NULL);
    }
  
  assert(tuile_parseur(tuiles, "tuiles_err10.txt") == EXIT_FAILURE);
  for(int i=0;i<NB_TUILES;i++)
    {
      assert(tuiles[i]==NULL);
    }
  
  assert(tuile_parseur(tuiles, "tuiles_err11.txt") == EXIT_FAILURE);
  for(int i=0;i<NB_TUILES;i++)
    {
      assert(tuiles[i]==NULL);
    }
  
  assert(tuile_parseur(tuiles, "tuiles_succ1.txt") == EXIT_SUCCESS);
  assert(tuiles[1]->image == 2);
  assert(tuiles[1]->graphe->champs[0]->actif == 1);
  assert(tuiles[1]->graphe->champs[1]->actif == 1);
  assert(tuiles[1]->graphe->champs[2]->actif == 1);
  assert(tuiles[1]->graphe->champs[3]->actif == 1);
  assert(tuiles[1]->graphe->villes[0]->actif == 0);
  assert(tuiles[1]->graphe->villes[1]->actif == 0);
  assert(tuiles[1]->graphe->villes[2]->actif == 0);
  assert(tuiles[1]->graphe->villes[3]->actif == 1);
  assert(tuiles[1]->graphe->routes[0]->actif == 1);
  assert(tuiles[1]->graphe->routes[1]->actif == 1);
  assert(tuiles[1]->graphe->routes[2]->actif == 1);
  assert(tuiles[1]->graphe->routes[3]->actif == 0);
  
  assert(tuiles[1]->graphe->mat_champs[0][0] == 0);
  assert(tuiles[1]->graphe->mat_champs[0][1] == 0);
  assert(tuiles[1]->graphe->mat_champs[0][2] == 1);
  assert(tuiles[1]->graphe->mat_champs[0][3] == 0);
  assert(tuiles[1]->graphe->mat_champs[1][0] == 0);
  assert(tuiles[1]->graphe->mat_champs[1][1] == 0);
  assert(tuiles[1]->graphe->mat_champs[1][2] == 0);
  assert(tuiles[1]->graphe->mat_champs[1][3] == 0);
  assert(tuiles[1]->graphe->mat_champs[2][0] == 0);
  assert(tuiles[1]->graphe->mat_champs[2][1] == 0);
  assert(tuiles[1]->graphe->mat_champs[2][2] == 0);
  assert(tuiles[1]->graphe->mat_champs[2][3] == 0);
  assert(tuiles[1]->graphe->mat_champs[3][0] == 0);
  assert(tuiles[1]->graphe->mat_champs[3][1] == 0);
  assert(tuiles[1]->graphe->mat_champs[3][2] == 0);
  assert(tuiles[1]->graphe->mat_champs[3][3] == 0);
  
  assert(tuiles[1]->graphe->mat_routes[0][0] == 0);
  assert(tuiles[1]->graphe->mat_routes[0][1] == 1);
  assert(tuiles[1]->graphe->mat_routes[0][2] == 0);
  assert(tuiles[1]->graphe->mat_routes[0][3] == 0);
  assert(tuiles[1]->graphe->mat_routes[1][0] == 0);
  assert(tuiles[1]->graphe->mat_routes[1][1] == 0);
  assert(tuiles[1]->graphe->mat_routes[1][2] == 1);
  assert(tuiles[1]->graphe->mat_routes[1][3] == 0);
  assert(tuiles[1]->graphe->mat_routes[2][0] == 0);
  assert(tuiles[1]->graphe->mat_routes[2][1] == 0);
  assert(tuiles[1]->graphe->mat_routes[2][2] == 0);
  assert(tuiles[1]->graphe->mat_routes[2][3] == 0);
  assert(tuiles[1]->graphe->mat_routes[3][0] == 0);
  assert(tuiles[1]->graphe->mat_routes[3][1] == 0);
  assert(tuiles[1]->graphe->mat_routes[3][2] == 0);
  assert(tuiles[1]->graphe->mat_routes[3][3] == 0);
  free_tuiles(tuiles);
  for(int i=0;i<NB_TUILES;i++)
    {
      assert(tuiles[i]==NULL);
    }
  
  assert(tuile_parseur(tuiles, "tuiles.txt") == EXIT_SUCCESS);
  for(int i=0;i<NB_TUILES;i++)
    {
      assert(tuiles[i]!=NULL);
    }
  free_tuiles(tuiles);
  for(int i=0;i<NB_TUILES;i++)
    {
      assert(tuiles[i]==NULL);
    }
  
  printf("\nAucune erreur detecté lors du parsing\n");
  return EXIT_SUCCESS;
}

int test_tuile_rotation()
{
  struct tuile* tuiles[NB_TUILES];
  struct pioche* pioche = init_pioche();
  struct tuile* rot_tuiles[6];
  for(int i=0;i<NB_TUILES;i++)
  {
    tuiles[i]=NULL;
  }
  tuile_parseur(tuiles, "tuiles.txt");
  
  for (int i=0; i<6; i++)
  {
    pioche->tuile_pioche = tuiles[i];
    tuile_rotation(pioche, 'g');
    rot_tuiles[i] = pioche->tuile_pioche;
  }
  
  
  for(int i=0;i<6;i++)
  {
    assert(rot_tuiles[i] != NULL);
  }
  assert(tuile_rotation(tuiles[2], 'r') == NULL);
  
  assert(rot_tuiles[0]->graphe->champs[0]->actif == 1);
  assert(rot_tuiles[0]->graphe->champs[1]->actif == 1);
  assert(rot_tuiles[0]->graphe->champs[2]->actif == 0);
  assert(rot_tuiles[0]->graphe->champs[3]->actif == 1);
  
  assert(rot_tuiles[0]->graphe->villes[0]->actif == 0);
  assert(rot_tuiles[0]->graphe->villes[1]->actif == 1);
  assert(rot_tuiles[0]->graphe->villes[2]->actif == 1);
  assert(rot_tuiles[0]->graphe->villes[3]->actif == 0);
  
  assert(rot_tuiles[0]->graphe->mat_champs[0][1] == 1);
  assert(rot_tuiles[0]->graphe->mat_champs[0][3] == 1);
  assert(rot_tuiles[0]->graphe->mat_villes[1][2] == 1);
  
  
  assert(rot_tuiles[1]->graphe->champs[0]->actif == 0);
  assert(rot_tuiles[1]->graphe->champs[1]->actif == 1);
  assert(rot_tuiles[1]->graphe->champs[2]->actif == 1);
  assert(rot_tuiles[1]->graphe->champs[3]->actif == 1);
  
  assert(rot_tuiles[1]->graphe->villes[0]->actif == 1);
  assert(rot_tuiles[1]->graphe->villes[1]->actif == 0);
  assert(rot_tuiles[1]->graphe->villes[2]->actif == 0);
  assert(rot_tuiles[1]->graphe->villes[3]->actif == 1);
  
  assert(rot_tuiles[1]->graphe->mat_champs[1][2] == 1);
  assert(rot_tuiles[1]->graphe->mat_champs[2][3] == 1);
  assert(rot_tuiles[1]->graphe->mat_villes[0][3] == 1);
  
  
  assert(rot_tuiles[2]->graphe->champs[0]->actif == 1);
  assert(rot_tuiles[2]->graphe->champs[1]->actif == 1);
  assert(rot_tuiles[2]->graphe->champs[2]->actif == 1);
  assert(rot_tuiles[2]->graphe->champs[3]->actif == 1);
  
  assert(rot_tuiles[2]->graphe->routes[0]->actif == 1);
  assert(rot_tuiles[2]->graphe->routes[1]->actif == 0);
  assert(rot_tuiles[2]->graphe->routes[2]->actif == 0);
  assert(rot_tuiles[2]->graphe->routes[3]->actif == 1);
  
  assert(rot_tuiles[2]->graphe->mat_champs[1][2] == 1);
  assert(rot_tuiles[2]->graphe->mat_champs[2][3] == 1);
  assert(rot_tuiles[2]->graphe->mat_routes[0][3] == 1);
  
  
  assert(rot_tuiles[3]->graphe->champs[0]->actif == 1);
  assert(rot_tuiles[3]->graphe->champs[1]->actif == 1);
  assert(rot_tuiles[3]->graphe->champs[2]->actif == 1);
  assert(rot_tuiles[3]->graphe->champs[3]->actif == 1);
  
  assert(rot_tuiles[3]->graphe->routes[0]->actif == 0);
  assert(rot_tuiles[3]->graphe->routes[1]->actif == 1);
  assert(rot_tuiles[3]->graphe->routes[2]->actif == 1);
  assert(rot_tuiles[3]->graphe->routes[3]->actif == 0);
  
  assert(rot_tuiles[3]->graphe->mat_champs[0][1] == 1);
  assert(rot_tuiles[3]->graphe->mat_champs[0][3] == 1);
  assert(rot_tuiles[3]->graphe->mat_routes[1][2] == 1);

  for(int i=0;i<NB_SOMMETS;i++)
  {
    assert(rot_tuiles[4]->graphe->champs[i]->actif == tuiles[5]->graphe->champs[i]->actif);
    assert(rot_tuiles[4]->graphe->routes[i]->actif == tuiles[5]->graphe->routes[i]->actif);
    assert(rot_tuiles[4]->graphe->villes[i]->actif == tuiles[5]->graphe->villes[i]->actif);
    
    assert(rot_tuiles[5]->graphe->champs[i]->actif == tuiles[5]->graphe->champs[i]->actif);
    assert(rot_tuiles[5]->graphe->routes[i]->actif == tuiles[5]->graphe->routes[i]->actif);
    assert(rot_tuiles[5]->graphe->villes[i]->actif == tuiles[5]->graphe->villes[i]->actif);

  }
  for(int i=0; i<NB_SOMMETS; i++)
  {
    for (int j=i+1; j<NB_SOMMETS; j++)
    {
      assert(rot_tuiles[4]->graphe->mat_champs[i][j] == tuiles[5]->graphe->mat_champs[i][j]);
      assert(rot_tuiles[4]->graphe->mat_routes[i][j] == tuiles[5]->graphe->mat_routes[i][j]);
      assert(rot_tuiles[4]->graphe->mat_villes[i][j] == tuiles[5]->graphe->mat_villes[i][j]);
      
      assert(rot_tuiles[5]->graphe->mat_champs[i][j] == tuiles[5]->graphe->mat_champs[i][j]);
      assert(rot_tuiles[5]->graphe->mat_routes[i][j] == tuiles[5]->graphe->mat_routes[i][j]);
      assert(rot_tuiles[5]->graphe->mat_villes[i][j] == tuiles[5]->graphe->mat_villes[i][j]);
    }
  }
  
  
  
  
  free_tuiles(rot_tuiles);
  free_tuiles(tuiles);
  return EXIT_SUCCESS;
}


int main(int argc, char* argv[])
{
  test_tuiles_parseur();
  test_tuile_rotation();
  printf("\nAucune erreur detecté lors du parsing\n");
  return 1;
}
