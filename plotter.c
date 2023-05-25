#include "plotter.h"
// global constants
#include <stdint.h>

const double DELTA_PER_STEP = 1e-5;
const double DELTA_MIN = 1e-7;
// where the plot starts
const double TIME_START = -3.0;
const double TIME_END = 3.0;
// simulation vars
void sim_start() {
  // initialize time as pre-defined starting time
  double t = TIME_START;
  // start rolling delta
  double rolling_delta = DELTA_PER_STEP;
  // just set multiplier as 1 for now, unless user decides otherwise
  double speed_mult = 1.0;
  // used to paused drawing
  bool paused = false;
  // setup the vertex array
}

void sim_loop() {}
