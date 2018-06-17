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
	sizes[0] = 2;
	sizes[1] = 3;
	sizes[2] = 1;
	Network *net = create_network(sizes, 3, 0);

	double *input  = malloc(sizeof(double) * 2);
	
	int i = 0;



	double **training_data =  malloc(sizeof(double *) * 4);//{{0, 0}, {0, 1}, {1, 0}, {1, 1}};//malloc(sizeof(double *) * sizes[0]);
	double **e = malloc(sizeof(double *) * 4);//{{0}, {1}, {1}, {0}};//malloc(sizeof(double *) * sizes[2]);
	
	size_t data_len = 4;

	for (int i = 0; i < data_len; ++i) {
		training_data[i] = malloc(sizeof(double) * 2);		
		e[i] = malloc(sizeof(double) * 2); 		
	}
	
	e[0][0] = 0;
	e[0][1] = 0;	

	e[1][0] = 1;
	e[1][1] = 0;
	
	e[2][0] = 0;
	e[2][1] = 1;
	
	e[3][0] = 1;
	e[3][1] = 1;
	
	training_data[0][0] = 0; 
	training_data[1][0] = 1; 
	training_data[2][0] = 1; 
	training_data[3][0] = 0; 

	SGD(net, 0.9, 0.3, e, 4, training_data, 10000000);

	input[0] = 0;
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


/*	init_sdl();
	SDL_Surface *img = load_image("img/letter/A_bigletter_Arial.png");

	convert_BW(img);

	struct matrixBW *mat = convertPicBW(img);
*/	return 0;
}
