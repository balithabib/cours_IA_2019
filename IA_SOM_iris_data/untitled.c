/*\brief La fonction permet de faire un test sur le réseau en passsant tous les données d'iris
 * on réalisant une petite stat et affiche une petite matrice qui représante la topologie.
 * \param data un pointeur sur le data contient la bdd de iris_data;
 * \param net un pointeur sur le réseau de neurones.
 */
/*void test(data_t *data, network_t *net){
	int dim_v = data->dim_v;
	int nbr_v = data->nbr_v;
	int nbr_l = net->l;
	int nbr_c = net->c;
	int nbr_n = net->t;
	int r, c, indice_minr,indice_minc;

	double *w;
	char label, t;
	double distance, distance_min;
	int ii = 0;
	int tab[3]={0},o;
	for (int i = 0; i < nbr_v; ++i)
	{

			w = data->vectors[i].v;
			distance_min = dist(w, net->neurons[0][0].v, dim_v);
			indice_minr = 0;
			indice_minc = 0;
			for (int r = 0; r < nbr_l; ++r)
			{
				for (int c = 0; c < nbr_c; ++c)
				{
					distance = dist(w, net->neurons[r][c].v, dim_v);
					if(distance < distance_min){
						distance_min = distance;
						indice_minr = r;
						indice_minc = c;
					}			
				}
			}
			char* label = data->vectors[i].label;
			char t;
			if(str_comp(label, _types_names[0])){
				t = 'A';
				o = 0;
			}else 
			if(str_comp(label, _types_names[1])){
				t = 'B';
				o = 1;
			}else
			if(str_comp(label, _types_names[2])){
				t = 'C';
				o = 2;
			}
			if(net->neurons[indice_minr][indice_minc].label == t){
				ii++;
				tab[o]++;
			}
	}

	printf("\tTaux de vériter: %.2f\n", ii/(double)nbr_v * 100.0);
	printf("\t|classe     nbr|\n");
	for (int i = 0; i < 3; ++i)
		printf("\t|%c \t==>  %d|\n",i+65, tab[i]);
}*/