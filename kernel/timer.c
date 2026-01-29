#include "kernel.h"

static unsigned int ticks = 0;

void timer_tick() {
    ticks++;
}

unsigned int timer_get_ticks() {
    return ticks;
}

