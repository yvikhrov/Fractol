#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

typedef struct  s_timer
{
    uint64_t    _start;
    uint64_t    _current;
    uint64_t    current_time;
    uint64_t    numer;
    uint64_t    denom;
    double        time;
    double        old_time;
}               t_timer;

void        init_timer(t_timer *timer);
double        get_delta_time(t_timer *timer);

#endif
