//binarize.h
#pragma once 


#include <stdlib.h>
#include "SDL_manip.h"
#include "pixel_operations.h"



void greyscale(SDL_Surface *img);

int getHisto(SDL_Surface *img, int* histo);

int getThreshold(int *histo, int total);

void otsu(SDL_Surface *img);
