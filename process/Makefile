## Simple SDL mini code
 
CC=gcc
 
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -w -Wall -Wextra  -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm
 
OBJ= anothernn.o utils.o pixel_operations.o matrix.o SDL_manip.o main_seg.o
DEP= ${OBJ:.o=.d}
 
all: main_seg
 
main_seg: ${OBJ}
 
clean:
	${RM} ${OBJ} ${DEP} *~
	${RM} main_seg return.bmp
 
-include ${DEP}
 
# END
