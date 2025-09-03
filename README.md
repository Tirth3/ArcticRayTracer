# C++ Ray Tracing Engine

A simple ray tracing engine written in C++, based on [*Ray Tracing in One Weekend*](https://raytracing.github.io/books/RayTracingInOneWeekend.html) by Peter Shirley. This version includes **multithreading** for faster rendering.

---

## Features

- Core ray tracing functionality:
  - Spheres, materials, and reflections
  - Lambertian, Metal, and Dielectric materials
  - Camera system with depth of field
- Outputs images in `.ppm` format
- **Multithreaded rendering** for improved performance
- Configurable scene setup

---

## Requirements

- C++17 or higher  
- Modern C++ compiler (g++, clang++, MSVC)

---

## Build Instructions

```bash
# Clone the repository
git clone https://github.com/yourusername/raytracing-engine.git
cd raytracing-engine

# make a build directory
mkdir build
# compile the project
cmake ..
make all
# run the executable
./RayTracer
```
## Preview
<img width="1920" height="1080" alt="canvas" src="https://github.com/user-attachments/assets/2e036a93-3252-42a4-9f4c-e162be630b2e" />

## Roadmap / Future Improvements
-- Additional geometry types (planes, triangles, meshes)
-- Textures and Perlin noise
-- BVH acceleration structures for faster rendering
-- GUI-based viewer for live previews

