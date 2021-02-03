CFLAGS = -std=c99 -Wall -Werror -O2 -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: mensageiro

mensageiro: mensageiro.c
	gcc $(CFLAGS) -c arvore.c $(LDFLAGS)
	gcc $(CFLAGS) -c mensageiro.c $(LDFLAGS)
	gcc $(CFLAGS) -o mensageiro mensageiro.o arvore.o $(LDFLAGS)
clean:
	rm -f mensageiro
	rm -f *.o
