#include "timer.h"
#include <mach/mach_time.h>

void        init_timer(t_timer *timer)
{
    mach_timebase_info_data_t coeff;

    mach_timebase_info(&coeff);
    timer->numer = coeff.numer;
    timer->denom = coeff.denom;
    timer->current_time = 0;
    timer->_start = mach_absolute_time();
    timer->_current = timer->_start;
    timer->time = 0.0;
    timer->old_time = 0.0;
}

double        get_delta_time(t_timer *timer)
{
    double delta_time;

    timer->_current = mach_absolute_time() - timer->_start;
    timer->current_time = timer->_current * timer->numer / timer->denom;
    timer->time = (double)(timer->current_time / 1000) / 1000000.0;
    delta_time = timer->time - timer->old_time;
    timer->old_time = timer->time;
    return (delta_time);
}
