#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../struct.h"
#include "../logique/graphe/graph.h"
#include "../logique/tuiles/tuiles.h"
#include "../logique/plateau/plateau.h"
#include "../logique/regles/regles.h"
#include "affichage.h"
#include "jeu.h"


enum{CENTRE, GAUCHE, DROITE};
enum{TOTALITE, VISIBLE};
enum{VIDE, VILLE, ROUTE, CHAMP};
enum{QUITTER_PARTIE, FIN_DE_PARTIE, PARTIE_EN_COURS};

int piocher(int numero_tuile_curseur)
{
  return numero_tuile_curseur + 1;
}

/**
 \fn : calcul_visible
 \brief : Cette fonction met à jour les tuiles à afficher sur la partie visible du plateau de jeu.
 \param : plateau (tableau de dimension 2 représentant l'ensemble des cases du jeu) plateau_visible (tableau de dimension 2 représenatant les cases visibles du jeu), x_visible (coordonnée horizontale de l'écran), y_visible (coordonnée verticale de l'écran)
 **/
void calcul_visible(struct tuile*** plateau_graphe, struct tuile*** plateau_visible, int x_visible, int y_visible)
{
  for (int i=0; i<5; i++)
  {
    for (int j=0; j<5; j++)
    {
      plateau_visible[i][j]=plateau_graphe[y_visible+(i-2)][x_visible+(j-2)];
    }
  }
}

/**x3
 \fn : rotation_visible
 \brief : Cette fonction fait "tourner" visuellement de 45° la carte en train d'être jouée; elle modifie en réalité simplement le numéro désignant l'image de cette carte.
 \param : numero_tuile_curseur (le numéro qui désigne l'image associée à la tuile en cours), sens (un indice indiquant le sens de la rotation)
 \return : le numéro de la nouvelle image à associer après rotation.
 **/
int rotation_visible(int numero_tuile_curseur, int sens)
{
  if (sens==DROITE)
    return numero_tuile_curseur = (numero_tuile_curseur + 24) %96;
  else if (sens==GAUCHE)
    if (numero_tuile_curseur <=24)
      return numero_tuile_curseur = (numero_tuile_curseur +96 - 24) %96;
    else return numero_tuile_curseur = (numero_tuile_curseur - 24) %96;
    else
      exit(EXIT_FAILURE);
}



void calcul_pions_possibles(int pions_possibles[9], struct tuile*** plateau_graphe, int y, int x)
{
  int villes_parcours[3];
  int routes_parcours[3];
  int champs_parcours[3];
  
  for (int i=0; i<9; i++)
    pions_possibles[i] = 0;
  for (int i=0; i<3; i++)
  {
    for (int j=0; j<3; j++)
    {
      villes_parcours[i] = 0;
      routes_parcours[i] = 0;
      champs_parcours[i] = 0;
    }
  }
  
  // VILLES -----------------------------------------------------------------------
  
  if (plateau_graphe[x][y]->graphe->villes[0]->actif == 1)
  {
    if (plateau_graphe[x][y]->graphe->mat_villes[0][1] == 1)
    {
      if (plateau_graphe[x][y]->graphe->mat_villes[1][2] == 1)
	    {
	      if (plateau_graphe[x][y]->graphe->mat_villes[2][3] == 1)
        {
          pions_possibles[1] = VILLE;
          villes_parcours[2] = 1;
        }
	      else
          pions_possibles[5] = VILLE;
	      villes_parcours[1] = 1;
	    }
      else if (plateau_graphe[x][y]->graphe->mat_villes[0][3] == 1)
      {
        pions_possibles[1] = VILLE;
        villes_parcours[2] = 1;
      }
      else
        pions_possibles[2] = VILLE;
      villes_parcours[0] = 1;
    }
    else if (plateau_graphe[x][y]->graphe->mat_villes[0][3] == 1)
    {
      if (plateau_graphe[x][y]->graphe->mat_villes[2][3] == 1)
      {
        pions_possibles[1] = VILLE;
        villes_parcours[1] = 1;
      }
      else
        pions_possibles[0] = VILLE;
      villes_parcours[2] = 1;
    }
    else if (plateau_graphe[x][y]->graphe->mat_villes[0][2] == 1)
    {
      pions_possibles[1] = VILLE;
      villes_parcours[1] = 1;
    }
    else
      pions_possibles[1] = VILLE;
  }
  
  if (plateau_graphe[x][y]->graphe->villes[1]->actif == 1)
  {
    if (villes_parcours[0] != 1)
    {
      if (plateau_graphe[x][y]->graphe->mat_villes[1][2] == 1)
	    {
        if (plateau_graphe[x][y]->graphe->mat_villes[2][3] == 1)
	      {
          pions_possibles[7] = VILLE;
          villes_parcours[2] = 1;
	      }
        else
          pions_possibles[8] = VILLE;
        villes_parcours[1] = 1;
	    }
      else if (plateau_graphe[x][y]->graphe->mat_villes[1][3] == 1)
	    {
	      pions_possibles[3] = VILLE;
	      villes_parcours[2] = 1;
	    }
      else
        pions_possibles[5] = VILLE;
    }
  }
  
  if (plateau_graphe[x][y]->graphe->villes[2]->actif == 1)
  {
    if (villes_parcours[1] != 1)
    {
      if (plateau_graphe[x][y]->graphe->mat_villes[2][3] == 1)
	    {
	      pions_possibles[6] = VILLE;
	      villes_parcours[2] = 1;
	    }
      else
        pions_possibles[7] = VILLE;
    }
  }
  
  if (villes_parcours[2] != 1)
    if (plateau_graphe[x][y]->graphe->villes[3]->actif == 1)
      pions_possibles[3] = VILLE;
  
  
  // ROUTES ----------------------------------------------------------------------
  
  if (plateau_graphe[x][y]->graphe->routes[0]->actif == 1)
  {
    if (plateau_graphe[x][y]->graphe->mat_routes[0][1] == 1)
    {
      pions_possibles[5] = ROUTE;
      routes_parcours[0] = 1;
    }
    else if (plateau_graphe[x][y]->graphe->mat_routes[0][2] == 1)
    {
      pions_possibles[1] = ROUTE;
      routes_parcours[1] = 1;
    }
    else if (plateau_graphe[x][y]->graphe->mat_routes[0][3] == 1)
    {
      pions_possibles[3] = ROUTE;
      routes_parcours[2] = 1;
    }
    else
      pions_possibles[1] = ROUTE;
  }
  
  if (routes_parcours[0] != 1)
  {
    if (plateau_graphe[x][y]->graphe->routes[1]->actif == 1)
    {
      if (plateau_graphe[x][y]->graphe->mat_routes[1][2] == 1)
	    {
	      pions_possibles[7] = ROUTE;
	      routes_parcours[1] = 1;
      }
      else if (plateau_graphe[x][y]->graphe->mat_routes[1][3] == 1)
	    {
	      pions_possibles[3] = ROUTE;
	      routes_parcours[2] = 1;
	    }
      else
        pions_possibles[5] = ROUTE;
    }
  }
  
  if (routes_parcours[1] != 1)
  {
    if (plateau_graphe[x][y]->graphe->routes[2]->actif == 1)
    {
      if (plateau_graphe[x][y]->graphe->mat_routes[2][3] == 1)
	    {
	      pions_possibles[3] = ROUTE;
	      routes_parcours[2] = 1;
	    }
      else
        pions_possibles[7] = ROUTE;
    }
  }
  
  if (routes_parcours[2] != 1)
    if (plateau_graphe[x][y]->graphe->routes[3]->actif == 1)
      pions_possibles[3] = ROUTE;
  
  // CHAMP -------------------------------------------------------------------
  
  
  if (plateau_graphe[x][y]->graphe->champs[0]->actif == 1)
  {
    if (plateau_graphe[x][y]->graphe->mat_champs[0][1] == 1)
    {
      if (plateau_graphe[x][y]->graphe->mat_champs[1][2] == 1)
	    {
	      if (plateau_graphe[x][y]->graphe->mat_champs[2][3] == 1)
        {
          if (pions_possibles[1] != VIDE || pions_possibles[7] != VIDE)
            pions_possibles[3] = CHAMP;
          else if (pions_possibles[3] != VIDE || pions_possibles[5] != VIDE)
            pions_possibles[1] = CHAMP;
          else
            pions_possibles[1] = CHAMP;
          champs_parcours[2] = 1;
        }
	      else
        {
          if (pions_possibles[5] != VIDE || pions_possibles[3] != VIDE)
            pions_possibles[1] = CHAMP;
          else
            pions_possibles[2] = CHAMP;
        }
        champs_parcours[1] = 1;
	    }
      else if (plateau_graphe[x][y]->graphe->mat_champs[0][3] == 1)
      {
        if (pions_possibles[1] == VILLE)
          pions_possibles[3] = CHAMP;
        else
          pions_possibles[0] = CHAMP;
        champs_parcours[2] = 1;
      }
      else
      {
        
        if (pions_possibles[1] != VIDE)
          pions_possibles[2] = CHAMP;
        else
          pions_possibles[1] = CHAMP;
        
      }
      champs_parcours[0] = 1;
    }
    else if (plateau_graphe[x][y]->graphe->mat_champs[0][3] == 1)
    {
      if (plateau_graphe[x][y]->graphe->mat_champs[2][3] == 1)
      {
        if (pions_possibles[3] == VILLE)
          pions_possibles[7] = CHAMP;
        else
          pions_possibles[3] = CHAMP;
        champs_parcours[1] = 1;
      }
      else
      {
        if (pions_possibles[3] != VIDE)
          pions_possibles[0] = CHAMP;
        else
          pions_possibles[3] = CHAMP;
      }
      champs_parcours[2] = 1;
    }
    else if (plateau_graphe[x][y]->graphe->mat_champs[0][2] == 1)
    {
      if (pions_possibles[0] != VIDE)
        pions_possibles[8] = CHAMP;
      else
        pions_possibles[0] = CHAMP;
      champs_parcours[1] = 1;
    }
    else if (pions_possibles[1] == VILLE)
    {
      if (pions_possibles[5] != VIDE)
        pions_possibles[2] = CHAMP;
      else
        pions_possibles[1] = CHAMP;
    }
    else
      pions_possibles[0] = CHAMP;
  }
  
  if (plateau_graphe[x][y]->graphe->champs[1]->actif == 1)
  {
    if (champs_parcours[0] != 1)
    {
      if (plateau_graphe[x][y]->graphe->mat_champs[1][2] == 1)
	    {
        if (plateau_graphe[x][y]->graphe->mat_champs[2][3] == 1)
	      {
          pions_possibles[8] = CHAMP;
          champs_parcours[2] = 1;
	      }
        else
          pions_possibles[5] = CHAMP;
        champs_parcours[1] = 1;
	    }
      else if (plateau_graphe[x][y]->graphe->mat_champs[1][3] == 1)
      {
        if (pions_possibles[7] == ROUTE)
          pions_possibles[3] = CHAMP;
        else
          pions_possibles[2] = CHAMP;//Valeur changé de 1 à 2 pour bug dans tuiles 22 et 19
        champs_parcours[2] = 1;
      }
      else
        pions_possibles[2] = CHAMP;
    }
  }
  
  if (plateau_graphe[x][y]->graphe->champs[2]->actif == 1)
  {
    if (champs_parcours[1] != 1)
    {
      if (plateau_graphe[x][y]->graphe->mat_champs[2][3] == 1)
	    {
        if (pions_possibles[7] != VIDE)
          pions_possibles[5] = CHAMP;
	      else
          pions_possibles[7] = CHAMP;
	      champs_parcours[2] = 1;
	    }
      else
        pions_possibles[8] = CHAMP;
    }
  }
  
  if (champs_parcours[2] != 1)
    if (plateau_graphe[x][y]->graphe->champs[3]->actif == 1)
      pions_possibles[6] = CHAMP;
}


/**
 \fn : jeu
 \brief : Cette fonction gère l'initialisation du jeu & son fonctionnement.
 \param : ecran (la surface SDL activée précédemment)
 **/
void jeu(SDL_Surface *ecran)
{
  SDL_Event event;
  
  SDL_Event event3;
  /**
   * Cet indice empêche le programme de quitter la boucle de jeu.
   **/
  int jeu_en_cours = PARTIE_EN_COURS;
  /**
   * Cet indice indique dans quelle position de l'écran le curseur se trouve. 9 positions sont possibles (indicées de 0 à 8 de gauche à droite, de haut en bas), c'est-à-dire les 3x3 cases visibles au centre de l'écran.
   **/
  int numero_tuile_curseur=0;
  int curseur_visible = 4;
  int curseur_pion_visible = 0;
  int x_curseur = CURSEUR_DEBUT;
  int y_curseur = CURSEUR_DEBUT;
  int x_visible = CURSEUR_DEBUT;
  int y_visible = CURSEUR_DEBUT;
  
  int pioche_restante = 72;
  
  struct tuile*** plateau_graphe = initialise_plateau(LARGEUR_PLATEAU);
  struct tuile*** plateau_visible = initialise_plateau(LARGEUR_PLATEAU_VISIBLE);
  struct pioche* pioche = init_pioche();
  struct tuile* tuiles[NB_TUILES];
  for (int i=0; i<NB_TUILES; i++)
  {
    tuiles[i]=NULL;
  }
  tuile_parseur(tuiles, "tuiles.txt");
  int num_tuile_courante = update_pioche(pioche, tuiles);
  
  struct tuile* tuile_initiale = NULL;
  tuile_initiale = init_tuile();
  dupliquer_tuiles(tuiles[14],tuile_initiale);
  
  plateau_graphe[72][71] = tuile_initiale;
  
  struct graphe_global* graphe_global = init_graphe_global(tuile_initiale);
  
  int pions_possibles[9];
  int pion_impossible = 0;
  
  struct joueurs* joueurs = initialise_joueurs();
  a_qui_le_tour(joueurs);
  
  /**
   * Cette variable vaut 1 lorsque la tuile actuelle ne peut être posée à la place actuelle du curseur.
   **/
  int statut_place = 0;
  int statut_rotation = 0;
  int phase_jeu = 0;
  int pose_pion_result = EXIT_FAILURE;
  
  
  calcul_visible(plateau_graphe, plateau_visible, x_curseur, y_curseur);
  
  numero_tuile_curseur = pioche->tuile_pioche->image;
  
  affichage(ecran, plateau_visible, curseur_visible, numero_tuile_curseur, jeu_en_cours, pioche_restante, statut_place, statut_rotation, phase_jeu, curseur_pion_visible, pions_possibles, pion_impossible, joueurs->rouge, joueurs->bleu, joueurs->courant);
  
  while(jeu_en_cours == PARTIE_EN_COURS)
  {
    SDL_WaitEvent(&event);
    switch(event.type)
    {
      case SDL_QUIT:
        jeu_en_cours = QUITTER_PARTIE;
        affichage(ecran, plateau_visible, curseur_visible, numero_tuile_curseur, jeu_en_cours, pioche_restante, statut_place, statut_rotation, phase_jeu, curseur_pion_visible, pions_possibles, pion_impossible, joueurs->rouge, joueurs->bleu, joueurs->courant);
        free_plateau(plateau_visible, LARGEUR_PLATEAU_VISIBLE);
        free_plateau(plateau_graphe, LARGEUR_PLATEAU);
        free_graphe_global(graphe_global);
        free_pioche(pioche);
        free_tuiles(tuiles);
        free_joueurs(joueurs);
        break;
      case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
	    {
        case SDLK_ESCAPE:
          jeu_en_cours = 0;
          break;
          
          /**
           *Lorsqu'une touche directionnelle est pressée, on vérifie en premier lieu que ce dernier ne va pas dépasser le bord du plateau de jeu; on peut alors modifier la coordonnée correspondante du curseur.
           *Ensuite, si le curseur se trouve au bord de la zone dans laquelle il peut se déplacer, on modifie la coordonnée correspondante du repère de l'écran, de manière à déplacer l'écran vers une direction (ce qui revient dans SDL à déplacer toutes les tuiles dans l'autre !)
           *Dans le cas contraire, on modifie seulement l'indice indiquant dans quelle "case" de l'écran visible le curseur se trouve.
           **/
        case SDLK_UP:
          if (y_curseur!=1)
          {
            y_curseur--;
            if (curseur_visible <= 2)
            {
              y_visible--;
              calcul_visible(plateau_graphe, plateau_visible, x_visible, y_visible);
            }
            else
              curseur_visible = curseur_visible - 3;
          }
          break;
          
        case SDLK_DOWN:
          if (y_curseur!=143)
          {
            y_curseur++;
            if (curseur_visible >= 6)
            {
              y_visible++;
              calcul_visible(plateau_graphe, plateau_visible, x_visible, y_visible);
            }
            else
              curseur_visible = curseur_visible + 3;
          }
          break;
          
        case SDLK_LEFT:
          /**
           *Evenement pour rotation
           **/
          if (event.key.keysym.mod & KMOD_SHIFT)
          {
            tuile_rotation(pioche, 'g');
            numero_tuile_curseur = pioche->tuile_pioche->image;
            statut_rotation = GAUCHE;
          }
          else
          {
            /**
             *Evenement pour déplacement
             **/
            if (x_curseur!=1)
            {
              x_curseur--;
              if (curseur_visible==0 || curseur_visible==3 || curseur_visible==6)
              {
                x_visible--;
                calcul_visible(plateau_graphe, plateau_visible, x_visible, y_visible);
              }
              else
                curseur_visible--;
            }
          }
          break;
          
        case SDLK_RIGHT:
          /**
           *Evenement pour rotation
           **/
          if (event.key.keysym.mod & KMOD_SHIFT)
          {
            tuile_rotation(pioche, 'd');
            numero_tuile_curseur = pioche->tuile_pioche->image;
            statut_rotation = DROITE;
          }
          else
          {
            /**
             *Evenement pour déplacement
             **/
            if (x_curseur!=143)
            {
              x_curseur++;
              if (curseur_visible==2 || curseur_visible==5 || curseur_visible==8)
              {
                x_visible++;
                calcul_visible(plateau_graphe, plateau_visible, x_visible, y_visible);
              }
              else
                curseur_visible++;
            }
          }
          break;
          
        case SDLK_TAB:
          pioche->nb_carte[num_tuile_courante]--;
          num_tuile_courante = update_pioche(pioche, tuiles);
          numero_tuile_curseur = pioche->tuile_pioche->image;
          if (joueurs->courant->score >= 4)
            joueurs->courant->score -= 4;
          else if (joueurs->courant->score >= 1)
            joueurs->courant->score -= 3; 
          a_qui_le_tour(joueurs);
          break;
          
        case SDLK_a:
          jeu_en_cours = FIN_DE_PARTIE;
          if (joueurs->bleu->score >= joueurs->rouge->score)
            joueurs->courant = joueurs->bleu;
          else
            joueurs->courant = joueurs->rouge;
          break;
          
        case SDLK_SPACE:
          if (poser_tuile(plateau_graphe, pioche->tuile_pioche, y_curseur, x_curseur) == EXIT_SUCCESS)
          {
            update_graphe_global(plateau_graphe, graphe_global, pioche->tuile_pioche, y_curseur, x_curseur);
            plateau_graphe[y_curseur][x_curseur]->joueur = joueurs->courant;
            calcul_visible(plateau_graphe, plateau_visible, x_visible, y_visible);
            struct tuile* temp_tuile = pioche->tuile_pioche;
            num_tuile_courante = update_pioche(pioche, tuiles);
            if (num_tuile_courante == EXIT_ANY_TILE_AVAILLABLE) {
              if (joueurs->bleu->score >= joueurs->rouge->score)
                joueurs->courant = joueurs->bleu;
              else
                joueurs->courant = joueurs->rouge;
              jeu_en_cours = FIN_DE_PARTIE;
            }
            else if (joueurs->courant->nb_partisans > 0)
            {
              phase_jeu = 1;
              SDL_Event event2;
              
              calcul_pions_possibles(pions_possibles, plateau_graphe, x_curseur, y_curseur);
              do
              {
                if(curseur_pion_visible == 8)
                  curseur_pion_visible = 0;
                else
                  curseur_pion_visible++;
              }while (pions_possibles[curseur_pion_visible] == VIDE);
              
              affichage(ecran, plateau_visible, curseur_visible, numero_tuile_curseur, jeu_en_cours, pioche_restante, statut_place, statut_rotation, phase_jeu, curseur_pion_visible, pions_possibles, pion_impossible, joueurs->rouge, joueurs->bleu, joueurs->courant);
              while(phase_jeu)
              {
                
                SDL_WaitEvent(&event2);
                switch(event2.type)
                {
                  case SDL_KEYDOWN:
                    switch(event2.key.keysym.sym)
                  {
                    case SDLK_LCTRL:
                      phase_jeu = 0;
                      break;
                    case SDLK_RIGHT:
                      do
                      {
                        if(curseur_pion_visible == 8)
                          curseur_pion_visible = 0;
                        else
                          curseur_pion_visible++;
                      }while (pions_possibles[curseur_pion_visible] == VIDE);
                      break;
                    case SDLK_LEFT:
                      do
                      {
                        if(curseur_pion_visible == 0)
                          curseur_pion_visible = 8;
                        else
                          curseur_pion_visible--;
                      }while (pions_possibles[curseur_pion_visible] == VIDE);
                      break;
                    case SDLK_SPACE:
                      switch(curseur_pion_visible)
                    {
                      case 0:
                        if (pions_possibles[0] == VILLE)
                        {
                          pose_pion_result = poser_pion(graphe_global, joueurs, plateau_graphe[y_curseur][x_curseur]->graphe->villes[0]);
                          plateau_graphe[y_curseur][x_curseur]->type_pion = VILLE;
                        }
                        else
                        {
                          pose_pion_result = poser_pion(graphe_global, joueurs, plateau_graphe[y_curseur][x_curseur]->graphe->champs[0]);
                          plateau_graphe[y_curseur][x_curseur]->type_pion = CHAMP;
                        }
                        if (pose_pion_result == EXIT_SUCCESS)
                        {
                          plateau_graphe[y_curseur][x_curseur]->pos_pion.y = 16;
                          plateau_graphe[y_curseur][x_curseur]->pos_pion.x = 16;
                        }
                        else
                          pion_impossible = 1;
                        
                        break;
                        
                      case 1:
                        if (pions_possibles[1] == VILLE)
                        {
                          pose_pion_result = poser_pion(graphe_global, joueurs, plateau_graphe[y_curseur][x_curseur]->graphe->villes[0]);
                          plateau_graphe[y_curseur][x_curseur]->type_pion = VILLE;
                        }
                        else if (pions_possibles[1] == ROUTE)
                        {
                          pose_pion_result = poser_pion(graphe_global, joueurs, plateau_graphe[y_curseur][x_curseur]->graphe->routes[0]);
                          plateau_graphe[y_curseur][x_curseur]->type_pion = ROUTE;
                        }
                        else
                        {
                          pose_pion_result = poser_pion(graphe_global, joueurs, plateau_graphe[y_curseur][x_curseur]->graphe->champs[0]);
                          plateau_graphe[y_curseur][x_curseur]->type_pion = CHAMP;
                        }
                        if (pose_pion_result == EXIT_SUCCESS)
                        {
                          plateau_graphe[y_curseur][x_curseur]->pos_pion.y = 16;
                          plateau_graphe[y_curseur][x_curseur]->pos_pion.x = 51;
                        }
                        else
                          pion_impossible = 1;
                        
                        break;
                        
                      case 2:
                        if (pions_possibles[2] == VILLE)
                        {
                          pose_pion_result = poser_pion(graphe_global, joueurs, plateau_graphe[y_curseur][x_curseur]->graphe->villes[1]);
                          plateau_graphe[y_curseur][x_curseur]->type_pion = VILLE;
                        }
                        else
                        {
                          pose_pion_result = poser_pion(graphe_global, joueurs, plateau_graphe[y_curseur][x_curseur]->graphe->champs[1]);
                          plateau_graphe[y_curseur][x_curseur]->type_pion = CHAMP;
                        }
                        if (pose_pion_result == EXIT_SUCCESS)
                        {
                          plateau_graphe[y_curseur][x_curseur]->pos_pion.y = 16;
                          plateau_graphe[y_curseur][x_curseur]->pos_pion.x = 86;
                        }
                        else
                          pion_impossible = 1;
                        
                        break;
                        
                      case 3:
                        if (pions_possibles[3] == VILLE)
                        {
                          pose_pion_result = poser_pion(graphe_global, joueurs, plateau_graphe[y_curseur][x_curseur]->graphe->villes[3]);
                          plateau_graphe[y_curseur][x_curseur]->type_pion = VILLE;
                        }
                        else if (pions_possibles[3] == ROUTE)
                        {
                          pose_pion_result = poser_pion(graphe_global, joueurs, plateau_graphe[y_curseur][x_curseur]->graphe->routes[3]);
                          plateau_graphe[y_curseur][x_curseur]->type_pion = ROUTE;
                        }
                        else
                        {
                          pose_pion_result = poser_pion(graphe_global, joueurs, plateau_graphe[y_curseur][x_curseur]->graphe->champs[3]);
                          plateau_graphe[y_curseur][x_curseur]->type_pion = CHAMP;
                        }
                        if (pose_pion_result == EXIT_SUCCESS)
                        {
                          plateau_graphe[y_curseur][x_curseur]->pos_pion.y = 51;
                          plateau_graphe[y_curseur][x_curseur]->pos_pion.x = 16;
                        }
                        else
                          pion_impossible = 1;
                        
                        break;
                        
                      case 5:
                        if (pions_possibles[5] == VILLE)
                        {
                          pose_pion_result = poser_pion(graphe_global, joueurs, plateau_graphe[y_curseur][x_curseur]->graphe->villes[1]);
                          plateau_graphe[y_curseur][x_curseur]->type_pion = VILLE;
                        }
                        else if (pions_possibles[5] == ROUTE)
                        {
                          pose_pion_result = poser_pion(graphe_global, joueurs, plateau_graphe[y_curseur][x_curseur]->graphe->routes[1]);
                          plateau_graphe[y_curseur][x_curseur]->type_pion = ROUTE;
                        }
                        else
                        {
                          pose_pion_result = poser_pion(graphe_global, joueurs, plateau_graphe[y_curseur][x_curseur]->graphe->champs[1]);
                          plateau_graphe[y_curseur][x_curseur]->type_pion = CHAMP;
                        }
                        if (pose_pion_result == EXIT_SUCCESS)
                        {
                          plateau_graphe[y_curseur][x_curseur]->pos_pion.y = 51;
                          plateau_graphe[y_curseur][x_curseur]->pos_pion.x = 86;
                        }
                        else
                          pion_impossible = 1;
                        
                        break;
                        
                      case 6:
                        if (pions_possibles[6] == VILLE)
                        {
                          pose_pion_result = poser_pion(graphe_global, joueurs, plateau_graphe[y_curseur][x_curseur]->graphe->villes[3]);
                          plateau_graphe[y_curseur][x_curseur]->type_pion = VILLE;
                        }
                        else
                        {
                          pose_pion_result = poser_pion(graphe_global, joueurs, plateau_graphe[y_curseur][x_curseur]->graphe->champs[3]);
                          plateau_graphe[y_curseur][x_curseur]->type_pion = CHAMP;
                        }
                        if (pose_pion_result == EXIT_SUCCESS)
                        {
                          plateau_graphe[y_curseur][x_curseur]->pos_pion.y = 86;
                          plateau_graphe[y_curseur][x_curseur]->pos_pion.x = 16;
                        }
                        else
                          pion_impossible = 1;
                        break;
                        
                      case 7:
                        if (pions_possibles[7] == VILLE)
                        {
                          pose_pion_result = poser_pion(graphe_global, joueurs, plateau_graphe[y_curseur][x_curseur]->graphe->villes[2]);
                          plateau_graphe[y_curseur][x_curseur]->type_pion = VILLE;
                        }
                        else if (pions_possibles[7] == ROUTE)
                        {
                          pose_pion_result = poser_pion(graphe_global, joueurs, plateau_graphe[y_curseur][x_curseur]->graphe->routes[2]);
                          plateau_graphe[y_curseur][x_curseur]->type_pion = ROUTE;
                        }
                        else
                        {
                          pose_pion_result = poser_pion(graphe_global, joueurs, plateau_graphe[y_curseur][x_curseur]->graphe->champs[2]);
                          plateau_graphe[y_curseur][x_curseur]->type_pion = CHAMP;
                        }
                        if (pose_pion_result == EXIT_SUCCESS)
                        {
                          plateau_graphe[y_curseur][x_curseur]->pos_pion.y = 86;
                          plateau_graphe[y_curseur][x_curseur]->pos_pion.x = 51;
                        }
                        else
                          pion_impossible = 1;
                        
                        break;
                        
                      case 8:
                        if (pions_possibles[8] == VILLE)
                        {
                          pose_pion_result = poser_pion(graphe_global, joueurs, plateau_graphe[y_curseur][x_curseur]->graphe->villes[2]);
                          plateau_graphe[y_curseur][x_curseur]->type_pion = VILLE;
                        }
                        else
                        {
                          pose_pion_result = poser_pion(graphe_global, joueurs, plateau_graphe[y_curseur][x_curseur]->graphe->champs[2]);
                          plateau_graphe[y_curseur][x_curseur]->type_pion = CHAMP;
                        }
                        if (pose_pion_result == EXIT_SUCCESS)
                        {
                          plateau_graphe[y_curseur][x_curseur]->pos_pion.y = 86;
                          plateau_graphe[y_curseur][x_curseur]->pos_pion.x = 86;
                        }
                        else
                          pion_impossible = 1;
                        
                        break;
                        
                    }
                      if (pion_impossible != 1)
                        phase_jeu = 0;
                      break;
                  }
                    affichage(ecran, plateau_visible, curseur_visible, numero_tuile_curseur, jeu_en_cours, pioche_restante, statut_place, statut_rotation, phase_jeu, curseur_pion_visible, pions_possibles, pion_impossible, joueurs->rouge, joueurs->bleu, joueurs->courant);
                    
                    pion_impossible = 0;
                }
              }
              
            }
            numero_tuile_curseur = pioche->tuile_pioche->image;
            pioche_restante--;
            a_qui_le_tour(joueurs);
            compter_points_ville_route(graphe_global, temp_tuile, joueurs);
          }
          else
          {
            statut_place = 1;
          }
          break;
	    }
    }
    
    affichage(ecran, plateau_visible, curseur_visible, numero_tuile_curseur, jeu_en_cours, pioche_restante, statut_place, statut_rotation, phase_jeu, curseur_pion_visible, pions_possibles, pion_impossible, joueurs->rouge, joueurs->bleu, joueurs->courant);
    statut_place = 0;
    statut_rotation = 0;
  }
  
  while(jeu_en_cours == FIN_DE_PARTIE)
  {
    SDL_WaitEvent(&event3);
    switch(event3.type)
    {
      case SDL_QUIT:
        jeu_en_cours = QUITTER_PARTIE;
        affichage(ecran, plateau_visible, curseur_visible, numero_tuile_curseur, jeu_en_cours, pioche_restante, statut_place, statut_rotation, phase_jeu, curseur_pion_visible, pions_possibles, pion_impossible, joueurs->rouge, joueurs->bleu, joueurs->courant);
        
        free_plateau(plateau_visible, LARGEUR_PLATEAU_VISIBLE);
        free_plateau(plateau_graphe, LARGEUR_PLATEAU);
        free_graphe_global(graphe_global);
        free_pioche(pioche);
        free_tuiles(tuiles);
        free_joueurs(joueurs);
        break;
      case SDL_KEYDOWN:
        switch(event3.key.keysym.sym)
	    {
        case SDLK_SPACE:
          affichage(ecran, plateau_visible, curseur_visible, numero_tuile_curseur, jeu_en_cours, pioche_restante, statut_place, statut_rotation, phase_jeu, curseur_pion_visible, pions_possibles, pion_impossible, joueurs->rouge, joueurs->bleu, joueurs->courant);
          
          free_plateau(plateau_visible, LARGEUR_PLATEAU_VISIBLE);
          free_plateau(plateau_graphe, LARGEUR_PLATEAU);
          free_graphe_global(graphe_global);
          free_pioche(pioche);
          free_tuiles(tuiles);
          free_joueurs(joueurs);
          jeu_en_cours = QUITTER_PARTIE;
          
          break;
	    }
    }
    
  }
}
