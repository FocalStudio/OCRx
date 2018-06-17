#ifndef ANOTHERNN_H_
#define ANOTHERNN_H_
typedef struct Network Network;

struct Network
{
	double **weightih;
	double **weightho;
	size_t weightlen;

	double *biash;
	double *biaso;
	size_t biaseslen;

	char *path;
	
	int *sizes;
	size_t sizeslen;

	size_t layernumber;
};

Network *create_network(int *sizes, int sizeslen, int tru);

Network *initialize_weight(Network *net, char *file_to_load);

int process(struct Network *, double, double, double *, size_t);

//void SGD(Network *net, double, double, struct matrixBW **, size_t, struct matrixBW **, int);
//void SGD(Network *net, double eta, double alpha, struct matrixBW **m, size_t len, struct matrixBW **m2, int epoch);


int SGD22(Network *net, double eta, double alpha, struct matrixBW **training_data_bw, size_t training_data_len, struct matrixBW **expected_result_bw, int epoch);

#endif
