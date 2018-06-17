## Simple SDL mini code
 
CC=gcc
 
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra  -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lSDL_gfx
 
OBJ= pixel_operations.o main_test.o SDL_manip.o matrix.o binarize.o
DEP= ${OBJ:.o=.d}
 
all: main_test
 
main_test: ${OBJ}
 
clean:
	${RM} ${OBJ} ${DEP} *~
	${RM} main_test return.bmp
 
-include ${DEP}
 
# END
