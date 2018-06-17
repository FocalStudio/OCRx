# include "SDL_manip.h"
# include <err.h>
# include "matrix.h"
# include "nn.h"
# include "anothernn.h"
# include "utils.h"

int main(int argc, char *argv[]) {
    int *sizes = malloc(sizeof(int) * 3);
    sizes[0] = 28 * 28;
    sizes[1] = 20;
    sizes[2] = 52;

	Network *net = create_network(sizes, 3, 1);

    struct matrixBW **matrix = malloc(sizeof(struct matrixBW *));
    training_matrix(matrix);

    struct matrixBW **r = malloc(sizeof(struct matrixBW *));
    training_matrix_result(r);
    
    printf("[Info]: Starting segmentation...\n");
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
    
    char *s = calloc(200, sizeof(char));
    int i = 0;
	int c = 0;

    printf("[Info]: Running neural network...\n");
    struct matrixBW *m, *n;
    while (!queue_is_empty(q)) {
    	m = queue_pop(q);
    	if (m == NULL) 
		s[i] = ' ';
	else 
	{
		c =  process(net, 0.3, 0.2, m->data, 28 * 28);
		if (c < 26)
			s[i] = 'A' + c;
		else if (c < 52) 
			s[i] = 'a' + c - 26;
	}
	++i;
    }

    printf("%s\n", s);
    free(q);
    return 0;
}
