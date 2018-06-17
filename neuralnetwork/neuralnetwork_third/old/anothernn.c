# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>

# include "neuron.h"
# include "anothernn.h"

double sigmoid(double z)
{
	return (double)(1.0 / (1.0 + exp(-z)));
}

double sigmoid_prime(double z)
{
	return z * (1 - z);
	//return sigmoid(z) * (1 - sigmoid(z));
}

Network *create_network(int *sizes, int len, char *path)
{
	
       	srand(time(NULL));
	
	Network *net = malloc(sizeof(Network));

	net->sizes = sizes;
	net->sizeslen = len;
	net->path = path;

	net->weightih = malloc(sizeof(double *) * 40);
	net->weightho = malloc(sizeof(double *) * 40);

	double *tmp;

	FILE *cfg = fopen(path, "r"); 
	/*if (cfg != NULL) {
		for (int layer = 0; layer < (len - 1), ++layer) {
			for (int i = 0; i < sizes[layer]; ++i) {
				for(int j = 0; j < sizes[layer + 1], ++j) {
					net->weight[]
				}
			}
		}
	}*/

	if (cfg != NULL)
		if (!load_weight(net, cfg))
			printf("[Error]: unable to load weight, aborting...\n");
	
	for (int i = 0; i < sizes[0]; ++i) {
			
		tmp = malloc(sizeof(double) * sizes[1]);
		
		for (int j = 0; j < sizes[1]; ++j) {
			tmp[j] = ((double)rand()/(double)RAND_MAX);
			printf("%f\n", tmp[j]);
		}	
		
		net->weightih[i] = tmp;	
	}	
	
	for (int i = 0; i < sizes[1]; ++i) {
		
		tmp = malloc(sizeof(double) * sizes[2]);
		
		for (int j = 0; j < sizes[2]; ++j) {
			tmp[j] = ((double)rand()/(double)RAND_MAX);
		}
		
		net->weightho[i] = tmp;
	}
	
	
	//free(tmp);
	//fclose(cfg);
	
	return net;
}

int load_weight(Network *net, FILE *cfg)
{

}

int save_weight(Network *net)
{
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
	
	fputc('{', cfg);

}

void SGD(Network *net, int epoch, double eta, double alpha)
{
	double error = 0.0;

	/**
	 *	Init delta to zero
	 */

	double delta_ih[net->sizes[0]][net->sizes[1]];
	double delta_ho[net->sizes[1]][net->sizes[2]];

	//double eta = 0.1, alpha = 0.1;
	
	double training_data[4][2] = { 
		{0, 0},
		{1, 0},
		{0, 1},
		{1, 1} 
	};

	double expected_result[4][1] = { {0}, {1}, {1}, {0} };
	int *training_data_order = malloc(sizeof(int) * 5);
	int training_data_len = 4;

	double sum_hidden[training_data_len][net->sizes[1]];
	double sum_output[training_data_len][net->sizes[2]];

	double hidden_layer[training_data_len][net->sizes[1]];
	double output_layer[training_data_len][net->sizes[2]];
	
	double *delta_hidden = malloc(sizeof(double) * net->sizes[1]);
	double *delta_output = malloc(sizeof(double) * net->sizes[2]);

        //double *sum = malloc(sizeof(double) * net->sizes[1]);
	double sum;
	
	for (int i = 0; i < training_data_len; ++i) {
		training_data_order[i] = i;
	}

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

	for (int e = 0; e < epoch; ++e) {
		
		/* Randomize test order */

		for (int i = 0, pos, tmp; i < training_data_len; ++i) {
			tmp = training_data_order[i];
			pos = i + rand() / RAND_MAX * (training_data_len - i);
			training_data_order[i] = training_data_order[pos];
			training_data_order[pos] = tmp;	
		}

		/* For each testing data pattern we are going to learn */
		
		error = 0;

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
				//sum_hidden[pattern][i] = net->weightih[0][i];

				for (int j = 0; j < net->sizes[0]; ++j) {
					sum_hidden[pattern][i] += training_data[pattern][j] * net->weightih[j][i];					
				}	
				hidden_layer[pattern][i] = sigmoid(sum_hidden[pattern][i]);
				
			}

			for (int i = 0; i < net->sizes[2]; ++i) {
				
				sum_output[pattern][i] = 0;
				//sum_output[pattern][i] = net->weightho[0][i]
				for (int j = 0; j < net->sizes[1]; ++j) {
					sum_output[pattern][i] += hidden_layer[pattern][j] * net->weightho[j][i];
				}
/*
				double digit = expected_result[pattern][i] - output_layer[pattern][i];
                printf("Digit equal : %f\n",digit);
                		error = 0.5 * (digit * digit);

                		delta_output[i] = (expected_result[pattern][i] - output_layer[pattern][i]) * sigmoid_prime(output_layer[pattern][i]);
			*/	
				output_layer[pattern][i] = sigmoid(sum_output[pattern][i]);
				error += 0.5 * ((expected_result[pattern][i] - output_layer[pattern][i]) * (expected_result[pattern][i] - output_layer[pattern][i]));

				delta_output[i] = (expected_result[pattern][i] - output_layer[pattern][i]) * sigmoid_prime(output_layer[pattern][i]); 
			}

			//printf("%f --", error);

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
				
				//delta_ih[0][i] = eta * delta_hidden[i] + alpha * delta_ih[0][i];
				//net->weightih[0][i] += delta_ih[0][i];

				for (int j = 0; j < net->sizes[0]; ++j) {
					delta_ih[j][i] = eta * training_data[pattern][j] * delta_hidden[i] + alpha * delta_ih[j][i];
					net->weightih[j][i] += delta_ih[j][i];
				}
			}

			for (int i = 0; i < net->sizes[2]; ++i) {
				
				//delta_ho[0][i] = eta * delta_output[i] + alpha * delta_ho[0][i];
				//net->weightho[0][i] += delta_ho[0][i];
				for (int j = 0; j < net->sizes[1]; ++j) {
					delta_ho[j][i] = eta * hidden_layer[pattern][j] * delta_output[i] + alpha * delta_ho[j][i];		
					net->weightho[j][i] += delta_ho[j][i];
					
				        //printf("%f\n\n", delta_ho[j][i]);
				        //printf("%f\n", net->weightho[j][i]);
				}
			}
			
			
		}

		/* Debug purpose stuff here */
		
		if (e % 100 == 0)
			printf("Epoch: %d -- Error: %f\n", e, error);

		if (error < 0.0004) {
			printf("%d\n", e);
			break;
		}
		
	}

	printf("%f\n", error);

	for (int i = 0; i < training_data_len; ++i) {
		
		for (int j = 0; j < net->sizes[2]; ++j) {
			printf("(%f-%f)-- %f\n", training_data[i][0], training_data[i][1], output_layer[j][i]);
		}

		
	}
	
        //printf("%d  -- %d", );

	//save_weight(net);
}
