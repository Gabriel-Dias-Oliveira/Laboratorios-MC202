CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: calculadora

calculadora: calculadora.c
	gcc $(CFLAGS) calculadora.c -o calculadora $(LDFLAGS)

clean:
	rm -f calculadora
