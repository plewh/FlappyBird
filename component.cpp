#include "component.h"
#include <cstdio>
#include <cstddef>

PositionComponent::PositionComponent(double x, double y) {

	this->tag = POSITION;
	this->x = x;
	this->y = y;

}

SpriteComponent::SpriteComponent(texture_e tName) {

	this->tag = SPRITE;
	this->tName = tName;

}

ListenerComponent::ListenerComponent() {

	;

}

void ListenerComponent::Responder(Event* event) {


}
