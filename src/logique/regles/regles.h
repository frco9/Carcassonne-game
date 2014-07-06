#ifndef Projet_Carcassonne_regles_h
#define Projet_Carcassonne_regles_h

int est_pion(struct sommet_successeurs* sommet_successeurs, struct sommet_successeurs** tab_successeur,int* nb_tuiles, int* tot_pions);

int est_poser_pion_possi(struct graphe_global* graphe_global, struct sommets* sommet);

int poser_pion(struct graphe_global* graphe_global, struct joueurs* joueurs, struct sommets* sommet);

int est_route_champ_complet(struct sommet_successeurs* sommet_successeurs, struct sommet_successeurs** tab_successeur, int* nb_tuiles, int* nb_pions);

int marquer_sommet_termine(struct sommet_successeurs* sommet_successeurs, struct sommet_successeurs** tab_successeur, int* nb_tuiles, int* nb_pions);

int compter_points_ville_route(struct graphe_global* graphe_global, struct tuile* tuile, struct joueurs* joueurs);

int calcul_score_pions(int nb_tot_pions, int nb_tuiles, int type, struct joueurs* joueurs);

struct joueurs* initialise_joueurs(void);

int free_joueurs(struct joueurs* joueurs);

int a_qui_le_tour(struct joueurs* joueurs);

#endif
