# include "SDL_manip.h"
# include <err.h>
#include "matrix.h"

int main(int argc, char *argv[]) {
    if (argc != 2)
        errx(1,"wrong nb of arg");
    init_sdl();
    SDL_Surface *img;
    SDL_Surface *screen;
    img = load_image(argv[argc-1]);
    screen = display_image(img);
    SDL_FreeSurface(screen);
    otsu(img);
    screen = display_image(img);
    SDL_FreeSurface(screen);
    img = cut_text(img);
    screen = display_image(img);
    SDL_FreeSurface(screen);
    struct queue *q = create_queue(img);
    free(q);
    return 0;
}

// bon ceci est un test
