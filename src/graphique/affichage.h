#ifndef _AFFICHAGE_H_
#define _AFFICHAGE_H_


SDL_Rect calcul_pos_curseur_tuile(int curseur_visible);

void affichage(SDL_Surface *ecran, struct tuile*** plateau_visible, int curseur_visible, int numero_tuile_curseur, int jeu_en_cours, int pioche_restante, int statut_place, int statut_rotation, int phase_jeu, int curseur_pion_visible, int pions_possibles[9], int pion_impossible, struct joueur* rouge, struct joueur* bleu, struct joueur* courant);

SDL_Rect calcul_pos_curseur_pion(int curseur_pion_visible, SDL_Rect pos_curseur_tuile);

#endif