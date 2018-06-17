# include <stdio.h>

struct neuron {	
	double input;

	double *weight;	
	size_t len_weight;

	double *delta_weight;
	size_t len_delta_weight;
} neuron_t;

int *init_neuron(struct neuron *neuron);

int *init_delta_neuron(struct neuron *neuron);

void remove_neuron(struct neuron *neuron);
