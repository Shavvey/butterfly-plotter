# using gcc for the compilier
CC=gcc
# using common compilier flags
CFLAGS=-W -Wall -g
# this tells the compilier where the sdl2 binaries are located
SDL_CFLAGS := $(shell sdl2-config --cflags) 
# tells linker what libraries to include
SDL_LDFLAGS := $(shell sdl2-config --libs) -lm
# plotter source files
PLOT = plotter.c plotter.h
# dependencies for final executable
DEPS = main.c plotter.o
# executable name
EXEC = butterfly-plotter
#make these targets: main and plotter.o
all: main plotter.o

#make object file, do not run linker yet
plotter.o: $(PLOT)
	$(CC) $(CFLAGS) -c $(PLOT)

#make final executable
main: plotter.o plotter.h
	$(CC) $(CFLAGS) $(SDL_CFLAGS) $(DEPS) -o $(EXEC) $(SDL_LDFLAGS)

#.PHONY rule ensures make doesn't use clean as a file
.PHONY : clean

#cleans out object files and final executable
clean: 
	rm $(EXEC) *.o
