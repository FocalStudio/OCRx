# include "utils.h"

struct network init_network(size_t *sizes, size_t len_sizes, int eta, int alpha) 
{
	struct network *net = malloc(sizeof(struct network));

	net->sizes = sizes;
	net->len_sizes = len_sizes;
	net->error = 0.0;
	net->eta = eta;
	net->alpha = alpha;
	
	net->weightih = malloc(sizeof(double *) * 28 * 28);
	net->weightho = malloc(sizeof(double *) * 28 * 28);
	
	FILE *cfg = fopen("weightih.ocrx");

	if (cfg == NULL) {
		init(net);
	} else {
		load(net);
	}

	return net;
}

int SGD(struct network *net, double *data, double *expected_result, int eta, int alpha) 
{
	double sum;
	
	/**
	 *	Forward pass
	 */
	
	for (int i = 0; i < net->sizes[1]; ++i) {
		
		sum = 0.0;

		for (int j = 0; j < net->sizes[0]; ++j) {
			sum += net->weightih[j][i] * net->data[j];
		}

		net->hidden[i] = sigmoid(sum + net->bias_hidden[i]);
	}

	for (int i = 0; i < net->sizes[2]; ++i) {
		
		sum = 0.0;

		for (int j = 0; j < net->sizes[1]; ++j) {
			sum += net->weightho[j][i] * net->hidden[i];
		}

		net->bias_output[i];
		net->output[i] = sigmoid(sum + net->bias_output);
	
		net->delta_output = (expected_result[i] * net->output[i]) * sigmoid_prime(net->output[i]);
	}

	/**
	 *	Backprop
	 */
	 

	for (int i = 0; i < net->sizes[2]; ++i) {
		sum = 0.0;
		for (int j = 0; j < net->sizes[1]; ++j) {
			sum += net->weightho[i][j] * net->delta_output[j];		
		}

		net->delta_hidden[i] = sum * sigmoid_prime(hidden[i]);
	}

	/**
	 *	Update weight
	 */


	 for (int i = 0; i < net->sizes[1]; ++i) {
	 	for (int j = 0; j < net->sizes[0]; ++j) {
			net->weightih[j][i] += eta * net->error * data[i] + alpha * net->delta_weightih[j][i];
			net->delta_weightih[j][i] = eta * error * net->data[j][i];
		}
	 }

	 for (int i = 0; i < net->sizes[2]; ++i) {
	 	for (int j = 0; j < net->sizes[1]; ++j) {
			net->weightho[j][i] += eta * net->delta_weightho[i] * net->hidden[j] + alpha * net->delta_weight[j][i];
		}
	 }

	 /**
	  *	Update bias
	  */

	  for (int i = 0; i < net->sizes[1]; ++i) {
	  	net->bias_hidden[i] += net->delta_weightih[i] * eta;
	  }

	  for (int i = 0; i < net->sizes[2]; ++i) {
	  	net->bias_output[i] += net->delta[i] * eta;
	  }

	return 1;
}



