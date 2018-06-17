#include <SDL/SDL.h>
#include <math.h>
#include <SDL/SDL_rotozoom.h>
#include <stdlib.h>
#include <string.h>
#include "SDL_manip.h"

int main()
{
    init_sdl();
    SDL_Surface *img;
    SDL_Surface *screen;
    img = load_image("test.jpg");
    screen = display_image(img);
    SDL_FreeSurface(screen);

	float ratio = ((float)(28.0/(img->w)));

	SDL_Surface *img_resize = rotozoomSurface (img, 0, ratio, 1);

    screen = display_image(img_resize);

    return 0;
}
