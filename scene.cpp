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
	sceneStack.push_back(new TitleScene);

}

SceneManager::~SceneManager() {

	;

}

void SceneManager::DoFrame() {

	for (int j = 0; j < sceneStack.size(); ++j)
		sceneStack[j]->DoFrame(renderer);

}

void SceneManager::Tick() {

	;

}

void SceneManager::Responder(Event* event) {

	switch (event->type) {
		
		case KEYDOWN:

			if (!strcmp(event->data, "q"))
				eventManager->Post(new Event(QUIT, NULL));
			else
				sceneStack.back()->Responder(event, eventManager);
			break;

		case CHANGE_SCENE:
			if (!strcmp(event->data, "GAME_SCENE")) {
				ChangeScene(GAME);
			}
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

TitleScene::TitleScene() {

	entMan = new EntityManager;
	int ent;

	// bckgnd
	ent = entMan->NewEntity();
	entMan->AddComponent(ent, new PositionComponent(0.0, 0.0));
	entMan->AddComponent(ent, new SpriteComponent(TEX_BCKGND));

	// splash
	ent = entMan->NewEntity();
	entMan->AddComponent(ent, new PositionComponent((640.0 - 300.0) / 2, (480.0 - 300.0) / 2));
	entMan->AddComponent(ent, new SpriteComponent(TEX_SPLASH));

}

TitleScene::~TitleScene() {

	delete(entMan);

}

void TitleScene::DoFrame(Renderer* renderer) {

	BlitSpriteSystem(renderer, entMan);

}

void TitleScene::Tick() {

	;

}

void TitleScene::Responder(Event* event, EventManager* eventManager) {

	if (event->type == KEYDOWN && !strcmp(event->data, " "))
		eventManager->Post(new Event(CHANGE_SCENE, "GAME_SCENE"));

}

GameScene::GameScene() {

	entMan = new EntityManager;

	int ent = entMan->NewEntity();
	entMan->AddComponent(ent, new PositionComponent(120.0, 120.0));
	entMan->AddComponent(ent, new SpriteComponent(DUNNO));

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
