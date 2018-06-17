//rlsa.h


#include <stdlib.h>
#include "SDL/SDL.h"
#include "pixel_operations.h"
#include "SDL_manip.h"


struct matrixBW
{
   size_t height, width;
   double *data;
};


struct matrixBW* convertPicBW(SDL_Surface *img);
