#include "gamescene.h"
#include "renderer.h"
#include "entity.h"
#include "component.h"
#include "system.h"

GameScene::GameScene(EventManager* eventManager) {

	Log("GameScene started");
	this->eventManager = eventManager;

	entMan = new EntityManager;
	PopulateWithInitEnts(entMan);

	//my name is lexi!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//my name is aidan!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

}

GameScene::~GameScene() {

	Log("GameScene cleaning up");
	delete(entMan);

}

void GameScene::DoFrame(Renderer* renderer) {

	BlitSpriteSystem(entMan, renderer, 0);
	PipeSpriteSystem(entMan, renderer);
	BlitSpriteSystem(entMan, renderer, 1);
	BlitSpriteSystem(entMan, renderer, 2);
	//HudSystem(entMan, renderer);

}

void GameScene::Tick() {

	FlappyPhysicsSystem(entMan);
	PipeSpawnerTickSystem(entMan, eventManager);
	PipeTickSystem(entMan, eventManager);
	CollisionHandlerSystem( entMan, eventManager );

}

void GameScene::Responder(Event* event, EventManager* eventManager) {

	switch (event->type) {

		case KEYDOWN:
			if (strcmp(event->data, "ENTER") == 0) {
				Restart();
			} else {
				FlappyInputSystem(entMan);
			}
			break;

		case SPAWN_PIPE:
			SpawnPipe();
			break;

		case GAME_RESTART:
			Restart();
			break;

		default:
			break;
	}

}

void GameScene::PopulateWithInitEnts(EntityManager* entMan) {

	int ent;
	// bckgnd
	ent = entMan->NewEntity();
	entMan->AddComponent(ent, new PositionComponent(0.0, 0.0));
	entMan->AddComponent(ent, new SpriteComponent(TEX_BCKGND, 1.0, 255.0, 0));

	// gnd
	ent = entMan->NewEntity();
	entMan->AddComponent(ent, new PositionComponent(0.0, 1280.0 - 160.0));
	entMan->AddComponent(ent, new SpriteComponent(TEX_GND, 1.0, 255.0, 1));
	entMan->AddComponent(ent, new SpriteSpanComponent(20));
	entMan->AddComponent(ent, new AnimComponent(50, -0.08, 48, 160, 1));

	// flappy
	ent = entMan->NewEntity();
	entMan->AddComponent(ent, new PositionComponent(366.0, (WIN_Y - 82) / 2));
	entMan->AddComponent(ent, new RotateComponent(0.0, 0.0));
	entMan->AddComponent(ent, new SpriteComponent(TEX_FLAP, 1.0, 255.0, 2));
	entMan->AddComponent(ent, new FlappyPhysicsComponent);
	entMan->AddComponent(ent, new FlappyInputComponent(eventManager));
	entMan->AddComponent(ent, new CollidableComponent);
	entMan->AddComponent(ent, new SizeComponent(110.0, 80.0));

	// pipe spawner
	ent = entMan->NewEntity();
	entMan->AddComponent(ent, new PipeSpawnerComponent(-0.007));

}

void GameScene::Restart() {

	Log("Caught game start event!");

	delete( entMan );
	entMan = new EntityManager;
	PopulateWithInitEnts(entMan);

}

void GameScene::SpawnPipe() {

	double offset = (double)GetRandom(10, WIN_Y - (PIPE_GAP + 80 + 160));
	int ent = entMan->NewEntity();
	entMan->AddComponent(ent, new PositionComponent(950.0, 0.0));
	entMan->AddComponent(ent, new PipeSpriteComponent(TEX_PIPE));
	entMan->AddComponent(ent, new PipeComponent(offset, -4.5));
	entMan->AddComponent(ent, new CollidableComponent);
	entMan->AddComponent(ent, new SizeComponent(160.0, PIPE_GAP));

}
