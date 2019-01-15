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

	for (int j = 0; j < MAX_ENTS; ++j) {

		if ( entMan->activeEnts[j] == true ) {
			BlitSpriteSystem(entMan, j, renderer, 0);
		}

	}

	for (int j = 0; j < MAX_ENTS; ++j) {

		if ( entMan->activeEnts[j] == true ) {
			PipeSpriteSystem(entMan, j, renderer);
		}

	}

	for (int j = 0; j < MAX_ENTS; ++j) {

		if ( entMan->activeEnts[j] == true ) {
			BlitSpriteSystem(entMan, j, renderer, 1);
		}

	}

	for (int j = 0; j < MAX_ENTS; ++j) {

		if ( entMan->activeEnts[j] == true ) {
			BlitSpriteSystem(entMan, j, renderer, 2);
		}

	}

	for (int j = 0; j < MAX_ENTS; ++j) {

		if ( entMan->activeEnts[j] == true ) {
			HudSystem(entMan, j, renderer);
		}

	}

}

void GameScene::Tick() {

	for (int j = 0; j < MAX_ENTS; ++j) {

		if ( entMan->activeEnts[j] == true ) {
			FlappyPhysicsSystem(entMan, j);
			PipeSpawnerTickSystem(entMan, j, eventManager);
			PipeTickSystem(entMan, j, eventManager);
			CollisionHandlerSystem( entMan, j, eventManager );
		}

	}

}

void GameScene::Responder(Event* event, EventManager* eventManager) {

	switch (event->type) {

		case KEYDOWN:
			if (strcmp(event->data, "ENTER") == 0) {
				Restart(eventManager);
			} else {
				for (int j = 0; j < MAX_ENTS; ++j) {

					if ( entMan->activeEnts[j] == true ) {
						FlappyInputSystem(entMan, j);
					}

				}

			}
			break;

		case SPAWN_PIPE:
			SpawnPipe();
			break;

		case GAME_RESTART:
			Restart(eventManager);
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

	// score
	ent = entMan->NewEntity();
	entMan->AddComponent( ent, new PositionComponent( 80.0, 0.0 ) );
	entMan->AddComponent( ent, new SizeComponent( 0.0, 0.0 ) );
	ScoreComponent* scr = new ScoreComponent;
	ScoreListenerComponent* slc = new ScoreListenerComponent(scr);
	eventManager->AddListener(slc);
	entMan->AddComponent( ent, scr );
	entMan->AddComponent( ent, slc );

}

void GameScene::Restart(EventManager* eventManager) {

	Log("Caught game start event!");

	for (int j = 0; j < MAX_ENTS; ++j) {

		if ( entMan->activeEnts[j] == true ) {

			if ( entMan->scoreListener[j] ) {

				EventListener* e = (EventListener*)(entMan->scoreListener[j]);
				eventManager->RemoveListener(e-1); // offset due to multiple inheritance

			}

		}

	}

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
