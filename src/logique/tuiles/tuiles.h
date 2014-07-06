#ifndef Projet_Carcassonne_tuiles_h
#define Projet_Carcassonne_tuiles_h

struct tuile* init_tuile();

int tuile_parseur(struct tuile* tuiles[], char* filename);

int free_tuiles(struct tuile* tuiles[]);

int dupliquer_tuiles(struct tuile* tuile_src, struct tuile* tuile_dst);

int tuile_rotation(struct pioche* pioche, char c);

#endif
