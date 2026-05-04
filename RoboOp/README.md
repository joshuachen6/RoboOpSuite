# RoboOp Library

The core high-performance library for autonomous robot operation, focusing on path generation and control systems.

## 🚀 Installation

This library is part of the **RoboOpSuite** and uses [xmake](https://xmake.io).

### As part of the Suite
Build from the root directory:
```bash
xmake
```

### Build Library & Tests only
```bash
xmake build RoboOp RoboOpTest
xmake run RoboOpTest
```

## 🛠 Features

### 1. Quintic Hermite Splines
Generate smooth, $C^2$ continuous paths with optimized arc-length parameterization.
- **Optimized Evaluation**: Uses Horner's method for efficient polynomial calculation.
- **Accurate Arc Length**: Implements Simpson's Rule for precise numerical integration.
- **Binary Search Lookup**: Fast $O(\log n)$ pose-by-distance lookups.

```cpp
auto trajectory = TrajectoryBuilderFactory::create({Vector2d(0, 0), 0})
    .to({Vector2d(10, 10), M_PI/4})
    .build();

Pose2d pose = trajectory->getPose(5.0); // Get pose at 5 units along the path
```

### 2. Motion Profiling
Highly accurate trapezoidal and triangular profiles.
- Handles distance-constrained peak velocities.
- Continuous position and velocity calculation.

### 3. PID Control
Industrial-grade PID implementation.
- **Anti-Windup**: Clamped accumulator to prevent integral overshoot.
- **Output Clamping**: Built-in safety limits.
- **Time-Scaled**: Derivative and integral terms are scaled by real delta-time.

### 4. Drive Controllers
- **Tank Drive**: Standard differential drive implementation.
- **Ramsete**: Advanced nonlinear path-following controller (Experimental).

## 📚 Dependencies
- **Eigen**: High-performance linear algebra library (managed by xmake).
- **Catch2**: Unit testing framework (managed by xmake).

## 🗺 Roadmap
- [ ] Improved Odometry & Localization.
- [ ] Pure Pursuit controller.
- [ ] Support for Mecanum/Swerve drives.
