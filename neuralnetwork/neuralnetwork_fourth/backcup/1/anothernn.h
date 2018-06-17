typedef struct Network Network;

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
};

Network *create_network(int *sizes, int sizeslen, int tru);

Network *initialize_weight(Network *net, char *file_to_load);

int process(struct Network *, double, double, double *, size_t);

void SGD(Network *net, int epoch, double eta, double alpha);
