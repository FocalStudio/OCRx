# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "matrix.h"
# include "anothernn.h"
# include "SDL_manip.h"

double *matrixFromFile(char *filename)
{
	double *matrix = malloc(sizeof(double) * 28 * 28);
	FILE *file = fopen(filename,"r");

	if(file == NULL)
		printf("[Error]: File is NULL \n");
	//if (matrix[index] == NULL)
	//	printf("[Error]: matrix is NULL\n");
	else {
		int c = 0;
		for(int i = 0, sum = 0; i < 29 && c != 42; ++i) {
			for (int j = 0; j < 29 && c !=42; ++j) {
				c = fgetc(file);
				if (feof(file)) {
					c = 42;
					printf("%d -- %d -- %d -- %s\n", i, j, sum, filename);
				}
				if(c == 49) {
					matrix[j + 28 * i] = 1;
				}
				else {//if(c == '0') {
					matrix[j + 28 * i] = 0;
				}
				}	

				sum += 28;
			}
			fclose(file);
		}
		return matrix;
		//SDL_Surface *img = load_image(filename);
		//struct matrixBW *m = pictureToMatrix(img);
		//double *matrix = m->data;
		return matrix;


	}

	double **training_result() 
	{
		double **result = malloc(sizeof(double *) * 52);

		for (int i = 0; i < 26; ++i) {
			//result[i] = calloc(52, sizeof(double));
			//result[i + 26] = calloc(52, sizeof(double));
			result[i][i] = 'A' + 26;
			result[i + 26][i + 26] = 'a' + 26;
		}

		return result;
	}

	double **training_input() 
	{
		char majs_path[14] = "majs/0/00.txt";
		char mins_path[14] = "mins/0/00.txt";

		char maj = 'A';
		char min = 'a';
		char count = '0';

		double **matrix = (double **)malloc(sizeof(double *) * 52);

		for(int i = 0; i < 52; ++i) {
		//	printf("%d", i);
		//	matrix[i] = (double *) malloc(sizeof(double) *28);
			if(i < 26 * 1) {
				majs_path[5] = maj;
				majs_path[7] = maj;
				majs_path[8] = count;

				matrix[i] = matrixFromFile(majs_path);
				++maj;

			} else if(i >= 26 * 1) {

				mins_path[5] = min;
				mins_path[7] = min;
				mins_path[8] = count;

				matrix[i] = matrixFromFile(mins_path);
				++min;

			}
		}

		printf("[Info]: Loading files finished !%d\n", matrix[26][0]);
		printf("%d\n", sizeof(matrix[0]));
		return matrix;
	}



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
