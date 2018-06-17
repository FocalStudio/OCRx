# include "utils.h"

void print_matrix (double **matrix, size_t lines, size_t cols) 
{
	for (size_t i = 0; i < lines; ++i) {
		for (size_t j = 0; j < cols; ++j) {
			printf("%d", (int)matrix[j + i * cols]);
		}

		printf("\n");
	}
}

double *result_c(char letter) 
{
	double *r = calloc(52, sizeof(double));

	/*
	 *	Convert char to expected result
	 */

	if (letter >= 'A' && letter <= 'Z')
		r[(int)(letter) - 65] = 1;
	else if (letter >= 'a' && letter <= 'z')
		r[(int)(letter) - 97 + 26] = 1;

	return r;
}

double **results()
{
	double **r = malloc(sizeof(double *) * 52);
	char caps = 'A';
	char min = 'Z';

	/*
	 *	Create a matrix of a result per letter
	 */

	for (int i = 0; i < 52; ++i) {
		if (i < 26) {
			r[i] = result_c(caps);
			++caps;
		} else {
			r[i] = result_c(min);
			++min;
		}
	}

	return r;
}

double *matrix_c(char *path)
{
	double *r = malloc(sizeof(double) * 28 * 28);

	FILE *file = fopen(path, "r");

	/**
	 *	From a file create the matrix
	 */

	if (file == NULL)
		printf("[Error]: FILE IS NULL");
	for (int i = 0, c; i < 29; ++i) {
		for (int j = 0; j < 29; ++j) {
			c = fgetc(file);
			if (c == 49) 
				r[j + i * 28] = 1;
			if (c == 48)
				r[j + i * 28] = 0;
		}
	}

	fclose(file);

	return r;
}

double **matrix()
{
	double **r = malloc(sizeof(double *) * 52);
	char caps_path[14] = "majs/0/00.txt\0";
	char mins_path[14] = "mins/0/00.txt\0";
	char caps = 'A';
	char min = 'a';
	char id = '0';

	for (int i = 0; i < 52; ++i) {
		if (i < 26) {
			caps_path[5] = caps;
			caps_path[7] = caps;
			caps_path[8] = id;
			r[i] = matrix_c(caps_path); 
			++caps;
		} else 	if (i < 26) {
			mins_path[5] = min;
			mins_path[7] = min;
			mins_path[8] = id;
			r[i] = matrix_c(mins_path);
			++min;
		}

	}

	return r;
}

/**int load(struct network *net)
{

	double *tmp;
	char *line = malloc(sizeof(char) * 15);
	FILE *weightih = fopen("weightih.ocrx", "r");
	for (int i = 0; i < net->sizes[0]; ++i) {
		tmp = malloc(sizeof(double) * net->sizes[1]);
		for (int j = 0; j < net->sizes[1]; ++j) {
			fgets(line, 15, weightih);
			strtok(line, "\n");
			tmp[j] = atof(line);
		}
		net->weightih[i] = tmp;
	}
	fclose(weightih);
	FILE *weightho = fopen("weightho.ocrx", "r");
	for (int i = 0; i < net->sizes[1]; ++i) {
		tmp = malloc(sizeof(double) * net->sizes[2]);
		for (int j = 0; j < net->sizes[2]; ++j) {
			fgets(line, 15, weightho);
			strtok(line, "\n");
			tmp[j] = atof(line);
		}
		net->weightho[i] = tmp;
	}
	fclose(weightho);

	return 1;
}


int save(struct network *net)
{
	FILE *weightih = fopen("weightih.ocrx", "ab+");
	FILE *weightho = fopen("weightho.ocrx", "ab+");

	for (int i = 0; i < net->sizes[0]; ++i) {
		for (int j = 0; j < net->sizes[1]; ++j) {
			fprintf(weightih, "%f\n", net->weightih[i][j]);
		}
	}

	for (int i = 0; i < net->sizes[1]; ++i) {
		for (int j = 0; j < net->sizes[2]; ++j) {
			fprintf(weightho, "%f\n", net->weightho[i][j]);
		}
	}

	fclose(weightih);
	fclose(weightho);

	return 1;
}

int init(struct network)
{
	for (int i = 0; i < sizes[0]; ++i) {

		//	printf("%d\n", i);
		tmp = malloc(sizeof(double) * sizes[1]);

		for (int j = 0; j < sizes[1]; ++j) {
			tmp[j] = ((double)rand()/(double)RAND_MAX);
		}	

		net->weightih[i] = tmp;	
	}	
	printf("[Info]: Initializing weightho...\n");
	for (int i = 0; i < sizes[1]; ++i) {
		tmp = malloc(sizeof(double) * sizes[2]);
		for (int j = 0; j < sizes[2]; ++j) {
			tmp[j] = ((double)rand()/(double)RAND_MAX);
		}

		net->weightho[i] = tmp;
	}

	return 1;
}*/
