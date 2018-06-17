//binarize.c



#include "binarize.h"



int* getHisto(SDL_Surface *img)
{
    Uint32 pixel;
    Uint8 r, g, b;
    int *histo = calloc(255, sizeof(int));
    for (int i = 0; i < img->w; ++i)
    {
        for (int j = 0; j < img->h; ++j)
        {
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            histo[r] += 1;
        }
    }
    return histo;
}
