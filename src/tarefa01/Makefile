CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: megasena 

megasena: megasena.c
	gcc $(CFLAGS) megasena.c -o megasena $(LDFLAGS)

clean:
	rm -f megasena