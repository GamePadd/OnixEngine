#pragma once

#include <stdint.h>
#include <vector>
#include <queue>

#define CAPACITY_ENTITIES 0xFFFFFF 
#define GENERATION_BIT 24

#define GET_GENERATION(id) ((id & 0xFF000000) >> GENERATION_BIT)
#define GET_INDEX(id) (id & CAPACITY_ENTITIES)
#define CREATE_ID(generation, index) (generation << GENERATION_BIT) | index

namespace Imp {
	typedef uint32_t entity_id;

	entity_id create_entity();
	void destroy_entity(entity_id);
}