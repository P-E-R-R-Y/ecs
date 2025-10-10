/**
 * @file Entity_impl.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @date 2025-01-29
 */

#ifndef ENTITY_IMPL_HPP
#define ENTITY_IMPL_HPP

//local
#include "Entity.hpp"
#include "Registry.hpp"

//global
#include <cstddef>

namespace ecs {

    class Registry;
    using RegistryRef = Registry &;

    template <typename ... Component, typename>
    void Entity::addComponent(Component&&... c) {
        (_ecs.addComponent<Component>(*this, std::forward<Component>(c)), ...);
    }

    template <typename ... Component, typename>
    void Entity::removeComponent() {
        (_ecs.removeComponent<Component>(*this), ...);
    }
}

#endif // ENTITY_IMPL_HPP