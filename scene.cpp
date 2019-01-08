#include "scene.h"
#include "renderer.h"
#include "entity.h"
#include "component.h"
#include "system.h"
#include <cstdio>
#include <cstring>

SceneManager::SceneManager(Renderer* renderer, EventManager* eventManager) {

	this->renderer = renderer;
	this->eventManager = eventManager;
	sceneStack.push_back(new TitleScene(this->eventManager));

}

SceneManager::~SceneManager() {

	;

}

void SceneManager::DoFrame() {

	for (size_t j = 0; j < sceneStack.size(); ++j)
		sceneStack[j]->DoFrame(renderer);

}

void SceneManager::Tick() {

	for (size_t j = 0; j < sceneStack.size(); ++j)
		sceneStack[j]->Tick();

}

void SceneManager::Responder(Event* event) {

	switch (event->type) {
		
		case KEYDOWN:

			if (!strcmp(event->data, "q"))
				eventManager->Post(new Event(QUIT, ""));
			else
				sceneStack.back()->Responder(event, eventManager);
			break;

		case CHANGE_SCENE:
			if (!strcmp(event->data, "GAME_SCENE")) {
				ChangeScene(GAME);
			}
			break;

		case TITLE_SPLASH_DONE:
			sceneStack[0]->Responder(event, eventManager);
			break;

		default:
			break;

	}

}

void SceneManager::ChangeScene(scene_e sceneTag) {

	sceneStack.clear();

	switch (sceneTag) {
		
		case GAME:
			sceneStack.push_back(new GameScene);
			break;

		default:
			break;

	};

}

TitleScene::TitleScene(EventManager* eventManager) {

	entMan = new EntityManager;
	this->eventManager = eventManager;

	int ent;
	// bckgnd
	ent = entMan->NewEntity();
	entMan->AddComponent(ent, new PositionComponent(0.0, 0.0));
	entMan->AddComponent(ent, new SpriteComponent(TEX_BCKGND, 1.0, 255.0));

	// splash
	ent = entMan->NewEntity();
	entMan->AddComponent(ent, new PositionComponent(0.0, 0.0));
	entMan->AddComponent(ent, new SizeComponent(900.0, 1000.0));
	entMan->AddComponent(ent, new SpriteComponent(TEX_SPLASH1, 0.0001, 255.0));
	entMan->AddComponent(ent, new RotateComponent(0.0, 0.0));
	entMan->AddComponent(ent, new SplashTickComponent(0.006, 2.0));

}

TitleScene::~TitleScene() {

	delete(entMan);

}

void TitleScene::DoFrame(Renderer* renderer) {

	BlitSpriteSystem(renderer, entMan);

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
		entMan->AddComponent(id, new SpriteComponent(TEX_MASK, 1.0, 255.0));
		entMan->AddComponent(id, new MaskTickComponent(-1.0));

	}

}

GameScene::GameScene() {

	entMan = new EntityManager;
	this->eventManager = eventManager;

	// bckgnd
	int ent = entMan->NewEntity();
	entMan->AddComponent(ent, new PositionComponent(0.0, 0.0));
	entMan->AddComponent(ent, new SpriteComponent(TEX_BCKGND, 1.0, 255.0));

	//my name is lexi!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//my name is aidan!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

}

GameScene::~GameScene() {

	delete(entMan);

}

void GameScene::DoFrame(Renderer* renderer) {

	BlitSpriteSystem(renderer, entMan);

}

void GameScene::Tick() {

	;

}

void GameScene::Responder(Event* event, EventManager* eventManager) {

	;

}
