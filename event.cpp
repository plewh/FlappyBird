#include "event.h"
#include <cstdio>

Event::Event(eventType_e type, char* data) {

	this->type = type;
	this->data = data;

}

EventManager::EventManager() {

	head = 0;
	tail = 0;

}

EventManager::~EventManager() {

	;

}

void EventManager::PumpEvents() {

	for (; tail != head; tail = (tail + 1) % MAX_EVENTS) {

		for (int j = 0; j < listenerVect.size(); ++j) {

			listenerVect[j]->Responder(eventQueue[tail]);
		}

		delete(eventQueue[tail]);
		eventQueue[tail] = NULL;

	}

}

void EventManager::AddListener(EventListener* listener) {

	listenerVect.push_back(listener);

}

void EventManager::Post(Event* event) {

	//queue.push_back(event);

	eventQueue[head] = event;
	head = (head + 1) % MAX_EVENTS;

}
