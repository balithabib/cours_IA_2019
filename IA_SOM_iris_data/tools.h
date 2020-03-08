#ifndef TOOLS_H
#define TOOLS_H

double norm(double *v, int dim_v);
double dist(double *a, double *b, int dim_v);
double rand_double(double min, double max);
double* min_max(double *vect_moy, double lower_bond, double upper_bound, int dim_v);

int rand_int(int min, int max);
void shuffle(int *tab, int nbr_v);
int* init_shuffle(int nbr_v);
int compare (void const *a, void const *b);
int str_comp(char* a, char* b);
#endif