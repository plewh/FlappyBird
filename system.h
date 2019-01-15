#pragma once
#include "defs.h"

struct Renderer;
struct EntityManager;
struct EventManager;

void BlitSpriteSystem (
	EntityManager* entMan, int id, Renderer* renderer, int layer);
void AngleTickSystem (
	EntityManager* entMan, int id);
void SplashTickSystem (
	EntityManager* entMan, int id, EventManager* eventManager);
void MaskTickSystem (
	EntityManager* entMan, int id, EventManager* eventManager);
void FlappyPhysicsSystem (
	EntityManager* entMan, int id);
void FlappyInputSystem (
	EntityManager* entMan, int id);
void PipeSpawnerTickSystem (
	EntityManager* entMan, int id, EventManager* eventManager);
void PipeTickSystem (
	EntityManager* entMan, int id, EventManager* eventManager);
void PipeSpriteSystem (
	EntityManager* entMan, int id, Renderer* renderer);
void CollisionHandlerSystem(
	EntityManager* entMan, int id, EventManager* eventManager);
void HudSystem (
	EntityManager* entMan, int id, Renderer* renderer);
