#include "free.h"

void free_config(config_t *config){
	if(config){
		free(config->filename);
		free(config);
	}
}

void free_data(data_t *data){
	if(data){
		for (int i = 0; i < data->nbr_v; ++i)
		{
			free(data->vectors[i].v);
			free(data->vectors[i].label);
		}
		free(data->vectors);
		free(data);
	}
}

void free_network(network_t *net){
	if(net){
		for (int i = 0; i < net->l; ++i)
		{
			for (int j = 0; j < net->c; ++j)
			{
				free(net->neurons[i][j].v);
			}
			free(net->neurons[i]);
		}
		free(net->neurons);
		free(net);
	}
}
