#include "gamescene.h"
#include "renderer.h"
#include "entity.h"
#include "component.h"
#include "system.h"

GameScene::GameScene(EventManager* eventManager) {

	Log("GameScene started");
	entMan = new EntityManager;
	this->eventManager = eventManager;

	int ent;
	// bckgnd
	ent = entMan->NewEntity();
	entMan->AddComponent(ent, new PositionComponent(0.0, 0.0));
	entMan->AddComponent(ent, new SpriteComponent(TEX_BCKGND, 1.0, 255.0));

	// gnd
	ent = entMan->NewEntity();
	entMan->AddComponent(ent, new PositionComponent(0.0, 1280.0 - 160.0));
	entMan->AddComponent(ent, new SpriteComponent(TEX_GND, 1.0, 255.0));
	entMan->AddComponent(ent, new SpriteSpanComponent(20));
	entMan->AddComponent(ent, new AnimComponent(50, -0.08, 48, 160, 1));

	// flappy
	ent = entMan->NewEntity();
	entMan->AddComponent(ent, new PositionComponent(366.0, (WIN_Y - 82) / 2));
	entMan->AddComponent(ent, new RotateComponent(0.0, 0.0));
	entMan->AddComponent(ent, new SpriteComponent(TEX_FLAP, 1.0, 255.0));
	entMan->AddComponent(ent, new FlappyPhysicsComponent);
	entMan->AddComponent(ent, new FlappyInputComponent(eventManager));

	ent = entMan->NewEntity();
	entMan->AddComponent(ent, new PipeSpawnerComponent(-0.05));

	//my name is lexi!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//my name is aidan!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

}

GameScene::~GameScene() {

	Log("GameScene cleaning up");
	delete(entMan);

}

void GameScene::DoFrame(Renderer* renderer) {

	BlitSpriteSystem(entMan, renderer);

}

void GameScene::Tick() {

	FlappyPhysicsSystem(entMan);
	PipeSpawnerTickSystem(entMan, eventManager);

}

void GameScene::Responder(Event* event, EventManager* eventManager) {

	if (event->type == KEYDOWN)
		FlappyInputSystem(entMan);

	if ( event->type == SPAWN_PIPE ) {
		int ent = entMan->NewEntity();
		entMan->AddComponent(ent, new PositionComponent(100.0, 100.0));
		entMan->AddComponent(ent, new SpriteComponent(TEX_PIPE, 1.0, 255.0));
	}

}
