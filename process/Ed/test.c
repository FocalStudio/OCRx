#include "pixel_operations.h"


void line_detect(SDL_Surface *img, int *yco){
  int width = img->w;
  int notfound = 1;
  int notend = 1;
  while (notfound){
  	for (int x = 0; x < width; x++){
  		Uint r, g, b, pixel;
  		pixel = getpixel(img,x,y);
		SDL_GetRGB(pixel,img->format, &r,&g,&b);
  		if (r == 255 && g == 255 && b == 255){
 			notfound = 0;
  			break;
  		}
  	}
  	if (notfound)
  		*yco++;
  }
  while (notend){
  	for (int x = 0; x < width; x++){
                Uint r, g, b, pixel;
                pixel = getpixel(img,x,y);
                SDL_GetRGB(pixel,img->format, &r,&g,&b);
                if (r == 0 && g == 0 && b == 0){
                        notend = 0;
  			break;
                }
  	if (notend)
                *yco++;
  	}
  }
}
