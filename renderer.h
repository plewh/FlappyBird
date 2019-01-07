#pragma once
#include <vector>
#include "defs.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

struct Texture {

	Texture(SDL_Texture* tex, int w, int h);

	SDL_Texture* tex;
	int          w;
	int          h;

};

struct Renderer {

	Renderer();
	~Renderer();

	void Blit(double x, double y, Texture* tex);
	//void Blit(double x, double y, double angle, asset_e id, double scale);
	//void Print(int x, int y, char const* text);
	void Clear();
	void Present();
	Texture* GetTexture(texture_e tag);

	private:
	SDL_Window* window;
	SDL_Renderer* renderer;

};
