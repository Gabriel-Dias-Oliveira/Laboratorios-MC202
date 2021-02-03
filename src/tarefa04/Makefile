CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: seaofwords

seaofwords: seaofwords.c
	gcc $(CFLAGS) seaofwords.c -o seaofwords $(LDFLAGS)

clean:
	rm -f seaofwords
