#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>

#include "struct.h"
#include "graphique/jeu.h"
#include "graphique/affichage.h"




/*! \mainpage Carcassonne Documentation
 *
 * \section intro_sec Introduction
 *
 * <p>Les pages suivantes contiennent la documentation de notre projet Carcassonne, réalisé dans le cadre des projets du semestre S6 de l'ENSEIRB-MATMMECA.</p>
 * <p>Il s'agit d'une réalisation de l'equipe 873 composée de : <ul><li>Nicolas Bouzat</li><li>Jeremie Foucault</li><li>Ismail Moumine</li><li>Guillaume Simon</li><li>Leon Villalba</li></ul></p>
 *
 * <p>Le dépot svn de notre équipe se trouve à cette adresse : <a href="https://thor.enseirb-matmeca.fr/svn/proj1as2-c-873/">Dépot SVN équipe 873</a>.<br /> Vous y trouverez les sources et le rapport de notre projet</p>
 *
 * \section compil_sec Compilation du jeu
 * <p>La compilation des sources du projet se fait par utilisation de CMake. Il suffit de se placer dans le dossier Build, puis d'éxecuter la commande "cmake .." enfin la compilation se fait par execution de la commande make. Enfin il suffit de lancer l'éxecutable "carcassonne"</p><p>La documentation peut être regénérée par execution d'un "make doc", elle se situera alors dans le dossier ../doc relativement au dossier build.</p>
 * 
 * \section commande_sec Commandes de contrôle du jeu
 *
 * <p>Le contrôle du jeu se fait au clavier. Les commandes suivantes peuvent être utilisées : <ul><li><strong>Touches directionnelles</strong>: navigation dans la grille</li><li><strong>Espace</strong>: valider la position du curseur</li><li><strong>Shift + Gauche ou Droite</strong>: Pour faire tourner une tuile</li><li><strong>CTRL gauche</strong>: Annuler la pose d'un pion</li><li><strong>Tab</strong>: Passer un carte (Pénalité -4pt)</li><li><strong>A</strong>: Met fin au jeu prématurement</li></ul></p>
 *
 */

#define ECRAN_X 1011
#define ECRAN_Y 600
#define TITRE_X 461
#define TITRE_Y 112
#define BLEU_R 8
#define BLEU_V 97
#define BLEU_B 189
/**
 * \fn int main(int argc, char* argv[])
 * \brief Le main contient l'initialisation de SDL; une fois celle-ci faite,
 * une boucle "infinie" est lancée, grace à laquelle SDL reste activée.
 * C'est dans cette boucle que nous allons ensuite faire appel aux
 * autres fonctions du jeu.
 **/
int main(int argc, char* argv[])
{
  time_t t;
  /* Intializes random number generator */
  srand((unsigned) time(&t));
  SDL_Surface *ecran = NULL, *ecran_titre = NULL, *ecran_titre2 = NULL;
  SDL_Rect pos_titre;
  SDL_Event event;
  int en_cours = 1;
  int ecran2 = 0;

  
  SDL_Init(SDL_INIT_VIDEO); 
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
      fprintf(stderr, "ERREUR : SDL non initialisée\n");
      exit(EXIT_FAILURE);
    }

  ecran = SDL_SetVideoMode(ECRAN_X, ECRAN_Y, 32, SDL_HWSURFACE);

  if (ecran == NULL)
    {
      fprintf(stderr, "ERREUR : Mode vidéo non chargé\n");
      exit(EXIT_FAILURE);
    }
  
  SDL_WM_SetIcon(IMG_Load("img/icone.bmp"), NULL);
  SDL_WM_SetCaption("Carcassonne", NULL);

  ecran_titre = IMG_Load("img/ecran_titre.png");
  ecran_titre2 = IMG_Load("img/ecran_titre2.png");
  pos_titre.x = 0;
  pos_titre.y = 0;

  while(en_cours)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
	{
	case SDL_QUIT:
	  en_cours = 0;  //Quitte le jeu
	  break;
	case SDL_KEYDOWN:
	  switch(event.key.keysym.sym)
	    {
	    case SDLK_ESCAPE:
	      en_cours = 0;
	      break;
	    case SDLK_SPACE:
	      if (ecran2 == 0)
		ecran2++;
	      else if (ecran2 == 1)
		{
		  ecran2 = 0;
		  jeu(ecran);
		}
	      break;
	    }
	  break;      
	}
      if (ecran2 == 0)
	SDL_BlitSurface(ecran_titre, NULL, ecran, &pos_titre);
      else if (ecran2 == 1)
	SDL_BlitSurface(ecran_titre2, NULL, ecran, &pos_titre);
      SDL_Flip(ecran);
    }

  SDL_FreeSurface(ecran_titre);
  SDL_FreeSurface(ecran_titre2);
  SDL_Quit();

  return EXIT_SUCCESS;
}
