#pragma once

#define WIN_X      1024
#define WIN_Y      786
#define TICK_RATE  60.0
#define MAX_ENTS   32
#define MAX_EVENTS 16

void PrintLog(int line, const char* func, const char* file, char* comment);

enum component_tag_e {

	POSITION,
	SPRITE

};

enum texture_e {

	DUNNO,
	TEX_BCKGND,
	TEX_FLAP,
	TEX_MASK,
	TEX_MENU,
	TEX_PIPE,
	TEX_SPLASH,
	TEX_SPLASH1

};

enum scene_e {

	TITLE,
	GAME

};
