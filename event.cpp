#include "event.h"

Event::Event(eventType_e type, const char* data) {

	this->type = type;
	this->data = data;

}

EventManager::EventManager() {

	Log("Event system starting ");

	head = 0;
	tail = 0;

	for ( int j = 0; j < MAX_EVENTS; ++j )
		eventQueue[j] = NULL;


}

EventManager::~EventManager() {

	Log("Cleaning up event system");

	;

}

void EventManager::PumpEvents() {

	for (; tail != head; tail = (tail + 1) % MAX_EVENTS) {

		for (size_t j = 0; j < listenerVect.size(); ++j) {

			listenerVect[j]->Responder(eventQueue[tail]);
		}

		delete(eventQueue[tail]);
		eventQueue[tail] = NULL;

	}

}

void EventManager::AddListener(EventListener* listener) {

	listenerVect.push_back(listener);

}

void EventManager::RemoveListener(EventListener* listener) {

	for ( auto j = listenerVect.begin(); j != listenerVect.end(); ++j) {

		if ( *j == listener ) {

			listenerVect.erase(j);
			return;

		}

	}

}

void EventManager::Post(Event* event) {

	eventQueue[head] = event;
	head = (head + 1) % MAX_EVENTS;

}
