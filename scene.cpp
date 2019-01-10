#include "scene.h"
#include "renderer.h"
#include "titlescene.h"
#include "gamescene.h"

SceneManager::SceneManager(Renderer* renderer, EventManager* eventManager) {

	Log("SceneManager starting");
	this->renderer = renderer;
	this->eventManager = eventManager;

	ChangeScene(TITLE);

}

SceneManager::~SceneManager() {

	Log("SceneManager cleaning up");
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

		case SPAWN_PIPE:
			sceneStack.back()->Responder(event, eventManager);
			break;

		default:
			break;

	}

}

void SceneManager::ChangeScene(scene_e sceneTag) {

	sceneStack.clear();

	switch (sceneTag) {

		case TITLE:
			sceneStack.push_back(new TitleScene(this->eventManager));
			Log("TitleScene added to scene stack");
			break;

		case GAME:
			sceneStack.push_back(new GameScene(this->eventManager));
			Log("GameScene added to scene stack");
			break;

		default:
			break;

	};

}
