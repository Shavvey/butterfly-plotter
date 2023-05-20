#include "plotter.h"
#include "screen.h"
/*WINDOW CONSTANTS*/
// define screen height, width, and animation ticks
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define NANO_PER_SEC 1000000000.0
/*SDL CONSTANTS*/
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;
// helper function to create window, renderer, and texture
void initialize_SDL() {
  printf("Initialzing Screen\n");
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL Could not be initialized! Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  window = SDL_CreateWindow("Butterfly Plotter", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                            SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("Window could not be created! Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  // create SDL renderer and texture
  // init renderer with hardware acceleration (GPU accelerated rendering)
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                              SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH,
                              SCREEN_HEIGHT);
}
// helper function to free memory allocated for window, renderer, and texture
void cleanup_SDL() {}
int main(int argc, char *argv[]) {
  initialize_SDL();
  return EXIT_SUCCESS;
}
