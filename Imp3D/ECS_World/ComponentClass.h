#pragma once
#include "ComponentBase.h"
#include "../ConsoleLogger.h"
namespace Imp {
	template<typename T>
	class Component : public ComponentBase {
		private:
			std::vector<T> components{ {} };
		public:
			using DestroyFunc = void(*)(T*);
			DestroyFunc DestroyFunction = nullptr;

			T* Create(entity_id entity, T component) {
				if (last_component == MAX_ENTITIES - 1) {
					ConsoleLogger::Instance().Log("Error, can't create Component, limit reached!", LOG::ERROR);
					return nullptr;
				}

				++last_component;
				uint32_t last_index = last_component;
				components.push_back(component);
				component_to_entity[last_index].id = entity;
				component_to_entity[last_index].generation += 1;
				uint32_t new_component_id = CREATE_ID(component_to_entity[last_index].generation, last_index);

				uint32_t entity_id = GET_INDEX(entity);
				uint32_t entity_generation = GET_GENERATION(entity);

				entity_to_component[entity_id].id = new_component_id;
				entity_to_component[entity_id].generation = entity_generation;

				ConsoleLogger::Instance().Log("Created new component for entity " + std::to_string(entity_id), LOG::INFO);

				return &components[last_index];

			}

			T* GetComponent(entity_id entity) {
				uint32_t entity_id = GET_INDEX(entity);
				uint8_t entity_generation = GET_GENERATION(entity);
				generational_ptr component_pointer = entity_to_component[entity_id];
				if (component_pointer.generation != entity_generation) {
					ConsoleLogger::Instance().Log("Error, component not found for entity " + std::to_string(entity_id), LOG::ERROR);
					return nullptr;
				}

				uint32_t component_index = GET_INDEX(component_pointer.id);
				return &components[component_index];
			}

			void Destroy(entity_id entity) {
				uint32_t entity_to_destroy_index = GET_INDEX(entity);
				generational_ptr component_pointer = entity_to_component[entity_to_destroy_index];
				if (component_pointer.generation != GET_GENERATION(entity)) {
					ConsoleLogger::Instance().Log("Can't destroy component!", LOG::ERROR);
					return;
				}

				uint32_t component_to_destroy_index = GET_INDEX(component_pointer.id);
				if (DestroyFunction) {
					DestroyFunction(&components[component_to_destroy_index]);
				}

				if (component_to_destroy_index == last_component) {
					component_to_entity[component_to_destroy_index].id = 0;
					component_to_entity[component_to_destroy_index].generation += 1;
					entity_to_component[entity_to_destroy_index].id = 0;
					entity_to_component[entity_to_destroy_index].generation += 1;

					ConsoleLogger::Instance().Log("Removed component", LOG::INFO);

					return;
				}

				generational_ptr entity_pointer_to_swap = component_to_entity[last_component];
				components[component_to_destroy_index] = components[last_component];
				component_to_entity[component_to_destroy_index] = entity_pointer_to_swap;
				component_to_entity[component_to_destroy_index].generation += 1;
				entity_to_component[GET_INDEX(entity_pointer_to_swap.id)].id = component_pointer.id;
				entity_to_component[entity_to_destroy_index].generation += 1;

				ConsoleLogger::Instance().Log("Removed component", LOG::INFO);
			}

			void Free() {
				if (DestroyFunction == nullptr) {
					components.clear();
					ConsoleLogger::Instance().Log("All components cleared!", LOG::INFO);
					return;
				}

				uint32_t components_size = components.size();
				for (size_t i = 1; i < components_size; ++i) {
					DestroyFunction(&components[i]);
				}
				components.clear();
				ConsoleLogger::Instance().Log("All components cleared!", LOG::INFO);
			}
	};
}