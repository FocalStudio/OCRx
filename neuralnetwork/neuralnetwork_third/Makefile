# Compilers and options
CC=gcc
CPPFLAGS= -MMD
CFLAGS= -Wall -Wextra -std=c99 -pedantic -O2
#CFLAGS= -g
LDFLAGS=
LDLIBS= -lm
 
SRC = neural_network.c main.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}
 
all: main
 
main: ${OBJ}
 
-include ${DEP}

#$(info WARNING, WARNING ARE IGNORED REMOVE -w OPTION)

clean:
	rm -f ${OBJ} ${DEP}
	rm -f main
 
 # END
