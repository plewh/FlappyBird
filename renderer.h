#pragma once
#include "defs.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

struct Texture {

	Texture(SDL_Texture* tex, int w, int h, int frames);

	SDL_Texture* tex;
	int          w;
	int          h;
	int          frames;

};

struct Renderer {

	Renderer();
	~Renderer();

	void Blit(
		double x, double y,
		int    w, int    h,
		double angle, 
		Texture* tex, 
		double scale, 
		double alpha,
		int frame,
		int offset);
	void Print(int x, int y, char const* text);
	void DrawLine(int aX, int aY, int bX, int bY);
	void Clear();
	void Present();
	Texture* GetTexture(texture_e tag);

	private:
	SDL_Window*   window;
	SDL_Renderer* renderer;
	SDL_Texture*  target;

};
