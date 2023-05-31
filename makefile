# using gcc for the compilier
CC=gcc
# using common compilier flags
CFLAGS=-W -Wall -g
# this tells the compilier where the sdl2 binaries are located
SDL_CFLAGS := $(shell sdl2-config --cflags)
# tells linker what libraries to include
SDL_LDFLAGS := $(shell sdl2-config --libs) -lm -lSDL2 -lSDL2_ttf
# plotter source files
PLOT = plotter.c plotter.h
# dependencies for final executable
DEPS = main.c plotter.o SDL_FontCache.o
CACHE = SDL_FontCache/SDL_FontCache.c SDL_FontCache/SDL_FontCache.h include/SDL2/SDL_ttf.h
# executable name
EXEC = butterfly-plotter
#make these targets: main and plotter.o
all: main plotter.o SDL_FontCache.o

#make object file, do not run linker yet
plotter.o: $(PLOT)
	$(CC) $(CFLAGS) -c $(PLOT)

SDL_FontCache.o: $(CACHE)
	$(CC) $(CFLAGS) -c $(CACHE)

#make final executable
main: $(DEPS)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) $(DEPS) -o $(EXEC) $(SDL_LDFLAGS)

#.PHONY rule ensures make doesn't use clean as a file
.PHONY : clean

#cleans out object files and final executable
clean: 
	rm $(EXEC) *.o
