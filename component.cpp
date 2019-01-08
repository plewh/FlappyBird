#include "component.h"
#include <cstdio>
#include <cstddef>

PositionComponent::PositionComponent(double x, double y) {

	this->tag = POSITION;
	this->x = x;
	this->y = y;

}

SpriteComponent::SpriteComponent(texture_e tName, double scale, double alpha) {

	this->tag   = SPRITE;
	this->tName = tName;
	this->scale = scale;
	this->alpha = alpha;

}

ListenerComponent::ListenerComponent() {

	;

}

void ListenerComponent::Responder(Event* event) {


}

RotateComponent::RotateComponent(double angle, double angleAcc) {

	this->tag      = ANGLE;
	this->angle    = angle;
	this->angleAcc = angleAcc;

}

SplashTickComponent::SplashTickComponent(double scaleAcc, double rotAcc) {

	this->tag      = SPLASH_TICK;
	this->scaleAcc = scaleAcc;
	this->rotAcc   = rotAcc;
	ended          = false;

}


SizeComponent::SizeComponent(double w, double h) {

	this->tag      = SIZE;
	this->w        = w;
	this->h        = h;

}

MaskTickComponent::MaskTickComponent(double decay) {

	this->tag   = MASK_TICK;
	this->value = 255.0;
	this->decay = decay;

}

FlappyPhysicsComponent::FlappyPhysicsComponent() {

	this->tag   = FLAPPY_PHYSICS;
	this->grav  = 1.0;
	this->yAcc  = 0.0;

}

FlappyInputComponent::FlappyInputComponent(EventManager* eventManager) {

	this->tag          = FLAPPY_INPUT;
	this->eventManager = eventManager;
	this->lift         = -20.0;

}
