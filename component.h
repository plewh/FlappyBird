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

	SpriteComponent(texture_e tName);

	texture_e tName;

};

struct ListenerComponent:Component, EventListener {

	ListenerComponent();
	void Responder(Event* event);

};
