# include <SDL.h>
# include <SDL_image.h>
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

SDL_Surface* cut_char(SDL_Surface *img, int y);

int path(SDL_Surface *img, int x, int y);

int ver(SDL_Surface *img, int x, int y);

SDL_Surface* cut_text(SDL_Surface *img);

int redline(SDL_Surface *img, int x, int y);

int green(SDL_Surface *img, int x, int y);

void del_green(SDL_Surface *img, int y);

int blue(SDL_Surface *img, int x, int y);

int det_max(SDL_Surface *img,int y, int x);

int det_min(SDL_Surface *img,int y, int x);

void det_width(SDL_Surface *img,int y, int *x,int *coord1, int *coord2);

int min(int a, int b);

int max(int a, int b);

SDL_Surface* create_surf(int width, int height);

SDL_Surface* create(SDL_Surface *img, int coor1, int coor2, int y);

struct queue* cut_lines(SDL_Surface *img,int y, struct queue *q);

struct matrixBW* convert_SurMatr(SDL_Surface *img);

struct queue* create_queue(SDL_Surface *img);

void greyscale(SDL_Surface *img);

int getHisto(SDL_Surface *img, int* histo);

int getThreshold(int *histo, int total);

void otsu(SDL_Surface *img);