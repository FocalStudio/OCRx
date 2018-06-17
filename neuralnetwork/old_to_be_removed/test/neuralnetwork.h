/**
 * 	Network struct
 */

typedef struct Network Network;
struct Network
{
	int layernumber;
	int *size;
	int layersize;
	double *biases;
	int lenbiases;
	double *weight;
	int lenweight;
	int min;
};

typedef struct Bash Bash;
struct Bash
{
	double *input;
	double res;
};

/**
 *	Logical function  
 */

int xor(int a, int b);

int and(int a, int b);

int nand(int a, int b);
