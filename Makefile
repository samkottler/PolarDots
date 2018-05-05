run: main.c controlPanel.h eventHandlers.h solid.h vector.h
	gcc -o run main.c -g -O3 -Wall -lm -std=gnu11 -fopenmp `pkg-config --libs --cflags gtk+-3.0`

.PHONY: clean
clean:
	rm -f run
