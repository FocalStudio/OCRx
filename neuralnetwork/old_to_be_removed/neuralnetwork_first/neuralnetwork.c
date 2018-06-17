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

double *dot_wb(Network *net, double *matrix)
{
	return 0;
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

//partial derivate
double* cost_derivate(double* outputactivation, double y, int lenarray)
{
	double *res = malloc(sizeof(double) * lenarray);
	for (int i = 0; i < lenarray; ++i)
	{
		res[i] = outputactivation[i] - y;
	} 
	return res;
}

/**
 *	Neural Network related function
 */

/**
 *	Neural Network initialisation and creation
 */

Network *init_network(int *size, int lensize)
{
	Network *net = malloc(sizeof(Network));
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

void LIBERER_DELIVRER(Network *net)
{
	free(net);
	/*
	free(net->size);
	free(net->biases);
	free(net->weight);*/
}

/**
 *	Neural Network  execution
 */

Bash *estimate(Bash *bash, double *weight, int *biases, int len)
{
	for (int i = 0; i < len; ++i)
	{
	//	bash = 	
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
	//	backpropagation(net, );
	}
}

double *feedforward(Network *net, double *a, double *res)
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
		b = bash[pos];
		bash[pos] = bash[len - i - 1];
		bash[len - i - 1] = b;
	}	
}

Bash* getBash(Bash *father, int start, int end)
{
	int len = start - end;
	Bash *b = malloc(sizeof(Bash) * len);

	for (int i = 0; i < len; ++i)
	{
		b[i] = father[i  + start];
	}

	return b;
}

double evaluate(Bash *trainingdata, int lentestdata, Network *net)
{
	double res;
	double **results = malloc(sizeof(double*) * len_test_data);
	double *result = malloc(sizeod(double) * net->min);
	for(int i = 0; i < lentestdata; ++i)
	{
		//FIXME should be numlayer
		results[i] = malloc(sizeof(double) * 2);
		feedforward(net, trainingdata[i].input, result);
		
	}
	return 0;
}

void SGD(Network *net, Bash *trainingdata, int lendata, int epoch, int mini_batch_size, Bash *testdata, int lentestdata)
{
	int n_test = lentestdata;
	int n = lendata;

	Bash **mini_batches = malloc(sizeof(double) * epoch * n);
	for (int i = 0; i < epoch; ++i)
	{
		shuffle(trainingdata, lendata);
		for (int k = 0; k < n; k += mini_batch_size)
		{
			//in python: mini_batches = [training_data[k:k+mini-batches for k in xrange...]]
			mini_batches[i + k] = getBash(trainingdata, k, k + mini_batch_size); 
		}	

		for (int j = 0; j < (n / mini_batch_size); ++j)
		{
			//TODO: update_mini_batch
		}

		if (lentestdata > 0)
		{
			printf("%d: %f / %zu\n", i, evaluate(testdata, lentestdata), n_test);	
		}
		else
		{
			printf("epoch is over");
		}
	}

	//return net; //maybe remove it
}

/**
 *	Backpropagation
 */

//if we want more than 3 layer we should modified this
void backpropagation(Network *net, double *x, double y)
{
	//TODO
	double *nabla_b = malloc(sizeof(double) * net->lenbiases);
	init_matrix(nabla_b, net->lenbiases);
	
	double *nabla_w = malloc(sizeof(double) * net->lenweight);	
	init_matrix(nabla_w, net->lenweight);

	//FIXME if we want more than 3 layer
	double *activation = malloc(sizeof(double) * net->min);
	for (int i = 0; i < net->min; ++i)
	{
		activation[i] = x[i];
	}
	double z;
	//FIXME if we want more than 3 layer
	double **activations = malloc(sizeof(double *) * 3);
	activations[0] = activation;
	//one for each layer
	double **zs = malloc(sizeof(double *) * net->layernumber);

       	zs[0] = dot_wb(net, activations[0]);
	//activations[1] = sigmoid_another(zs, FIXME);
	zs[1] = dot_wb(net, activations[1]);
	//activations[2] = sigmoid(net, activations[2]);
	
	//FIXME change the 2 to something dynamic
	double *delta = cost_derivate(activations[2], y, net->size[2]);

	for (int i = 0; i < net->size[2]; ++i)
	{
		delta[i] *= sigmoid_prime(zs[1][i]);
	}

	//FIXME here the 1 correspond to the hidden layer
	for (int i = net->size[1]; i < net->lenbiases; ++i)
	{
		nabla_b[i] = delta[i];
	}

	/*for (int i = 0; i < net->min; ++i)
	{
		z = dot_const(w, activation, net->min) + b;
		zs[i] = 


	}*/

	free(activation);
	free(activations);
	free(nabla_b);
	free(nabla_w);
		
}

