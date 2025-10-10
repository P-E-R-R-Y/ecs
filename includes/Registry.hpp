/**
 * @file Registry.hpp
 * @author @Perry-chouteau (perry.chouteau@outook.com)
 * @brief 
 * @date 2025-01-27
 */

#ifndef REGISTRY_HPP
#define REGISTRY_HPP

//local
#include "SparseArray.hpp"

//global
#include <any>
#include <functional>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include "System.hpp"
#include "Concepts.hpp"

namespace ecs {

    class Entity;
    class System;

    /**
     * @brief Component is a template define in Registry. (not a class) 
     * @class Component
     */
    
    /**
     * @brief define the Registry class
     *
     * @class Registry
     */
    class Registry {

        public:

            /// @brief handling entities (define in Registry.cpp)

            /**
             * @brief Create a Entity object
             * 
             * @return Entity 
             */
            Entity createEntity();

            /**
             * @brief Create a Entity object from an index
             * 
             * @param idx 
             * @return Entity 
             */
            Entity entityFromIndex(std::size_t idx);

            /**
             * @brief Kill the given entity
             * 
             * @param e 
             */
            void killEntity(Entity const &e);

            /// @brief handling components (define in Registry_impl.hpp)

            /**
             * @brief register a component
             * 
             * @tparam Component 
             * @return SparseArray<Component>& 
             */
            template <typename Component>
            SparseArray<Component> &registerComponent();

            /**
             * @brief register a list of components
             * 
             * @tparam Components 
             */
            template <class ... Components>
            void registerComponents();

            /**
             * @brief register every components by extraction from a tuple
             * 
             * @tparam Tuple 
             */
            template <IsTuple Tuple>
            void registerComponentsByExtraction();

            /**
             * @brief get components of a given type
             * 
             * @tparam Component 
             * @return SparseArray<Component>&
             */
            template <class Component>
            SparseArray<Component> &getComponents();

            /**
             * @brief get immutable components of a given type
             * 
             * @tparam Component 
             * @return const SparseArray<Component>&
             */
            template <class Component>
            const SparseArray<Component> &getComponents() const;

            /**
             * @brief 
             * 
             * @tparam add a component to the given entity 
             * @param to 
             * @param c
             * @return SparseArray<Component>::reference_type 
             */
            template <typename... Component, typename = std::enable_if_t<(sizeof...(Component) != 0)>>
            void addComponent(Entity const &to, Component &&...c);

            /**
             * @brief emplace a component to the given entity
             * 
             * @tparam Component 
             * @tparam Params 
             * @param to 
             * @param p 
             * @return SparseArray <Component>::reference_type 
             */
            template <typename Component, typename ... Params>
            void emplaceComponent(Entity const &to, Params &&... p);

            /**
             * @brief remove a component from the given entity
             * 
             * @tparam Component 
             * @param from 
             */
            template <typename... Component, typename = std::enable_if<(sizeof...(Component) != 0)>>
            void removeComponent(Entity const &from);

            /// @brief handling systems
            /**
             * @brief add lvalue
             * 
             * @tparam System 
             * @param s 
             */
            template<SystemImplementation System>
            void addSystem(System& s);

            /**
             * @brief add rvalue
             * 
             * @tparam move constructor
             * @param s 
             */
            template<SystemImplementation System>
            void addSystem(System&& s);

            /**
             * @brief add a system to the registry
             * 
             * @tparam ... T 
             * @tparam control variadic list isn't empty
             * @param s 
             */
            template <SystemImplementation... System, typename = std::enable_if<(sizeof...(System) != 0)>>
            void addSystem(System&& ... s);

            /**
             * @brief add a system to the registry
             * 
             * @tparam T 
             * @param existingSystem 
             * @return size_t 
             */
            template <SystemImplementation System, typename ... Params>
            void emplaceSystem(Params &&... params);

            /**
             * @brief remove a system from the registry
             * 
             * @tparam T 
             */
            template <SystemImplementation ... System, typename = std::enable_if<(sizeof...(System) != 0)>>
            void removeSystem();

            /**
             * @brief call a system
             * 
             * @tparam T 
             */
            template <SystemImplementation ... System, typename = std::enable_if<(sizeof...(System) != 0)>>
            void callSystem();

        private:

            size_t _entitiesCount = 0;
            std::vector<Entity> killedEntities;

            std::unordered_map<std::type_index, std::any> componentsArrays;
            std::unordered_map<std::type_index, std::any> systemsArrays;

            std::vector<std::function<void(Registry &, Entity const &)>> componentsRemoves;

            std::unordered_map<std::type_index, std::shared_ptr<ISystem>> systems;
    };

}

#endif // REGISTRY_HPP