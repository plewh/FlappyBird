#pragma once
#include <vector>
#include "defs.h"

struct Component;
struct ComponentContainer;
struct PositionComponent;
struct SpriteComponent;

struct EntityManager {

	EntityManager();
	~EntityManager();

	int NewEntity();
	void AddComponent(int id, Component* component);
	void RemoveComponent(int id, component_tag_e tag);

	int entCount;
	Component* position [MAX_ENTS];
	Component* sprite   [MAX_ENTS];

};
