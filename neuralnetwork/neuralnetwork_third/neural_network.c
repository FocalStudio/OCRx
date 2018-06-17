# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>

# include "neuron.h"
# include "layer.h"
# include "network.h"

double sigmoid(double z)
{
	return (double)(1.0 / (1.0 + exp(-z)));
}

double sigmoid_prime(double z)
{
	return z * (1 - z);
	//return sigmoid(z) * (1 - sigmoid(z));
}

struct network *create_network(int *sizes, int len, char *path)
{
	
       	srand(time(NULL));
	
	struct network *net = malloc(sizeof(network_t));

	net->sizes = sizes;
	net->len_sizes = len;
	net->path = path;

	net->layers = malloc(sizeof(layer_t) * len);

	double *tmp;

	FILE *cfg = fopen(path, "r"); 

//	if (cfg != NULL)
//		if (!load_weight(net, cfg))
//			printf("[Error]: unable to load weight, aborting...\n");
	for (int layer = 0; layer < (len - 1); ++layer) {
		net->layers[layer].neurons = malloc(sizeof(neuron_t) * sizes[layer]);
		for (int i = 0; i < sizes[layer]; ++i) { //for each neuron in the layer
			tmp = malloc(sizeof(double) * sizes[layer + 1]);
			for (int j = 0; j < sizes[layer + 1]; ++j) {
				
				tmp[j] = ((double)rand()/(double)RAND_MAX);
				printf("%f\n", tmp[j]);
			}	
			net->layers[layer].neurons[i].weight = tmp;
			net->layers[layer].neurons[i].len_weight = sizes[layer + 1];	
		}
		net->layers[layer].len_neurons = sizes[layer];
	}		
	return net;
}

int init_deltas(network_t *net)
{
	int b = 1;
	for (size_t layer = 0; b && layer < (len - 1); ++layer) {
		for (size_t i = 0; b && i < net->sizes[layer]; ++i) {
			b &= init_delta_weight(net->layers[layer].neurons[i], net->sizes[layer]);
		}
	}

	return b;

}

void SGD(network_t, size_t epoch, double eta, double alpha)
{
        double error = 0.0, tmp;
	double *delta;
	
	double training_data[4][2] = { 
		{0, 0},
		{0, 1},
		{1, 0},
		{1, 1}
	};

	double expected_result[4][1] = {{0},{1},{1},{0}};
	size_t training_data_order = malloc(sizeof(size_t) * network_t->sizes[0]);
	
	for (size_t i = 0; i < len_training_data; ++i) {
                training_data_order[i] = i;	
        }
        //init delta
        
        for (size_t e = 0; e < epoch; ++e) {
                /* Randomize test order*/
                for (size_t i, pos, tmp; i < len_training_data; ++i) {
                        tmp = training_data_order[i];
                        pos = i + rand() / RAND_MAX * (len_training_data - i);
                        training_data_order[i] = training_data_order[pos];
                        training_data_order[pos] = tmp;
                }
		
		error = 0.0;
		for (size_t p = 0, pattern; p < len_training_data; ++p) {
			pattern = training_data[p];
			
			for (size_t i = 0; i < net->sizes[0]; ++i) {
				net->layers[0].neurons[i] = training_data[i];
			}
			
			for (size_t layer = 0; layer < (net->len_sizes - 1); ++layer) {
				for (size_t i = 0; i < net->sizes[layer + 1]; ++i) {
					tmp = 0.0;
					for (size_t j = 0; j < net->sizes[layer]; ++j) {
						tmp += net->layers[layer].neurons[i].weight[j] 
							* net->layers[layer].neurons[i].in;
					}
					net->layers[layer + 1].neurons[i].weight[j].in = sigmoid(tmp);
				}
			}
		}
        } 
}

int save_weight(network_t *net)
{/*
	FILE *cfg = fopen(net->path, "w");
	if (cfg == NULL)
		printf("Can't save the weight, aborting...");
	fputc('{', cfg);

	for (int i = 0; i < net->sizes[0]; ++i) {
		
		fputc('{', cfg);

		for (int j = 0; j < net->sizes[1]; ++j) {
			fputc(net->weightih[i][j], cfg);
		}
		
		fputc('}', cfg);
	}
	
	fputc('}', cfg);
	fputc('{', cfg);
	
	for (int i = 0; i < net->sizes[1]; ++i) {
		
		fputc('{', cfg);

		for (int j = 0; j < net->sizes[2]; ++j) {
			fputc(net->weightho[i][j], cfg);
		}
		
		fputc('}', cfg);
	}
	
	fputc('{', cfg);*/

}

