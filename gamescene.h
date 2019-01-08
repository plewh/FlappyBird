#pragma once
#include "defs.h"
#include "scene.h"

struct Renderer;
struct Event;
struct EventManager;

struct GameScene:Scene {

	GameScene();
	~GameScene();

	void DoFrame(Renderer* renderer);
	void Tick();
	void Responder(Event* event, EventManager* eventManager);

};
