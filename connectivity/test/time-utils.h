#ifndef HEADER_TIME_UTILS_H
#define HEADER_TIME_UTILS_H

#include <time.h>

static inline double compute_used_cpu_time(clock_t start_time, clock_t end_time) {
    return ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
}

#endif // HEADER_TIME_UTILS_H