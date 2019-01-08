#include "scene.h"
#include "renderer.h"
#include "titlescene.h"
#include "gamescene.h"
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
