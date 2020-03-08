#ifndef DATA_H
#define DATA_H
struct iris{
	double *v;
	double norm;
	char *label;
};
typedef struct iris iris_t;

struct data{
	int dim_v;
	int nbr_v;
	int nbr_a;
	iris_t *vectors;
};
typedef struct data data_t;

double* vect_mean(data_t *data);

data_t* init_data(int dim_v, int nbr_v, int nbr_arg);

void create_data(char *name_file, data_t* data);
void normalisation(data_t *data);
void afficher_data(data_t *data);
#endif