
#ifndef FRAMES_H // Guardas de inclusão

#define FRAMES_H

#include "pico/stdlib.h"

#define NUM_PIXELS 25

double frame[25] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0
    };

double seta_1[25] = {
        0.0, 0.0, 0.2, 0.0, 0.0,
        0.0, 0.2, 0.2, 0.0, 0.0,
        0.2, 0.2, 0.2, 0.2, 0.2,
        0.0, 0.2, 0.2, 0.0, 0.0,
        0.0, 0.0, 0.2, 0.0, 0.0
    };

    double seta_2[25] = {
        0.0, 0.0, 0.2, 0.0, 0.0,
        0.0, 0.0, 0.2, 0.2, 0.0,
        0.2, 0.2, 0.2, 0.2, 0.2,
        0.0, 0.0, 0.2, 0.2, 0.0,
        0.0, 0.0, 0.2, 0.0, 0.0
    };
    



double* leds[3] = {frame, seta_1, seta_2 };

#endif