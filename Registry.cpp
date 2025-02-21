/**
 * @file Registry.cpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-29
 * 
 * @addtogroup ecs
 * @{
 */

#include "Registry.hpp"
#include "Entity.hpp"

using namespace ecs;

/// @brief handling entities
Entity Registry::createEntity() {
  if (!killedEntities.empty()) {
        Entity tmp = killedEntities.back();
        killedEntities.pop_back();
        return tmp;
    } else {
        ++_entitiesCount;
        return Entity(_entitiesCount - 1, *this);
    }
};

Entity Registry::entityFromIndex(std::size_t idx) {
    return Entity(idx, *this);
};

void Registry::killEntity(Entity const &e) {
    killedEntities.push_back(e);
    for (const auto &f: componentsRemoves) {
        f(*this, e);
    }
};