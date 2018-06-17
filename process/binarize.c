//binarize.c



#include "binarize.h"




void greyscale(SDL_Surface *img)
{
    Uint32 pixel;
    Uint8 r, g, b, Lum;
    for (int i = 0; i < img->w; ++i)
    {
        for (int j = 0; j < img->h; ++j)
        {
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            Lum = (r + g + b) / 3;
            putpixel(img, i, j, SDL_MapRGB(img->format, Lum, Lum, Lum));
        }
    }
}



int getHisto(SDL_Surface *img, int* histo)
{
    Uint32 pixel;
    Uint8 r, g, b;
    int result = 0;
    for (int i = 0; i < img->w; ++i)
    {
        for (int j = 0; j < img->h; ++j)
        {
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            histo[r] += 1;
            result++;
        }
    }
    return result;
}


int getThreshold(int *hist, int total)
{
    double q1 = 0, q2 = 0, m1 = 0, m2 = 0, w1 = 0, w2 = 0;
    double sum1 = 0, sum2 = 0, between = 0, max = 0;
    int pos = 0;
    for (int i = 0; i < 256; ++i)
    {
        sum1 += hist[i];
        sum2 += hist[256 - i];
        w1 = sum1/ total;
        w2 = sum2 / total;
        q1 += i * hist[i];
        q2 += (256 - i) * hist[256 - i];
        m1 = q1 / sum1;
        m2 = q2 / sum2;
        between = w1 * w2 * (m1 - m2) * (m1 - m2);
        if (between > max)
        {
            max = between;
            pos = i;
        }

    }
    return pos;
} 

void otsu(SDL_Surface *img)
{
    greyscale(img);
    int *histo = calloc(256, sizeof(int));
    int total = getHisto(img, histo);
    int pos = getThreshold(histo, total);
    Uint32 pixel;
    Uint8 r, g, b;
    for (int i = 0; i < img->w; ++i)
    {
        for (int j = 0; j < img->h; ++j)
        {
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            if (r > pos)
                putpixel(img, i, j, SDL_MapRGB(img->format, 255,255,255));
            else
                putpixel(img, i, j, SDL_MapRGB(img->format, 0,0,0));

        }
    }
}
