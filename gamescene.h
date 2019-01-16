#pragma once
#include "defs.h"
#include "scene.h"

struct Renderer;
struct Event;
struct EventManager;

struct GameScene:Scene {

	GameScene(EventManager* eventManager);
	~GameScene();

	void DoFrame(Renderer* renderer);
	void Tick();
	void Responder(Event* event, EventManager* eventManager);

	private:
	void PopulateWithInitEnts(EntityManager* entMan);
	void Restart(EventManager* eventManager);
	void SpawnPipe();
	bool restartFlag;
	void DoPreRestart(EntityManager* entMan);
	int  maxScore;

};
