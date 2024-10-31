#pragma once
#include <Components/component_manager.hpp>
#include <Entities/entity.hpp>
#include <Entities/entity_manager.hpp>
#include <entity_struct.hpp>

int CheckEntityPosition(
    uint32_t entityId, ComponentManager componentManager, EntityManager entityManager);

int CheckEntityMovement(
    EntityInformation desc, ComponentManager componentManager, EntityManager entityManager);
