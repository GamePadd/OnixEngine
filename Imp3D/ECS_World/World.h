#pragma once

#include <vector>
#include <queue>
#include <unordered_map>
#include <string>

namespace Imp {
	struct World;

	typedef void(*system_t)(World* world, float delta_time);

	struct World {
		std::unordered_map<std::string, system_t> systems;

		std::vector<uint8_t> entities = { 0 };
		std::queue<uint32_t> empty_entities_spots;
	};

	void world_register_system(World*, system_t, const char*);
	void world_unregister_system(World*, const char*);

	World* create_world();
	void destroy_world(World* world);
}