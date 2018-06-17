//matrix.c


#include "matrix.h"
#include "SDL_rotozoom.h"


struct matrixBW* newMatrix(size_t w, size_t h)
{
    struct matrixBW *result = malloc(sizeof(struct matrixBW));
    result->height = h;
    result->width = w;
    result->data = malloc(sizeof(double) * w * h);
    return result;
}


void freeMatrix(struct matrixBW *matrix)
{
    free(matrix->data);
    free(matrix);
}


struct matrixBW* pictureToMatrix(SDL_Surface *img)
{
   
    Uint32 pixel;
    Uint8 r, g, b;
    struct matrixBW *result = newMatrix(img->w, img->h);
    for (int i = 0; i < img->w; ++i)
    {
        for (int j = 0; j < img->h; ++j)
        {
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            if (r == 255)
                result->data[j + i * result->height] = 0;
            else
                result->data[j + i * result->height] = 1;
        }
    }
    return result;
}

void matrixToPicture(SDL_Surface *img, struct matrixBW *matrix)
{
    Uint8 grey;
    for (int i = 0; i < img->w; ++i)
    {
        for (int j = 0; j < img->h; ++j)
        {
            if (matrix->data[j + i * img->h] == 0)
                grey = 255;
            else
                grey =0;
            putpixel(img, i, j, SDL_MapRGB(img->format, grey, grey, grey));
        }
    }
}

