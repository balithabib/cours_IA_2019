#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>

#include "tools.h"
#include "data.h"
#include "network.h"

/*\brief un tableau qui représenter les différents types de iris_data.*/
char * _types_names[] = { "Iris-setosa",  "Iris-versicolor", "Iris-virginica"};

/*\brief La fonction permet d'inisialiser le réseaux de neurones en centrant les données.
 *  
 * \param nbr_l le nombre de ligne.
 * \param nbr_c le nombre de colonne.
 * \param dim_v la dimension du vecteur.
 * \param vect_min_max un vecteur de dimension 8 qui contient le vecteur max et min pour centrer les données. 
 * \return network_t* return un pointeur vers la structure du réseau initialisé.
 */
network_t* init_network_neuron(int nbr_l, int nbr_c, int dim_v,double *vect_min_max){

	network_t *net= malloc(sizeof *net);
	net->l = nbr_l;
	net->c = nbr_c;
	net->t = nbr_l * nbr_c;
	net->neurons = malloc(nbr_l * sizeof(*net->neurons));

	for (int i = 0; i < nbr_l; ++i)
	{	
		net->neurons[i] = malloc(nbr_c * sizeof(*net->neurons[i]));
		neuron_t *neurons_ligne = net->neurons[i];
		for (int j = 0; j < nbr_c; ++j)
		{
			neurons_ligne[j].l = i;
			neurons_ligne[j].c = j;
			neurons_ligne[j].label = 0;
			neurons_ligne[j].v = malloc(dim_v * sizeof(*net->neurons[i][j].v));
			double *v = neurons_ligne[j].v;
			for (int k = 0;k < dim_v; ++k)
			{
				v[k] = rand_double(vect_min_max[k],vect_min_max[k + dim_v]);
			}
		}
	}
	return net;
}
/*\brief La afficher les données des variables de types network_t.
 *  
 * \param net le réseau de neurones.
 */
void afficher_network(network_t * net){
	int nbr_l = net->l;
	int nbr_c = net->c;
	for (int i = 0; i < nbr_l; i++)
	{
		for (int j = 0; j < nbr_c; ++j)
		{	
			printf("[%f %f %f %f] ", net->neurons[i][j].v[0], net->neurons[i][j].v[1], net->neurons[i][j].v[2], net->neurons[i][j].v[3]);
		}
		printf("\n");
	}	
}

/*\brief La fonction permet de trouver le best match unit.
 *  
 * \param net le réseau de neurones.
 * \param v le vecteur de données. 
 * \param dim_v la dimension du vecteur.
 * \param indice indice de la donnée.
 * \return neuron_t* return un pointeur vers le best match unit trouver.
 */
neuron_t* best_match_unit(network_t *net, double *v, int dim_v){
	
	int nbr_l = net->l;
	int nbr_c = net->c;
	double distance;

	neuron_t *bmu_candidate = malloc(sizeof *bmu_candidate);
	
	bmu_candidate->l = 0; 
	bmu_candidate->c = 0;
	double activ_state = dist(net->neurons[0][0].v, v, dim_v);
	
	for (int l = 0; l < nbr_l; ++l)
	{
		for (int c = 0; c < nbr_c; ++c)
		{
			distance = dist(net->neurons[l][c].v, v, dim_v);
			if(distance < activ_state){
				activ_state = distance;
				bmu_candidate->l = l; 
				bmu_candidate->c = c;
			}
		}
	}
	return bmu_candidate;
}

/*\brief La fonction permet de parser la base de données iris_data et la sauvgarder dans une structure type data_t
 *  la normaliser et l'initialisation du réseau de neurones.
 * \param config une structure qui contient tous les configuration nécessaire.
 * \param data un pointeur sur le data qui va contenir la bdd de iris_data;
 * \param net un pointeur sur le réseau qui sera initialisé. 
 */
void init(config_t* config,data_t **data_o, network_t **net_o){

	double *vect_moy;
	double *vect_min_max;
	network_t *net;
	data_t *data;

	data = init_data(config->dim_vect, config->nbr_vect, config->nbr_arg);
	create_data(config->filename, data);
	normalisation(data);
	
	vect_moy = vect_mean(data);
	vect_min_max = min_max(vect_moy, config->lower_bound, config->upper_bound, config->dim_vect); 

	net = init_network_neuron(config->nbr_l, config->nbr_c, config->dim_vect, vect_min_max);
	*data_o = data;
	*net_o = net; 
}

/*\brief La fonction permet de faire les deux phase d'apprentisage.
 * \param nbr_iter le nombre d'itération. 
 * \param r le rayon de voisinage.
 * \param alpha_i l'alpha initialle.
 * \param data un pointeur sur le data contient la bdd de iris_data;
 * \param net un pointeur sur le réseau de neurones.
 */
void learning_phase(int nbr_iter, int r, double alpha_i,data_t *data, network_t *net){
	int dim_v = data->dim_v;
	int nbr_v = data->nbr_v;
	int nbr_l = net->l;
	int nbr_c = net->c;
	int *tab;
	int node_r;
	int node_c;
	int begin_r, end_r, begin_c, end_c;
	int pas_r = nbr_iter / r;
	double *v;
	double *w;	
	double alpha;
	neuron_t * bmu_v = NULL;
	tab = init_shuffle(nbr_v);
	for (int i = 1; i <= nbr_iter; ++i)
	{	
		shuffle(tab, nbr_v);
		alpha = alpha_i *(1.0 - ((double)i/(double)nbr_iter));

		for (int j = 0; j < nbr_v; ++j)
		{
			v = data->vectors[tab[j]].v;
			bmu_v = best_match_unit(net, v, dim_v);

			node_r = bmu_v->l;
			node_c = bmu_v->c;

			begin_r = max(0, node_r - r);
			end_r = min(node_r + r, nbr_l - 1);

			begin_c = max(0, node_c - r);
			end_c = min(node_c + r, nbr_c -1);

			for (int r = begin_r; r <= end_r; ++r)
			{
				for (int c = begin_c; c <= end_c; ++c)
				{
					w = net->neurons[r][c].v;
					for (int k = 0; k < dim_v; ++k)
					{
						w[k] += alpha * (v[k] - w[k]);
					}
				}
			} 
		}
		if(pas_r && i % pas_r == 0)
			r -= (r>1)? 1: 0;
	}
	free(tab);
	free(bmu_v);
}

/*\brief La fonction permet de faire l'étiquetage du réseau
 * \param nbr_iter le nombre d'itération. 
 * \param data un pointeur sur le data contient la bdd de iris_data;
 * \param net un pointeur sur le réseau de neurones.
 */
void etiquetage(data_t *data, network_t *net){
	int dim_v = data->dim_v;
	int nbr_v = data->nbr_v;
	int nbr_l = net->l;
	int nbr_c = net->c;
	int indice_min;
	int *tab = init_shuffle(nbr_v);
	shuffle(tab, nbr_v);
	double *w;
	char *label, t;
	double distance, distance_min;

	for (int r = 0; r < nbr_l; ++r)
	{
		for (int c = 0; c < nbr_c; ++c)
		{
			t = ' ';
			w = net->neurons[r][c].v;
			distance_min = dist(w, data->vectors[tab[0]].v, dim_v);
			indice_min = 0;

			for (int i = 1; i < nbr_v; ++i)
			{
				distance = dist(w, data->vectors[tab[i]].v, dim_v);
				if(distance < distance_min){
					distance_min = distance;
					indice_min = tab[i];
				}
			}

			label = data->vectors[indice_min].label;
			if(str_comp(label, _types_names[0])){
				t = 'A';
				color(RED);
			}else 
			if(str_comp(label, _types_names[1])){
				t = 'B';
				color(GREEN);
			}else
			if(str_comp(label, _types_names[2])){
				t = 'C';
				color(BLUE);
			}
			net->neurons[r][c].label = t;
			printf(" %c ",net->neurons[r][c].label);
			color(WHITE);
		}
		printf("\n");
	}
}

/*\brief La fonction permet de parser un fichier qui contient tous les données d'initialisations requise
 * \param filename le nom du fichier à parser
 * \return config_t* return la structur inisialisé
 */
config_t* load_configuration(char* filename){
	FILE* fichier = NULL;
	int taille_chaine = 512;
	char chaine[taille_chaine];
	char *token;
	int tab_i[7], i = 0;
	double tab_d[3];
	config_t *config = malloc(sizeof * config);

	fichier = fopen(filename, "r");

 	if (fichier != NULL){
        while ( i< 7 && fgets(chaine, taille_chaine, fichier) != NULL)
        { 
			token = strtok(chaine, ":");
			token = strtok(NULL, ":");
			tab_i[i] = atoi(token);
			i++;
		}
		i = 0;
       while (fgets(chaine, taille_chaine, fichier) != NULL && i< 3)
        { 
			token = strtok(chaine, ":");
			token = strtok(NULL, ":");
			tab_d[i] = strtod(token , NULL);
			i++;
		}
		token = strtok(chaine, ":");
		token = strtok(NULL, ":");
		config->filename = malloc((strlen(token)) * sizeof(char));
		strcpy(config->filename, token);

		config->nbr_vect = tab_i[0];config-> nbr_c= tab_i[4];
		config->dim_vect = tab_i[1];config->nbr_iter = tab_i[5];
		config->nbr_arg = tab_i[2];config->rayon = tab_i[6];
		config->nbr_l = tab_i[3];

		config->alpha_i = tab_d[0];
		config->lower_bound = tab_d[1];
		config->upper_bound = tab_d[2];

	}
	fclose(fichier);
	return config;
}
