# RoboOpVisualizer

An interactive GUI tool for designing, inspecting, and generating code for robot trajectories.

![Visualizer](https://github.com/user-attachments/assets/05924ffa-f4d6-416a-916b-234c3aeed642)

## 🚀 Getting Started

The visualizer is part of the **RoboOpSuite** and is built using [xmake](https://xmake.io).

### Installation
From the suite root:
```bash
xmake build RoboOpVisualizer
xmake run RoboOpVisualizer
```

## 🛠 Features

### Interactive Path Editor
- **Real-time Graphing**: View paths instantly as you modify control points.
- **Overlay Support**: Load field images or reference maps (PNG/JPG) using SOIL2.
- **Dynamic Panning/Zooming**: Navigate complex paths with mouse controls.

### Trajectory Management
- Add, remove, and reorder path segments.
- Control entry/exit angles (Quintic Hermite Splines).
- Preview motion along the path.

### Code Generation
- Export your designed paths directly to C++ code compatible with the `RoboOp` library.

### Modern Interface
- **Dockable Windows**: Powered by Dear ImGui, allowing for custom workspace layouts.
- **High-Performance Plotting**: Uses ImPlot for smooth rendering of dense trajectory data.

## 📚 Dependencies
All dependencies are automatically managed by xmake:
- **RoboOp**: The underlying math & trajectory library.
- **Dear ImGui**: For the docking-enabled user interface.
- **ImPlot**: For advanced 2D plotting.
- **GLFW/OpenGL3**: For cross-platform windowing and rendering.
- **SOIL2**: For image loading.

## 📖 Usage
1. **Menus**: Use the `Tools` menu to open the Trajectory Manager, Graph, and Code Generator.
2. **Graph**: Use `Scroll` to zoom and `Right Click + Drag` to pan.
3. **Paths**: Update coordinates and rotations in the Trajectory Manager to see the path update live.
