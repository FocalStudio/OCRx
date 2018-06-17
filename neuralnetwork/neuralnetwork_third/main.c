#include <stdlib.h>
#include <stdio.h>
# include "network.h"
int xor();

int main()
{
	xor();
	return 0;
}
/*
int letter(int layer_amount, int image_x, int image_y)
{
	int *sizes = malloc(sizeof(int) * layer_amount);
	sizes[0] = image_x * image_y;
	sizes[1] = 28;
	sizes[2] = 28;
	sizes[3] = 57;
	
	Network = create_network(sizes, 4, NULL);
	SGD(net, 10000, 0.1, 0.9);

}
*/
int xor()
{
	int *sizes = malloc(sizeof(int) * 3);
	sizes[0] = 2;
	sizes[1] = 2;
	sizes[2] = 1;
	struct network *net = create_network(sizes, 3, NULL);
//	Network *net = create_network(sizes, 3, NULL);
//	printf("weightho:	%d\n", net->weightho[1][2]);
	//SGD(net, 100000, 0.1, 0.9);
	printf("Done!\n");
	return 0;
}
