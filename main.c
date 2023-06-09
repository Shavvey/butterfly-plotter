#include "plotter.h"
#include "sdl.h"
/*WINDOW CONSTANTS*/
// define screen height, width, and animation ticks
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT (SCREEN_WIDTH)
/*SDL CONSTANTS*/
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;
// pixel buffer used for bitmap graphics
uint32_t *pixelbuffer;
// helper function to make text on SDL window

void make_text() {
  // this opens a font style and sets a size
  TTF_Font *font = TTF_OpenFont("OpenSans-Regular.ttf", 30);

  // this is the color in rgb format,
  // maxing out all would give you the color white,
  // and it will be your text's color
  SDL_Color font_color = {255, 255, 255};

  // as TTF_RenderText_Solid could only be used on
  // SDL_Surface then you have to create the surface first
  SDL_Surface *surface_message =
      TTF_RenderText_Solid(font, "Hello, World!", font_color);

  // now you can convert it into a texture
  SDL_Texture *message =
      SDL_CreateTextureFromSurface(renderer, surface_message);

  SDL_Rect message_rect; // create a rect
  message_rect.x = 50;   // controls the rect's x coordinate
  message_rect.y = 50;   // controls the rect's y coordinte
  message_rect.w = 100;  // controls the width of the rect
  message_rect.h = 100;  // controls the height of the rect

  // (0,0) is on the top left of the window/screen,
  // think a rect as the text's box,
  // that way it would be very simple to understand

  // Now since it's a texture, you have to put RenderCopy
  // in your game loop area, the area where the whole code executes

  // you put the renderer's name first, the Message,
  // the crop size (you can ignore this if you don't want
  // to dabble with cropping), and the rect which is the size
  // and coordinate of your texture
  SDL_RenderCopy(renderer, message, NULL, &message_rect);
  // destory surface and texture afterwards
  SDL_FreeSurface(surface_message);
  SDL_DestroyTexture(message);
}
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
  printf("Initialzing TTF engine\n");
  if (TTF_Init() < 0) {
    fprintf(stderr, "TTF could not be initialized\n");
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
  // quit of SDL engine, deinitializes everything!
  SDL_Quit();
  // do the same of TTF engine
  TTF_Quit();
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
    // draw();
    // makes the texture necessary for each frame of the screen!
    // this is a little inefficient, but oh well
    make_text();
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
  return EXIT_SUCCESS;
}
