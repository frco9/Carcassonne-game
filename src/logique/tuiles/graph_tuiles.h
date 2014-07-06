//
//  graph_tuiles.h
//  Projet-Carcassonne
//
//  Created by Jérémie FOUCAULT on 04/05/13.
//  Copyright (c) 2013 Enseirb. All rights reserved.
//

#ifndef Projet_Carcassonne_graph_tuiles_h
#define Projet_Carcassonne_graph_tuiles_h

struct sommets* init_sommet();

int free_sommet(struct sommets* sommet);

struct graphe* init_graphe();

int free_graphe(struct graphe* graphe);


#endif
