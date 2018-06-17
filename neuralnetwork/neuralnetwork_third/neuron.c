# include "neuron.h"
# include <stdlib.h>
# include <stdio.h>

int init_neuron(struct neuron *neuron)
{
	neuron = malloc(sizeof(neuron));
	if (neuron == NULL) {
		printf("[ERR]: error during neuron allocation");
		return 1;
	}
	return 0;
}

void remove_neuron(struct neuron *neuron)
{
	if (neuron)
		free(neuron);
}

int init_delta_weight(struct neuron *neuron, size_t len)
{
	neuron->len_delta_weight = len;
	net->delta_weight = malloc(sizeof(double) * len);
	if (net->delta_weight == NULL)
		return 0;
	for (size_t i = 0; i < len; ++i) {
		net->delta_weight[i] = 0.0;
	}
	return 1;
}
