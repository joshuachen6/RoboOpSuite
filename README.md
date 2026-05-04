# RoboOpSuite

A comprehensive robotics toolkit for path planning, control, and visualization. This suite provides a high-performance C++ library for autonomous robot operations and a powerful GUI for path visualization and editing.

<img width="1627" height="1118" alt="Screenshot_20260504_081942" src="https://github.com/user-attachments/assets/356ac5d6-4522-49c5-af7c-a54bdcc4121b" />

## Project Structure

- **[RoboOp](./RoboOp)**: The core C++20 library. Includes quintic splines, trapezoidal motion profiles, PID controllers, and tank drive implementations.
- **[RoboOpVisualizer](./RoboOpVisualizer)**: An interactive GUI tool for designing and inspecting trajectories in real-time.

## Quick Start

This project uses [xmake](https://xmake.io) for its build system. xmake will automatically handle all dependencies (Eigen, ImGui, ImPlot, GLFW, etc.).

### Prerequisites
- [xmake](https://xmake.io/guide/installation)
- A C++20 compatible compiler (GCC 10+, Clang 10+, or MSVC 19.29+)

### Build Everything
```bash
# Clone the repository
git clone https://github.com/joshuachen6/RoboOpSuite.git
cd RoboOpSuite

# Build the entire suite
xmake
```

### Run the Visualizer
```bash
xmake run RoboOpVisualizer
```

### Run the Tests
```bash
xmake run RoboOpTest
```

## Features

- **Quintic Hermite Splines**: Smooth, $C^2$ continuous path generation with optimized arc-length parameterization.
- **Motion Profiling**: High-accuracy trapezoidal and triangular profiles for velocity control.
- **PID Control**: Robust controller with integral windup protection and output clamping.
- **Real-time Visualization**: Interactive graph with panning, zooming, and image overlays.
- **Seamless Integration**: Unified build system with manage-free dependencies.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
