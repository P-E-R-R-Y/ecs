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

    template <class Tuple>
    void Registry::registerComponentsByExtraction() {
        static_assert(is_tuple<Tuple>::value, "Extraction must a std::tuple of Components.");
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

    template <typename Component>
    typename SparseArray<Component>::reference_type Registry::addComponent(Entity const &to, Component &&c) {
        getComponents<Component>().emplaceAt(to._idx, c);
        return getComponents<Component>()[to._idx];
    };

    template <typename Component, typename ... Params>
    typename SparseArray <Component>::reference_type Registry::emplaceComponent(Entity const &to, Params &&... p) {
        getComponents<Component>().emplaceAt(to._idx, p...);
        return getComponents<Component>()[to._idx];
    };

    template <typename Component>
    void Registry::removeComponent(Entity const &from) {
        getComponents<Component>().erase(from._idx);
    };

    /// @brief handling systems

    template <typename T, typename... Args>
    size_t Registry::addSystem(Args&&... args) {
        static_assert(std::is_base_of<System, T>::value, "T must derive from System");
        systems[std::type_index(typeid(T))] = std::make_unique<T>(std::forward<Args>(args)...);
        return systems.size();
    }

    template <typename T>
    size_t Registry::addSystem(std::unique_ptr<T> existingSystem) {
        static_assert(std::is_base_of<System, T>::value, "T must derive from System");
        systems[std::type_index(typeid(T))] = std::move(existingSystem);
        return systems.size();
    }

    template <typename T>
    void Registry::removeSystem() {
        auto type = std::type_index(typeid(T));
        systems.erase(type);
    }

    template <typename T>
    void Registry::callSystem() {
        systems[std::type_index(typeid(T))]->lambda(*this);
    }

    void Registry::callSystems() {
        for (auto& [type, system] : systems) {
            system->lambda(*this);
        }
    }

}

#endif // REGISTRY_IMPL_HPP