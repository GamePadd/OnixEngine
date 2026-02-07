#pragma once

#include <typeinfo>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include "ComponentBase.h"
#include "ComponentClass.h"
#include <functional>

#include "../ConsoleLogger.h"

namespace Imp {
	class World;

	//typedef void(*system_t)(World* world, float delta_time);
	using system_t = std::function<void(World*, float)>;

	class World {
		private:
			std::unordered_map<std::string, ComponentBase*> components;
			std::unordered_map<std::string, system_t> systems;

			std::vector<uint8_t> entities = { 0 };
			std::queue<uint32_t> empty_entities_spots;

		public:
			World();
			~World();

			void RegisterSystem(system_t, const char*);
			void UnregisterSystem(const char*);

			entity_id CreateEntity();
			void DestroyEntity(entity_id);

			const std::unordered_map<std::string, system_t> GetSystems() const;
			const std::unordered_map<std::string, ComponentBase*> GetComponents() const;
			const std::vector<uint8_t>& GetEntities() const;

			template<typename T>
			void RegisterComponent() {
				std::string type_name = typeid(T).name();

				if (components.find(type_name) != components.end()) {
					ConsoleLogger::Instance().Log("Component is already registered!", LOG::ERROR);
					return;
				}

				Component<T>* new_component_type = new Component<T>();
				ComponentBase* base_component_type = new_component_type;
				components.insert({ type_name, base_component_type });
				ConsoleLogger::Instance().Log("New component registered!", LOG::INFO);
			}

			template<typename T>
			void RegisterComponentWithDestroy(std::function<void(T*)> DestroyFunction) {
				std::string type_name = typeid(T).name();

				if (components.find(type_name) != components.end()) {
					ConsoleLogger::Instance().Log("Component is already registered!", LOG::ERROR);
					return;
				}

				Component<T>* new_component_type = new Component<T>();
				new_component_type->DestroyFunction = DestroyFunction;
				ComponentBase* base_component_type = new_component_type;
				components.insert({ type_name, base_component_type });
				ConsoleLogger::Instance().Log("New component registered!", LOG::INFO);
			}

			template<typename T>
			void AddComponent(entity_id entity, T component) {
				std::string type_name = std::string(typeid(component).name());
				Component<T>* component_type = dynamic_cast<Component<T>*>(components[type_name]);
				component_type->Create(entity, component);
				//ConsoleLogger::Instance().Log("Component " + type_name + " added for entity " + std:to_string(GET_INDEX(entity)), LOG::INFO);
			}

			template<typename T>
			T* GetComponent(entity_id entity) {
				std::string type_name = std::string(typeid(T).name());
				//Component<T>* component_type = (Component<T>*)(components[type_name]);
				Component<T>* component_type = dynamic_cast<Component<T>*>(components[type_name]);
				return component_type->GetComponent(entity);
			}

			template<typename... T>
			bool HasComponents(entity_id entity) {
				std::string components_names[] = { " ", std::string(typeid(T).name())... };

				uint32_t types_size = sizeof...(T);
				std::vector<ComponentBase*> type_bases;
				for (size_t i = 1; i < types_size; i++) {
					type_bases.push_back(components[components_names[i]]);
				}

				for (size_t i = 0; i < types_size; i++) {
					if (!type_bases[i]->HasComponent(entity)) { return false; };
				}

				return true;
			}
	};
}