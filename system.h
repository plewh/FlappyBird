#pragma once
#include "defs.h"

struct Renderer;
struct EntityManager;
struct EventManager;

void BlitSpriteSystem(Renderer* renderer, EntityManager* entMan);
void AngleTickSystem(EntityManager* entMan);
void SplashTickSystem(EntityManager* entMan, EventManager* eventManager);
void MaskTickSystem(EntityManager* entMan, EventManager* eventManager);

