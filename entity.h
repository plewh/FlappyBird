#pragma once
#include <vector>
#include "defs.h"

/*******
	Creating a component:
		- create struct in component.cpp
		- create new tag in enum in defs.h
		- ensure struct uses inherited tag member
		- create array in entitymanager for component
		- ensure array is NULLed in constructor
		- update AddComponent and RemoveComponent

*******/

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
	Component* position   [MAX_ENTS];
	Component* sprite     [MAX_ENTS];
	Component* angle      [MAX_ENTS];
	Component* splashTick [MAX_ENTS];
	Component* size       [MAX_ENTS];
	Component* maskTick   [MAX_ENTS];

};
