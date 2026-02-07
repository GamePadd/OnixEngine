#include <typeinfo>
#include <vector>
#include <queue>

#include "World.h"
#include "../ConsoleLogger.h"

namespace Imp {
	void world_register_system(World* world, system_t system, const char* system_name) {
		world->systems.insert({ system_name,system });
		ConsoleLogger::Instance().Log("Registered new system: " + std::string(system_name), LOG::INFO);
	}

	void world_unregister_system(World* world, const char* system_name) {
		world->systems.erase(system_name);
		ConsoleLogger::Instance().Log("Deleted system: " + std::string(system_name), LOG::INFO);
	}

	World* create_world() {
		World* world = new World();
		ConsoleLogger::Instance().Log("New world created!", LOG::INFO);
		return world;
	}

	void destroy_world(World* world) {
		std::unordered_map<std::string, ComponentBase*>::iterator level_component_iterator = world->components.begin();
		while (level_component_iterator != world->components.end()) {
			level_component_iterator->second->free();
			delete level_component_iterator->second;
			++level_component_iterator;
		}

		delete world;
		ConsoleLogger::Instance().Log("World deleted", LOG::INFO);
	}

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
		++world->entities[entity_index];
		world->empty_entities_spots.push(entity_index);

		std::unordered_map<std::string, ComponentBase*>::iterator component_iterator = world->components.begin();

		while (component_iterator != world->components.end()) {
			component_iterator->second->destroy(entity);
			++component_iterator;
		}

		ConsoleLogger::Instance().Log("Deleted Entity: " + std::to_string(GET_INDEX(entity_index)), Imp::LOG::INFO);
	}
}