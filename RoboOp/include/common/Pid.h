#pragma once
class PID {
private:
  double p, i, d;
  double accumulator;
  double lastError;
  double lastTime;
  double maxOutput;

public:
  PID(double p = 0, double i = 0, double d = 0, double maxOutput = 1.0) 
    : p{p}, i{i}, d{d}, accumulator{0}, lastError{0}, lastTime{-1}, maxOutput{maxOutput} {}
  void setCoefficients(double p, double i, double d);
  void setMaxOutput(double maxOutput);
  double update(double error);
};