/**
 * @file TestRegistry.cpp
 * @author 
 * @brief Unit tests for ecs::Registry implementation using GoogleTest.
 * @date 2025-10-07
 */

#include <gtest/gtest.h>
#include <string>
#include <memory>
#include <iostream>
#include "Ecs.hpp"

using namespace ecs;

// --- Components ---
struct Velocity {
    int x, y;
    bool operator==(const Velocity& other) const { return x == other.x && y == other.y; }
    friend std::ostream& operator<<(std::ostream& os, const Velocity& v) {
        return os << "Velocity(" << v.x << "," << v.y << ")";
    }
};

struct Position {
    int x, y;
    
    bool operator==(const Position& other) const { return x == other.x && y == other.y; }
    void operator+=(const Velocity& vel) { x += vel.x; y += vel.y; }

    friend std::ostream& operator<<(std::ostream& os, const Position& p) {
        return os << "Position(" << p.x << "," << p.y << ")";
    }
};

struct Health {
    int value;

    friend std::ostream& operator<<(std::ostream& os, const Health& h) {
        return os << "Health(" << h.value << ")";
    }
};

// --- Instance ---
class Singleton {
    public:
        static Singleton& getInstance() {
            static Singleton singleton;

            return singleton;
        }

        Singleton(const Singleton&) = delete;

        Singleton& operator=(const Singleton&) = delete;

        void display(Position& v) {
            std::cerr << "pos .x: " << v.x << " .y: " << v.y << std::endl;
        }

    private:
        Singleton() {}
        int n = 2;
};

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

class DisplaySystem: public ISystem {
    public:
        DisplaySystem(Singleton& s):_s(s) {}

        void update(Registry &r) override {
            auto& positions = r.getComponents<Position>();
            auto& velocities = r.getComponents<Velocity>();

            for(size_t i = 0; i < positions.size(); ++i) {
                if (positions[i]) {
                    _s.display(positions[i].value());
                }
            }
        }
    private:
        Singleton& _s;
};

// --- Component registration ---
TEST(RegistryTest, RegisterAndRetrieveComponents) {
    Registry registry;

    registry.registerComponents<Position, Velocity, Health>();

    auto& posArray = registry.getComponents<Position>();
    EXPECT_EQ(posArray.size(), 0u);

    // Ensure that the same instance is returned (not copies)
    EXPECT_EQ(&registry.getComponents<Position>(), &posArray);
}

// --- Register by tuple extraction ---
TEST(RegistryExtractionTest, RegisterComponentsByExtraction) {
    Registry registry;
    using MyComponents = std::tuple<Position, Velocity, Health>;
    registry.registerComponentsByExtraction<MyComponents>();

    EXPECT_NO_THROW(registry.getComponents<Position>());
    EXPECT_NO_THROW(registry.getComponents<Velocity>());
    EXPECT_NO_THROW(registry.getComponents<Health>());
}

TEST(RegistryExtractionTest, Intergration) {
    Registry registry;

    Singleton&s = Singleton::getInstance();


    using MyComponents = std::tuple<Position, Velocity, Health>;
    registry.registerComponentsByExtraction<MyComponents>();

    EXPECT_NO_THROW(registry.getComponents<Position>());
    EXPECT_NO_THROW(registry.getComponents<Velocity>());
    EXPECT_NO_THROW(registry.getComponents<Health>());

    Entity player = registry.createEntity();

    player.addComponent(Position{0, 0}, Velocity{1, 0});

    auto&positons = registry.getComponents<Position>();

    registry.addSystem(MoveSystem(), DisplaySystem(s));

    EXPECT_EQ(positons[0].value().x, 0);
    registry.callSystem<DisplaySystem, MoveSystem, DisplaySystem>();

    EXPECT_EQ(positons[0].value().x, 1);

}