#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "tools.h"

double norm(double *v, int dim_v){
	double som = 0.0;
	for (int i = 0; i < dim_v; ++i)
	{
		som += pow(v[i], 2);
	}
	return sqrt(som);
}

double dist(double *a, double *b, int dim_v){
	double som = 0.0;
	for (int i = 0; i < dim_v; ++i)
	{
		som += pow(b[i] - a[i], 2);
	}
	return sqrt(som);
}

double rand_double(double min, double max){
  	double r = (double)rand() / (double)(RAND_MAX + 1.0);
  	return r * (max - min) + min;
}

int rand_int(int min, int max){
  	return rand()%(max - min) + min;
}

double* min_max(double *vect_moy, double lower_bound, double upper_bound, int dim_v){
	double *min_max = malloc(2 * dim_v * sizeof(*min_max));	

	for (int i = 0; i < dim_v; ++i)
	{
		min_max[i] = vect_moy[i] - lower_bound;
		min_max[i + dim_v] = vect_moy[i] + upper_bound;
	}

	return min_max;
}

int* init_shuffle(int nbr_v){
	int *tab = malloc(nbr_v * sizeof *tab);
	// initialisation du tableau de 0 à nbr_v
	for (int i = 0; i < nbr_v; ++i)
	{
		tab[i] = i;	
	}
	return tab;
}

void shuffle(int *tab, int nbr_v){
	int tmp, rand_i;
	// méllanger  le tableau aléatoirment
	for (int i = 0; i < nbr_v; ++i)
	{
	
		rand_i = rand_int(i, nbr_v);
		//printf("%d  %d  %d\n",i,nbr_v,rand_i);
		tmp = tab[i];
		tab[i] = tab[rand_i];
		tab[rand_i] = tmp;
	}
}

int str_comp(char* a, char* b){
	int length_a = strlen(a);
	int length_b = strlen(b);
	int length_min = (length_a > length_b)? length_b : length_a;

	for (int i = 0; i < length_min; ++i)
	{
		if(a[i] != b[i])
			return 0;
	}
	return 1;
}