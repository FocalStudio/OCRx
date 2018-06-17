# include "utils.h"
# include "fifth.h"

int main() {
	double **a = matrix();
	print_matrix(a, 28, 28);
	return 0;
}
/**
int engage(int epoch, int eta, int alpha) {
	printf("[Info]: Initializing network...\n");

	size_t *sizes = malloc(sizeof(double) * 3);
	sizes[0] = 28 * 28;
	sizes[1] = 20;
	sizes[2] = 56;
	
	struct network net = init_network(sizes, 3, eta, alpha);
	
	double **expected_results = results();
	double **training_data = matrix();
	
	char i;

	printf("[Info]: Launching training...\n");

	for (size_t e = 0; e < epoch; ++e) {
		i = 0;
		for (int l = 0; l < 52; ++l) {
			SGD(net, training_data[l], expected_results[l]);	
		}

		if (e % 100 == 0)
			printf("Epoch %d: error = %f\n", e, net->error);

		if (net->error < 0.00004 && net->error != 0.0)
			break;
		net->error = 0.0;
	}

	printf("[Info]: Training sucess.\n[Info]: Saving...\n");
	save(net);
	printf("[Info]: Data saved, exiting...\n");

	return 1;
}*/
