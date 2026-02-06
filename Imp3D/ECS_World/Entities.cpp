#include "Entities.h"
#include "../ConsoleLogger.h"

namespace Imp {
	entity_id create_entity(World* world) {
		if (!world->empty_entities_spots.empty()) {
			uint32_t empty_spot = world->empty_entities_spots.front();
			world->empty_entities_spots.pop();
			++world->entities[empty_spot];
			entity_id new_entity = CREATE_ID(world->entities[empty_spot], empty_spot);

			ConsoleLogger::Instance().Log("Spawned Entity: " + std::to_string(GET_INDEX(new_entity)), Imp::LOG::INFO);

			return new_entity;
		}

		world->entities.push_back(1);
		entity_id new_entity = CREATE_ID(1, world->entities.size() - 1);

		ConsoleLogger::Instance().Log("Spawned Entity: " + std::to_string(GET_INDEX(new_entity)), Imp::LOG::INFO);

		return new_entity;
	}

	void destroy_entity(World* world, entity_id entity) {
		uint32_t entity_index = GET_INDEX(entity);

		ConsoleLogger::Instance().Log("Deleted Entity: " + std::to_string(GET_INDEX(entity_index)), Imp::LOG::INFO);

		++world->entities[entity_index];
		world->empty_entities_spots.push(entity_index);
	}
}