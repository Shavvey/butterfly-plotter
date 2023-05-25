/*IMPORTS*/
#include <stdbool.h>
#include <stdint.h>
/*GLOBAL VARS*/
// globals for entire plotter
#define ITERS 800
#define STEPS_PER_FRAME 500
// NOTE: I want parameters working, eventually, so im adding this now
#define NUM_PARAMS 18
/*STRUCT IMPLEMENATION*/
typedef struct color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} color_t;

typedef struct vector {
  float x; // x component of vector
  float y; // y component of vector
} vector_t;
typedef struct vertex {
  // each vertex has a vector component
  vector_t vector;
  // and a color component
  color_t color;
} vertex_t;
// simulation vars, mutable vars that run the simulation
extern double t;
extern vector_t history[ITERS];
extern vertex_t vertex_array[ITERS * STEPS_PER_FRAME];
extern double speed_mult;
// eventually i want to start and stop the sim
extern bool paused;
// maybe add trail and dot type later on??
extern bool iteration_limit;
extern bool rolling_delta;
/*FUNCTION PROTOTYPING*/
void sim_start();
void sim_loop();
