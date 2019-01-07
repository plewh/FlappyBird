#include "entity.h"
#include "component.h"
#include <cstddef>

EntityManager::EntityManager() {

	entCount = 0;

	for (int j = 0; j < MAX_ENTS; ++j) {

		position[j] = NULL;
		sprite[j]   = NULL;

	}

}

EntityManager::~EntityManager() {

	for (int j = 0; j < MAX_ENTS; ++j) {

		delete(position[j]);
		delete(sprite[j]);

	}

}

int EntityManager::NewEntity() {

	return entCount++;

}

void EntityManager::AddComponent(int id, Component* component) {

	switch (component->tag) {

		case POSITION:
			position[id] = component;
			break;

		case SPRITE:
			sprite[id] = component;
			break;

		default:
			break;

	}

}

void EntityManager::RemoveComponent(int id, component_tag_e componentTag) {

	switch (componentTag) {

		case POSITION:
			delete(position[id]);
			position[id] = NULL;
			break;

		case SPRITE:
			delete(sprite[id]);
			sprite[id] = NULL;
			break;

		default:
			break;

	}

}
