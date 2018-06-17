# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <err.h>
# include "utils.h"

//# include "neuron.h"

double sigmoid(double z)
{
	return (double)(1.0 / (1.0 + exp(-z)));
}

double sigmoid_prime(double z)
{
	return z * (1 - z);
	//return sigmoid(z) * (1 - sigmoid(z));
}

Network *create_network(int *sizes, int len, int init)
{

	srand(time(NULL));

	Network *net = malloc(sizeof(Network));

	net->sizes = sizes;
	net->sizeslen = len;
	//	net->path = path;

	net->weightih = malloc(sizeof(double *) * sizes[0] * sizes[1] + 60);
	net->weightho = malloc(sizeof(double *) * sizes[1] * sizes[0] + 60);

	double *tmp;

	if (init) {
		if (!load(net))
			printf("[Error]: unable to load weight, aborting...\n");
		printf("[Info]: weight loaded\n");
	} else {
		printf("[Info]: weight creation...\n");
		printf("[Info]: Initializing weightih...\n");
		for (int i = 0; i < sizes[0]; ++i) {

		//	printf("%d\n", i);
			tmp = malloc(sizeof(double) * sizes[1]);

			for (int j = 0; j < sizes[1]; ++j) {
				tmp[j] = ((double)rand()/(double)RAND_MAX);
			}	

			net->weightih[i] = tmp;	
		}	
		printf("[Info]: Initializing weightho...\n");
		for (int i = 0; i < sizes[1]; ++i) {
			tmp = malloc(sizeof(double) * sizes[2]);
			for (int j = 0; j < sizes[2]; ++j) {
				tmp[j] = ((double)rand()/(double)RAND_MAX);
			}

			net->weightho[i] = tmp;
		}
		printf("[Info]: Initialization finished.\n");
	}
	return net;
}

int process(Network *net, double eta, double alpha, double *input, size_t input_len) 
{
	/*	double *input = malloc(sizeof(double) * 2);
		size_t input_len = 2;
		input[0] = 0;
		input[1] = 1;
	 */
	double sum_hidden[net->sizes[1]];
	double sum_output[net->sizes[2]];

	double hidden_layer[net->sizes[1]];
	double output_layer[net->sizes[2]];

	for (int i = 0; i < net->sizes[1]; ++i) {

		sum_hidden[i] = 0;
		for (int j = 0; j < net->sizes[0]; ++j) {
			sum_hidden[i] += input[j] * net->weightih[j][i];					
		}	
		hidden_layer[i] = sigmoid(sum_hidden[i]);

	}

	for (int i = 0; i < net->sizes[2]; ++i) {

		sum_output[i] = 0;
		for (int j = 0; j < net->sizes[1]; ++j) {
			sum_output[i] += hidden_layer[j] * net->weightho[j][i];
		}	
		output_layer[i] = sigmoid(sum_output[i]);
	}

	int i = 0, max_layer;
	double max = 0;

	for (; i < net->sizes[2]; ++i) {
		if (output_layer[i] > max) {
			max_layer = i;
			max = output_layer[i];
		}
		printf("Layer %d, max=%f\n", i, max);
	}

	return round(max);
}

void SGD(Network *net, double eta, double alpha, double **training_data, size_t training_data_len, double **expected_result, int epoch)
{
	/**
	 *	Use this function to train the neural network
	 *	If the weight are already initialized use "process"
	 */

	double error = 0.0;

	/**
	 *	Init delta to zero
	 */

	double delta_ih[net->sizes[0]][net->sizes[1]];
	double delta_ho[net->sizes[1]][net->sizes[2]];

	//double eta = 0.1, alpha = 0.1;

	/*	double training_data[4][2] = { 
		{0, 0},
		{1, 0},
		{0, 1},
		{1, 1} 
		};

		double expected_result[4][1] = { {0}, {1}, {1}, {0} };
	 */	
	 int *training_data_order = malloc(sizeof(int) * training_data_len); /*
								       int training_data_len = 4;
								     */
	double sum_hidden[training_data_len][net->sizes[1]];
	double sum_output[training_data_len][net->sizes[2]];

	double hidden_layer[training_data_len][net->sizes[1]];
	double output_layer[training_data_len][net->sizes[2]];

	double *delta_hidden = malloc(sizeof(double) * net->sizes[1]);
	double *delta_output = malloc(sizeof(double) * net->sizes[2]);

	//double *sum = malloc(sizeof(double) * net->sizes[1]);
	double sum;

	printf("[Info]: Step 1: Initializing training info\n");

	for (int i = 0; i < training_data_len; ++i) {
		training_data_order[i] = i;
	}

	printf("[Info]: Step 2: Initializing deltas\n");

	for (int i = 0; i < net->sizes[0]; ++i) {
		for (int j = 0; j < net->sizes[1]; ++j) {
			delta_ih[i][j] = 0.0;
		}
	}

	for (int i = 0; i < net->sizes[1]; ++i) {
		for (int j = 0; j < net->sizes[2]; ++j) {
			delta_ho[i][j] = 0.0;
		}
	}

	/* Starting learning here */

	printf("[Info]: Step 3: Learning starts\n");

	for (int e = 0; e < epoch; ++e) {

		/* Randomize test order */

		for (int i = 0, pos, tmp; i < training_data_len; ++i) {
			tmp = training_data_order[i];
			pos = i + rand() / RAND_MAX * (training_data_len - i);
			training_data_order[i] = training_data_order[pos];
			training_data_order[pos] = tmp;	
		}

		/* For each testing data pattern we are going to learn */

		error = 0.0;

		/**
		 * 	change neuron reprensation by a struct 
		 *	to add a layer need and "inter layer" matrices
		 *	and add a for in for
		 *	also modify the sizes to something dynamic
		 *
		 *	0 -> input
		 *	1 -> hidden
		 *	2 -> output
		 *
		 *	ih stands for input to hidden
		 *
		 *	ho stands for hidden to output
		 *
		 *	we must replace all the variable containing "pattern" with a struct / list
		 */

		for (int p = 0, pattern; p < training_data_len; ++p) {
			pattern = training_data_order[p];

			for (int i = 0; i < net->sizes[1]; ++i) {

				sum_hidden[pattern][i] = 0;
				for (int j = 0; j < net->sizes[0]; ++j) {
					sum_hidden[pattern][i] += training_data[pattern][j] * net->weightih[j][i];					
				}	
				hidden_layer[pattern][i] = sigmoid(sum_hidden[pattern][i]);

			}

			for (int i = 0; i < net->sizes[2]; ++i) {

				sum_output[pattern][i] = 0;
				for (int j = 0; j < net->sizes[1]; ++j) {
					sum_output[pattern][i] += hidden_layer[pattern][j] * net->weightho[j][i];
				}

				output_layer[pattern][i] = sigmoid(sum_output[pattern][i]);
				error += 0.5 * ((expected_result[pattern][i] - output_layer[pattern][i]) * (expected_result[pattern][i] - output_layer[pattern][i]));

				delta_output[i] = (expected_result[pattern][i] - output_layer[pattern][i]) * sigmoid_prime(output_layer[pattern][i]); 
			}


			/*
			 *	Backpropagation
			 */


			/**
			 *	Merge this loop with the next one
			 */

			for (int i = 0; i < net->sizes[1]; ++i) {
				sum = 0;

				for (int j = 0; j < net->sizes[2]; ++j) {
					sum += net->weightho[i][j] * delta_output[j];
				}

				delta_hidden[i] = sum * sigmoid_prime(hidden_layer[pattern][i]);
			}

			for (int i = 0; i < net->sizes[1]; ++i) {
				for (int j = 0; j < net->sizes[0]; ++j) {
					delta_ih[j][i] = eta * training_data[pattern][j] * delta_hidden[i] + alpha * delta_ih[j][i];
					net->weightih[j][i] += delta_ih[j][i];
				}
			}

			for (int i = 0; i < net->sizes[2]; ++i) {
				for (int j = 0; j < net->sizes[1]; ++j) {
					delta_ho[j][i] = eta * hidden_layer[pattern][j] * delta_output[i] + alpha * delta_ho[j][i];		
					net->weightho[j][i] += delta_ho[j][i];

				}
			}


		}

		/* Debug purpose stuff here */

		if (e % 10000 == 0)
			printf("Epoch: %d -- Error: %f\n", e, error);

		if (error < 0.0004) {
			printf("Error: %d\n", e);
			break;
		}

	}

	printf("%f\n", error);
	
	   for (int i = 0; i < training_data_len; ++i) {
		printf("Pattern %d:\n", i);		
	   	for (int j = 0; j < net->sizes[2]; ++j) {
	   		//printf("(%f-%f)-- %f\n", training_data[i][0], training_data[i][1], output_layer[j][i]);	
			printf("neuron %d: %f\n", j, round(output_layer[i][j]));
	   	}
	}

	//printf("%d  -- %d", );

	save(net);
}
