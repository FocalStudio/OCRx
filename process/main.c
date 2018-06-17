# include <stdio.h>
# include <stdlib.h>
# include "SDL/SDL.h"
# include "utils.h"
# include "anothernn.h"
# include "rlsa.h"
# include "SDL_manip.h"
# include "pixel_operations.h"
# include "nn.h"

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

	Network *net = create_network(sizes, 3,1 );

//	double *input  = malloc(sizeof(double) * 2);

//	int i = 0;
	//init_sdl();
	
	
	
	
	
	struct matrixBW **matrix = malloc(sizeof(struct matrixBW *));	
	training_matrix(matrix);	
/*	for (int i = 0; i < 29; ++i) {
		for (int j = 0; j < 29; ++j) {
			printf("%d", matrix[2]->data[j + i * 28] == 1);
		}

		printf("\n");
	}*/

	struct matrixBW **r = malloc(sizeof(struct matrixBW *));
	training_matrix_result(r);
	/*for (int i = 0; i < 29; ++i) {
		//for (int j = 0; j < 29; ++j) {
			printf("%f\n", r[2]->data[i]);
		//}

		//printf("\n");
	}*/
	//SGD2(net, 0.9, 0.5, matrix, 52, r, 50000);
	for (int i = 0, c; i < 52; ++i) {
		printf("%d\n", i);
		c = process(net, 0.3, 0.5, matrix[i]->data, 28*28);
//		printf("%d -- %d", i, c);
	}

	
	
	/*	input[0] = 0;
		input[1] = 0;
		i = process(net, 0.9, 0.3, input, 2);
		printf("0, 0: %d\n", i);	
		input[0] = 0;
		input[1] = 1;
		i = process(net, 0.9, 0.3, input, 2);
		printf("0, 1:Â %d\n", i);
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
