# include "SDL/SDL.h"
# include "SDL/SDL_image.h"
# include <err.h>
#include <stdio.h>
# include <stdlib.h>


void wait_for_keypressed(void);

void init_sdl(void);

SDL_Surface* load_image(char *path);

SDL_Surface* display_image(SDL_Surface *img);

SDL_Surface* convert_BW(SDL_Surface *img);

int line_detect(SDL_Surface *img, int y);

SDL_Surface* horizontalLine (SDL_Surface *img, int coord);

SDL_Surface* verticalLine (SDL_Surface *img, int x,int y);

SDL_Surface* cutchar (SDL_Surface *img);




