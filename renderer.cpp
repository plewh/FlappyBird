#include "renderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

static Texture* dunno;
static Texture* tex_bckgnd;
static Texture* tex_flap;
static Texture* tex_mask;
static Texture* tex_menu;
static Texture* tex_pipe;
static Texture* tex_splash;
static Texture* tex_splash1;
static Texture* tex_gnd;

static TTF_Font* font;
static SDL_Color red;
static SDL_Color white;
static SDL_Color black;
static SDL_Color yellow;

static Texture* LoadTex(SDL_Renderer* renderer, char const* fPath);
static Texture* LoadTex(SDL_Renderer* renderer, char const* fPath, int w, int h, int frames);

Texture::Texture(SDL_Texture* tex, int w, int h, int frames) {

	this->tex    = tex;
	this->w      = w;
	this->h      = h;
	this->frames = frames;

}

Renderer::Renderer() {

	Log("Renderer starting");
	Log("Starting SDL...");
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(WIN_X, WIN_Y, 0, &window, &renderer);
	SDL_SetWindowResizable(window, SDL_FALSE);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	Log("Starting SDL_ttf...");
	TTF_Init();
	Log("Loading fonts...");
	font = TTF_OpenFont("ass/arial.ttf", 80);
	red.r   = 155;
	red.g   = 50;
	red.b   = 50;
	red.a   = 255;
	white.r = 255;
	white.g = 255;
	white.b = 255;
	white.a = 255;
	black.r = 0;
	black.b = 0;
	black.g = 0;
	black.a = 255;
	yellow.r = 255;
	yellow.b = 0;
	yellow.g = 211;
	yellow.a = 255;

	Log("Loading textures...");
	dunno       = LoadTex(renderer, "ass/dunno.bmp");
	tex_bckgnd  = LoadTex(renderer, "ass/tex_bckgnd.bmp");
	tex_flap    = LoadTex(renderer, "ass/tex_flap.bmp");
	tex_mask    = LoadTex(renderer, "ass/tex_mask.bmp");
	tex_menu    = LoadTex(renderer, "ass/tex_menu.bmp");
	tex_pipe    = LoadTex(renderer, "ass/tex_pipe.bmp");
	tex_splash  = LoadTex(renderer, "ass/tex_splash.bmp");
	tex_splash1 = LoadTex(renderer, "ass/tex_splash1.bmp");
	tex_gnd     = LoadTex(renderer, "ass/tex_gnd.bmp", 45, 160, 2);

}

Renderer::~Renderer() {

	Log("Cleaning up renderer");
	TTF_Quit();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

}

void Renderer::Blit(
	double x, 
	double y,
	int    w,
	int    h,
	double angle, 
	Texture* tex, 
	double scale, 
	double alpha, 
	int frame,
	int offset) {

	SDL_Rect sQuad;
	if ( offset == -1 ) {
		sQuad.x = w * frame;
		sQuad.y = 0; 
		sQuad.w = w;
		sQuad.h = h;
	} else {
		sQuad.x = frame;
		sQuad.y = 0; 
		sQuad.w = w;
		sQuad.h = h;

	}

	SDL_Rect dQuad = {(int)x, (int)y, (int)(w * scale), (int)(h * scale)};
	SDL_SetTextureAlphaMod(tex->tex, alpha);
	SDL_RenderCopyEx(
		renderer,
		tex->tex,
		&sQuad,
		&dQuad,
		angle,
		NULL,
		SDL_FLIP_NONE
	);

}

void Renderer::Print(int x, int y, char const* text) {

	SDL_Rect r = {x, y, 0, 0};
	TTF_SizeText(font, text, &r.w, &r.h);
	SDL_Surface* surf = TTF_RenderText_Solid(font, text, red );
	SDL_Texture* tex  = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_RenderCopyEx(
		renderer,
		tex,
		NULL,
		&r,
		0.0,
		NULL,
		SDL_FLIP_NONE
	);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(tex);

}

void Renderer::DrawLine(int aX, int aY, int bX, int bY) {

	SDL_RenderDrawLine(renderer, aX, aY, bX, bY);

}

void Renderer::Clear() {
	
	SDL_RenderClear(renderer);

}

void Renderer::Present() {

	SDL_RenderPresent(renderer);

}

Texture* Renderer::GetTexture(texture_e tag) {

	switch (tag) {

		case DUNNO:
			return dunno;

		case TEX_BCKGND:
			return tex_bckgnd;

		case TEX_FLAP:
			return tex_flap;

		case TEX_MASK:
			return tex_mask;

		case TEX_MENU:
			return tex_menu;

		case TEX_PIPE:
			return tex_pipe;

		case TEX_SPLASH:
			return tex_splash;

		case TEX_SPLASH1:
			return tex_splash1;

		case TEX_GND:
			return tex_gnd;

		default:
			return dunno;

	}

}

static Texture* LoadTex(SDL_Renderer* renderer, char const* fPath) {

	SDL_Surface* surf = SDL_LoadBMP(fPath);
	SDL_SetColorKey(surf, true, SDL_MapRGB(surf->format, 0, 255, 255));
	SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_SetTextureBlendMode(text, SDL_BLENDMODE_BLEND);
	SDL_FreeSurface(surf);

	int w, h;
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	Texture* tex = new Texture(text, w, h, 0);

	return tex;

}

static Texture* LoadTex(SDL_Renderer* renderer, char const* fPath, int w, int h, int frames) {

	SDL_Surface* surf = SDL_LoadBMP(fPath);
	SDL_SetColorKey(surf, true, SDL_MapRGB(surf->format, 0, 255, 255));
	SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_SetTextureBlendMode(text, SDL_BLENDMODE_BLEND);
	SDL_FreeSurface(surf);

	Texture* tex = new Texture(text, w, h, frames);

	return tex;

}
