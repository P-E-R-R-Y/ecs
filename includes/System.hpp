/**
 * @file System.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-29
 * 
 * @addtogroup ecs
 * @{
 */

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <concepts>

namespace ecs {

    class Registry;

    /**
     * @brief Abstract base class representing a system in the ECS architecture.
     *
     * The `System` class defines the interface that all concrete systems must implement.
     * Each system operates on entities and their components, typically through a `Registry`.
     *
     * @class System
     * @ingroup ECS
     */
    class ISystem {
        public:
            /**
             * @brief Virtual destructor to allow safe polymorphic destruction.
             */        
            virtual ~ISystem() = default;

            /**
             * @brief Pure virtual function executed by all concrete systems.
             *
             * This function defines the logic a system performs during the update phase.
             * 
             * @param registry Reference to the ECS registry.
             */
            virtual void update(Registry &) = 0;
    };

    /**
     * @brief Concept that ensures a type derives from `System`.
     *
     * This concept can be used to constrain template parameters,
     * guaranteeing that only classes implementing the `System` interface
     * can be used in ECS-related templates.
     *
     * @tparam T The type to check.
     *
     * @see System
     */
    template<typename T>
    concept SystemImplementation = std::derived_from<T, ISystem>;

}


#endif // SYSTEM_HPP