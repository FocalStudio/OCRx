# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "anothernn.h"

int load(struct Network *net) 
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


int save(struct Network *net) 
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
