#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../struct.h"
#include "../tuiles/tuiles.h"
#include "../tuiles/graph_tuiles.h"
#include "plateau.h"

/*
 typedef enum {champs, routes, villes, monaster};
 typedef enum {oui, non} ;
 */

/**
 * \fn struct tuile*** initialise_plateau()
 * \brief Fonction Initialisant le tableau utilisé comme le plateau du jeu
 * \param taille_plateau Correspond à la taille du plateau à alouer
 * \return struct tuile*** plateau Pointeur vers un tableau deux dimensions
 */
struct tuile*** initialise_plateau(int taille_plateau)
{
  struct tuile*** plateau;
  
  plateau = malloc(sizeof(struct tuile**) * taille_plateau);
  for(int y=0; y<taille_plateau; y++)
  {
    plateau[y] = malloc(sizeof(struct tuile*) * taille_plateau);
    for(int x=0; x<taille_plateau; x++)
    {
      plateau[y][x] = NULL;
    }
  }
  return plateau;
}


/**
 * \fn int free_plateau(struct tuile*** plateau)
 * \brief Fonction libérant toute la memoire alouée pour le plateau
 * \param struct tuile*** plateau Tableau de pointeur vers des structures tuile
 * \param taille_plateau Taille du plateau à liberer
 * \return int Correspond au succès ou l'echec de l'execution.
 */
int free_plateau(struct tuile*** plateau, int taille_plateau)
{
  
  for (int i=0; i<taille_plateau; i++)
  {
    for (int j=0; j<taille_plateau; j++)
    {
      if (plateau[i][j] != NULL)
      {
        if (taille_plateau == LARGEUR_PLATEAU)
        {
          free_graphe(plateau[i][j]->graphe);
          free(plateau[i][j]);
        }
        plateau[i][j] = NULL;
      }
    }
    free(plateau[i]);
  }
  free(plateau);
  
  return EXIT_SUCCESS;
}


/**
 * \fn int poser_tuile(struct tuile*** plateau, struct tuile* tuile_n, int x, int y)
 * \brief Fonction permettant le placement d'une tuile après verification que son placement est possible.
 * \param struct tuile*** plateau Plateau du jeu contenant les pointeurs des tuiles déjà posées.
 * \param struct tuile* tuile_n Pointeur vers la tuile que l'on souhaite poser.
 * \param int x Coordonnée x où l'on veut placer la tuile.
 * \param int y Coordonnée y où l'on veut placer la tuile.
 * \return int Code erreur correspondant à la réussite ou l'echec du placement de la fonction.
 */
int poser_tuile(struct tuile*** plateau, struct tuile* tuile_n, int x, int y)
{
  if((x<LARGEUR_PLATEAU) && (y<LARGEUR_PLATEAU) && (plateau[x][y]==NULL) && (tuiles_compatibles(plateau, tuile_n, x ,y) == EXIT_COMPATIBLE))
  {
    plateau[x][y] = tuile_n;
    return EXIT_SUCCESS;
  }
  else
  {
    return EXIT_FAILURE;
  }
}


/**
 * \fn int est_compatible_villes(struct tuile*** plateau, struct tuile* tuile_n, int x, int y,char position)
 * \brief Fonction qui test les sommets ville des tuiles autours de la case du plateau de coordonnée (x,y) pour s'assurer qu'ils sont compatible avec la tuile qu'on veut placer
 *
 * \param struct tuile*** plateau Plateau du jeu contenant les pointeurs des tuiles déjà posées.
 * \param struct tuile* tuile_n Pointeur vers la tuile que l'on souhaite poser.
 * \param int x Coordonnée x où l'on veut placer la tuile.
 * \param int y Coordonnée y où l'on veut placer la tuile.
 * \param char position Caractère correspondant à la position que l'on veut tester (h=haut, b=bas, g=gauche, d=droite)
 *
 * \return EXIT_VERTICES_ACTIVATED si les deux tuilles ont un sommet ville activé
 * \return EXIT_VERTICES_DESACTIVATED si les deux tuilles ont un sommet ville desactivé
 * \return EXIT_VERTICES_DIFFERENT si les deux tuilles ont des sommets dans des états différents
 *
 */
int est_compatible_villes(struct tuile*** plateau, struct tuile* tuile_n, int x, int y,char position)
{
  int x_p;
  int y_p;
  int sommet_plato;
  int sommet_tuile;
  switch (position)
  {
    case 'h':
      x_p = x-1;
      y_p = y;
      sommet_plato = 2;
      sommet_tuile = 0;
      break;
      
    case 'b':
      x_p = x+1;
      y_p =y;
      sommet_plato = 0;
      sommet_tuile = 2;
      break;
      
    case 'g':
      x_p = x;
      y_p = y-1;
      sommet_plato = 1;
      sommet_tuile = 3;
      break;
      
    case 'd':
      x_p = x;
      y_p = y+1;
      sommet_plato = 3;
      sommet_tuile = 1;
      break;
      
    default:
      printf("La position à tester est manquante");
      return EXIT_FAILURE;
      break;
  }
  if ((plateau[x_p][y_p]->graphe->villes[sommet_plato]->actif==1) && (tuile_n->graphe->villes[sommet_tuile]->actif==1))
    return EXIT_VERTICES_ACTIVATED;
  
  else if ((plateau[x_p][y_p]->graphe->villes[sommet_plato]->actif==0) && (tuile_n->graphe->villes[sommet_tuile]->actif==0))
    return EXIT_VERTICES_DESACTIVATED;
  
  else
    return EXIT_VERTICES_DIFFERENT;
  
}


/**
 * \fn int est_compatible_routes(struct tuile*** plateau, struct tuile* tuile_n, int x, int y,char position)
 * \brief Fonction qui test les sommets route des tuiles autours de la case du plateau de coordonnée (x,y) pour s'assurer qu'ils sont compatible avec la tuile qu'on veut placer
 *
 * \param struct tuile*** plateau Plateau du jeu contenant les pointeurs des tuiles déjà posées.
 * \param struct tuile* tuile_n Pointeur vers la tuile que l'on souhaite poser.
 * \param int x Coordonnée x où l'on veut placer la tuile.
 * \param int y Coordonnée y où l'on veut placer la tuile.
 * \param char position Caractère correspondant à la position que l'on veut tester (h=haut, b=bas, g=gauche, d=droite)
 *
 * \return EXIT_VERTICES_ACTIVATED si les deux tuilles ont un sommet route activé
 * \return EXIT_VERTICES_DESACTIVATED si les deux tuilles ont un sommet route desactivé
 * \return EXIT_VERTICES_DIFFERENT si les deux tuilles ont des sommets dans des états différents
 *
 */
int est_compatible_routes(struct tuile*** plateau, struct tuile* tuile_n, int x, int y,char position)
{
  int x_p;
  int y_p;
  int sommet_plato;
  int sommet_tuile;
  switch (position)
  {
    case 'h':
      x_p = x-1;
      y_p = y;
      sommet_plato = 2;
      sommet_tuile = 0;
      break;
      
    case 'b':
      x_p = x+1;
      y_p =y;
      sommet_plato = 0;
      sommet_tuile = 2;
      break;
      
    case 'g':
      x_p = x;
      y_p = y-1;
      sommet_plato = 1;
      sommet_tuile = 3;
      break;
      
    case 'd':
      x_p = x;
      y_p = y+1;
      sommet_plato = 3;
      sommet_tuile = 1;
      break;
      
    default:
      printf("La position à tester est manquante");
      return EXIT_FAILURE;
      break;
  }
  
  
  if ((plateau[x_p][y_p]->graphe->routes[sommet_plato]->actif==1) && (tuile_n->graphe->routes[sommet_tuile]->actif==1))
    return EXIT_VERTICES_ACTIVATED;
  
  else if ((plateau[x_p][y_p]->graphe->routes[sommet_plato]->actif==0) && (tuile_n->graphe->routes[sommet_tuile]->actif==0))
    return EXIT_VERTICES_DESACTIVATED;
  
  else
    return EXIT_VERTICES_DIFFERENT;
  
}


/**
 * \fn char* position_tuiles_voisines(struct tuile*** plateau, int x, int y)
 * \brief Fonction qui teste tout les cas de positionnement de tuiles voisines afin de tester seulement les cartes posées sur le plateau. On verifie toutes les positions autour de la case de coordonées (x,y) ou l'on veut placer notre tuile.
 *
 * \return position Tableau contenant les positions à tester, par defaut "gdhb" (gauche,droite,haut,bas)
 */
char* position_tuiles_voisines(struct tuile*** plateau, int x, int y)
{
  char* position = "gdhb";
  
  if((plateau[x][y-1] == NULL) && (plateau[x][y+1] == NULL) && (plateau[x-1][y] == NULL) && (plateau[x+1][y] == NULL))
  {
    position = "";
  }
  else if((plateau[x][y-1] == NULL) && (plateau[x][y+1] == NULL) && (plateau[x-1][y] == NULL))
  {
    position = "b";
  }
  else if((plateau[x][y-1] == NULL) && (plateau[x][y+1] == NULL) && (plateau[x+1][y] == NULL))
  {
    position = "h";
  }
  else if((plateau[x][y+1] == NULL) && (plateau[x-1][y] == NULL) && (plateau[x+1][y] == NULL))
  {
    position = "g";
  }
  else if((plateau[x][y-1] == NULL) && (plateau[x-1][y] == NULL) && (plateau[x+1][y] == NULL))
  {
    position = "d";
  }
  else if(((x == 0) && (y == 0)) || ((plateau[x][y-1] == NULL) && (plateau[x+1][y] == NULL)))
  {
    position = "dh";
  }
  else if(((x == 0) && (y == LARGEUR_PLATEAU-1)) || ((plateau[x][y+1] == NULL) && (plateau[x+1][y] == NULL)))
  {
    position = "gh";
  }
  else if(((x == LARGEUR_PLATEAU-1) && (y == LARGEUR_PLATEAU-1)) || ((plateau[x][y+1] == NULL) && (plateau[x-1][y] == NULL)))
  {
    position = "gb";
  }
  else if(((x==LARGEUR_PLATEAU-1) && (y==0)) || ((plateau[x][y-1] == NULL) && (plateau[x-1][y] == NULL)))
  {
    position = "db";
  }
  else if((plateau[x][y-1] == NULL) && (plateau[x][y+1] == NULL))
  {
    position = "hb";
  }
  else if((plateau[x-1][y] == NULL) && (plateau[x+1][y] == NULL))
  {
    position = "gd";
  }
  else if ((x == LARGEUR_PLATEAU-1) || (plateau[x+1][y] == NULL))
  {
    position = "dgh";
  }
  else if((x == 0) || (plateau[x-1][y] == NULL))
  {
    position = "dgb";
  }
  else if((y == 0) || (plateau[x][y-1] == NULL))
  {
    position = "dhb";
  }
  else if((y == LARGEUR_PLATEAU-1) || (plateau[x][y+1] == NULL))
  {
    position = "ghb";
  }
  
  return position;
}


/**
 * \fn int tuiles_compatibles(struct tuile*** plateau, struct tuile* tuile_n, int x, int y)
 * \brief Fonction qui teste les tuiles autours de la case du plateau de coordonnée (x,y) pour s'assurer qu'elles sont compatibles avec la tuile que l'on veut placer
 *
 * \return 1 si les tuiles autour sont compatibles sinon elle retourne 0
 */
int tuiles_compatibles(struct tuile*** plateau, struct tuile* tuile_n, int x, int y)
{
  int i = 0;
  char* position = position_tuiles_voisines(plateau, x, y);
  if (position[0] == '\0')
    return EXIT_FAILURE;
  
  while (position[i] != '\0') {
    int compa_routes = est_compatible_routes(plateau, tuile_n, x, y, position[i]);
    int compa_villes = est_compatible_villes(plateau, tuile_n, x, y, position[i]);
    if ((compa_routes == EXIT_VERTICES_DIFFERENT) || (compa_villes == EXIT_VERTICES_DIFFERENT))
      return EXIT_NOT_COMPATIBLE;
    else if ((compa_routes == EXIT_FAILURE) || (compa_villes == EXIT_FAILURE))
      return EXIT_FAILURE;
    i++;
  }
  return EXIT_COMPATIBLE;
}


/**
 * \fn struct pioche* init_pioche(
 * \brief Fonction Initialisant la pioche
 *
 * \return pioche pointeur vers la pioche qui vient d'être initialisée.
 */
struct pioche* init_pioche()
{
  struct pioche* pioche = NULL;
  pioche = malloc(sizeof(struct pioche));
  pioche->tuile_pioche = NULL;
  for (int i=0; i<NB_TUILES; i++) {
    pioche->nb_carte[i] = 0;
  }
  pioche->nb_carte_max[0] = 3;
  pioche->nb_carte_max[1] = 3;
  pioche->nb_carte_max[2] = 3;
  pioche->nb_carte_max[3] = 4;
  pioche->nb_carte_max[4] = 2;
  pioche->nb_carte_max[5] = 1;
  pioche->nb_carte_max[6] = 9;
  pioche->nb_carte_max[7] = 8;
  pioche->nb_carte_max[8] = 4;
  pioche->nb_carte_max[9] = 1;
  pioche->nb_carte_max[10] = 3;
  pioche->nb_carte_max[11] = 1;
  pioche->nb_carte_max[12] = 2;
  pioche->nb_carte_max[13] = 5;
  pioche->nb_carte_max[14] = 4;
  pioche->nb_carte_max[15] = 3;
  pioche->nb_carte_max[16] = 3;
  pioche->nb_carte_max[17] = 1;
  pioche->nb_carte_max[18] = 3;
  pioche->nb_carte_max[19] = 1;
  pioche->nb_carte_max[20] = 2;
  pioche->nb_carte_max[21] = 2;
  pioche->nb_carte_max[22] = 2;
  pioche->nb_carte_max[23] = 2;
  
  return pioche;
}


/**
 * \fn int free_pioche(struct pioche* pioche)
 * \brief Fonction libérant toute la memoire alouée pour la pioche.
 * \param pioche Pointeur vers la structure pioche à liberer
 * \return int Correspond au succès ou l'echec de l'execution.
 */
int free_pioche(struct pioche* pioche)
{
  free(pioche);
  return EXIT_SUCCESS;
}


/**
 * \fn int est_fin_pioche(struct pioche* pioche)
 * \brief Fonction determinant si toutes les tuiles on été posées
 * \param pioche Pointeur vers la structure pioche à liberer
 * \return int Correspond au booleen vrai ou faux.
 */
int est_fin_pioche(struct pioche* pioche)
{
  for (int i=0; i<NB_TUILES; i++)
  {
    if (pioche->nb_carte[i] != pioche->nb_carte_max[i])
      return 0;
  }
  return 1;
}


/**
 * \fn int update_pioche(struct pioche* pioche, struct tuile* tuiles[])
 * \brief Fonction "piochant" une nouvelle tuile.
 * \param pioche Pointeur vers la structure pioche à liberer
 * \param tuiles[] Tableau de pointeur des les tuiles.
 * \return int Correspond au succès ou l'echec de l'execution.
 */
int update_pioche(struct pioche* pioche, struct tuile* tuiles[])
{
  int i = 0;
  int num_tuile_aleat = rand()%NB_TUILES;
  pioche->tuile_pioche = tuiles[num_tuile_aleat];
  while ((pioche->nb_carte[num_tuile_aleat+i] >= pioche->nb_carte_max[num_tuile_aleat+i]) && ((num_tuile_aleat + i) <NB_TUILES) && !est_fin_pioche(pioche))
  {
    i++;
    if ((num_tuile_aleat+i) == NB_TUILES )
    {
      i = -num_tuile_aleat;
    }
  }
  if (est_fin_pioche(pioche))
  {
    return EXIT_ANY_TILE_AVAILLABLE;
  }
  struct tuile* nou_tuile = init_tuile();
  dupliquer_tuiles(tuiles[num_tuile_aleat+i], nou_tuile);
  pioche->tuile_pioche = nou_tuile;
  pioche->nb_carte[num_tuile_aleat+i] += 1;
  return num_tuile_aleat+i;
}