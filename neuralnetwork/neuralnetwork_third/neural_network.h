/*typedef struct Network Network;

struct Network
{
	double **weightih;
	double **weightho;
	size_t weightlen;

	double *biases;
	size_t biaseslen;

	char *path;
	
	int *sizes;
	size_t sizeslen;

	size_t layernumber;
};*/


Network *initialize_weight(Network *net, char *file_to_load);

void SGD(Network *net, int epoch, double eta, double alpha);
