//rlsa.c



//(j + i * cols)

#include "rlsa.h"

struct *matrixBW convertPicBW(SDL_Surface *img)
{
    Uint32 pixel;
    Uint8 = r, g, b;
    struct matrixBW *result = malloc(sizeof(struct matrixBW));
    result->height = img->h;
    result->width = img->w;
    result->data = malloc(sizeof(double) * img->h * img->w);
    for (int i = 0; i < img->w; ++i)
    {
        for (int j = 0; j < img->h; ++j)
        {
            pixel = getpixel(img, x, y);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            if (r == 255)
                result->data[j + i * result->height] = 0;
            else
                result->data[j + i * result->height] = 0;
        }
    }
    return result;
}
