# Compilers and options
CC=gcc
CPPFLAGS= -MMD
CFLAGS= -w -Wall -Wextra -std=c99 -pedantic -O2
#CFLAGS= -g
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm
 
SRC =  utils.c fifth.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}
 
all: fifth 
 
fifth: ${OBJ}
 
-include ${DEP}

#$(info WARNING, WARNING ARE IGNORED REMOVE -w OPTION)

clean:
	rm -f ${OBJ} ${DEP}
	rm -f fifth 
 
 # END
