struct network {
	size_t *sizes;
	size_t len_sizes;

	double **weightih;
	double **weightho;

	double *delta_weightih;
	double *delta_weightho;

	double eta;
	double alpha;

	double *bias_output;
	double *bias_hidden;

	double *hidden;
	double *output;

	double error;

	char *result;
}

int SGD(struct network, double **, double **);
