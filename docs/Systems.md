# ECS - Systems implementation

```cpp
#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include "Registry.hpp"
#include "Component.hpp"
#include "System.hpp"

class Math {
    public:
        Math() = default;
        ~Math() = default;

        int sqrt(int a) {
            return a * a;
        }
};

class ExampleSystem: public System {
    public:
        ExampleSystem(Math& math): _math(math) {};
        ~ExampleSystem() = default;

        void lambda(Registry &r) override {
            std::cout << "----- Display Begin -----" << std::endl;
            auto& positions = r.getComponents<Position>();

            for (size_t i = 0; i < positions.size(); ++i) {
                if (!positions[i]) {
                  continue;
                }
                std::cout  << "sqrtPos .x:" <<  _math.sqrt(positions[i]->x) << " y:" << _math.sqrt(positions[i]->y) << std::endl;
            }
        }

    private:

        Math& _math;

};

#endif // SYSTEMS_HPP
```