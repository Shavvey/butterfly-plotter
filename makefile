# using gcc for the compilier
CC=gcc
# using common compilier flags
CFLAGS=-W -Wall -g
# this tells the compilier where the sdl2 binaries are located
SDL_CFLAGS := $(shell sdl2-config --cflags) 
# tells linker what libraries to include
SDL_LDFLAGS := $(shell sdl2-config --libs)

PLOT = plotter.c plotter.h

all: main plotter

plotter.o: $(PLOT)
	$(CC) $(CFLAGS) -c plotter.c -lm

main: plotter.o plotter.h
	$(CC) $(CFLAGS) $(SDL_CFLAGS) main.c plotter.o -o butterfly-plotter $(SLD_LDFLAGS)
