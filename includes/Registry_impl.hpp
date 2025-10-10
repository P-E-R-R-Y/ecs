/**
 * @file Registry_impl.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-29
 * 
 * @addtogroup ecs
 * @{
 */

#ifndef REGISTRY_IMPL_HPP
#define REGISTRY_IMPL_HPP

#include "Registry.hpp"
#include "Entity.hpp"
#include "SparseArray.hpp"
#include "Concepts.hpp"

#include "System.hpp"

namespace ecs {

    template <class Component>
    SparseArray<Component> &Registry::registerComponent() {
        componentsArrays[std::type_index(typeid(Component))] = std::make_any<SparseArray<Component>>();
        componentsRemoves.push_back([] (Registry &r, Entity const &e) { r.getComponents<Component>().erase(e._idx); } );
        return std::any_cast<SparseArray<Component> &>(componentsArrays[std::type_index(typeid(Component))]);
    };

    template <class ... Components>
    void Registry::registerComponents() {
        (registerComponent<Components>(), ...);
    };

    template <IsTuple Tuple>
    void Registry::registerComponentsByExtraction() {
        std::apply([this](auto ... components) {
            this->registerComponents<std::decay_t<decltype(components)>...>();
        }, Tuple{});
    }

    template <class Component>
    SparseArray<Component> &Registry::getComponents() {
        return std::any_cast<SparseArray<Component> &>(componentsArrays[std::type_index(typeid(Component))]); //
    };

    template <class Component>
    const SparseArray<Component> &Registry::getComponents() const {
        return std::any_cast<SparseArray<Component> &>(componentsArrays.at(std::type_index(typeid(Component))));
    };

    template <typename... Component, typename> // =  std::enable_if_t<(sizeof...(Component) >= 1)>
    void Registry::addComponent(Entity const &to, Component&&... c) {
        (getComponents<std::remove_reference_t<Component>>().emplaceAt(to._idx, std::forward<Component>(c)), ...);
    }

    template <typename Component, typename ... Params>
    void Registry::emplaceComponent(Entity const &to, Params &&... p) {
        getComponents<Component>().emplaceAt(to._idx, std::forward<Params>(p)...);
        return getComponents<Component>()[to._idx];
    };

    template <typename ... Component, typename>
    void Registry::removeComponent(Entity const &from) {
        (getComponents<Component>().erase(from._idx), ...);
    };

    /// @brief handling systems

    template<SystemImplementation System>
    void Registry::addSystem(System& s) {
        systems[std::type_index(typeid(System))] = std::shared_ptr<ISystem>(&s, +[](ISystem*){});
    }

    template<SystemImplementation System>
    void Registry::addSystem(System&& s) {
        systems[std::type_index(typeid(System))] = std::make_shared<System>(std::move(s));
    }

    template <SystemImplementation... System, typename> // =  std::enable_if_t<(sizeof...(System) >= 1)>
    void Registry::addSystem(System&& ... s) {
        (addSystem(std::forward<System>(s)), ...);
    }
    
    template <SystemImplementation System, typename... Args>
    void Registry::emplaceSystem(Args&&... args) {
        systems[std::type_index(typeid(System))] = std::make_shared<System>(std::forward<Args>(args)...);
    }

    template <SystemImplementation ... System, typename>
    void Registry::removeSystem() {
        (systems.erase(std::type_index(typeid(System))), ...);
    }

    template <SystemImplementation ... System, typename>
    void Registry::callSystem() {
        (systems[std::type_index(typeid(System))]->update(*this), ...);
    }
}

#endif // REGISTRY_IMPL_HPP