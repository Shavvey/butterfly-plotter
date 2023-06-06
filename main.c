#include "plotter.h"
#include "screen.h"
/*WINDOW CONSTANTS*/
// define screen height, width, and animation ticks
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
/*SDL CONSTANTS*/
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;
// pixel buffer used for bitmap graphics
uint32_t *pixelbuffer;
TTF_Font *font;
// helper function to make text on SDL window
void make_text() {}
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
  renderer = SDL_CreateRenderer(window, 1, SDL_RENDERER_ACCELERATED);
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                              SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH,
                              SCREEN_HEIGHT);
  // creating the pixel buffer used to update texturer and window
  pixelbuffer = malloc(sizeof(uint32_t) * SCREEN_HEIGHT * SCREEN_WIDTH);
  // color information is representing by a 32 bit unsigned integer, we
  // initialized the pixel buffer to be black
  memset(pixelbuffer, 0x00, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));
}
// helper function to free memory allocated for window, renderer, and texture
void cleanup_SDL() {
  if (texture) {
    SDL_DestroyTexture(texture);
  }
  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }
  if (window) {
    SDL_DestroyWindow(window);
  }
  SDL_Quit();
}
void draw() {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderDrawLineF(renderer, 10.0, 10.0, 90.0, 90.0);
}
// SDL event loop helper function
// First, we update the texture based on pixelbuffer
// Then, we poll for keyboards event and execute commands accordingly
// Lastly, we load the texture into the renderer
void event_loop_SDL() {
  // main loop of SDL window
  int ended = 0;
  SDL_Event event;
  while (!ended) {
    SDL_UpdateTexture(texture, NULL, pixelbuffer,
                      SCREEN_WIDTH * sizeof(uint32_t));
    // poll for SDL Events
    while (SDL_PollEvent(&event)) {
      // polling for different events inside SDL
      switch (event.type) {
      case SDL_KEYDOWN:
        break;
        // quits out of window
      case SDL_QUIT:
        ended = 1;
        break;
      }
      // listen for keyboard input do action accordingly
      switch (event.key.keysym.sym) {}
      // initialize sim and do main loop for it, provided by plotter.c
      sim_start();
    }
    SDL_RenderClear(renderer);
    // this updates the renderer based on a texture, used by pixelbuffer
    // sets the background to be black
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    draw();
    SDL_RenderPresent(renderer);
    // present the renderer window after loading the texture into the renderer
  }
}
int main(int argc, char *argv[]) {
  // init window, renderer, and texturer
  initialize_SDL();
  // poll for SDL events and keyboard inputs
  event_loop_SDL();
  // cleanup memory allocated to SDL
  cleanup_SDL();
  // printf("Number of args: %d\n", argc);
  return EXIT_SUCCESS;
}
