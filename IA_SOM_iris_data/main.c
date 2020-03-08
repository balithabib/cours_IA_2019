#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>

#include "tools.h"
#include "network.h"
#include "data.h"
#include "free.h"

int main(int argc, char *argv[]){
	srand(time(NULL));

	char* filename = "configuration.txt";
	
	config_t* config;	
	data_t *data;
	network_t *net;
	
	//====================================================================
	printf("Initialisation:\n");
	config = load_configuration(filename);
	printf("\tnombre de vecteur : %d.\n\tdim_vecteur : %d.\n", config->nbr_vect, config->dim_vect);
	printf("\tnb_neurons: (%d, %d).\n", config->nbr_l, config->nbr_c);
	printf("\tnbr_iter: %d.\n\trayon : %d.\n", config->nbr_iter, config->rayon);
	printf("\talpha init : %.2f.\n\n", config->alpha_i);
	init( config, &data, &net);
	//===================================================================
	printf("----------------------------------------\n");
	printf("Apprentisage:\n");
	printf("Phase 1 (ordonnancement).\n");
	learning_phase(2 * config->nbr_iter / 10, config->rayon, config->alpha_i, data, net);
	//====================================================================
	config->alpha_i = 0.07;
	config->rayon = 1;
	printf("Phase 2 (affinage).\n\n");
	learning_phase(config->nbr_iter - 2 * config->nbr_iter / 10, config->rayon, config->alpha_i, data, net);
	//====================================================================
	printf("----------------------------------------\n");
	printf("Etiquetage:\n");
	etiquetage(data, net);
	//====================================================================

	free_config(config);
	free_data(data);
	free_network(net);

    return 0;
}
