#include "app.h"
#include <SDL2/SDL.h>
#include <cstdio>
#include "renderer.h"
#include "scene.h"
#include "defs.h"

App::App() {

	renderer     = new Renderer;
	eventManager = new EventManager;
	eventManager->AddListener(this);
	sceneManager = new SceneManager(renderer, eventManager);
	eventManager->AddListener(sceneManager);

	running      = true;

	lastTicks    = 0.0;
	tickRate     = 1.0 / TICK_RATE;
	lag          = 0.0;

}

App::~App() {

	delete(renderer);

}

void App::Run() {

	while (running) {

		PumpSystemEvents();
		eventManager->PumpEvents();

		for (lag += GetDelta(); lag >= tickRate; lag -= tickRate) {

			sceneManager->Tick();

		}

		renderer->Clear();
		sceneManager->DoFrame();
		renderer->Present();

	}

}

double App::GetDelta() {

	double ticks = SDL_GetTicks();
	double delta = ticks - lastTicks;
	lastTicks = ticks;

	return delta/1000.0;

}

void App::PumpSystemEvents() {

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		
		switch (event.type) {
			
			case SDL_QUIT:
				eventManager->Post(new Event(QUIT, NULL));
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {

					case SDLK_SPACE:
						eventManager->Post(new Event(KEYDOWN, " "));
						break;

					case SDLK_q:
						eventManager->Post(new Event(KEYDOWN, "q"));
						break;

					default:
						break;

				}

			default:
				break;

		}

	}

}

void App::Responder(Event* event) {

	if (event->type == QUIT)
		running = false;

}
