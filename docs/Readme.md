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
![+= C++20](https://img.shields.io/badge/C%2B%2B-17-blue.svg)

Core goals:
- 🧩 **Component-oriented** storage with type-safety
- ⚡ **Fast lookups** via `SparseArray` and type-based storage  
- 🔄 **Flexible Systems**: can operate on any combination of components
- ✅ **Unit-tested** with GoogleTest  
- 🚀 **Header-only**, easy integration

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
#include <memory>

using namespace ecs;

struct Velocity { int x, y; };
struct Position { int x, y; void operator+=(const Velocity& vel) { x += vel.x; y += vel.y; } };
struct Health { int value; };

// --- Systems ---
class MoveSystem: public ISystem {
    public:
        MoveSystem() {}

        void update(Registry &r) override {
            auto& positions = r.getComponents<Position>();
            auto& velocities = r.getComponents<Velocity>();

            for(size_t i = 0; i < positions.size(); ++i) {
                if (positions[i] && velocities[i])
                    positions[i].value() += velocities[i].value();
            }
        }
};

int main() {
    Registry registry;

    using MyComponents = std::tuple<Position, Velocity, Health /*, ...*/>;
    registry.registerComponentsByExtraction<MyComponents>(); 
    //or use registry.registerComponents<Position /*, ...*/>();

    Entity player = registry.createEntity();
    Entity enemy = registry.createEntity();

    Health h{100}; 

    player.addComponent(Position{0, 0}, Velocity{1, 0}, h /*, ...*/);
    registry.addComponent(enemy, Health{50} /*, ...*/);

    auto&positons = registry.getComponents<Position>();

    registry.addSystem(MoveSystem()/*, ...*/);

    registry.callSystem<MoveSystem/*, ...*/>();
}
```