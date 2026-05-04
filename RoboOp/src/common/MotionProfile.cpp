#include "common/MotionProfile.h"
#include <cmath>
#include <algorithm>

double MotionProfile::getX(double t) const {
    double distance = std::abs(end - start);
    if (distance < 1e-9) return start;
    
    double accelDist = (maxVelocity * maxVelocity) / (2.0 * maxAcceleration);
    double cruiseDist, tAccel, tCruise, tTotal;
    double actualMaxVel;

    if (2.0 * accelDist <= distance) {
        // Trapezoidal
        actualMaxVel = maxVelocity;
        tAccel = maxVelocity / maxAcceleration;
        cruiseDist = distance - 2.0 * accelDist;
        tCruise = cruiseDist / maxVelocity;
    } else {
        // Triangular
        actualMaxVel = std::sqrt(distance * maxAcceleration);
        tAccel = actualMaxVel / maxAcceleration;
        tCruise = 0;
    }
    tTotal = 2.0 * tAccel + tCruise;

    if (t < 0) return start;
    if (t > tTotal) return end;

    double relativeX;
    if (t < tAccel) {
        relativeX = 0.5 * maxAcceleration * t * t;
    } else if (t < tAccel + tCruise) {
        relativeX = 0.5 * maxAcceleration * tAccel * tAccel + actualMaxVel * (t - tAccel);
    } else {
        double tDecel = t - tAccel - tCruise;
        relativeX = distance - 0.5 * maxAcceleration * (tTotal - t) * (tTotal - t);
    }

    return (end > start) ? (start + relativeX) : (start - relativeX);
}

double MotionProfile::getDuration() const {
    double distance = std::abs(end - start);
    if (distance < 1e-9) return 0;

    double accelDist = (maxVelocity * maxVelocity) / (2.0 * maxAcceleration);
    if (2.0 * accelDist <= distance) {
        // Trapezoidal
        double tAccel = maxVelocity / maxAcceleration;
        double cruiseDist = distance - 2.0 * accelDist;
        return 2.0 * tAccel + (cruiseDist / maxVelocity);
    } else {
        // Triangular
        double actualMaxVel = std::sqrt(distance * maxAcceleration);
        return 2.0 * (actualMaxVel / maxAcceleration);
    }
}
