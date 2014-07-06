#ifndef Projet_Carcassonne_plateau_h
#define Projet_Carcassonne_plateau_h


struct tuile*** initialise_plateau(int taille_plateau);

int est_compatible_villes(struct tuile*** plateau, struct tuile* tuile_n, int x, int y,char position);

int est_compatible_routes(struct tuile*** plateau, struct tuile* tuile_n, int x, int y,char position);

int tuiles_compatibles(struct tuile*** plateau, struct tuile* tuile_n, int x, int y);

char* position_tuiles_voisines(struct tuile*** plateau, int x, int y);

int poser_tuile(struct tuile*** plateau, struct tuile* tuile_n, int x, int y);

int free_plateau(struct tuile*** plateau, int taille_plateau);

struct pioche* init_pioche();

int free_pioche(struct pioche* pioche);

int est_fin_pioche(struct pioche* pioche);

int update_pioche(struct pioche* pioche, struct tuile* tuiles[]);

#endif
