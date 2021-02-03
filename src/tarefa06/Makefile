CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: sala_de_espera

sala_de_espera: sala_de_espera.c
	gcc $(CFLAGS) sala_de_espera.c -o sala_de_espera $(LDFLAGS)

clean:
	rm -f sala_de_espera
