# ECS - Component implementation

```cpp
#ifndef COMPONENT_HPP_
    #define COMPONENT_HPP_
    
    #include <ostream>
    #include <tuple>

struct Position {
    float x;
    float y;
};

std::ostream& operator<<(std::ostream& os, Position const &c)
{
    return (os << c.x << ", " << c.y);
}

struct Velocity {
    float x;
    float y;
};

std::ostream& operator<<(std::ostream& os, Velocity const &c)
{
    return (os << c.x << ", " << c.y);
}

/// @brief define a tuple to register every component by extraction.
#include <tuple>
#include "Component.hpp"
    
struct config {
    using components_list = std::tuple<Position, Velocity>;
};

#endif /* !COMPONENT_HPP_ */
```