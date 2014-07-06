#ifndef _JEU_H_
#define _JEU_H_


int piocher(int numero_tuile_curseur);

void calcul_visible(struct tuile*** plateau_graphe, struct tuile*** plateau_visible, int x_visible, int y_visible);

int rotation_visible(int numero_tuile_curseur, int sens);

void jeu(SDL_Surface *ecran);

#endif

