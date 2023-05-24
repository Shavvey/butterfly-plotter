#include "plotter.h"
// global constants
#include <stdint.h>
const int NUM_PARAMS = 18;
const int ITERS = 800;
const int STEPS_PER_FRAME = 500;
const double DELTA_PER_STEP = 1e-5;
const double DELTA_MIN = 1e-7;
// where the plot starts
const double TIME_START = -3.0;
const double TIME_END = 3.0;
