#pragma once

#include <utility>

static constexpr double H_STEP = 0.01;

template<typename T>
double integrate(double start, double end, T function, int steps = 100) {
    if (steps % 2 != 0) steps++; // Simpson's rule requires even steps
    
    double h = (end - start) / steps;
    double sum = function(start) + function(end);
    
    for (int i = 1; i < steps; i++) {
        double x = start + i * h;
        if (i % 2 == 0) {
            sum += 2 * function(x);
        } else {
            sum += 4 * function(x);
        }
    }
    
    return sum * h / 3.0;
}
