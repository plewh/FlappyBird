#pragma once
#include "defs.h"

struct Renderer;
struct EntityManager;
struct EventManager;

void BlitSpriteSystem     (EntityManager* entMan, Renderer* renderer);
void AngleTickSystem      (EntityManager* entMan);
void SplashTickSystem     (EntityManager* entMan, EventManager* eventManager);
void MaskTickSystem       (EntityManager* entMan, EventManager* eventManager);
void FlappyPhysicsSystem  (EntityManager* entMan);
void FlappyInputSystem    (EntityManager* entMan);
void PipeSpawnerTickSystem(EntityManager* entMan, EventManager* eventManager);
void PipeTickSystem       (EntityManager* entMan, EventManager* eventManager);
void PipeSpriteSystem     (EntityManager* entMan, Renderer* renderer);
