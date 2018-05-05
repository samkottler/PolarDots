run: main.c eventHandlers.h player.h game.h
	gcc -o run main.c -g -O3 -Wall -lm -std=gnu11 -fopenmp `pkg-config --libs --cflags gtk+-3.0`

.PHONY: clean
clean:
	rm -f run
