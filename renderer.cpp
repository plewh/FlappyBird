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

static Texture* LoadTex(SDL_Renderer* renderer, char const* fPath);

Texture::Texture(SDL_Texture* tex, int w, int h) {

	this->tex = tex;
	this->w   = w;
	this->h   = h;

}

Renderer::Renderer() {

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(WIN_X, WIN_Y, 0, &window, &renderer);

	TTF_Init();

	dunno       = LoadTex(renderer, "ass/dunno.bmp");
	tex_bckgnd  = LoadTex(renderer, "ass/tex_bckgnd.bmp");
	tex_flap    = LoadTex(renderer, "ass/tex_flap.bmp");
	tex_mask    = LoadTex(renderer, "ass/tex_mask.bmp");
	tex_menu    = LoadTex(renderer, "ass/tex_menu.bmp");
	tex_pipe    = LoadTex(renderer, "ass/tex_pipe.bmp");
	tex_splash  = LoadTex(renderer, "ass/tex_splash.bmp");
	tex_splash1 = LoadTex(renderer, "ass/tex_splash1.bmp");

}

Renderer::~Renderer() {

	TTF_Quit();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

}

void Renderer::Blit(double x, double y, Texture* tex) {

	SDL_Rect dQuad = {(int)x, (int)y, tex->w, tex->h};
	SDL_RenderCopyEx(
		renderer,
		tex->tex,
		NULL,
		&dQuad,
		0.0,
		NULL,
		SDL_FLIP_NONE
	);

}

	/*
void Renderer::Blit(double x, double y, double angle, asset_e id, double scale) {

	Asset* ass = GetAssFromID(id);

	SDL_Rect r = {(int)x, (int)y, ass->w * scale, ass->h * scale};

	SDL_RenderCopyEx(
		renderer,                   // SDL context
		ass->tex,                   // texture
		NULL,                       // src rect
		&r,                         // dst rect 
		angle,                      // angle
		NULL,                       // centre
		SDL_FLIP_NONE               // don't flip the texture
	);             

}

void Renderer::Print(int x, int y, char const* text) {

	SDL_Rect r = {x, y, 0, 0};
	TTF_SizeText(GetFont(), text, &r.w, &r.h);
	SDL_Surface* surf = TTF_RenderText_Solid(GetFont(), text, *GetFontColour());
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
	*/

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

		default:
			return dunno;

	}

}

static Texture* LoadTex(SDL_Renderer* renderer, char const* fPath) {

	SDL_Surface* surf = SDL_LoadBMP(fPath);
	SDL_SetColorKey(surf, true, SDL_MapRGB(surf->format, 0, 255, 255));
	SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);

	int w, h;
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	Texture* tex = new Texture(text, w, h);

	return tex;

}
