#include <iostream>
#include <string>

#include "Imp3D.h"
#include "ECS_World/World.h"
#include "ECS_World/Entities.h"
#include "ConsoleLogger.h"

void test_system(Imp::World* world, float delta) {
	std::cout << "System working\n";
	return;
}

int main() {
	Imp::World* world = Imp::create_world();
	
	Imp::entity_id entity = Imp::create_entity(world);
	Imp::world_register_system(world, test_system, "system");

	float delta_time = 1.0f / 60.0f;

	for (std::pair<std::string, Imp::system_t> system : world->systems) {
		system.second(world, delta_time);
	}
	std::cout << "entity id is: " << std::to_string(entity) << "\n";

	Imp::destroy_world(world);

	return 0;
}