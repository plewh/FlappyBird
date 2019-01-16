#include "component.h"

PositionComponent::PositionComponent(double x, double y) {

	this->tag = POSITION;
	this->x = x;
	this->y = y;

}

SpriteComponent::SpriteComponent(texture_e tName, double scale, double alpha, int layer) {

	this->tag   = SPRITE;
	this->tName = tName;
	this->scale = scale;
	this->alpha = alpha;
	this->layer = layer;

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
	this->grav  = 1.2;
	this->yAcc  = 0.0;

}

FlappyInputComponent::FlappyInputComponent(EventManager* eventManager) {

	this->tag          = FLAPPY_INPUT;
	this->eventManager = eventManager;
	this->lift         = -40.0;

}

SpriteSpanComponent::SpriteSpanComponent(int repeat) {

	this->tag          = SPRITE_SPAN;
	this->repeat       = repeat;

}

AnimComponent::AnimComponent(int fCount, double decay, int w, int h, int offset) {

	this->tag          = ANIM;
	this->fCount       = fCount;
	this->currFrame    = 0;
	this->value        = 1.0;
	this->decay        = decay;
	this->w            = w;
	this->h            = h;
	this->offset       = offset;

}

PipeSpawnerComponent::PipeSpawnerComponent(double decay) {

	this->tag          = PIPE_SPAWN;
	this->value        = 1.0;
	this->decay        = decay;

}

PipeComponent::PipeComponent(double offset, double xAcc) {

	this->tag          = PIPE;
	this->offset       = offset;
	this->xAcc         = xAcc;
	this->hasScore     = true;

}

PipeSpriteComponent::PipeSpriteComponent(texture_e tName) {

	this->tag          = PIPE_SPRITE;
	this->tName        = tName;

}

CollidableComponent::CollidableComponent() {

	this->tag          = COLLIDABLE;

}

ScoreComponent::ScoreComponent(int maxScore) {

	this->tag          = SCORE;
	this->score        = 0;
	this->maxScore     = maxScore;

}

ScoreListenerComponent::ScoreListenerComponent(ScoreComponent* scr) {

	this->tag          = SCORELISTENER;
	this->scr          = scr;

}

void ScoreListenerComponent::Responder(Event* event) {

	if ( event->type == INC_SCORE ) {
		this->scr->score += 1;
	}

}
