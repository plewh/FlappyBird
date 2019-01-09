#pragma once
#include "defs.h"
#include "event.h"

struct Texture;
struct Event;

struct Component {

	component_tag_e tag;

};

struct PositionComponent:Component {

	PositionComponent(double x, double y);

	double x;
	double y;

};

struct SpriteComponent:Component {

	SpriteComponent(texture_e tName, double scale, double alpha);

	texture_e tName;
	double    scale;
	double    alpha;

};

struct ListenerComponent:Component, EventListener {

	ListenerComponent();
	void Responder(Event* event);

};

struct RotateComponent:Component {

	RotateComponent(double angle, double angleAcc);
	
	double angle;
	double angleAcc;

};

struct SplashTickComponent:Component {

	SplashTickComponent(double scaleAcc, double rotAcc);

	double scaleAcc;
	double rotAcc;
	bool   ended;

};

struct SizeComponent:Component {

	SizeComponent(double w, double h);

	double w;
	double h;

};

struct MaskTickComponent:Component {

	MaskTickComponent(double decay);

	double decay;
	double value;

};

struct FlappyPhysicsComponent:Component {

	FlappyPhysicsComponent();

	double grav;
	double yAcc;

};

struct FlappyInputComponent:Component {

	FlappyInputComponent(EventManager* eventManager);

	EventManager* eventManager;
	double lift;

};

struct SpriteSpanComponent:Component {

	SpriteSpanComponent(int repeat);
	int repeat;

};

struct AnimComponent:Component {

	AnimComponent(int fCount, double decay, int w, int h, int offset);
	int    fCount;
	int    currFrame;
	double value;
	double decay;
	int    w;
	int    h;
	int    offset;

};
