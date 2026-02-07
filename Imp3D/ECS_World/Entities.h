#pragma once

#include <stdint.h>
#include <vector>
#include <queue>

#define MAX_ENTITIES 0x00000FFFF

#define CAPACITY_ENTITIES 0x00FFFFFF 
#define GENERATION_BIT 24

#define GET_GENERATION(id) ((id & 0xFF000000) >> GENERATION_BIT)
#define GET_INDEX(id) (id & CAPACITY_ENTITIES)
#define CREATE_ID(generation, index) (generation << GENERATION_BIT) | index

namespace Imp {
	typedef uint32_t entity_id;

	struct generational_ptr {
		entity_id id;
		uint8_t generation;
	};
}