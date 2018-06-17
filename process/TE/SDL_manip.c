// library


# include "pixel_operations.h"
# include "SDL_manip.h"
#include "SDL_rotozoom.h"

//END library

//Function

//wait for key

void wait_for_keypressed(void) {
    SDL_Event             event;
    // Infinite loop, waiting for event
    for (;;) {
        // Take an event
        SDL_PollEvent( &event );
        // Switch on event type
        switch (event.type) {
            // Someone pressed a key -> leave the function
            case SDL_KEYDOWN: return;
            default: break;
        }
        // Loop until we got the expected event
    }
}

//INI SDL

void init_sdl(void) {
    // Init only the video part
    if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
        // If it fails, die with an error message
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
    }
    // We don't really need a function for that ...
}

//Load Image

SDL_Surface* load_image(char *path) {
    SDL_Surface          *img;
    // Load an image using SDL_image with format detection
    img = IMG_Load(path);
    if (!img)
        // If it fails, die with an error message
        errx(3, "can't load %s: %s", path, IMG_GetError());
    return img;
}

//display

SDL_Surface* display_image(SDL_Surface *img) {
    SDL_Surface          *screen;
    // Set the window to the same size as the image
    screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
    if ( screen == NULL ) {
        // error management
        errx(1, "Couldn't set %dx%d video mode: %s\n",
                img->w, img->h, SDL_GetError());
    }

    /* Blit onto the screen surface */
    if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    // Update the screen
    SDL_UpdateRect(screen, 0, 0, img->w, img->h);

    // wait for a key
    wait_for_keypressed();

    // return the screen for further uses
    return screen;
}

SDL_Surface* convert_BW(SDL_Surface *img){
    int width = img->w;
    int height = img->h;
    for (int x = 0; x < width;x++){
        for (int y = 0; y<height; y++){
            Uint8 r, g, b, Lum;
            Uint32 pixel;
            pixel = getpixel(img,x,y);
            SDL_GetRGB(pixel,img->format, &r,&g,&b);
            Lum = (r + g + b) / 3;
            if(Lum > 175)
                Lum = 255;
            else
                Lum = 0;
            putpixel(img,x,y,SDL_MapRGB(img->format,Lum,Lum,Lum)); 
        }
    }
    return img;
}


SDL_Surface* horizontalLine (SDL_Surface *img, int coord)
{
    Uint8 r, blank;
    r = 255;
    blank = 0;
    for(int i = 0; i < img->w; ++i)
    {
        putpixel(img,i,coord,SDL_MapRGB(img->format,r,blank,blank));
    }
    return img;
}

SDL_Surface* verticalLine (SDL_Surface *img, int x,int y)
{
    Uint8 b ,r, g, blank;
    Uint32 pixel;
    g = 255;
    blank = 0;
    for (int yco = y; yco < img->h; yco++)
    {
        pixel = getpixel(img,x,yco);
        SDL_GetRGB(pixel,img->format, &r,&g,&b);
        if (r == 255 && g ==0 && b ==0)
            break;
        putpixel(img, x, yco,SDL_MapRGB(img->format,blank,g,blank));
    }
    return img;
}

// distance between lines

int line_detect(SDL_Surface *img, int y){
    int width = img->w;
    int notfound = 1;
    int notend = 1;
    Uint8 r, g, b;
    Uint32 pixel;
    while (notfound || notend){
        for (int x = 0; x < width; x++){
            pixel = getpixel(img,x,y);
            SDL_GetRGB(pixel,img->format, &r,&g,&b);
            if (r == 0 && g == 0 && b == 0){  //black pixel
                notfound = 0;
                break;
            }
            if (notend && notfound == 0 && x == width -1)  //white pixel + end of line 
                notend = 0;
        }
        if (notfound || notend)
            y += 1;
    }
    return y + 1;
}

//cut char

SDL_Surface* cutchar (SDL_Surface *img){
    int width = img->w;
    int height = img->h;
    Uint8 r, g, b;
    Uint32 pixel;
    for (int y = 0; y < height; y++){ // find a line 
        pixel = getpixel(img,0,y);
        SDL_GetRGB(pixel,img->format, &r,&g,&b);
        if (r == 255 && g == 0 && b == 0){ // start of cut
            int notchar = 1;
            for (int i = 0; i < width; i++){
                int white = 1;
                for (int j = y+1; j < height; j++){ // travel through the line
                    pixel = getpixel(img,i,j);
                    SDL_GetRGB(pixel,img->format, &r,&g,&b);
                    if (r == 0 && g == 0 && b ==0){ //black pixel
                        white = 0;
                        if (notchar){ // char found
                            notchar = 0;
                            img = verticalLine(img, i-1,y+1);
                            break;
                        }
                    }
                    else if (r == 255 && g == 0 && b == 0){ // end of line
                        if (notchar == 0 && white){ // end of cut of 1 char
                            notchar = 1;
                            img = verticalLine(img, i+1,y+1);
                        }
                        break;
                    }
                }
            }	
        }
    }
    return img;
}

SDL_Surface* cut_char(SDL_Surface *img, int y){
   int width = img->w;
   Uint8 r, g, b;
   Uint32 pixel;
   int redline = 1;
   int cnt = 0;
   for( int j = y+1; redline; j++){
    pixel = getpixel(img,0,j);
    SDL_GetRGB(pixel,img->format, &r,&g,&b);
    if (r == 255 && g == 0 && b == 0)
      redline = 0;
    cnt ++;
   }
   cnt += y;
   for (int i = 0; i < width; i++){
     int white = 1;
     for (int j = y+1; j < cnt; j++){
       pixel = getpixel(img,i,j);
       SDL_GetRGB(pixel,img->format, &r,&g,&b);
       if (r == 255 && g == 255 && b == 255)
         putpixel(img,i,j,SDL_MapRGB(img->format,0,255,0));
       else if (r == 0 && g == 0 && b == 0){
         white = 0;
         if(!ver(img,i,j-1))
            for(int d = j-1;d > y; d--)
                putpixel(img,i,d,SDL_MapRGB(img->format,255,255,255));
         else {
            putpixel(img,i,j-1,SDL_MapRGB(img->format,255,255,255));
            if(!path(img,i,j-1))
                for(int d = j-1;d > y; d--)
                    putpixel(img,i,d,SDL_MapRGB(img->format,255,255,255));
         }
         break;
       }
     }
     if (white)
       for(int d = cnt-1;d > y; d--)
         putpixel(img,i,d,SDL_MapRGB(img->format,255,255,255));
   }
   int ct = 1;
   for (int i = 0; i < width; i++){
    pixel = getpixel(img,i,y+1);
    SDL_GetRGB(pixel,img->format, &r,&g,&b);
    if( r == 0 && g == 255 && b == 0){
        if (ct % 2 == 0)
            for (int j = y+1;g == 255; j++){
                pixel = getpixel(img,i,j);
                SDL_GetRGB(pixel,img->format, &r,&g,&b);
                putpixel(img,i,j,SDL_MapRGB(img->format,255,255,255));
        }
        ct ++;
    }
   }
   printf("%d\n", ct);
   return img;
}


int path(SDL_Surface *img, int x, int y){
    Uint8 r, g, b;
    Uint32 pixel;
    pixel = getpixel(img,x,y);
    SDL_GetRGB(pixel,img->format, &r,&g,&b);
    if (r == 255 && g == 0 && b == 0)
        return 1;
    if (r == 0 && g == 0 && b == 0)
        return 0;
    if (r == 0 && g == 255 && b == 0)
        return 0;
    if (r == 254 && g == 254 && b == 254)
        return 0;
    else{
        printf("%d , %d\n", x, y);
        putpixel(img,x,y,SDL_MapRGB(img->format,0,255,0));
        if (path(img,x,y+1)){
            return 1;
        }
        else if (path(img,x+1,y+1)){
            return 1;
        }
        else if (path (img,x-1,y+1)){
            return 1;
        }
        else{
            printf("bonjour\n");
            putpixel(img,x,y,SDL_MapRGB(img->format,254,254,254));
            return 0;
        }
    }
}

int ver(SDL_Surface *img, int x, int y){
    Uint8 Gr, Gg, Gb;
    Uint8 Dr, Dg, Db;
    Uint32 pixel;
    pixel = getpixel(img,x+1,y);
    SDL_GetRGB(pixel,img->format, &Dr,&Dg,&Db);
    pixel = getpixel(img,x-1,y);
    SDL_GetRGB(pixel,img->format, &Gr,&Gg,&Gb);
    if ((Gr == 255 && Gg == 255 && Gb == 255) || (Dr == 255 && Dg == 255 && Db == 255)){
        pixel = getpixel(img,x+1,y+1);
        SDL_GetRGB(pixel,img->format, &Dr,&Dg,&Db);
        pixel = getpixel(img,x-1,y+1);
        SDL_GetRGB(pixel,img->format, &Gr,&Gg,&Gb);
        if ((Gr == 255 && Gg == 255 && Gb == 255) || (Dr == 255 && Dg == 255 && Db == 255))
            return 1;
    }
    return 0;
}