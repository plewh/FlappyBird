#include "gamescene.h"
#include "renderer.h"
#include "entity.h"
#include "component.h"
#include "system.h"
#include <cstring>
#include <cstdio>

GameScene::GameScene() {

	entMan = new EntityManager;
	this->eventManager = eventManager;

	int ent;
	// bckgnd
	ent = entMan->NewEntity();
	entMan->AddComponent(ent, new PositionComponent(0.0, 0.0));
	entMan->AddComponent(ent, new SpriteComponent(TEX_BCKGND, 1.0, 255.0));

	// flappy
	ent = entMan->NewEntity();
	entMan->AddComponent(ent, new PositionComponent(366.0, (WIN_Y - 82) / 2));
	entMan->AddComponent(ent, new RotateComponent(0.0, 0.0));
	entMan->AddComponent(ent, new SpriteComponent(TEX_FLAP, 1.0, 255.0));
	entMan->AddComponent(ent, new FlappyPhysicsComponent);
	entMan->AddComponent(ent, new FlappyInputComponent(eventManager));

	//my name is lexi!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//my name is aidan!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

}

GameScene::~GameScene() {

	delete(entMan);

}

void GameScene::DoFrame(Renderer* renderer) {

	BlitSpriteSystem(entMan, renderer);

}

void GameScene::Tick() {

	FlappyPhysicsSystem(entMan);

}

void GameScene::Responder(Event* event, EventManager* eventManager) {

	if (event->type == KEYDOWN)
		FlappyInputSystem(entMan);

}
