#include "Entity.hpp"
#include "Registry.hpp"

namespace ecs {

    Entity::Entity(size_t idx, Registry& ecs)
        : _idx(idx), _ecs(ecs) {}

} // namespace ecs