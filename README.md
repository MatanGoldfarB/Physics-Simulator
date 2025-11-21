# Physics Simulator

A real-time physics simulation engine built in C++ and OpenGL.  
This project showcases my understanding of **numerical physics**, **collision handling**, **rendering**, and **interactive simulation control**. It was designed as a learning project and as a demonstration of my ability to build complex systems from scratch — both mathematically and architecturally.

---

## 🎥 Project Demo

https://api.myfiles.ai/download?path=/mnt/data/PhysicsSimulator.mov

*(If the video preview doesn’t load on GitHub, click the link to view the .mov directly.)*

---

## 🚀 Features

### ⚙️ **Physics Engine**
- Rigid-body simulation (boxes, spheres, arbitrary objects)  
- Newtonian motion (forces, momentum, acceleration, velocity integration)  
- Gravity, friction, and tunable material properties  
- Stable numerical solvers (semi-implicit Euler / Verlet-style integration)

### 🧱 **Collision Detection & Response**
- Broad-phase & narrow-phase collision detection  
- AABB & OBB support  
- Surface normals, penetration depth, and bounce resolution  
- Elastic & inelastic collision handling

### 🖥️ **Rendering Engine (OpenGL)**
- Real-time OpenGL rendering pipeline  
- Camera with orbit/pan/zoom  
- Object coloring & depth  
- Shaders (vertex + fragment)  
- Optional ImGui interface for debugging

---

## 🛠️ Technologies Used
- **C++17**  
- **OpenGL**  
- **GLFW**  
- **GLAD**  
- **ImGui** (optional UI)  
- **Eigen** (math library, if included)  
- **CMake** (build system)

---

## 📁 Project Structure
```
Physics-Simulator/
│
├── src/
│   ├── main.cpp
│   ├── physics/
│   │   ├── Rigidbody.h/.cpp
│   │   ├── Collider.h/.cpp
│   │   ├── Integrator.h/.cpp
│   │   └── World.h/.cpp
│   ├── rendering/
│   │   ├── Renderer.h/.cpp
│   │   ├── Camera.h/.cpp
│   │   └── Shader.h/.cpp
│   └── utils/
├── shaders/
├── resources/
└── README.md
```

---

## 📌 What This Project Demonstrates

This project demonstrates my ability to:

- Build real-time interactive systems  
- Implement physics from mathematical definitions  
- Use C++ in a modular, engineering-grade way  
- Work with low-level graphics APIs  
- Combine rendering + physics + UI into one unified engine  
- Write clean, maintainable, object-oriented design  
- Debug numerical stability and performance issues  

Perfect for roles involving:
- Simulation  
- Graphics / Rendering  
- Robotics / Physics Engines  
- Game engines  
- Computer vision + geometry  
- Real-time software engineering  

---

## 🚀 Running the Project

### **Build Instructions**
```bash
git clone https://github.com/MatanGoldfarB/Physics-Simulator
cd Physics-Simulator
mkdir build && cd build
make
./PhysicsSimulator
```

### **Dependencies**
- CMake  
- C++17 compiler  
- GLFW  
- GLAD  
- OpenGL drivers  

---

## 🗺️ Roadmap
- Soft-body physics  
- Cloth simulation  
- GPU acceleration (CUDA/OpenCL)  
- Scene editor with UI  
- Save/load simulation states  
- Better collision primitives (capsules, convex hull)  

---

## 📬 Contact
If you're a recruiter or hiring manager and want to discuss the project:

**Matan Goldfarb**  
📧 Email: matangoldfarb1@gmail.com  
🔗 GitHub: https://github.com/MatanGoldfarB  

---

---

## 🚀 Features

### **⚙️ Physics Engine**
- Rigid-body simula# Physics-Simulator
