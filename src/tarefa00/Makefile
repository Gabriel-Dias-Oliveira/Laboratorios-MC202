CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: bomdia boanoite

bomdia: bomdia.c
	gcc $(CFLAGS) bomdia.c -o bomdia $(LDFLAGS)

boanoite: boanoite.c
	gcc $(CFLAGS) boanoite.c -o boanoite $(LDFLAGS)

clean:
	rm -f bomdia boanoite