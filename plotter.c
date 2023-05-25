#include "plotter.h"
// global constants
#include <stdint.h>
// simulation vars
void sim_start() {
  // initialize time as pre-defined starting time
  t = TIME_START;
  // start rolling delta
  rolling_delta = DELTA_PER_STEP;
  // just set multiplier as 1 for now, unless user decides otherwise
  speed_mult = 1.0;
  // used to paused drawing
  paused = false;
  // setup the vertex array
  vertex_t vectex_array[ITERS * STEPS_PER_FRAME];
}

void sim_loop() {}
