CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: fakenews

fakenews: fakenews.c
	gcc $(CFLAGS) fakenews.c -o fakenews $(LDFLAGS)

clean:
	rm -f fakenews
