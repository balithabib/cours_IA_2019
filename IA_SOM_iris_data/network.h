#ifndef NETWORK_H
#define NETWORK_H
#include<stdio.h>
#include<stdlib.h>
#include "data.h"
/// Des macros qui nous permet d'afficher un texte en couleur passer en paramétre.
#define color(param) printf("\e[%sm",param)
#define RED "41"
#define GREEN "42"
#define BLUE "44"
#define WHITE "0"
/// Des macros qui nous permet de calculer le max et le min.
#define max(a,b) ((a>b)? a:b)
#define min(a,b) ((a<b)? a:b)

struct neuron{
	int l;
	int c;
	double* v;
	char label;
};
typedef struct neuron neuron_t;

struct network{
	int l;
	int c;
	int t;
	neuron_t **neurons;
};
typedef struct network network_t;

struct config
{
	int nbr_vect, dim_vect, nbr_arg;
	int nbr_l, nbr_c, nbr_iter;
	int rayon;
	double alpha_i, lower_bound, upper_bound;

	char* filename;
};
typedef struct config config_t;

network_t* init_network_neuron(int nbr_l, int nbr_c, int dim_v,double *vect_min_max);
neuron_t* best_match_unit(network_t *network, double *v, int dim_v);

void init(config_t* config, data_t **data, network_t **net);
void learning_phase(int nbr_iter, int r, double alpha,data_t *data, network_t *network);
void etiquetage(data_t *data, network_t *net);
void test(data_t *data, network_t *net);
config_t* load_configuration(char* filename);

void afficher_network(network_t * net);

#endif
