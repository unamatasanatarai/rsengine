#include <unistd.h>
#include <sys/time.h>
#include "loop.h"

const unsigned long NANOSECOND  = 1000000000;
const unsigned long MICROSECOND = 1000000;
const unsigned long MILLISECOND = 1000;

unsigned int fps = 60;
unsigned int fps_delay = 16666;
unsigned long tick = 0;

short running = 0;

struct timespec time_start, time_now;

void rs_fps(int n){
    fps = n;
    fps_delay = (unsigned int)(MICROSECOND / fps);
}

unsigned long get_time(){
    return time_now.tv_nsec + time_now.tv_sec * NANOSECOND;
}

unsigned long update_time(){
    clock_gettime(CLOCK_MONOTONIC_RAW, &time_now);
    return get_time();
}

// return time since start in MILLISECONDS
unsigned long rs_get_tick(){
    return tick;
}

unsigned int get_elapsed(){
    unsigned long s = get_time();
    unsigned long e = update_time();
    return (unsigned int)((e-s)/MILLISECOND);
}

void align_fps(){
    unsigned int elapsed = fps_delay - get_elapsed();
    if (elapsed > 0){
        usleep(elapsed);
    }
}

void rs_stop(){
    running = 0;
}

void rs_start(){
    running = 1;
    clock_gettime(CLOCK_MONOTONIC_RAW, &time_start);
    while(running){
        update_time();
        rs_main();
        tick++;
        align_fps();
    }
}
