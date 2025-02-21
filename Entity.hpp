/**
 * @file Entity.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-29
 * 
 * @addtogroup ecs
 * @{
 */

#ifndef ENTITY_HPP
#define ENTITY_HPP

//local

//global
#include <cstddef>

namespace ecs {

    class Registry;
    using RegistryRef = Registry &;

    /**
     * @brief Entity class from ECS
     * @class Entity
     */
    class Entity {
        public:

            friend Registry;

        public:

            /**
             * @brief Deleted default constructor, use Registry::createEntity() instead
             */
            Entity() = delete;
            
            /**
             * @brief Destroy the Entity object
             * 
             */
            ~Entity() = default;

            /**
             * @brief add a component to the entity using the registryRef method addComponent
             * 
             * @tparam Component 
             * @param c 
             */
            template <class Component>
            void addComponent(Component&& c);

            /**
             * @brief remove a component from the entity using the registryRef method removeComponent
             * 
             * @tparam Component 
             */
            template <class Component>
            void removeComponent();

        private:

            /**
             * @brief Construct a new Entity object with the given index and registry reference
             * 
             * @param idx 
             * @param ecs 
             */
            explicit Entity(size_t idx, RegistryRef ecs);

        private:

            size_t _idx;
            RegistryRef _ecs;
    };
}

#endif // ENTITY_HPP