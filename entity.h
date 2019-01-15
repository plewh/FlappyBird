#pragma once
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

	int  NewEntity();
	void KillEntity(int id);
	void AddComponent(int id, Component* component);
	void RemoveComponent(int id, component_tag_e tag);

	bool       activeEnts[MAX_ENTS];

	Component* position      [MAX_ENTS];
	Component* sprite        [MAX_ENTS];
	Component* angle         [MAX_ENTS];
	Component* splashTick    [MAX_ENTS];
	Component* size          [MAX_ENTS];
	Component* maskTick      [MAX_ENTS];
	Component* flappyPhysics [MAX_ENTS];
	Component* flappyInput   [MAX_ENTS];
	Component* spriteSpan    [MAX_ENTS];
	Component* anim          [MAX_ENTS];
	Component* pipeSpawn     [MAX_ENTS];
	Component* pipe          [MAX_ENTS];
	Component* pipeSprite    [MAX_ENTS];
	Component* collidable    [MAX_ENTS];
	Component* score         [MAX_ENTS];
	Component* scoreListener [MAX_ENTS];

};
