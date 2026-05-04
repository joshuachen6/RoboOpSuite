#include "pathing/Spline.h"
#include "common/calc.h"
#include <cmath>

static double evaluatePolynomial(const Vector6d& coeffs, double t) {
    // Horner's method: a*t^5 + b*t^4 + c*t^3 + d*t^2 + e*t + f
    return ((((coeffs[0] * t + coeffs[1]) * t + coeffs[2]) * t + coeffs[3]) * t + coeffs[4]) * t + coeffs[5];
}

static double evaluateDerivative(const Vector6d& coeffs, double t) {
    // 5*a*t^4 + 4*b*t^3 + 3*c*t^2 + 2*d*t + e
    return (((5 * coeffs[0] * t + 4 * coeffs[1]) * t + 3 * coeffs[2]) * t + 2 * coeffs[3]) * t + coeffs[4];
}

double Spline::arcLength(double start, double end) const {
    return std::abs(integrate(start, end, [&](double t){
        double dx = evaluateDerivative(xCoefficients, t);
        double dy = evaluateDerivative(yCoefficients, t);
        return std::sqrt(dx * dx + dy * dy);
    }, 200));
}

double Spline::tangent(double t) const {
    return std::atan2(evaluateDerivative(yCoefficients, t), evaluateDerivative(xCoefficients, t));
}

Eigen::Vector2d Spline::get(double t) const {
    return {
        evaluatePolynomial(xCoefficients, t),
        evaluatePolynomial(yCoefficients, t)
    };
}

Pose2d Spline::poseByArcLength(double length) const {
    if (length <= 0) return {get(0), tangent(0)};
    if (length >= this->length) return {get(1), tangent(1)};

    // Binary search for t such that arcLength(0, t) == length
    double low = 0, high = 1;
    for (int i = 0; i < 15; i++) { // 15 iterations give plenty of precision
        double mid = (low + high) / 2.0;
        if (arcLength(0, mid) < length) {
            low = mid;
        } else {
            high = mid;
        }
    }
    double t = (low + high) / 2.0;
    return {get(t), tangent(t)};
}


Spline SplineFactory::makeSpline(Vector6d xCoefficients, Vector6d yCoefficients, Pose2d start, Pose2d end) {
    Spline spline = {xCoefficients, yCoefficients, start, end, 0};
    spline.length = spline.arcLength(0, 1);
    return spline;
}

Spline SplineFactory::makeSpline(Pose2d start, Pose2d end) {
    Eigen::Matrix<double, 6, 6> A;
    A << 0, 0, 0, 0, 0, 1,
         1, 1, 1, 1, 1, 1,
         0, 0, 0, 0, 1, 0,
         5, 4, 3, 2, 1, 0,
         0, 0, 0, 2, 0, 0,
         20, 12, 6, 2, 0, 0;

    // We can tune the "tightness" of the spline by scaling the velocity vectors.
    // For now, we use the distance between points as a heuristic for velocity magnitude.
    double d = (end.position - start.position).norm();
    if (d < 1e-6) d = 1.0;

    Vector6d bx = {start.position.x(), end.position.x(), std::cos(start.rotation) * d, std::cos(end.rotation) * d, 0, 0};
    Vector6d by = {start.position.y(), end.position.y(), std::sin(start.rotation) * d, std::sin(end.rotation) * d, 0, 0};

    auto solver = A.colPivHouseholderQr();
    Vector6d xCoefficients = solver.solve(bx);
    Vector6d yCoefficients = solver.solve(by);

    return makeSpline(xCoefficients, yCoefficients, start, end);
}

Spline SplineFactory::makeSpline(const Spline& start, Pose2d end){ 
    return makeSpline(start.end, end);
}
