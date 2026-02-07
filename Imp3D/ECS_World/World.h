#pragma once

#include <typeinfo>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include "ComponentBase.h"
#include "ComponentClass.h"

#include "../ConsoleLogger.h"

namespace Imp {
	struct World;

	typedef void(*system_t)(World* world, float delta_time);

	struct World {
		std::unordered_map<std::string, ComponentBase*> components;
		std::unordered_map<std::string, system_t> systems;

		std::vector<uint8_t> entities = { 0 };
		std::queue<uint32_t> empty_entities_spots;
	};

	void world_register_system(World*, system_t, const char*);
	void world_unregister_system(World*, const char*);

	entity_id create_entity(World*);
	void destroy_entity(World*, entity_id);

	template<typename T>
	void world_register_component(World* world) {
		std::string type_name = typeid(T).name();

		if (world->components.find(type_name) != world->components.end()) {
			ConsoleLogger::Instance().Log("Component is already registered!", LOG::ERROR);
			return;
		}

		Component<T>* new_component_type = new Component<T>();
		ComponentBase* base_component_type = new_component_type;
		world->components.insert({ type_name, base_component_type });
		ConsoleLogger::Instance().Log("New component registered!", LOG::INFO);
	}

	template<typename T>
	void world_register_component_with_destroy(World* world, void(*destroy_function)(T*)) {
		std::string type_name = typeid(T).name();

		if (world->components.find(type_name) != world->components.end()) {
			ConsoleLogger::Instance().Log("Component is already registered!", LOG::ERROR);
			return;
		}

		Component<T>* new_component_type = new Component<T>();
		new_component_type->destroy_function = destroy_function;
		ComponentBase* base_component_type = new_component_type;
		world->components.insert({ type_name, base_component_type });
		ConsoleLogger::Instance().Log("New component registered!", LOG::INFO);
	}

	template<typename T>
	void world_add_component(World* world, entity_id entity, T component) {
		std::string type_name = std::string(typeid(component).name());
		Component<T>* component_type = (Component<T>*)(world->components[type_name]);
		component_type->create(entity, component);
		//ConsoleLogger::Instance().Log("Component " + type_name + " added for entity " + std:to_string(GET_INDEX(entity)), LOG::INFO);
	}

	template<typename T>
	T* world_get_component(World* world, entity_id entity) {
		std::string type_name = std::string(typeid(T).name());
		Component<T>* component_type = (Component<T>*)(world->components[type_name]);
		return component_type->get_component(entity);
	}

	template<typename... T>
	bool world_has_components(World* world, entity_id entity) {
		std::string components_names[] = { " ", std::string(typeid(T).name())... };

		uint32_t types_size = sizeof...(T);
		std::vector<ComponentBase*> type_bases;
		for (size_t i = 1; i < types_size; i++) {
			type_bases.push_back(world->components[components_names[i]]);
		}

		for (size_t i = 0; i < types_size; i++) {
			if (!type_bases[i]->has_component(entity)) { return false; };
		}

		return true;
	}

	World* create_world();
	void destroy_world(World* world);
}