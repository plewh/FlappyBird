#pragma once
#include "defs.h"
#include "event.h"

struct Renderer;
struct EventManager;
struct SceneManager;

struct App:EventListener {

	App();
	~App();

	void          Run();
	void          Responder(Event* event);

	private:
	double        GetDelta();
	void          PumpSystemEvents();

	Renderer*     renderer;
	EventManager* eventManager;
	SceneManager* sceneManager;

	bool          running;
	double        lastTicks;
	double        tickRate;
	double        lag;

};
