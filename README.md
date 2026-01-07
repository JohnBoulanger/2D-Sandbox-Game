# Terraria Clone (C++ / SFML)

<img width="793" height="593" alt="Screenshot 2026-01-06 at 7 18 14 PM" src="https://github.com/user-attachments/assets/4764ffbd-ae65-4edb-ad1d-8dccee7cfaf7" />

A 2D sandbox game inspired by Terraria, built from scratch in C++ using SFML.
Focuses on tile-based worlds, procedural generation, player physics, and clean engine-style architecture.

---

## Features

- Tile-based 2D world
- Procedural terrain generation (FastNoise2 / Perlin-style noise)
- Player movement, gravity, and collision
- Sprite-based rendering with animation
- Chunked world layout (scales beyond screen size)
- Separation of rendering, physics, and world logic

---
xx
## Tech Stack

- Language: C++17
- Graphics: SFML (2.6.x)
- Build System: CMake
- Noise: FastNoise2

---

## Project Structure

Terraria-Clone/
├── src/
│   ├── core/
│   ├── world/
│   ├── entities/
│   ├── physics/
│   └── graphics/
├── assets/
│   ├── textures/
│   └── shaders/
├── CMakeLists.txt
└── README.md

---

## Build Instructions

Prerequisites:
- CMake ≥ 3.27
- C++17 compiler
- Git

Build:
git clone https://github.com/your-username/terraria-clone.git
cd terraria-clone
cmake -S . -B build
cmake --build build

Executable output:
build/bin/

---

## Controls

A / D – Move left / right
Space – Jump
Esc – Exit

---

## Roadmap

- Biomes and layered terrain
- Tile breaking and placement
- Inventory system
- Lighting system
- Enemies and basic AI
- Save/load worlds

---

## License

MIT License
