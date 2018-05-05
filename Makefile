polarDots: main.c eventHandlers.h player.h game.h
	gcc -o polarDots main.c -g -O3 -Wall -lm `pkg-config --libs --cflags gtk+-3.0`

.PHONY: clean
clean:
	rm -f polarDots
