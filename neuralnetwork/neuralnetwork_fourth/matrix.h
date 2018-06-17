//matrix.h


#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL_manip.h"
#include "pixel_operations.h"



struct matrixBW
{
    size_t height, width;
    double *data;
};


struct matrixBW* newMatrix(size_t, size_t );

void freeMatrix(struct matrixBW*);

struct matrixBW* pictureToMatrix(SDL_Surface*);

void matrixToPicture(SDL_Surface *img, struct matrixBW*);
