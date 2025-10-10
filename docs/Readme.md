# ⚛️ P-E-R-R-Y ECS  

A modern, lightweight **Entity-Component-System** framework in C++.

[![Build](https://github.com/P-E-R-R-Y/ecs/actions/workflows/cmake.yml/badge.svg)](https://github.com/P-E-R-R-Y/ecs/actions)
[![Docs](https://img.shields.io/badge/docs-doxygen-blue.svg)](https://p-e-r-r-y.github.io/ecs)
![License](https://img.shields.io/badge/license-MIT-green.svg)

---

## ✨ Overview

`P-E-R-R-Y ECS` is a **header-only**, type-safe library for game development, simulations, or any system that benefits from separating **data** from **logic**.

It implements the **Entity-Component-System (ECS)** pattern with modern C++ features:
- Templates & variadic functions for type safety
- Optional concepts (C++20) for system constraints
- Efficient storage and fast iteration

Supported C++ versions:  
![C++11](https://img.shields.io/badge/C%2B%2B-11-orange.svg)  
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)

Core goals:
- 🧩 **Strongly typed components** using templates  
- ⚡ **Fast lookups** via `SparseArray` and type-based storage  
- 🔄 **Flexible systems** supporting owned/non-owned objects  
- 🚀 **Header-only**, **zero dependencies**  
- ✅ **Unit-tested** with GoogleTest  

---

## 🧱 Features

- Create entities and attach any combination of components  
- Add systems that operate on specific components  
- Variadic interface: add multiple components or systems at once  
- Owned (rvalue) vs Non-owned (lvalue) systems  
- Safe runtime updates via `Registry::callSystem<System>()`  
- Component access via `getComponents<T>()`  

---

## 🧩 Example Usage

```cpp
#include "Ecs.hpp"
#include <iostream>

// Components
struct Position { int x, y; };
struct Velocity { int dx, dy; };

// System that moves entities with Position + Velocity
struct MovementSystem : public ISystem {
    void update(Registry& registry) override {
        for (auto& [pos, vel] : registry.view<Position, Velocity>()) {
            pos.x += vel.dx;
            pos.y += vel.dy;
        }
    }
};

int main() {
    Registry registry;

    // Create entity
    Entity e{0};
    registry.addComponent(e, Position{10, 20});
    registry.addComponent(e, Velocity{1, 2});

    // Add system
    registry.addSystem(MovementSystem{});

    // Run system
    registry.callSystem<MovementSystem>();

    // Access updated position
    auto& pos = registry.getComponents<Position>()[e._idx];
    std::cout << "Updated Position: (" << pos.x << "," << pos.y << ")\n";

    return 0;
}