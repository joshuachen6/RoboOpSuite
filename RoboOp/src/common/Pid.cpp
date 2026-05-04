#include "common/Pid.h"
#include <cmath>
#include <algorithm>
#include "common/time.h"

void PID::setCoefficients(double p, double i, double d) {
    this->p = p;
    this->i = i;
    this->d = d;
}

void PID::setMaxOutput(double maxOutput) {
    this->maxOutput = maxOutput;
}

double PID::update(double error) {
    double value = 0;
    double currentTime = getMillis() / 1000.0;
    
    if (lastTime >= 0) {
        double dt = currentTime - lastTime;
        if (dt > 0) {
            double de_dt = (error - lastError) / dt;
            accumulator += error * dt;
            
            // Basic anti-windup: clamp accumulator based on maxOutput
            if (std::abs(i) > 1e-9) {
                double iLimit = maxOutput / i;
                accumulator = std::clamp(accumulator, -iLimit, iLimit);
            }

            value = p * error + i * accumulator + d * de_dt;
        }
    }
    
    lastError = error;
    lastTime = currentTime;
    
    // Clamp final output
    return std::clamp(value, -maxOutput, maxOutput);
};
