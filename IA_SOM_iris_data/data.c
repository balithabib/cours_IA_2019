#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "tools.h"
#include "data.h"
/*\brief La fonction permet de calculer le vecteur moyenne sur tous la base de données
 * \param data un pointeur sur le data contient la bdd de iris_data;
 * \param double* return un pointeur sur le vecteur moyenne.
 */
double* vect_mean(data_t *data){
	iris_t *vectors = data->vectors;

	double *vect_moy = calloc(data->dim_v, sizeof(*vect_moy));
	int dim_v = data->dim_v;
	int nbr_v = data->nbr_v;

	for (int i = 0; i < dim_v; ++i)
	{
		for (int j = 0; j < nbr_v ; j++)
		{
			vect_moy[i] += vectors[j].v[i];
		}
		vect_moy[i] /= nbr_v;
	}
	
	return vect_moy;
}

/*\brief La fonction permet d'initialiser la structure data.
 * \param dim_vect ladimenssion du vecteur. 
 * \param nbr_vect le nombre de vecteur.
 * \param nbr_arg la dimension du vecteur + le label.
 * \return le pointeur de la structure inisialisé.
 */
data_t* init_data(int dim_vect, int nbr_vect, int nbr_arg){
	
	data_t *data = malloc(sizeof *data);
	data->dim_v = dim_vect;
	data->nbr_v = nbr_vect;
	data->nbr_a = nbr_arg;
	data->vectors = NULL;

	return data;
}

/*\brief La fonction permet de parser la bdd d'iris_data
 * \param name_file le nom du ficheir à parser 
 * \param data un pointeur sur le data contient la bdd de iris_data.
 */
void create_data(char *name_file, data_t* data){
	int dim_v = data->dim_v;
	int nbr_v = data->nbr_v;
	int nbr_a = data->nbr_a;
	int taille_chaine = 1000;
	int j = 0;	
	
	FILE* fichier = NULL;
	char chaine[taille_chaine];
	char *token, *str;

	iris_t *vectors;

	vectors = malloc(nbr_v * sizeof(*vectors));	

	fichier = fopen(name_file, "r");

 	if (fichier != NULL){
        while (fgets(chaine, taille_chaine, fichier) != NULL)
        { 
			str = chaine;
			vectors[j].v = malloc(dim_v * sizeof(*vectors[j].v));

			for (int i = 0; i < nbr_a ; i++) 
			{
			    token = strtok(str, ",");
				str = NULL;
			    if (token == NULL)
					break;
				vectors[j].v[i] =  strtod(token, NULL);	
			}
			vectors[j].norm = norm(vectors[j].v, dim_v);
			vectors[j].label = malloc((strlen(token)) * sizeof(char));
			strcpy(vectors[j].label, token);
			if(j!=nbr_v-1)
				vectors[j].label[strlen(token)-1] = '\0';

			j++;
			if(j > nbr_v)
			{
				nbr_v = 2 * nbr_v;
				vectors = realloc(vectors, nbr_v);
			}
		}
	}
	fclose(fichier);


	data->nbr_v = j;
	data->vectors = vectors;
}

void normalisation(data_t *data){
	iris_t *vectors = data->vectors;
	int dim_v = data->dim_v;
	int nbr_v = data->nbr_v;

	for (int i = 0; i < nbr_v; ++i)
	{
		for (int j = 0; j < dim_v; ++j)
		{
			vectors[i].v[j] = vectors[i].v[j] / vectors[i].norm;	
		}
	}
}

void afficher_data(data_t *data){
	iris_t *vectors = data->vectors;
	int nbr_v = data->nbr_v;

	for (int i = 0; i < nbr_v; i++)
	{
		printf("vec = (%.2f %.2f %.2f %.2f),  norm = %f  label = %s\n",
			vectors[i].v[0], vectors[i].v[1], vectors[i].v[2], vectors[i].v[3],
			vectors[i].norm, vectors[i].label);
	}	
}
