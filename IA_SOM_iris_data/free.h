#ifndef FREE_H
#define FREE_H

#include "network.h"
#include "data.h"

void free_config(config_t *config);
void free_data(data_t *data);
void free_network(network_t *net);

#endif
