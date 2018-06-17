//rlsa.h


#include <stdlib.h>
#include <SDL.h>
#include "pixel_operations.h"



struct matrixBW
{
   size_t height, width;
   double *data;
};


struct matrixBW* convertPicBW(SDL_Surface *img);
