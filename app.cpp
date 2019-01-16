#include "app.h"
#include <SDL2/SDL.h>
#include "renderer.h"
#include "scene.h"
#include "event.h"

App::App() {

	Log("App starting");
	renderer     = new Renderer;
	eventManager = new EventManager;
	eventManager->AddListener(this);
	sceneManager = new SceneManager(renderer, eventManager);
	eventManager->AddListener(sceneManager);

	running      = true;

	lastTicks    = 0.0;
	tickRate     = 1.0 / TICK_RATE;
	lag          = 0.0;

	InitRandom();

}

App::~App() {

	Log("App cleaning up...");
	delete(renderer);
	delete(eventManager);
	delete(sceneManager);

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
				eventManager->Post(new Event(QUIT, ""));
				break;

			case SDL_KEYDOWN:
				if (event.key.repeat == 1)
					break;

				switch (event.key.keysym.sym) {

					case SDLK_SPACE:
						eventManager->Post(new Event(KEYDOWN, " "));
						break;

					case SDLK_q:
						eventManager->Post(new Event(KEYDOWN, "q"));
						break;

					case SDLK_RETURN:
						eventManager->Post(new Event(KEYDOWN, "ENTER"));
						break;

					default:
						break;

				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				eventManager->Post(new Event(MOUSE_BUTT, " "));
				break;

			default:
				break;

		}

	}

}

void App::Responder(Event* event) {

	if (event->type == QUIT)
		running = false;

}
