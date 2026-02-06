#include "World.h"

#include <vector>
#include <queue>

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
		delete world;
		ConsoleLogger::Instance().Log("World deleted", LOG::INFO);
	}
}