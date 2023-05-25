// plotter imports
#include <stdbool.h>
#include <stdint.h>
// globals for entire plotter
#define ITERS 800
#define STEPS_PER_FRAME 500
const double DELTA_PER_STEP = 1e-5;
const double DELTA_MIN = 1e-7;
// where the plot starts
const double TIME_START = -3.0;
const double TIME_END = 3.0;
// NOTE: I want parameters working, eventually, so im adding this now
#define NUM_PARAMS 18
// struct implementation
typedef struct color {
  uint32_t red;
  uint32_t green;
  uint32_t blue;
  uint32_t alpha;
} color_t;

typedef struct vector {
  double x; // x component of vector
  double y; // y component of vector
} vector_t;
typedef struct vertex {
  vector_t vector;
  color_t color;
} vertex_t;
// simulation vars, mutable vars that run the simulation
extern double t;
extern vector_t history[ITERS];
extern double speed_mult;
// eventually i want to start and stop the sim
extern bool paused;
// maybe add trail and dot type later on??
extern bool iteration_limit;
extern bool rolling_delta;
