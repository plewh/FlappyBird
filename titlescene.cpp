#include "titlescene.h"
#include "renderer.h"
#include "entity.h"
#include "component.h"
#include "system.h"

TitleScene::TitleScene(EventManager* eventManager) {

	Log("TitleScene started");
	entMan = new EntityManager;
	this->eventManager = eventManager;

	int ent;
	// bckgnd
	ent = entMan->NewEntity();
	entMan->AddComponent(ent, new PositionComponent(0.0, 0.0));
	entMan->AddComponent(ent, new SpriteComponent(TEX_BCKGND, 1.0, 255.0, 0));

	// splash
	ent = entMan->NewEntity();
	entMan->AddComponent(ent, new PositionComponent(0.0, 0.0));
	entMan->AddComponent(ent, new SizeComponent(900.0, 1000.0));
	entMan->AddComponent(ent, new SpriteComponent(TEX_SPLASH1, 0.0001, 255.0, 0));
	entMan->AddComponent(ent, new RotateComponent(0.0, 0.0));
	entMan->AddComponent(ent, new SplashTickComponent(0.006, 2.0));

}

TitleScene::~TitleScene() {

	Log("TitleScene cleaning up");
	delete(entMan);

}

void TitleScene::DoFrame(Renderer* renderer) {

	BlitSpriteSystem(entMan, renderer, 0);

}

void TitleScene::Tick() {

	SplashTickSystem(entMan, eventManager);
	MaskTickSystem(entMan, eventManager);
	AngleTickSystem(entMan);

}

void TitleScene::Responder(Event* event, EventManager* eventManager) {

	if (event->type == KEYDOWN && !strcmp(event->data, " "))
		eventManager->Post(new Event(CHANGE_SCENE, "GAME_SCENE"));

	if (event->type == TITLE_SPLASH_DONE) {

		int id = entMan->NewEntity();
		entMan->AddComponent(id, new PositionComponent(0.0, 0.0));
		entMan->AddComponent(id, new SpriteComponent(TEX_MASK, 1.0, 255.0, 0));
		entMan->AddComponent(id, new MaskTickComponent(-1.0));

	}

}

