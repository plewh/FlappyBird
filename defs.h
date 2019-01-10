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

#define Log(comment) fprintf(stderr, "|%-14s %-13s:%-3d | %s\n", __FILE__, __func__, __LINE__, comment);

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
	PIPE_SPAWN

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
