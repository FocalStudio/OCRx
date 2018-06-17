#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "neuralnetwork.h"

/**
 *	Logical function
 */

int xor(int a, int b)
{
	return a != b;
}

int and(int a, int b)
{
	return a && b;
}

int nand(int a, int b)
{
	return !(a && b);
}

/**
 *	Utilities functions
 */

double sigmoid(double z)
{
	return 1 / (1 + exp(-z));
}

double sigmoid_prime(double z)
{
	return sigmoid(z) / (1 - sigmoid(z));
}

double dot_const(double k, double *array, int arraylen)
{
	double res = 0;

	for (int i = 0; i < arraylen; ++i)
	{
		res += *(array + i) * k;
	}

	return res;
}

double delta(double a, double y)
{
	return a - y;
}

void init_matrix(double *start, int len)
{
	for (int i = 0; i < len; ++i)
	{
		start[i] = 0;
	}
}

/**
 *	Neural Network related function
 */

/**
 *	Neural Network initialisation and creation
 */

Network init_network(Network *net, int *size, int lensize)
{
	net->size = size;
	net->layernumber = 3;

	net->lenbiases = size[1] + size[2]; //we admit that there is only one hidden layer 
	net->biases = malloc(sizeof(double) * net->lenbiases);
	for (int i = 0; i < net->lenbiases; ++i)
	{
		/**
		 *	since RAND_MAX is the max value for a random number the
		 *	following calcul will return a number between 0 and 1
		 */
		net->biases[i] = (double)rand() / (double) RAND_MAX; 
	}

	net->weight = malloc(sizeof(double) * net->lenweight);
	net->weight = size[0] * size[1] + size[1] * size[2]; //product of each layer
	for (int i = 0; i < net->lenweight; ++i)
	{
		net->weight[i] = (double)rand() / (double) RAND_MAX;
	}

	net->min = net->lenbiases > net->lenweight ? net->lenweight : net->lenbiases;

	return net;
}

void LIBERER_DELIVRER(Network net)
{
	free(net->size);
	free(net->biases);
	free(net->weight);
}

/**
 *	Neural Network  execution
 */

Bash estimate(Bash *bash, double *weight, int *biases, int len)
{
	for (int i = 0; i < len; ++i)
	{
		bash = 	
	}

	return bash;
}

Bash update_mini_batch(Network *net, Bash *bash, int lenbash, double eta, Bash *res)
{
	double *nabla_b = malloc(sizeof(double) * net->lenbiases);
	init_matrix(nabla_b, net->lenbiases);

	double *nabla_w = malloc(sizeof(double) * net->lenweight);
	init_matrix(nabla_w, net->lenweight);

	double *delta_b = malloc(sizeof(double) * net->lenbiases);
	init_matrix(delta_b, net->lenbiases);

	double *delta_w = malloc(sizeof(double) * net->lenweight);
	init_matrix(delta_w, net->lenweight);

	for (int i = 0; i < lenbash; ++i)
	{
		backpropagation(net, );
	}
}

double feedforward(Network net, double *a, double *res)
{
	double tmp;
	for (size_t i = 0; i < net->min; ++i)
	{
		tmp = dot_const(net->weight[i], a, net->min); 
		res[i] = sigmoid(tmp + net->biases[i]);
	}

	return a;
}


/**
 *	SGD
 */

void shuffle(Bash *bash, int len)
{
	srand(time(NULL));
	Bash b;
	for (int i = 0, pos; i < len - 1; ++i)
	{
		pos = rand() % (len - 1 - i);
		tmp = bash[pos];
		bash[pos] = bash[len - i - 1];
		bash[len - i - 1] = tmp;
	}	
}

Bash* getBash(Bash father, int start, int end)
{
	int len = start - end;
	Bash b = malloc(sizeof(Bash) * len);

	for (int i = 0; i < len; ++i)
	{
		b[i] = father[i  + start];
	}

	return b;
}

Network SGD(Network *net, Bash *trainingdata, int lendata, int epoch, int mini_batch_size, Bash *testdata, int lentestdata)
{
	int n_test = lentestdata;
	int n = lendata;

	Bash **mini_batches = malloc(sizeof(double) * epoch * n);
	for (int i = 0; i < epoch; ++i)
	{
		shuffle(trainingdata, lendata);
		for (int k = 0; k < n; k + = mini_batch_size)
		{
			//in python: mini_batches = [training_data[k:k+mini-batches for k in xrange...]]
			mini_batches[i + k] = getBash(trainingdata, k, k + mini_batch_size); 
		}	

		for (int j = 0; j < (n / mini_batch_size); ++j)
		{
			//TODO: update_mini_batch
		}

		if (test_data)
		{
			printf("%d: %f / %zu\n", i, evaluate(test_data, lentestdata), n_test);	
		}
		else
		{
			printf("epoch is over");
		}
	}

	return net; //maybe remove it
}

/**
 *	Backpropagation
 */

void backpropagation(Network *net, double *x, double y)
{
	//TODO
	double *nabla_b = malloc(sizeof(double) * net->lenbiases);
	init_matrix(nabla_b, net.lenbiases);
	
	double *nabla_w = malloc(sizeof(double) * net->lenweight);	
	init_matrix(nabla_w, net->lenweight);

	double *activation = malloc(sizeof(double) * net->min);
	for (int i = 0; i < net->min; ++i)
	{
		activation[i] = x[i];
	}
	double z;
	double **activations = malloc(sizeof(*double) * net->min);
	activations[0] = activation;
	double **zs = malloc(sizeof(*double) * net->min);
	for (int i = 0; i < net->min; ++i)
	{
		z = dot(w, activations);

	}

	free(activation);
	free(activations);
	free(nabla_b);
	free(nabla_h);
	
		
}

