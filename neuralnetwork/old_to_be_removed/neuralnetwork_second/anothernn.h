typedef struct Network Network;

struct Network
{
	double **weightih;
	double **weightho;
	size_t weightlen;

	double *biases;
	size_t biaseslen;

	int *sizes;
	size_t sizeslen;

	size_t layernumber;
};
