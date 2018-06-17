// library


# include "pixel_operations.h"
# include "SDL_manip.h"
# include "matrix.h"

//END library

//Function

//wait for key

SDL_Surface* create_surf(int width, int height){
	SDL_Surface *surface;
    Uint32 rmask, gmask, bmask, amask;

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    	rmask = 0xff000000;
    	gmask = 0x00ff0000;
    	bmask = 0x0000ff00;
    	amask = 0x000000ff;
	#else
    	rmask = 0x000000ff;
    	gmask = 0x0000ff00;
    	bmask = 0x00ff0000;
    	amask = 0xff000000;
	#endif

    surface = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
    if (surface == NULL) {
        exit(1);
    }
    return surface;
}

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
    int height = img->h;
    int notfound = 1;
    int notend = 1;
    Uint8 r, g, b;
    Uint32 pixel;
    while (notfound || notend){
    	if (y == height -1)
    		return y;
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
    return y;
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

void del_green(SDL_Surface *img, int y){
	int width = img->w;
    Uint8 r, g, b;
    Uint32 pixel;
    for(int x = 0;x<width;x++){
    	pixel = getpixel(img,x,y-1);
    	SDL_GetRGB(pixel,img->format, &r,&g,&b);
    	if (r == 0 && g == 255 && b == 0){
    		for(int j = y-1; !redline(img,x,j);j--){
    			putpixel(img,x,j,SDL_MapRGB(img->format,0,0,255));
    			for(int i = -1;i <2;i++){
    				if (green(img,x+i,j-1))
    					x = x+i;
    			}
    		}
    	}
    }
}

int redline(SDL_Surface *img, int x, int y){
	Uint8 r, g, b;
    Uint32 pixel;
    pixel = getpixel(img,x,y);
    SDL_GetRGB(pixel,img->format, &r,&g,&b);
    if (r == 255 && g == 0 && b == 0)
    	return 1;
    return 0;
}

int green(SDL_Surface *img, int x, int y){
	Uint8 r, g, b;
    Uint32 pixel;
    pixel = getpixel(img,x,y);
    SDL_GetRGB(pixel,img->format, &r,&g,&b);
    if (r == 0 && g == 255 && b == 0)
    	return 1;
    return 0;
}

int blue(SDL_Surface *img, int x, int y){
	Uint8 r, g, b;
    Uint32 pixel;
    pixel = getpixel(img,x,y);
    SDL_GetRGB(pixel,img->format, &r,&g,&b);
    if (r == 0 && g == 0 && b == 255)
    	return 1;
    return 0;
}

int black(SDL_Surface *img, int x, int y){
	Uint8 r, g, b;
    Uint32 pixel;
    pixel = getpixel(img,x,y);
    SDL_GetRGB(pixel,img->format, &r,&g,&b);
    if (r == 0 && g == 0 && b == 0)
    	return 1;
    return 0;
}

SDL_Surface* cut_text(SDL_Surface *img){
    int height = img->h;
    int width = img->w;
    int y = 0;
    y = line_detect(img, y);
    horizontalLine(img,0);
    int cnt = 0;
    while(y != height-1){
    	horizontalLine(img,y);
    	y = line_detect(img,y);
    	cnt++;
    }
    horizontalLine(img,y);
    for (int j = 0; j < height-1; j++){
    	if(redline(img,0,j))
    		cut_char(img,j);
    }
    for (int j = 1; j < height-1; j++)
    	if(redline(img, 0, j)){
    		del_green(img,j);
    	}
    for(int x = 0; x < width; x++){
    	for(int y = 0; y < height; y++){
    		if(x == width-1)
    			putpixel(img,x,y,SDL_MapRGB(img->format,0,0,255));
    		if(green(img,x,y))
    			putpixel(img,x,y,SDL_MapRGB(img->format,255,255,255));
    	}
    }
    return img;
}

int max(int a, int b){
	if (a>b)
		return a;
	return b;
}

int min(int a, int b){
	if (a<b)
		return a;
	return b;
}

int det_max(SDL_Surface *img,int y,int x){
	int i =x;
	int ma = i;
	for(int j = y;!redline(img,0,j);j++){
		i = x;
		for (;!blue(img,i,j);)
			i++;
		ma = max(i,ma);
	}
	return ma;
}

int det_min(SDL_Surface *img,int y, int x){
	int i = x;
	int mi = det_max(img,y,x);
	for(int j = y;!redline(img,0,j);j++){
		i = x;
		for (;!blue(img,i,j);)
			i++;
		mi = min(i,mi);
	}
	return mi;
}

void det_width(SDL_Surface *img, int y, int *x, int *coor1 , int *coor2){
	int min1 = det_min(img, y, *x);
	int max1 = det_max(img,y , *x);
	*x = max1 + 1;
	*coor1 = min1-1;
	int max2 = det_max(img,y ,*x);
	*coor2 = max2+1;
}

SDL_Surface* create(SDL_Surface *img, int coor1, int coor2, int y){
  int height = 0;
  for(int j= y; !redline(img,0,j);j++)
  	height++;
  int width = coor2-coor1;
  SDL_Surface *res = create_surf(width, height);
  int in = 0;
  int y1 = 0;
  for(int j = y; !redline(img,0,j);j++){
  	int x = 0;
  	for(int i = coor1; i < coor2; i++){
  		if(blue(img,i,j)){
  			if(in)
  				in = 0;
  			else
  				in = 1;
  			putpixel(res,x,y1,SDL_MapRGB(res->format,255,255,255));
  		}
  		if(black(img,i,j)){
  			if(in)
  				putpixel(res,x,y1,SDL_MapRGB(res->format,0,0,0));
  			else
  				putpixel(res,x,y1,SDL_MapRGB(res->format,255,255,255));
  		}
  		else{
  			putpixel(res,x,y1,SDL_MapRGB(res->format,255,255,255));
  		}
  		x++;
  	}
  	y1 ++;
  }
  return res;
}

size_t cnt_white(struct matrixBW *mt){
    size_t cnt = 0;
    int white = 1;
    for(size_t j = mt->cols-1; j > 0; j--){
        for(size_t i = 0; i < mt->line; i++){
            if (*(mt->data + j +i*mt->cols)){
                white = 0;
                break;
            }
        }
        if(!white)
            break;
        cnt ++;
    }
    return cnt;
}

struct matrixBW* cut_mat(struct matrixBW *mt, int y){
    struct matrixBW *new = newMatrix(mt->line,mt->cols - y);
    for(size_t i = 0; i<new->line; i++){
        for(size_t j = 0; j<new->cols; j++){
            *(new->data + j + i*new->cols) = *(mt->data + j + i*mt->cols);
        }
    }
    return new;
}

struct queue* cut_lines(SDL_Surface *img,int y, struct queue *q){
	int width = img->w;
	int coor1,coor2,x;
	SDL_Surface *res;
	coor1 = 0;
	coor2 = 0;
	x = 0;
	for(;;){
		det_width(img,y, &x, &coor1, &coor2);
		if (x > width-1)
			break;
		res = create(img,coor1,coor2,y);
		struct matrixBW* tmp = convert_SurMatr(res);
        size_t y = cnt_white(tmp);
        if(y > (tmp->cols/4)){
            queue_push(q,NULL);
            tmp = cut_mat(tmp,y);
            if (tmp->cols < 3){
                freeMatrix(tmp);
                continue;
            }
        }
        tmp = resizeMatrix(tmp);
        queue_push(q,tmp);
		//SDL_Surface *screen;
		//screen = display_image(res);
		freeMatrix(tmp);
		//SDL_FreeSurface(screen);
	}
    return q;
}

struct matrixBW* convert_SurMatr(SDL_Surface *img){
	struct matrixBW *new = newMatrix(img->h,img->w);
	for(int i = 0; i < img->h; i++){
		for (int j = 0; j < img->w;j++){
			if(black(img,j,i))
				*(new->data + j + i*img->w) = 1;
			else
				*(new->data + j + i*img->w) = 0;
		}
	}
	return new;
}

struct queue* create_queue(SDL_Surface *img){
    struct queue *q = malloc(sizeof(struct queue));
    queue_init(q);
    for(int y = 0;y < img->h-5; y++){
        if(redline(img,0,y))
            q = cut_lines(img, y +1,q);
    }
    return q;
}



// Binarize


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
