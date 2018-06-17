# include <stdio.h>
# include <stdlib.h>
# include "SDL/SDL.h"
# include "anothernn.h"
# include "rlsa.h"
# include "SDL_manip.h"
# include "pixel_operations.h"

int main() 
{

	int *sizes = malloc(sizeof(int) * 3);
	sizes[0] = 28 * 28;
	sizes[1] = 20;
	sizes[2] = 52;
	
	/*
	 *	1 = loading file
	 *	0 = creating new weight
	 */

	Network *net = create_network(sizes, 3, 0);

//	double *input  = malloc(sizeof(double) * 2);

//	int i = 0;
//	init_sdl();
	
	
	
	
	
	
	
	double **training_data = training_input();
	printf("%d\n", sizeof(training_data[0]));
	printf("%d\n", training_data[26][0]);





/**	double *tmp;
	for (int i = 0; i < 52; ++i) {
		tmp  = calloc(28 * 28 + 1, sizeof(double));
		for (int j = 0; j <= 28 * 28; ++j ) {
			tmp[j] = 0;
		}
		training_data[i] = tmp;
		//printf("%d\n", training_data[i][15]);
	}*/	
//	training_data = training_input();
	for (int i = 0; i < 28*28; ++i) {
		printf("%d", training_data[0][0] == 1);
		if (i % 28 == 0)
			printf("\n");
	}
/*
	for (int i = 0; i < 29; ++i) {
		for (int j = 0; j < 29; ++j) {
			printf("%d", training_data[i][j]);
		}
		printf("\n");
	}*/
/*	double **training_results = malloc(sizeof(double *) * 52);
	for (int i = 0; i < 52; ++i) {
		tmp = calloc(52, sizeof(double));
		for (int j = 0; j < 52; ++j) {
			tmp[j] = 0;
		}

		training_results[i] = tmp;
	}
	
	training_result();
*/
//	SGD(net, 0.9, 0.3, training_data, 2, training_results, 1000000);
	/*	input[0] = 0;
		input[1] = 0;
		i = process(net, 0.9, 0.3, input, 2);
		printf("0, 0: %d\n", i);	
		input[0] = 0;
		input[1] = 1;
		i = process(net, 0.9, 0.3, input, 2);
		printf("0, 1: %d\n", i);
		input[0] = 1;
		input[1] = 0;
		i = process(net, 0.9, 0.3, input, 2);
		printf("1, 0: %d\n", i);
		input[0] = 1;
		input[1] = 1;
		i = process(net, 0.9, 0.3, input, 2);
		printf("0, 0: %d\n", i);
	//SGD(net, 10000000, 0.9, 0.3);
	 */

	/*	init_sdl();
		SDL_Surface *img = load_image("img/letter/A_bigletter_Arial.png");

		convert_BW(img);

		struct matrixBW *mat = convertPicBW(img);
	 */	return 0;
}
