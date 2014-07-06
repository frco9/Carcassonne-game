#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../struct.h"
#include "graph_tuiles.h"
#include "tuiles.h"


#define _DELIMITEUR_SEQ_SOMMET_ '*'
#define _DELIMITEUR_SEQ_ARC_ '%'



/**
 * \fn struct tuile* init_tuile()
 * \brief Fonction Initialisant une tuile
 *
 * \return tuile_n pointeur vers la tuile qui vient d'être initialisée.
 */
struct tuile* init_tuile()
{
  struct tuile* tuile_n= malloc(sizeof(struct tuile));
  tuile_n->graphe = init_graphe();
  tuile_n->embleme = 0;
  tuile_n->image = 0;
  tuile_n->pos_pion.x = 0;
  tuile_n->pos_pion.y = 0;
  tuile_n->type_pion = 0;
  return tuile_n;
}

/**
 * \fn int free_tuiles(struct tuile* tuiles[])
 * \brief Fonction libérant toute la memoire alouée pour les tuiles du tableau tuiles[] et correspondant à une strucutre tuile
 * \param tuiles[] Tableau de pointeur vers des structures tuile à libérer
 * \return int Correspond au succès ou l'echec de l'execution.
 */
int free_tuiles(struct tuile* tuiles[])
{
  for (int i=0; i<NB_TUILES; i++)
  {
    if (tuiles[i] != NULL)
    {
      free_graphe(tuiles[i]->graphe);
      free(tuiles[i]);
      tuiles[i] = NULL;
    }
  }
  return EXIT_SUCCESS;
}

/**
 * \fn int tuile_parseur(struct tuile* tuiles[])
 * \brief Fonction Initialisant les differentes tuiles a partir d'une lecture du fichier et les ajoute au tableau tuiles
 * \param tuiles[] Tableau de pointeurs vers la structure tuile, contient l'ensemble des tuiles créées
 * \param filename chaine de caractères du nom de fichier
 * \return int Indiquant le succès ou l'echec du parsage du fichier.
 */
int tuile_parseur(struct tuile* tuiles[], char* filename)
{
  char c = 0;
  int num_tuile;
  FILE *fichier_tuiles;
  if ((fichier_tuiles = fopen(filename,"r")) == NULL)
    {
      fprintf(stderr, "\nErreur: Impossible de lire le fichier %s\n",filename);
      return EXIT_FAILURE;
    }
  
  
  c = fgetc(fichier_tuiles);
  while (c != EOF)
  {
    num_tuile = -1;
    switch (c) {
      case '#':
        while ((c != '\n') && (c != '\r')) {
          c = fgetc(fichier_tuiles);
        }
        break;
      
      case ' ':
        c = fgetc(fichier_tuiles);
        break;
      
      case '\n':
        c = fgetc(fichier_tuiles);
        break;
      
      case _DELIMITEUR_SEQ_SOMMET_:
        fscanf (fichier_tuiles, "%d", &num_tuile);
        if (num_tuile == -1)
        {
          fprintf(stderr, "\nErreur: Une erreur s'est produite lors de la lecture du fichier %s, au moment de lire une nouvelle tuile. Verifiez que vous avez bien indiqué le numéro de chaque tuile", filename);
          free_tuiles(tuiles);
          fclose(fichier_tuiles);
          return EXIT_FAILURE;  
        }
        if (tuiles[num_tuile] == NULL)
        {
          tuiles[num_tuile] = init_tuile();
        }
        tuiles[num_tuile]->image = num_tuile+1;
        c=fgetc(fichier_tuiles);
        while (c != _DELIMITEUR_SEQ_SOMMET_) {
          switch (c) {
            case 'c':
              for (int i=0;i<4;i++)
              {
                c = fgetc(fichier_tuiles);
                if (c == '0')
                {
                  tuiles[num_tuile]->graphe->champs[i]->actif = 0;
                }
                else if	(c == '1')
                {
                  tuiles[num_tuile]->graphe->champs[i]->actif = 1;
                }
                else
                {
                  fprintf(stderr, "\nErreur: Une erreur s'est produite lors de la lecture du fichier %s, dans la tuile N°: %d. Il est probablement malformaté", filename, num_tuile);
                  free_tuiles(tuiles);
                  fclose(fichier_tuiles);
                  return EXIT_FAILURE;
                }
              }
              if ((c=fgetc(fichier_tuiles)) != 'c')
              {
                fprintf(stderr, "\nErreur: Une erreur s'est produite lors de la lecture du fichier %s, dans la tuile N°: %d. Il est probablement malformaté", filename, num_tuile);
                free_tuiles(tuiles);
                fclose(fichier_tuiles);
                return EXIT_FAILURE;
              }
              c = fgetc(fichier_tuiles);
              break;
          
            case 'v':
              for (int i=0;i<4;i++)
              {
                c = fgetc(fichier_tuiles);
                if (c == '0')
                {
                  tuiles[num_tuile]->graphe->villes[i]->actif = 0;
                }
                else if (c == '1')
                {
                  tuiles[num_tuile]->graphe->villes[i]->actif = 1;
                }
                else
                {
                  fprintf(stderr, "\nErreur: Une erreur s'est produite lors de la lecture du fichier %s, dans la tuile N°: %d. Il est probablement malformaté", filename, num_tuile);
                  free_tuiles(tuiles);
                  fclose(fichier_tuiles);
                  return EXIT_FAILURE;
                }
              }
              if ((c=fgetc(fichier_tuiles)) != 'v')
              {
                fprintf(stderr, "\nErreur: Une erreur s'est produite lors de la lecture du fichier %s, dans la tuile N°: %d. Il est probablement malformaté", filename, num_tuile);
                free_tuiles(tuiles);
                fclose(fichier_tuiles);
                return EXIT_FAILURE;
              }
              c = fgetc(fichier_tuiles);
              break;
          
            case 'r':
              for (int i=0;i<4;i++)
              {
                c = fgetc(fichier_tuiles);
                if (c == '0')
                {
                  tuiles[num_tuile]->graphe->routes[i]->actif = 0;
                }
                else if	(c == '1')
                {
                  tuiles[num_tuile]->graphe->routes[i]->actif = 1;
                }
                else
                {
                  fprintf(stderr, "\nErreur: Une erreur s'est produite lors de la lecture du fichier %s, dans la tuile N°: %d. Il est probablement malformaté", filename, num_tuile);
                  free_tuiles(tuiles);
                  fclose(fichier_tuiles);
                  return EXIT_FAILURE;
                }
              }
              if ((c=fgetc(fichier_tuiles)) != 'r')
              {
                fprintf(stderr, "\nErreur: Une erreur s'est produite lors de la lecture du fichier %s, dans la tuile N°: %d. Il est probablement malformaté", filename, num_tuile);
                free_tuiles(tuiles);
                fclose(fichier_tuiles);
                return EXIT_FAILURE;
              }
              c = fgetc(fichier_tuiles);
              break;
						
            case 'm':
              c = fgetc(fichier_tuiles);
              if (c == '0')
              {
                tuiles[num_tuile]->graphe->monaster = 0;
              }
              else if (c == '1')
              {
                tuiles[num_tuile]->graphe->monaster = 1;
              }
              else
              {
                fprintf(stderr, "\nErreur: Une erreur s'est produite lors de la lecture du fichier %s, dans la tuile N°: %d. Il est probablement malformaté", filename, num_tuile);
                free_tuiles(tuiles);
                fclose(fichier_tuiles);
                return EXIT_FAILURE;
              }
          
              if ((c=fgetc(fichier_tuiles)) != 'm')
              {
                fprintf(stderr, "\nErreur: Une erreur s'est produite lors de la lecture du fichier %s, dans la tuile N°: %d. Il est probablement malformaté", filename, num_tuile);
                free_tuiles(tuiles);
                fclose(fichier_tuiles);
                return EXIT_FAILURE;
              }
              c = fgetc(fichier_tuiles);
            break;
              
            case 'e':
              c = fgetc(fichier_tuiles);
              if (c == '0')
              {
                tuiles[num_tuile]->embleme = 0;
              }
              else if (c == '1')
              {
                tuiles[num_tuile]->embleme = 1;
              }
              else
              {
                fprintf(stderr, "\nErreur: Une erreur s'est produite lors de la lecture du fichier %s, dans la tuile N°: %d. Il est probablement malformaté", filename, num_tuile);
                free_tuiles(tuiles);
                fclose(fichier_tuiles);
                return EXIT_FAILURE;
              }
              
              if ((c=fgetc(fichier_tuiles)) != 'e')
              {
                fprintf(stderr, "\nErreur: Une erreur s'est produite lors de la lecture du fichier %s, dans la tuile N°: %d. Il est probablement malformaté", filename, num_tuile);
                free_tuiles(tuiles);
                fclose(fichier_tuiles);
                return EXIT_FAILURE;
              }
              c = fgetc(fichier_tuiles);
              break;
														
            case ' ':
              c = fgetc(fichier_tuiles);
              break;
														
            default:
              fprintf(stderr, "\nErreur: Une erreur s'est produite lors de la lecture du fichier %s, dans la tuile N°: %d. Il est probablement malformaté", filename, num_tuile);
              free_tuiles(tuiles);
              fclose(fichier_tuiles);
              return EXIT_FAILURE;
              break;
          }
          
        }
        c = fgetc(fichier_tuiles);
        break;
          
      case _DELIMITEUR_SEQ_ARC_:
          fscanf (fichier_tuiles, "%d", &num_tuile);
          if (num_tuile == -1)
          {
            fprintf(stderr, "\nErreur: Une erreur s'est produite lors de la lecture du fichier %s, au moment de lire une nouvelle tuile. Verifiez que vous avez bien indiqué le numéro de chaque tuile", filename);
            free_tuiles(tuiles);
            return EXIT_FAILURE;
          }
          if (tuiles[num_tuile] == NULL)
          {
            tuiles[num_tuile] = init_tuile();
          }
          tuiles[num_tuile]->image = num_tuile+1;
          c=fgetc(fichier_tuiles);
          while (c != _DELIMITEUR_SEQ_ARC_) {
            int ligne=-1;
            int col=-1;
            int val=-1;
            
            switch (c) {
              case 'c':
                fscanf(fichier_tuiles, "%d %d %d", &ligne, &col, &val);
                if ((ligne < NB_SOMMETS-1) && (ligne >= 0) && (col > 0) && (col < NB_SOMMETS) && ((val == 1) || (val == 0)))
                {
                  tuiles[num_tuile]->graphe->mat_champs[ligne][col] = val;
                }
                else
                {
                  fprintf(stderr, "\nErreur: Une erreur s'est produite lors de la lecture du fichier %s, dans la tuile N°: %d, lors de la lecture de la matrice. Elle est probablement malformaté", filename, num_tuile);
                  free_tuiles(tuiles);
                  return EXIT_FAILURE;
                }
                
                if ((c=fgetc(fichier_tuiles)) != 'c')
                {
                  fprintf(stderr, "\nErreur: Une erreur s'est produite lors de la lecture du fichier %s, dans la tuile N°: %d, lors de la lecture de la matrice. Elle est probablement malformaté", filename, num_tuile);
                  free_tuiles(tuiles);
                  return EXIT_FAILURE;
                }
                c = fgetc(fichier_tuiles);
                break;
                
              case 'v':
                fscanf(fichier_tuiles, "%d %d %d", &ligne, &col, &val);
                if ((ligne < NB_SOMMETS-1) && (ligne >= 0) && (col > 0) && (col < NB_SOMMETS) && ((val == 1) || (val == 0)))
                {
                  tuiles[num_tuile]->graphe->mat_villes[ligne][col] = val;
                }
                else
                {
                  fprintf(stderr, "\nErreur: Une erreur s'est produite lors de la lecture du fichier %s, dans la tuile N°: %d, lors de la lecture de la matrice. Elle est probablement malformaté", filename, num_tuile);
                  free_tuiles(tuiles);
                  return EXIT_FAILURE;
                }
                
                if ((c=fgetc(fichier_tuiles)) != 'v')
                {
                  fprintf(stderr, "\nErreur: Une erreur s'est produite lors de la lecture du fichier %s, dans la tuile N°: %d, lors de la lecture de la matrice. Elle est probablement malformaté", filename, num_tuile);
                  free_tuiles(tuiles);
                  return EXIT_FAILURE;
                }
                c = fgetc(fichier_tuiles);
                break;
                
              case 'r':
                fscanf(fichier_tuiles, "%d %d %d", &ligne, &col, &val);
                if ((ligne < NB_SOMMETS-1) && (ligne >= 0) && (col > 0) && (col < NB_SOMMETS) && ((val == 1) || (val == 0)))
                {
                  tuiles[num_tuile]->graphe->mat_routes[ligne][col] = val;
                }
                else
                {
                  fprintf(stderr, "\nErreur: Une erreur s'est produite lors de la lecture du fichier %s, dans la tuile N°: %d, lors de la lecture de la matrice. Elle est probablement malformaté", filename, num_tuile);
                  free_tuiles(tuiles);
                  return EXIT_FAILURE;
                }
                
                if ((c=fgetc(fichier_tuiles)) != 'r')
                {
                  fprintf(stderr, "\nErreur: Une erreur s'est produite lors de la lecture du fichier %s, dans la tuile N°: %d, lors de la lecture de la matrice. Elle est probablement malformaté", filename, num_tuile);
                  free_tuiles(tuiles);
                  return EXIT_FAILURE;
                }
                c = fgetc(fichier_tuiles);
                break;
                
              case ' ':
                c = fgetc(fichier_tuiles);
                break;
                
              default:
                fprintf(stderr, "\nErreur: Une erreur s'est produite lors de la lecture du fichier %s, dans la tuile N°: %d, lors de la lecture de la matrice. Elle est probablement malformatée", filename, num_tuile);
                free_tuiles(tuiles);
                return EXIT_FAILURE;
                break;
            }
            
          }
          c = fgetc(fichier_tuiles);
          break;
    
									
      default:
        fprintf(stderr, "\nErreur: Une erreur s'est produite lors de la lecture du fichier %s. Il est probablement malformaté", filename);
        free_tuiles(tuiles);
        fclose(fichier_tuiles);
        return EXIT_FAILURE;
        break;
    }
							
  }
  
  fclose(fichier_tuiles);
  return EXIT_SUCCESS;
    
}


/**
 * \fn void dupliquer_tuiles(struct tuile* tuile_src, struct tuile* tuile_dst)
 * \brief Fonction dupliquant une tuile source dans un pointeur vers une tuiles destination
 * \param tuile_src Pointeur vers la tuile a copier
 * \param tuile_dst Pointeur vers la nouvelle tuile.
 * \return int correspondant au resultat de l'execution
 */
int dupliquer_tuiles(struct tuile* tuile_src, struct tuile* tuile_dst)
{
  tuile_dst->embleme = tuile_src->embleme;
  tuile_dst->image = tuile_src->image;
  tuile_dst->graphe->monaster = tuile_src->graphe->monaster;
  tuile_dst->graphe->pion_monaster = tuile_src->graphe->pion_monaster;
  for (int i=0; i<NB_SOMMETS; i++)
  {
    tuile_dst->graphe->routes[i]->actif = tuile_src->graphe->routes[i]->actif;
    tuile_dst->graphe->routes[i]->pion = tuile_src->graphe->routes[i]->pion;
    
    tuile_dst->graphe->champs[i]->actif = tuile_src->graphe->champs[i]->actif;
    tuile_dst->graphe->champs[i]->pion = tuile_src->graphe->champs[i]->pion;
    
    tuile_dst->graphe->villes[i]->actif = tuile_src->graphe->villes[i]->actif;
    tuile_dst->graphe->villes[i]->pion = tuile_src->graphe->villes[i]->pion;
  }
  
  for (int i=0; i<NB_SOMMETS; i++)
  {
    for (int j=0; j<NB_SOMMETS; j++)
    {
      tuile_dst->graphe->mat_champs[i][j] = tuile_src->graphe->mat_champs[i][j];
      tuile_dst->graphe->mat_villes[i][j] = tuile_src->graphe->mat_villes[i][j];
      tuile_dst->graphe->mat_routes[i][j] = tuile_src->graphe->mat_routes[i][j];
    }
  }
  return EXIT_SUCCESS;
}


/**
 * \fn void tuile_rotation(struct pioche* pioche, char c)
 * \brief Fonction qui effectue la rotation d'une tuile donnée en paramètre selon le sens donné dans c
 * \param tuile Pointeur vers la structure tuile.
 * \param c Caractère corespondant au sens de la rotation
 * \return int correspondant au resultat de l'execution
 */
int tuile_rotation(struct pioche* pioche, char c)
{
  int x,y,z,w,img_id;
  switch (c) {
    case 'g':
      x = 1;
      y = 2;
      z = 3;
      w = 0;
      if (pioche->tuile_pioche->image <=24)
        img_id = (pioche->tuile_pioche->image + 96 - NB_TUILES) % ((4*NB_TUILES)+1);
      else
        img_id = (pioche->tuile_pioche->image - NB_TUILES) % ((4*NB_TUILES)+1);
      break;
      
    case 'd':
      x = 3;
      y = 0;
      z = 1;
      w = 2;    
      if (pioche->tuile_pioche->image == 72)
	img_id = 96;
      else
	img_id = (pioche->tuile_pioche->image + NB_TUILES) % (4*NB_TUILES);
      break;
      
    default:
      printf("Veuillez spécifier le sens de la rotation par d (=droite) ou g (=gauche)");
      return EXIT_FAILURE;
      break;
  }
  
  struct tuile* r_tuile = init_tuile();
  int pos[] = {x,y,z,w};
  
  //Modification des monasters et emblème
  r_tuile->embleme = pioche->tuile_pioche->embleme;
  r_tuile->graphe->monaster = pioche->tuile_pioche->graphe->monaster;
  r_tuile->graphe->pion_monaster = pioche->tuile_pioche->graphe->pion_monaster;
  
  //Modification de l'image associée
  r_tuile->image = img_id;
  
  //Modification des sommets
  for (int i=0; i<NB_SOMMETS; i++)
  {
    r_tuile->graphe->champs[i]->actif = pioche->tuile_pioche->graphe->champs[pos[i]]->actif;
    r_tuile->graphe->routes[i]->actif = pioche->tuile_pioche->graphe->routes[pos[i]]->actif;
    r_tuile->graphe->villes[i]->actif = pioche->tuile_pioche->graphe->villes[pos[i]]->actif;
  }
  
  //Modification de la matrice de booleen
  for (int i=0; i<NB_SOMMETS; i++)
  {
    for (int j=i+1; j<NB_SOMMETS; j++)
    {
      if (pos[i] < pos[j])
      {
        r_tuile->graphe->mat_champs[i][j] = pioche->tuile_pioche->graphe->mat_champs[pos[i]][pos[j]];
        r_tuile->graphe->mat_routes[i][j] = pioche->tuile_pioche->graphe->mat_routes[pos[i]][pos[j]];
        r_tuile->graphe->mat_villes[i][j] = pioche->tuile_pioche->graphe->mat_villes[pos[i]][pos[j]];
      }
      else
      {
        r_tuile->graphe->mat_champs[i][j] = pioche->tuile_pioche->graphe->mat_champs[pos[j]][pos[i]];
        r_tuile->graphe->mat_routes[i][j] = pioche->tuile_pioche->graphe->mat_routes[pos[j]][pos[i]];
        r_tuile->graphe->mat_villes[i][j] = pioche->tuile_pioche->graphe->mat_villes[pos[j]][pos[i]];
      }
    }
  }
  dupliquer_tuiles(r_tuile, pioche->tuile_pioche);
  free_graphe(r_tuile->graphe);
  free(r_tuile);
  return EXIT_SUCCESS;
}
