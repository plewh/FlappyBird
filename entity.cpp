#include "entity.h"
#include "component.h"

EntityManager::EntityManager() {

	Log("EntityManager starting");

	for (int j = 0; j < MAX_ENTS; ++j) {
		
		activeEnts[j]    = false;

		position[j]      = NULL;
		sprite[j]        = NULL;
		angle[j]         = NULL;
		splashTick[j]    = NULL;
		size[j]          = NULL;
		maskTick[j]      = NULL;
		flappyPhysics[j] = NULL;
		flappyInput[j]   = NULL;
		spriteSpan[j]    = NULL;
		anim[j]          = NULL;
		pipeSpawn[j]     = NULL;
		pipe[j]          = NULL;
		pipeSprite[j]    = NULL;
		collidable[j]    = NULL;
		score[j]         = NULL;
		scoreListener[j] = NULL;

	}

}

EntityManager::~EntityManager() {

	Log("EntityManager cleaning up");
	for (int j = 0; j < MAX_ENTS; ++j) {

		KillEntity(j);

	}

}

int EntityManager::NewEntity() {

	for ( int j = 0; j < MAX_ENTS; ++j ) {

		if ( activeEnts[j] == false ) {
			activeEnts[j] = true;
			return j;
		}

	}

	return -1;

}

void EntityManager::KillEntity(int id) {

	RemoveComponent(id, POSITION);
	RemoveComponent(id, SPRITE);
	RemoveComponent(id, ANGLE);
	RemoveComponent(id, SPLASH_TICK);
	RemoveComponent(id, SIZE);
	RemoveComponent(id, MASK_TICK);
	RemoveComponent(id, FLAPPY_PHYSICS);
	RemoveComponent(id, FLAPPY_INPUT);
	RemoveComponent(id, SPRITE_SPAN);
	RemoveComponent(id, ANIM);
	RemoveComponent(id, PIPE_SPAWN);
	RemoveComponent(id, PIPE);
	RemoveComponent(id, PIPE_SPRITE);
	RemoveComponent(id, COLLIDABLE);
	RemoveComponent(id, SCORE);
	RemoveComponent(id, SCORELISTENER);

	activeEnts[id] = false;

}

void EntityManager::AddComponent(int id, Component* component) {

	switch (component->tag) {

		case POSITION:
			position[id]      = component;
			break;

		case SPRITE:
			sprite[id]        = component;
			break;

		case ANGLE:
			angle[id]         = component;
			break;

		case SPLASH_TICK:
			splashTick[id]    = component;
			break;

		case SIZE:
			size[id]          = component;
			break;

		case MASK_TICK:
			maskTick[id]      = component;
			break;

		case FLAPPY_PHYSICS:
			flappyPhysics[id] = component;
			break;

		case FLAPPY_INPUT:
			flappyInput[id]   = component;
			break;

		case SPRITE_SPAN:
			spriteSpan[id]    = component;
			break;

		case ANIM:
			anim[id]          = component;
			break;

		case PIPE_SPAWN:
			pipeSpawn[id]     = component;
			break;

		case PIPE:
			pipe[id]          = component;
			break;

		case PIPE_SPRITE:
			pipeSprite[id]    = component;
			break;

		case COLLIDABLE:
			collidable[id]    = component;
			break;

		case SCORE:
			score[id]         = component;
			break;

		case SCORELISTENER:
			scoreListener[id] = component;
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

		case ANGLE:
			delete(angle[id]);
			angle[id] = NULL;
			break;

		case SPLASH_TICK:
			delete(splashTick[id]);
			splashTick[id] = NULL;
			break;

		case SIZE:
			delete(size[id]);
			size[id] = NULL;
			break;

		case MASK_TICK:
			delete(maskTick[id]);
			maskTick[id] = NULL;
			break;

		case FLAPPY_PHYSICS:
			delete(flappyPhysics[id]);
			flappyPhysics[id] = NULL;
			break;

		case FLAPPY_INPUT:
			delete(flappyInput[id]);
			flappyInput[id] = NULL;
			break;

		case SPRITE_SPAN:
			delete(spriteSpan[id]);
			spriteSpan[id] = NULL;
			break;

		case ANIM:
			delete(anim[id]);
			anim[id] = NULL;
			break;

		case PIPE_SPAWN:
			delete(pipeSpawn[id]);
			pipeSpawn[id] = NULL;
			break;

		case PIPE:
			delete(pipe[id]);
			pipe[id] = NULL;
			break;

		case PIPE_SPRITE:
			delete(pipeSprite[id]);
			pipeSprite[id] = NULL;
			break;

		case COLLIDABLE:
			delete(collidable[id]);
			collidable[id] = NULL;
			break;

		case SCORE:
			delete(score[id]);
			score[id] = NULL;
			break;

		case SCORELISTENER:
			//delete(scoreListener[id]);
			scoreListener[id] = NULL;
			break;

		default:
			break;

	}

}
