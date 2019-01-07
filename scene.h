#pragma once
#include "event.h"

struct Renderer;
struct EntityManager;
struct Scene;
struct EventManager;

struct SceneManager:EventListener {

	SceneManager(Renderer* renderer, EventManager* eventManager);
	~SceneManager();

	void DoFrame();
	void Tick();
	void Responder(Event* event);

	private:
	void ChangeScene(scene_e sceneTag);
	std::vector<Scene*> sceneStack;
	Renderer*           renderer;
	EventManager*       eventManager;

};

struct Scene {

	virtual void DoFrame(Renderer* renderer)                         =0;
	virtual void Tick()                                              =0;
	virtual void Responder(Event* event, EventManager* eventManager) =0;

	EntityManager* entMan;

};

struct TitleScene:Scene {

	TitleScene();
	~TitleScene();

	void DoFrame(Renderer* renderer);
	void Tick();
	void Responder(Event* event, EventManager* eventManager);

};

struct GameScene:Scene {

	GameScene();
	~GameScene();

	void DoFrame(Renderer* renderer);
	void Tick();
	void Responder(Event* event, EventManager* eventManager);

};
