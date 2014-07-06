#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../struct.h"
#include "affichage.h"


enum{VIDE, VILLE, ROUTE, CHAMP};
enum{QUITTER_PARTIE, FIN_DE_PARTIE, PARTIE_EN_COURS};

/**
 * \fn SDL_Rect calcul_pos_curseur_tuile()
 * \brief Fonction qui retourne les coordonnées "graphiques" du curseur de placement de tuile à partir de sa position "théorique".
 * \param curseur_visible Entier compris entre 0 et 8 dont la valeur correspond à la position théorique du curseur de placement de tuile (le curseur peut prendre 9 positions dans un carré de 3x3 cases, chaque case numérotée de 0 à 8, de gauche à droite, de haut en bas).
 *\return SDL_Rect Coordonnées dans la fenêtre du curseur.
 **/


SDL_Rect calcul_pos_curseur_tuile(int curseur_visible)
{
  SDL_Rect pos_curseur;
  switch(curseur_visible)
  {
    case 0:
      pos_curseur.x = ORIGINE_POS_CURSEUR_X;
      pos_curseur.y = ORIGINE_POS_CURSEUR_Y;
      break;
    case 1:
      pos_curseur.x = ORIGINE_POS_CURSEUR_X + PIX_CARTE;
      pos_curseur.y = ORIGINE_POS_CURSEUR_Y;
      break;
    case 2:
      pos_curseur.x = ORIGINE_POS_CURSEUR_X + 2*PIX_CARTE;
      pos_curseur.y = ORIGINE_POS_CURSEUR_Y;
      break;
    case 3:
      pos_curseur.x = ORIGINE_POS_CURSEUR_X;
      pos_curseur.y = ORIGINE_POS_CURSEUR_Y + PIX_CARTE;
      break;
    case 4:
      pos_curseur.x = ORIGINE_POS_CURSEUR_X + PIX_CARTE;
      pos_curseur.y = ORIGINE_POS_CURSEUR_Y + PIX_CARTE;
      break;
    case 5:
      pos_curseur.x = ORIGINE_POS_CURSEUR_X + 2*PIX_CARTE;
      pos_curseur.y = ORIGINE_POS_CURSEUR_Y + PIX_CARTE;
      break;
    case 6:
      pos_curseur.x = ORIGINE_POS_CURSEUR_X;
      pos_curseur.y = ORIGINE_POS_CURSEUR_Y + 2*PIX_CARTE;
      break;
    case 7:
      pos_curseur.x = ORIGINE_POS_CURSEUR_X + PIX_CARTE;
      pos_curseur.y = ORIGINE_POS_CURSEUR_Y + 2*PIX_CARTE;
      break;
    case 8:
      pos_curseur.x = ORIGINE_POS_CURSEUR_X + 2*PIX_CARTE;
      pos_curseur.y = ORIGINE_POS_CURSEUR_Y + 2*PIX_CARTE;
      break;
  }
  return pos_curseur;
}

/**
 * \fn SDL_Rect calcul_pos_curseur_pion()
 * \brief Fonction qui retourne les coordonnées "graphiques" du curseur de placement de pion à partir de sa position "théorique".
 * \param curseur_visible Entier compris entre 0 et 8 dont la valeur correspond à la position théorique du curseur de placement de pion (le curseur peut prendre 9 positions dans un carré de 3x3 cases, chaque case numérotée de 0 à 8, de gauche à droite, de haut en bas).
 *\return SDL_Rect Coordonnées dans la fenêtre du curseur.
 **/

SDL_Rect calcul_pos_curseur_pion(int curseur_pion_visible, SDL_Rect pos_curseur_tuile)
{
  SDL_Rect pos_curseur;
  switch(curseur_pion_visible)
  {
    case 0:
      pos_curseur.x = pos_curseur_tuile.x + ORIGINE_POS_PION_X;
      pos_curseur.y = pos_curseur_tuile.y + ORIGINE_POS_PION_Y;
      break;
    case 1:
      pos_curseur.x = pos_curseur_tuile.x + ORIGINE_POS_PION_X + ESPACE_ENTRE_PIONS;
      pos_curseur.y = pos_curseur_tuile.y + ORIGINE_POS_PION_Y;
      break;
    case 2:
      pos_curseur.x = pos_curseur_tuile.x + ORIGINE_POS_PION_X + 2*ESPACE_ENTRE_PIONS;
      pos_curseur.y = pos_curseur_tuile.y + ORIGINE_POS_PION_Y;
      break;
    case 3:
      pos_curseur.x = pos_curseur_tuile.x + ORIGINE_POS_PION_X;
      pos_curseur.y = pos_curseur_tuile.y + ORIGINE_POS_PION_Y + ESPACE_ENTRE_PIONS;
      break;
    case 4:
      pos_curseur.x = pos_curseur_tuile.x + ORIGINE_POS_PION_X + ESPACE_ENTRE_PIONS;
      pos_curseur.y = pos_curseur_tuile.y + ORIGINE_POS_PION_Y + ESPACE_ENTRE_PIONS;
      break;
    case 5:
      pos_curseur.x = pos_curseur_tuile.x + ORIGINE_POS_PION_X + 2*ESPACE_ENTRE_PIONS;
      pos_curseur.y = pos_curseur_tuile.y + ORIGINE_POS_PION_Y + ESPACE_ENTRE_PIONS;
      break;
    case 6:
      pos_curseur.x = pos_curseur_tuile.x + ORIGINE_POS_PION_X;
      pos_curseur.y = pos_curseur_tuile.y + ORIGINE_POS_PION_Y + 2*ESPACE_ENTRE_PIONS;
      break;
    case 7:
      pos_curseur.x = pos_curseur_tuile.x + ORIGINE_POS_PION_X + ESPACE_ENTRE_PIONS;
      pos_curseur.y = pos_curseur_tuile.y + ORIGINE_POS_PION_Y + 2*ESPACE_ENTRE_PIONS;
      break;
    case 8:
      pos_curseur.x = pos_curseur_tuile.x + ORIGINE_POS_PION_X + 2*ESPACE_ENTRE_PIONS;
      pos_curseur.y = pos_curseur_tuile.y + ORIGINE_POS_PION_Y + 2*ESPACE_ENTRE_PIONS;
      break;
  }
  return pos_curseur;
}

/**
 * \fn void calcul_score()
 * \brief Fonction qui remplit un tableau d'entier donné en paramètre dont chaque case contient le chiffre de la puissance de dix d'un entier donné en paramètre. (la case[0] contenant le "chiffre du millier", la case[1] celui des centaines, et ainsi de suite jusqu'à la case [4]. Ce tableau permettra ensuite d'afficher différents chiffres à l'écran.
 * \param score Tableau d'entiers vide, de taille 4 (chaque case correspondant au chiffre d'une puissance de dix)
 * \param nombre Le nombre dont on veut séparer chaque chiffre 
 * \return void Le tableau score est rempli par effet de bord.
 **/

void calcul_score(int score[4], int nombre)
{
  int tmp = nombre;
  
  for (int i=0; i<4; i++)
    score[i] = 0;
  
  while (tmp >= 1000)
  {
    score[3]++;
    tmp -= 1000;
  }
  while (tmp >= 100)
  {
    score[2]++;
    tmp -= 100;
  }
  while (tmp >= 10)
  {
    score[1]++;
    tmp -= 10;
  }
  while (tmp > 0)
  {
    score[0]++;
    tmp--;
  }
}

/**
 * \fn void affichage
 * \brief Fonction qui gère l'affichage de l'ensemble du jeu durant une partie.
 * \param ecran La surface de base (la fenêtre) sur laquelle SDL superpose toutes les images.
 * \param plateau_visible Le tableau de tuiles qui contient les 12 tuiles visibles dans la fenêtre de jeu.
 * \param curseur_visible Entier compris entre 0 et 8 dont la valeur correspond à la position théorique du curseur de placement de tuile (le curseur peut prendre 9 positions dans un carré de 3x3 cases, chaque case numérotée de 0 à 8, de gauche à droite, de haut en bas).
 * \param numero_tuile_curseur Entier dont la valeur est égale au numéro de l'image de la tuile que l'on veut poser.
 * \param jeu_en_cours Entier dont la valeur correspond au moment de la partie en cours : PARTIE_EN_COURS (= 2) pendant le jeu, FIN_DE_PARTIE (= 1) lors de la fin du jeu, et QUITTER_PARTIE (= 0) lorsque l'on quitte le jeu. 
 * \param pioche_restante Entier dont la valeur correspond au nombre de cartes restantes dans la pioche (nombre affiché à l'écran)
 * \param statut_place Entier qui indique si la tuile en cours peut être placée à l'endroit pointé par le curseur ou non.
 * \param statut_rotation Entier qui indique si une rotation a eu lieu (et son sens, 1 = gauche, 2 = droit).
 * \param phase_jeu Entier dont la valeur correspond à la phase de jeu de la partie (à savoir, 0 = pose de tuile, 1 = pose de jeton)
 * \param curseur_pion_visible Entier à la fonction similaire à cuseur_visible, mais pour le curseur de placement des partisan.
 * \param pions_possibles Tableau d'entiers, dont chaque case correspond à l'une des 9 positions possibles sur lesquelles placer un partisan. Selon la valeur de ses cases, on affichera l'image d'"emplacement de partisan possible" correspondante (trois images existant, selon le type de terrain sur lesquels le partisan peut être placé) ou rien.
 * \param pion_impossible_indice Entier qui, lorsqu'il est à 1, indique que l'on ne peut placer un partisan à l'endroit actuel.
 * \param rouge Joueur rouge (contient son score et son nombre de partisans restants)
 * \param bleu Joueur bleu (contient son score et son nombre de partisans restant)
 * \param courant Joueur qui est en train de jouer (= rouge ou = bleu, selon le tour)
 * \return void affichage étant une fonction d'affichage, elle ne renvoie aucune valeur.
 **/

void affichage(SDL_Surface *ecran, struct tuile*** plateau_visible, int curseur_visible, int numero_tuile_curseur, int jeu_en_cours, int pioche_restante, int statut_place, int statut_rotation, int phase_jeu, int curseur_pion_visible, int pions_possibles[9], int pion_impossible_indice, struct joueur* rouge, struct joueur* bleu, struct joueur* courant)
{
  static SDL_Surface *tuile[NB_TUILES*4+1] = {NULL};
  static SDL_Surface *chiffre[CHIFFRES] = {NULL};
  static SDL_Surface *chiffre_final[CHIFFRES] = {NULL};
  SDL_Surface *carte_pioche_actuelle = NULL;
  static SDL_Surface *cadre;
  static SDL_Surface *curseur;
  static SDL_Surface *curseur_mauvais;
  static SDL_Surface *grille;
  static SDL_Surface *pion_rouge_ville;
  static SDL_Surface *pion_rouge_route;
  static SDL_Surface *pion_rouge_champ;
  static SDL_Surface *pion_bleu_ville;
  static SDL_Surface *pion_bleu_route;
  static SDL_Surface *pion_bleu_champ;
  static SDL_Surface *rotation_gauche;
  static SDL_Surface *rotation_droite;
  static SDL_Surface *pion_possible_ville;
  static SDL_Surface *pion_possible_route;
  static SDL_Surface *pion_possible_champ;
  static SDL_Surface *pion_rouge_possible;
  static SDL_Surface *pion_bleu_possible;
  static SDL_Surface *pion_impossible;
  static SDL_Surface *compteur_partisan_rouge;
  static SDL_Surface *compteur_partisan_bleu;
  static SDL_Surface *compteur_partisan_vide;
  static SDL_Surface *joueur_rouge;
  static SDL_Surface *joueur_bleu;
  static SDL_Surface *game_over;
  static SDL_Surface *game_over_g;
  
  SDL_Rect pos_origine;
  pos_origine.x = 0;
  pos_origine.y = 0;
  
  SDL_Rect pos_grille;
  pos_grille.x = LARGEUR_PIX_CADRE;
  pos_grille.y = 0;
  
  SDL_Rect pos_dizaine_pioche;
  pos_dizaine_pioche.x = DIZAINE_PIOCHE_X;
  pos_dizaine_pioche.y = DIZAINE_PIOCHE_Y;
  
  SDL_Rect pos_unite_pioche;
  pos_unite_pioche.x = UNITE_PIOCHE_X;
  pos_unite_pioche.y = UNITE_PIOCHE_Y;
  
  SDL_Rect pos_score_rouge;
  pos_score_rouge.x = ORIGINE_SCORE_ROUGE_X;
  pos_score_rouge.y = ORIGINE_SCORE_ROUGE_Y;
  
  SDL_Rect pos_score_bleu;
  pos_score_bleu.x = ORIGINE_SCORE_BLEU_X;
  pos_score_bleu.y = ORIGINE_SCORE_BLEU_Y;
  
  
  SDL_Rect pos_curseur_tuile = calcul_pos_curseur_tuile(curseur_visible);
  SDL_Rect pos_curseur_pion = calcul_pos_curseur_pion(curseur_pion_visible, pos_curseur_tuile);
  
  SDL_Rect pos_carte;
  
  SDL_Rect pos_pion_possible;
  
  SDL_Rect pos_pion_pose;
  
  SDL_Rect pos_compteur_partisan_rouge;
  SDL_Rect pos_compteur_partisan_bleu;
  
  SDL_Rect pos_joueur;
  pos_joueur.x = 860;
  pos_joueur.y = 90;

  SDL_Rect pos_blason_final;
  pos_blason_final.x = POS_BLASON_ORIGINE_X;
  pos_blason_final.y = POS_BLASON_ORIGINE_Y;

  SDL_Rect pos_score_final;
  pos_score_final.x = POS_SCORE_FINAL_X;
  pos_score_final.y = POS_SCORE_FINAL_Y;
  
  int score_pioche_restante[4];
  int score_rouge[4];
  int score_bleu[4];
  int score_final[4];
  
  int tmp_dizaine = 0;
  int tmp_unite = 0;
  
  /**
   * Afin d'éviter de les charger à chaque appel de la fonction (c'est-à-dire en permanence), les images (ou SDL_Surfaces) sont "static". On initialise l'entier "static" loaded à 0; la première fois que affichage est appellée, elle rentre donc dans la condition ci-dessous, et charge toutes les images. Une fois celles-ci chargées, on affecte à loaded la valeur 1; aux prochains appels de affichage, les images ne seront pas rechargées (puisque, étant "static", elles n'ont besoin de l'être qu'une seule fois).
   **/
  static int loaded = 0;
  
  if (!loaded)
  {
    grille = IMG_Load("img/grille.png");
    cadre = IMG_Load("img/cadre.png");
    curseur = IMG_Load("img/curseur.png");
    curseur_mauvais = IMG_Load("img/curseur_mauvais.png");

    pion_rouge_ville = IMG_Load("img/pion_rouge_ville.png");
    pion_rouge_route = IMG_Load("img/pion_rouge_route.png");
    pion_rouge_champ = IMG_Load("img/pion_rouge_champ.png");

    pion_bleu_ville = IMG_Load("img/pion_bleu_ville.png");
    pion_bleu_route = IMG_Load("img/pion_bleu_route.png");
    pion_bleu_champ = IMG_Load("img/pion_bleu_champ.png");
  
    rotation_gauche = IMG_Load("img/rotation_gauche.png");
    rotation_droite = IMG_Load("img/rotation_droite.png");
    
    pion_possible_ville = IMG_Load("img/pion_possible_ville.png");
    pion_possible_route = IMG_Load("img/pion_possible_route.png");
    pion_possible_champ = IMG_Load("img/pion_possible_champ.png");
    
    pion_rouge_possible = IMG_Load("img/pion_rouge_possible.png");
    pion_bleu_possible = IMG_Load("img/pion_bleu_possible.png");
    pion_impossible = IMG_Load("img/pion_impossible.png");

    compteur_partisan_rouge = IMG_Load("img/compt_partisan_rouge.png");
    compteur_partisan_bleu = IMG_Load("img/compt_partisan_bleu.png");
    compteur_partisan_vide = IMG_Load("img/compt_partisan_vide.png");
    
    joueur_rouge = IMG_Load("img/blason_rouge.png");
    joueur_bleu = IMG_Load("img/blason_bleu.png");
    
    game_over = IMG_Load("img/game_over.png");
    game_over_g = IMG_Load("img/game_over_g.png");
    
    
    chiffre[0] = IMG_Load("img/0.png");
    chiffre[1] = IMG_Load("img/1.png");
    chiffre[2] = IMG_Load("img/2.png");
    chiffre[3] = IMG_Load("img/3.png");
    chiffre[4] = IMG_Load("img/4.png");
    chiffre[5] = IMG_Load("img/5.png");
    chiffre[6] = IMG_Load("img/6.png");
    chiffre[7] = IMG_Load("img/7.png");
    chiffre[8] = IMG_Load("img/8.png");
    chiffre[9] = IMG_Load("img/9.png");
    
    chiffre_final[0] = IMG_Load("img/0_fin.png");
    chiffre_final[1] = IMG_Load("img/1_fin.png");
    chiffre_final[2] = IMG_Load("img/2_fin.png");
    chiffre_final[3] = IMG_Load("img/3_fin.png");
    chiffre_final[4] = IMG_Load("img/4_fin.png");
    chiffre_final[5] = IMG_Load("img/5_fin.png");
    chiffre_final[6] = IMG_Load("img/6_fin.png");
    chiffre_final[7] = IMG_Load("img/7_fin.png");
    chiffre_final[8] = IMG_Load("img/8_fin.png");
    chiffre_final[9] = IMG_Load("img/9_fin.png");

    tuile[1]=IMG_Load("img/card01.jpg");
    tuile[2]=IMG_Load("img/card02.jpg");
    tuile[3]=IMG_Load("img/card03.jpg");
    tuile[4]=IMG_Load("img/card04.jpg");
    tuile[5]=IMG_Load("img/card05.jpg");
    tuile[6]=IMG_Load("img/card06.jpg");
    tuile[7]=IMG_Load("img/card07.jpg");
    tuile[8]=IMG_Load("img/card08.jpg");
    tuile[9]=IMG_Load("img/card09.jpg");
    tuile[10]=IMG_Load("img/card10.jpg");
    tuile[11]=IMG_Load("img/card11.jpg");
    tuile[12]=IMG_Load("img/card12.jpg");
    tuile[13]=IMG_Load("img/card13.jpg");
    tuile[14]=IMG_Load("img/card14.jpg");
    tuile[15]=IMG_Load("img/card15.jpg");
    tuile[16]=IMG_Load("img/card16.jpg");
    tuile[17]=IMG_Load("img/card17.jpg");
    tuile[18]=IMG_Load("img/card18.jpg");
    tuile[19]=IMG_Load("img/card19.jpg");
    tuile[20]=IMG_Load("img/card20.jpg");
    tuile[21]=IMG_Load("img/card21.jpg");
    tuile[22]=IMG_Load("img/card22.jpg");
    tuile[23]=IMG_Load("img/card23.jpg");
    tuile[24]=IMG_Load("img/card24.jpg");
    
    tuile[25]=IMG_Load("img/card01_W.jpg");
    tuile[26]=IMG_Load("img/card02_W.jpg");
    tuile[27]=IMG_Load("img/card03_W.jpg");
    tuile[28]=IMG_Load("img/card04_W.jpg");
    tuile[29]=IMG_Load("img/card05_W.jpg");
    tuile[30]=IMG_Load("img/card06_W.jpg");
    tuile[31]=IMG_Load("img/card07_W.jpg");
    tuile[32]=IMG_Load("img/card08_W.jpg");
    tuile[33]=IMG_Load("img/card09_W.jpg");
    tuile[34]=IMG_Load("img/card10_W.jpg");
    tuile[35]=IMG_Load("img/card11_W.jpg");
    tuile[36]=IMG_Load("img/card12_W.jpg");
    tuile[37]=IMG_Load("img/card13_W.jpg");
    tuile[38]=IMG_Load("img/card14_W.jpg");
    tuile[39]=IMG_Load("img/card15_W.jpg");
    tuile[40]=IMG_Load("img/card16_W.jpg");
    tuile[41]=IMG_Load("img/card17_W.jpg");
    tuile[42]=IMG_Load("img/card18_W.jpg");
    tuile[43]=IMG_Load("img/card19_W.jpg");
    tuile[44]=IMG_Load("img/card20_W.jpg");
    tuile[45]=IMG_Load("img/card21_W.jpg");
    tuile[46]=IMG_Load("img/card22_W.jpg");
    tuile[47]=IMG_Load("img/card23_W.jpg");
    tuile[48]=IMG_Load("img/card24_W.jpg");
    
    tuile[49]=IMG_Load("img/card01_S.jpg");
    tuile[50]=IMG_Load("img/card02_S.jpg");
    tuile[51]=IMG_Load("img/card03_S.jpg");
    tuile[52]=IMG_Load("img/card04_S.jpg");
    tuile[53]=IMG_Load("img/card05_S.jpg");
    tuile[54]=IMG_Load("img/card06_S.jpg");
    tuile[55]=IMG_Load("img/card07_S.jpg");
    tuile[56]=IMG_Load("img/card08_S.jpg");
    tuile[57]=IMG_Load("img/card09_S.jpg");
    tuile[58]=IMG_Load("img/card10_S.jpg");
    tuile[59]=IMG_Load("img/card11_S.jpg");
    tuile[60]=IMG_Load("img/card12_S.jpg");
    tuile[61]=IMG_Load("img/card13_S.jpg");
    tuile[62]=IMG_Load("img/card14_S.jpg");
    tuile[63]=IMG_Load("img/card15_S.jpg");
    tuile[64]=IMG_Load("img/card16_S.jpg");
    tuile[65]=IMG_Load("img/card17_S.jpg");
    tuile[66]=IMG_Load("img/card18_S.jpg");
    tuile[67]=IMG_Load("img/card19_S.jpg");
    tuile[68]=IMG_Load("img/card20_S.jpg");
    tuile[69]=IMG_Load("img/card21_S.jpg");
    tuile[70]=IMG_Load("img/card22_S.jpg");
    tuile[71]=IMG_Load("img/card23_S.jpg");
    tuile[72]=IMG_Load("img/card24_S.jpg");
    
    tuile[73]=IMG_Load("img/card01_E.jpg");
    tuile[74]=IMG_Load("img/card02_E.jpg");
    tuile[75]=IMG_Load("img/card03_E.jpg");
    tuile[76]=IMG_Load("img/card04_E.jpg");
    tuile[77]=IMG_Load("img/card05_E.jpg");
    tuile[78]=IMG_Load("img/card06_E.jpg");
    tuile[79]=IMG_Load("img/card07_E.jpg");
    tuile[80]=IMG_Load("img/card08_E.jpg");
    tuile[81]=IMG_Load("img/card09_E.jpg");
    tuile[82]=IMG_Load("img/card10_E.jpg");
    tuile[83]=IMG_Load("img/card11_E.jpg");
    tuile[84]=IMG_Load("img/card12_E.jpg");
    tuile[85]=IMG_Load("img/card13_E.jpg");
    tuile[86]=IMG_Load("img/card14_E.jpg");
    tuile[87]=IMG_Load("img/card15_E.jpg");
    tuile[88]=IMG_Load("img/card16_E.jpg");
    tuile[89]=IMG_Load("img/card17_E.jpg");
    tuile[90]=IMG_Load("img/card18_E.jpg");
    tuile[91]=IMG_Load("img/card19_E.jpg");
    tuile[92]=IMG_Load("img/card20_E.jpg");
    tuile[93]=IMG_Load("img/card21_E.jpg");
    tuile[94]=IMG_Load("img/card22_E.jpg");
    tuile[95]=IMG_Load("img/card23_E.jpg");
    tuile[96]=IMG_Load("img/card24_E.jpg");
    loaded = 1;
  }
  /**
   * Lorsque le joueur quitte la partie (lorsque jeu_en_cours = QUITTER PARTIE), affichage libère l'ensemble des images (ou SDL_Surfaces) de la mémoire, et réaffecte à loaded la valeur 0, afin que le joueur puisse éventuellement recommencer une partie.
   **/
  if (jeu_en_cours == QUITTER_PARTIE)
	{
	  for (int k=1; k<=NB_TUILES*4; k++)
	    SDL_FreeSurface(tuile[k]);
	  for (int k=0; k<CHIFFRES; k++)
    {
      SDL_FreeSurface(chiffre[k]);
      SDL_FreeSurface(chiffre_final[k]);
    }
	  SDL_FreeSurface(carte_pioche_actuelle);
	  SDL_FreeSurface(cadre);
	  SDL_FreeSurface(curseur);
	  SDL_FreeSurface(curseur_mauvais);
	  SDL_FreeSurface(grille);
	  SDL_FreeSurface(pion_rouge_ville);
	  SDL_FreeSurface(pion_rouge_route);
	  SDL_FreeSurface(pion_rouge_champ);
	  SDL_FreeSurface(pion_bleu_ville);
	  SDL_FreeSurface(pion_bleu_route);
	  SDL_FreeSurface(pion_bleu_champ);
	  SDL_FreeSurface(rotation_gauche);
	  SDL_FreeSurface(rotation_droite);
	  SDL_FreeSurface(pion_possible_ville);
	  SDL_FreeSurface(pion_possible_route);
	  SDL_FreeSurface(pion_possible_champ);
	  SDL_FreeSurface(pion_rouge_possible);
	  SDL_FreeSurface(pion_bleu_possible);
	  SDL_FreeSurface(pion_impossible);
	  SDL_FreeSurface(compteur_partisan_rouge);
	  SDL_FreeSurface(compteur_partisan_bleu);
	  SDL_FreeSurface(compteur_partisan_vide);
	  SDL_FreeSurface(joueur_rouge);
	  SDL_FreeSurface(joueur_bleu);
    SDL_FreeSurface(game_over);
    SDL_FreeSurface(game_over_g);
	  loaded = 0;
	}

  else
	{
	  /**
	   * Ici est géré les 12 tuiles visibles & leurs jetons éventuels. On parcourt donc les 12 cases du tableau de tuiles plateau_visible. Si la case ne pointe pas vers NULL (ie si la tuile n'est pas vide), on affiche l'image correspondante à la tuile (dont le numéro est un champ de la structure tuile). Puis, si le champ pos_pion de la tuile n'est pas égal à (0,0), on affiche le pion posé sur la tuile. pos_pion est en effet un SDL_Rect, qui décrit les coordonnées de l'éventuel jeton sur la tuile; si ces coordonnées ne sont pas nulles, il y a un pion. 
	   **/
	  carte_pioche_actuelle = tuile[numero_tuile_curseur];
	  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 248, 231, 231));
	  
	  if (jeu_en_cours == PARTIE_EN_COURS)
	    {
	      for (int i=0; i< LARGEUR_PLATEAU_VISIBLE; i++)
		{
		  for (int j=0; j< LARGEUR_PLATEAU_VISIBLE; j++)
		    {
		      pos_carte.x = j * PIX_CARTE + LARGEUR_PIX_CADRE;
		      pos_carte.y = i * PIX_CARTE + HAUTEUR_PIX_CADRE;
		      if (plateau_visible[i][j] != NULL)
			{
			  SDL_BlitSurface(tuile[plateau_visible[i][j]->image], NULL, ecran, &pos_carte);
			  if (plateau_visible[i][j]->pos_pion.x != 0)
			    {
			      pos_pion_pose.x = pos_carte.x + plateau_visible[i][j]->pos_pion.x;
			      pos_pion_pose.y = pos_carte.y + plateau_visible[i][j]->pos_pion.y;
			      if (plateau_visible[i][j]->joueur == rouge)
				{
				  if (plateau_visible[i][j]->type_pion == VILLE)
				    SDL_BlitSurface(pion_rouge_ville, NULL, ecran, &pos_pion_pose);
				  else if (plateau_visible[i][j]->type_pion == ROUTE)
				    SDL_BlitSurface(pion_rouge_route, NULL, ecran, &pos_pion_pose);
				  else
				    SDL_BlitSurface(pion_rouge_champ, NULL, ecran, &pos_pion_pose);
				}
			      else
				{
				  if (plateau_visible[i][j]->type_pion == VILLE)
				    SDL_BlitSurface(pion_bleu_ville, NULL, ecran, &pos_pion_pose);
				  else if (plateau_visible[i][j]->type_pion == ROUTE)
				    SDL_BlitSurface(pion_bleu_route, NULL, ecran, &pos_pion_pose);
				  else
				    SDL_BlitSurface(pion_bleu_champ, NULL, ecran, &pos_pion_pose);
				}
			    }
			}
		    }
		}
	      SDL_BlitSurface(grille, NULL, ecran, &pos_grille);
	    }

    
	  /**
	   * Lorsque phase_jeu = 0, le joueur est en train de choisir où poser sa tuile, tandis que lorsque phase_jeu = 1, il choisit où placer son jeton sur la tuile.
	   **/
	  
	  if (phase_jeu == 0)
    {
      SDL_BlitSurface(carte_pioche_actuelle, NULL, ecran, &pos_curseur_tuile);
	    if (statut_place == 1)
        SDL_BlitSurface(curseur_mauvais, NULL, ecran, &pos_curseur_tuile);
	    else
        SDL_BlitSurface(curseur, NULL, ecran, &pos_curseur_tuile);
    }
	  else if (phase_jeu == 1)
    {
      for (int i=0; i<3; i++)
      {
        for (int j=0; j<=3; j++)
        {
          if (pions_possibles[j*3 + i] != 0)
          {
            pos_pion_possible.x = pos_curseur_tuile.x + ORIGINE_POS_PION_X + i*ESPACE_ENTRE_PIONS;
            pos_pion_possible.y = pos_curseur_tuile.y + ORIGINE_POS_PION_Y + j*ESPACE_ENTRE_PIONS;
            if (pions_possibles[j*3 +i] == VILLE)
              SDL_BlitSurface(pion_possible_ville, NULL, ecran, &pos_pion_possible);
            else if (pions_possibles[j*3 + i] == ROUTE)
              SDL_BlitSurface(pion_possible_route, NULL, ecran, &pos_pion_possible);
            else if (pions_possibles[j*3 + i] == CHAMP)
              SDL_BlitSurface(pion_possible_champ, NULL, ecran, &pos_pion_possible);
          }
        }
      }
	  if (courant == rouge)
	    SDL_BlitSurface(pion_rouge_possible, NULL, ecran, &pos_curseur_pion);
	  else
	    SDL_BlitSurface(pion_bleu_possible, NULL, ecran, &pos_curseur_pion);
    }

	  /**
	   * Si le partie est en cours, on affiche alors le cadre qui entoure le plateau visible, et sur lequel on va afficher  les informations de jeu. Si la partie est terminée, on affiche l'écran de "game over" (sur lequel on affiche également les informations de jeu)"
	   **/	
	  if (jeu_en_cours == PARTIE_EN_COURS)
	    SDL_BlitSurface(cadre, NULL, ecran, &pos_origine);
	  else if (jeu_en_cours == FIN_DE_PARTIE)
	    SDL_BlitSurface(game_over, NULL, ecran, &pos_origine);
    
	  /**
	   * A cet endroit, on affiche le compteur de partisans à l'aide d'une boucle (on décale à chaque itération l'abcisse de la position (ou SDL_Rect), et affiche, selon le nombre de partisans restant à chaque joueur, l'image d'une unité du compteur "pleine" ou "vide").
	   **/
    pos_compteur_partisan_rouge.y = COMPTEUR_PARTISAN_ROUGE_Y;
    pos_compteur_partisan_bleu.y = COMPTEUR_PARTISAN_BLEU_Y;
    
    for (int i=0; i<10; i++)
    {
      pos_compteur_partisan_rouge.x = COMPTEUR_PARTISAN_ORIGINE_X + i*COMPTEUR_PARTISAN_LARGEUR;
      pos_compteur_partisan_bleu.x = COMPTEUR_PARTISAN_ORIGINE_X + i*COMPTEUR_PARTISAN_LARGEUR;
      if (i < rouge->nb_partisans)
        SDL_BlitSurface(compteur_partisan_rouge, NULL, ecran, &pos_compteur_partisan_rouge);
      else
        SDL_BlitSurface(compteur_partisan_vide, NULL, ecran, &pos_compteur_partisan_rouge);
      if(i < bleu->nb_partisans)
        SDL_BlitSurface(compteur_partisan_bleu, NULL, ecran, &pos_compteur_partisan_bleu);
      else
        SDL_BlitSurface(compteur_partisan_vide, NULL, ecran, &pos_compteur_partisan_bleu);
    }
    
    /**
     * Selon la valeur de statut_rotation, on affiche une image indiquant au joueur qu'il vient d'effectuer une rotation vers la gauche ou vers la droite.
     **/
    if (statut_rotation == 1)
      SDL_BlitSurface(rotation_gauche, NULL, ecran, &pos_curseur_tuile);
    else if (statut_rotation == 2)
      SDL_BlitSurface(rotation_droite, NULL, ecran, &pos_curseur_tuile);
    
    /**
     * Lorsque le joueur ne peut placer de jeton à l'endroit désigné, on affiche une image lui indiquant cette information.
     **/
    if (pion_impossible_indice == 1)
      SDL_BlitSurface(pion_impossible, NULL, ecran, &pos_curseur_pion);

    /**
     * Ici est géré l'affichage du nombre de cartes restantes dans la pioche (mise de chaque chiffre du nombre dans un tableau, puis affichage de chaque chiffre à la position voulue.
     **/
    calcul_score(score_pioche_restante, pioche_restante);
    
    SDL_BlitSurface(chiffre[score_pioche_restante[1]], NULL, ecran, &pos_dizaine_pioche);
    SDL_BlitSurface(chiffre[score_pioche_restante[0]], NULL, ecran, &pos_unite_pioche);
    

    /**
     * Ici est géré l'affichage du score de chaque joueur, de la même façon que pour le nombre de cartes restant dans la pioche, mais avec 4 chiffres et deux nombres à afficher.
     **/
    calcul_score(score_rouge, rouge->score);
    calcul_score(score_bleu, bleu->score);
    
    for (int i=0; i<4; i++)
    {
      pos_score_rouge.x = POS_SCORE_ORIGINE_X + i*30;
      pos_score_bleu.x = POS_SCORE_ORIGINE_X + i*30;
      SDL_BlitSurface(chiffre[score_rouge[(3-i)]], NULL, ecran, &pos_score_rouge);
      SDL_BlitSurface(chiffre[score_bleu[(3-i)]], NULL, ecran, &pos_score_bleu);
    }
    

    /**
     * Lorsque la partie est en cours, le jeu affiche dans le coin droit de l'écran le blason du joueur dont c'est le tour de jouer.
     **/
    if (jeu_en_cours == PARTIE_EN_COURS)
      {
	if (courant == rouge)
	  SDL_BlitSurface(joueur_rouge, NULL, ecran, &pos_joueur);
	else
	  SDL_BlitSurface(joueur_bleu, NULL, ecran, &pos_joueur);
      }

    /**
     * Lorsque la partie est terminée, le jeu affiche au centre de l'écran (sur l'écran de "game over") le blason du joueur vainqueur, ainsi que son score.
     **/
    if (jeu_en_cours == FIN_DE_PARTIE)
      {
        if (courant == rouge)
          SDL_BlitSurface(joueur_rouge, NULL, ecran, &pos_blason_final);
        else
          SDL_BlitSurface(joueur_bleu, NULL, ecran, &pos_blason_final);

        calcul_score(score_final, courant->score);
        for (int i=0; i<4; i++)
        {
          pos_score_final.x = 430 + i*40;
          SDL_BlitSurface(chiffre_final[score_final[(3-i)]], NULL, ecran, &pos_score_final);
        }
      }
    /**
     * Une fois que l'on a indiqué à SDL quelles images placer à quelles coordonnées de la fenêtre (à l'aide de la fonction SDL_BlitSurface), on appelle la fonction SDL_Flip, qui affiche effectivement ces images sur l'écran.
     **/
    SDL_Flip(ecran);
	}
}


