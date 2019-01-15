#pragma once
#include <vector>
#include <cstdio>
#include <cstddef>
#include <cstring>

#define WIN_X      960
#define WIN_Y      1280
#define TICK_RATE  60.0
#define MAX_ENTS   32
#define MAX_EVENTS 16
#define PIPE_GAP   312.0
#define MAX_LAYER  3

#define Log(comment) fprintf(stderr, "|%-14s %-14s:%-3d | %s\n", __FILE__, __func__, __LINE__, comment);

void InitRandom();
int  GetRandom(int a, int b);

enum component_tag_e {

	POSITION,
	SPRITE,
	ANGLE,
	SPLASH_TICK,
	SIZE,
	MASK_TICK,
	FLAPPY_PHYSICS,
	FLAPPY_INPUT,
	SPRITE_SPAN,
	ANIM,
	PIPE_SPAWN,
	PIPE,
	PIPE_SPRITE,
	COLLIDABLE,
	SCORE,
	SCORELISTENER

};

enum texture_e {

	DUNNO,
	TEX_BCKGND,
	TEX_FLAP,
	TEX_MASK,
	TEX_MENU,
	TEX_PIPE,
	TEX_SPLASH,
	TEX_SPLASH1,
	TEX_GND

};

enum scene_e {

	TITLE,
	GAME

};
