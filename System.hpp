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

#include "Registry.hpp"

namespace ecs {

    /**
     * @brief System class
     * 
     * @class System
     */
    class System {
        public:
            virtual ~System() = default;

            virtual void lambda(Registry &) = 0;
    };

}

#endif // SYSTEM_HPP