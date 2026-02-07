#include <iostream>
#include <string>

#include "Imp3D.h"
#include "ECS_World/World.h"
#include "ECS_World/Entities.h"
#include "ConsoleLogger.h"

struct Test {
	int x;
	int y;
};

void system_template(Imp::World* world, float delta) {

	std::vector<uint8_t>::iterator entities_iterator = world->entities.begin();
	std::vector<uint8_t>::iterator entities_begin = world->entities.begin();
	while (entities_iterator != world->entities.end()) {
		uint32_t entity_index = entities_iterator - entities_begin;
		Imp::entity_id entity = CREATE_ID((*entities_iterator), entity_index);

		if (entity != 0 && Imp::world_get_component<Test>(world, entity) != nullptr) {
			Test* test = Imp::world_get_component<Test>(world, entity);

			test->x = 5;
			test->y = 4;
		}

		++entities_iterator;
	}
	return;
}

int main() {
	Imp::World* world = Imp::create_world();
	
	Imp::entity_id entity = Imp::create_entity(world);
	Imp::world_register_system(world, system_template, "system");
	Imp::world_register_component<Test>(world);

	Test test;
	test.x = 1;
	test.y = 2;
	Imp::world_add_component<Test>(world, entity, test);

	float delta_time = 1.0f / 60.0f;

	for (std::pair<std::string, Imp::system_t> system : world->systems) {
		system.second(world, delta_time);
	}
	std::cout << "entity id is: " << std::to_string(GET_INDEX(entity)) << "\n";
	Test* test_ee = Imp::world_get_component<Test>(world, entity);
	std::cout << "entity x is " << std::to_string(test_ee->x) << ", y is " << std::to_string(test_ee->y) << "\n";
	Imp::destroy_entity(world,entity);
	Imp::destroy_world(world);
	return 0;
}