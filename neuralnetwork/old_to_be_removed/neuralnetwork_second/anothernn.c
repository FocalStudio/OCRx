#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>

#include "anothernn.h"

/**
 *	Mathematical function
 */

double sigmoid(double z)
{
	return 1 / (1 + exp(-z));
}

double sigmoid_prime(double z)
{
	return sigmoid(z) * (1 - sigmoid(z));
}
/*
void shuffle()
{
}*/

/**
 *	Neural network related function
 */

int create_network(int *sizes, size_t sizeslen, double **deltaweightih, double **deltaweightho)
{
	Network *net = malloc(sizeof(Network));

	net->sizes = sizes;
	net->sizeslen = 3;

	net->weightih = malloc(sizes[1] * sizes[0] * sizeof(double *));
	net->weightho = malloc(sizeof(double *) * sizes[1] * sizes[2]);

	srand(time(NULL));
	
	for (int i = 0; i < net->sizes[1]; ++i)
	{
		for (int j = 0; j < net->sizes[2]; ++j)
		{
			deltaweightih[i][j] = 0;
			net->weightih[i][j] = (double) rand() / ((double) RAND_MAX + 1);
		}
	}

	for (int i = 0; i < net->sizes[2]; ++i)
	{
		for (int j = 0; j < net->sizes[1]; ++j)
		{
			deltaweightho[i][j] = 0;
			net->weightho[i][j] = (double) rand() / ((double) RAND_MAX + 1);
		}
	}

	return 0;
}

int SGD(Network *net, int epoch, int errormagin, double **testing_data, double **expected_result, int testing_data_len, double **output)
{
	double tmp;
	int *test_order = malloc(sizeof(int) * testing_data_len);
	double *deltajesaisplus = malloc(sizeof(double) * net->sizes[1]);

	/**
	 *	matrix for summing every single combination
	 */
	double **sum_hidden_layer = malloc(sizeof(double *) * net->sizes[1] * net->sizes[0]); 
	double **sum_output_layer = malloc(sizeof(double *) * net->sizes[1] * net->sizes[2]);
	double **sum_hidden_delta = malloc(sizeof(double *) * net->sizes[1] * net->sizes[0]);
	double **sum_output_delta = malloc(sizeof(double *) * net->sizes[1] * net->sizes[2] * epoch);
	double **hidden_layer     = malloc(sizeof(double *) * net->sizes[2] * epoch);

	double error;
	for (int i = 0; i < testing_data_len; ++i)
	{
		*test_order[i] = i;
	}

	for (int e = 0, pos; e < epoch; ++epoch)
	{
		/*
		for (int p = 0; p < testing_data_len; ++p)
		{
			tmp = testing_data[p];
			pos = rand() % (tesing_data_len - 1 - p);
			tesing_data[p] = testing_data[pos];
			testing_data[pos] = tmp;	
		}*/

		for (int pattern = 0, current_p; pattern < testing_data_len; ++pattern)
		{
			current_p = *testing_data[pattern];
			for (int i = 0; i < net->sizes[1]; ++i)
			{
				sum_hidden_layer[current_p][i] = net->weightih[0][i];
				for (int j = 0; j < net->sizes[0]; ++j)
				{
					sum_hidden_layer[current_p][i] += 
						testing_data[current_p][j] * net->weightih[j][i];
				}
				hiddenlayer[current_p][i] = 
					sigmoid(-sum_hidden_layer[current_p][i]);
			}

			for (int i = 0; i < net->sizes[2]; ++i)
			{
				sum_output_layer[current_p][i] = net->weightho[0][i];
				for (int j = 0; j < net->sizes[1]; ++j)
				{
					sum_output_layer[current_p][i] += 
						hiddenlayer[current_p][i] * net->weightho[j][i];
				}
				output[current_p][i] = sigmoid(-sum_output_layer[current_p][i]);
				error += 0.5 *  (expected_result[current_p][i] - output[current_p][i]) * (expected_result[current_p][i] - output[current_p][i]);
				//define me senpai
				delta_output[i] = (expected_result[current_p][i] - output[current_p][i]) * sigmoid_prime(output[current_p][i]);
			}
			/**
			 *	backpropagation
			 */
			
			for (int i = 0; i < net->sizes[1]; ++i)
			{
				deltajesaisplusquoi[i] = 0;
				for (int j = 0; j < net->sizes[2]; ++j)
				{
					//define delta_output
					detlajesaisplusquoi[i] += net->weight[i][j] * delta_output[i];
				}					
				deltahidden[i] = deltajesaisplusquoi[i] * sigmoid_prime(hidden_layer[current_p][i]);
			}

			/**
			 *	just need to implement the weight update and we will be done !
			 */
		}

		if (!(epoch % 100))
			print("Epoch n°d: Error = %f", e, error);

	}


}
