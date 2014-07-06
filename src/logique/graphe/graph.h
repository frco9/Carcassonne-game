#ifndef Projet_Carcassonne_graph_h
#define Projet_Carcassonne_graph_h


int free_successeur(struct sommet_successeurs* sommet_successeur);

struct graphe_global* init_graphe_global(struct tuile* tuile_depart);

int free_graphe_global(struct graphe_global* graphe_global);

int ajout_sommet(struct graphe_global* graphe_global, struct sommets* nouv_sommet);

struct sommet_successeurs* dernier_successeur(struct sommet_successeurs* tete_liste);

int ajout_succ_chaine(struct sommets* nouv_sommet, struct sommet_successeurs** sommet_successeurs, int sommet_ind, int type_arete);

int ajout_arete(struct graphe_global* graphe_global, struct sommets* sommet_src, struct sommets* sommet_dst, int type_arete);

int update_graphe_global(struct tuile*** plateau, struct graphe_global* graphe_global, struct tuile* tuile, int x, int y);

int ajouter_tuile_graphe_global(struct tuile*** plateau, struct graphe_global* graphe_global, struct tuile* tuile, int x, int y, char position);

int parcourt_graphe_global(struct graphe_global* graphe_global, struct sommets* sommet, int* nb_tuile, int* nb_pion, int nb_fonctions_traitement, int (*fonctions_a_exec[])(struct sommet_successeurs*, struct sommet_successeurs**, int*, int*), int resultats_attendus[]);

int init_parcourt_graphe(struct graphe_global* graphe_global);

#endif
