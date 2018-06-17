#Makefile
CC=gcc

CPPFLAGS= -MMD
CFLAGS= -Wall -Wextra  -std=c99 `pkg-config --cflags gtk+-3.0`
LDLIBS= -lm `pkg-config --libs gtk+-3.0`
LDFLAGS= $(PTHREAD) $(GTKLIB) -export-dynamic

SRC= interface.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}


all: interface

interface: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} *~ interface

-include ${DEP}

#END
