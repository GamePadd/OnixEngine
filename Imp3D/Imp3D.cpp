#include <iostream>
#include <string>

#include "Imp3D.h"
#include "Entities.h"
#include "ConsoleLogger.h"

int main() {

	Imp::entity_id player_entity = Imp::create_entity();
	Imp::ConsoleLogger& Logger = Imp::ConsoleLogger::Instance();

	Logger.Log("Spawned Entity: " + std::to_string(player_entity), Imp::LOG::INFO);
	return 0;
}