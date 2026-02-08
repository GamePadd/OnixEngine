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
	std::vector<uint8_t>::const_iterator entities_iterator = world->GetEntities().begin();
	std::vector<uint8_t>::const_iterator entities_begin = world->GetEntities().begin();

	while (entities_iterator != world->GetEntities().end()) {
		uint32_t entity_index = entities_iterator - entities_begin;
		Imp::entity_id entity = CREATE_ID((*entities_iterator), entity_index);

		if (entity != 0 && world->GetComponent<Test>(entity) != nullptr) {
			Test* test = world->GetComponent<Test>(entity);

			test->x = 5;
			test->y = 4;
		}

		++entities_iterator;
	}
	return;
}

int main() {
	Imp::World* world = new Imp::World();
	
	Imp::entity_id entity = world->CreateEntity();
	world->RegisterSystem(system_template, "system");
	world->RegisterComponent<Test>();

	Test test;
	test.x = 1;
	test.y = 2;
	world->AddComponent<Test>(entity, test);

	float delta_time = 1.0f / 60.0f;

	for (std::pair<std::string, Imp::system_t> system : world->GetSystems()) {
		system.second(world, delta_time);
	}
	std::cout << "entity id is: " << std::to_string(GET_INDEX(entity)) << "\n";
	Test* test_ee = world->GetComponent<Test>(entity);
	std::cout << "entity x is " << std::to_string(test_ee->x) << ", y is " << std::to_string(test_ee->y) << "\n";
	
	world->DestroyEntity(entity);
	delete world;

	int asd;
	std::cin >> asd;
	return 0;
}