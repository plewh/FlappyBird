#pragma once
#include "defs.h"

enum eventType_e {

	QUIT,
	NONE,
	CHANGE_SCENE,
	KEYDOWN,
	TITLE_SPLASH_DONE,
	SPAWN_PIPE

};

struct Event {

	Event(eventType_e type, const char* data);

	eventType_e type;
	const char* data;

};

struct EventListener {

	virtual void Responder(Event* event)=0;

};

struct EventManager {

	EventManager();
	~EventManager();

	void PumpEvents();
	void AddListener(EventListener* listener);
	void Post(Event* event);

	private:
	std::vector<EventListener*> listenerVect;
	std::vector<Event*> queue;
	Event* eventQueue[MAX_EVENTS];
	int head;
	int tail;

};
