#ifndef _STRUCT_H_
#define _STRUCT_H_
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define TAILLE_PLATEAU 72
#define NB_SOMMETS 4
#define NB_TYPE_SOMMETS 3
#define NB_TUILES 24

#define LARGEUR_PLATEAU 145
#define LARGEUR_PLATEAU_VISIBLE 5
#define CHIFFRES 10
#define PIX_CARTE 120
#define LARGEUR_PIX_CADRE 218
#define HAUTEUR_PIX_CADRE 0
#define ORIGINE_POS_CURSEUR_X 333
#define ORIGINE_POS_CURSEUR_Y 115
#define ORIGINE_POS_PION_X 20
#define ORIGINE_POS_PION_Y 20
#define ESPACE_ENTRE_PIONS 35
#define ORIGINE_SCORE_ROUGE_X 90
#define ORIGINE_SCORE_ROUGE_Y 325
#define ORIGINE_SCORE_BLEU_X 92
#define ORIGINE_SCORE_BLEU_Y 442
#define DIZAINE_PIOCHE_X 863
#define DIZAINE_PIOCHE_Y 311
#define UNITE_PIOCHE_X 897
#define UNITE_PIOCHE_Y 311
#define COMPTEUR_PARTISAN_ROUGE_Y 380
#define COMPTEUR_PARTISAN_BLEU_Y 496
#define COMPTEUR_PARTISAN_ORIGINE_X 80
#define COMPTEUR_PARTISAN_LARGEUR 15
#define POS_SCORE_ORIGINE_X 90
#define POS_BLASON_ORIGINE_X 470
#define POS_BLASON_ORIGINE_Y 205
#define POS_SCORE_FINAL_X 430
#define POS_SCORE_FINAL_Y 380


#define CURSEUR 1
#define CURSEUR_DEBUT 72

#define BLANC 32
#define GRIS 64
#define NOIR 128
#define PARTISAN_BLEU 3546
#define PARTISAN_ROUGE 7655
#define COMPLET_ELEMENT 256
#define _VIDE 511
#define _CHAMP 512
#define _VILLE 1024
#define _ROUTE 2048
#define _INTERNE 4096
#define _EXTERNE 8192
#define EXIT_NO_SUCCESSOR 5456
#define NO_COMPLET_ELEMENT 257

#define EXIT_VERTICES_ACTIVATED 2
#define EXIT_VERTICES_DESACTIVATED 3
#define EXIT_VERTICES_DIFFERENT 8
#define EXIT_NOT_COMPATIBLE 9
#define EXIT_COMPATIBLE 6
#define EXIT_ANY_TILE_AVAILLABLE 25
#define EXIT_VERTICE_DO_NOT_EXIST -12




/**
 * \struct sommets
 * \brief Structure contenant les champs gérant les sommets
 */
struct sommets{
  int actif; 
  int pion;
  int parcourt_graphe;
  int sommet_indice;
  int fin_element;
  int type_sommet;
  int construct_complet;
};

/**
 * \struct graphe
 * \brief Structure gérant le graphe interne aux tuiles
 */
struct graphe{
  struct sommets* champs[4];
  struct sommets* routes[4];
  struct sommets* villes[4];
  int mat_champs[4][4];
  int mat_routes[4][4];
  int mat_villes[4][4];
  int monaster;
  int pion_monaster;
};

/**
 * \struct sommet_successeurs
 * \brief Structure gérant les successeurs de la liste chainée
 */
struct sommet_successeurs{
  struct sommets* sommet;
  int type_arete;
  struct sommet_successeurs* suivant;
};

/**
 * \struct graphe_global
 * \brief Structure gérant le graphe global avec son tableau de sommet et le tableau de successeur pour chacun des sommets
 */
struct graphe_global{
  int nb_sommet;
  int nb_arete;
  struct sommets** id_sommet;
  struct sommet_successeurs** tab_successeurs;
};

/**
 * \struct pioche
 * \brief Structure gérant la pioche
 */
struct pioche{
  struct tuile* tuile_pioche;
  int nb_carte[NB_TUILES];
  int nb_carte_max[NB_TUILES];
};

/**
 * \struct tuile
 * \brief Structure gérant la tuile et sa représentation sous forme de graphe
 */
struct tuile{
  struct graphe* graphe;
  int image;
  int embleme;
  SDL_Rect pos_pion;
  int type_pion;
  struct joueur* joueur;
};

/**
 * \struct joueur
 * \brief Structure contenant les champs permettants la gestion d'un joueur
 */
struct joueur{
  int nb_partisans;
  int score;
  int pion;
};

/**
 * \struct joueurs
 * \brief Structure regroupant les structures des deux joueur et un pointeur vers le joueur courant.
 */
struct joueurs{
  struct joueur* bleu;
  struct joueur* rouge;
  struct joueur* courant;
};

#endif
  
