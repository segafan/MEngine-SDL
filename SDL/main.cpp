#include "MEngine.h"

int main(int argc, char *argv[])
{
	if (Init() != 0)
		return 1;

	Logger *logger = new Logger;

	//Create Window
	SDL_Window *window = CreateAndLogWindow("SDL", 1024, 768, SDL_WINDOW_SHOWN, logger);

	if (window == NULL)
		return 1;

	//Create Renederer
	SDL_Renderer *renderer = NULL;
	renderer = CreateAndLogRenderer(window, logger, true, false);

	if (renderer == NULL)
		return 1;

	Global *global = new Global(window, renderer);

	Timer *timer = new Timer();
	timer->Start();
	
	FPSTimer FPS(60.0f);
	FPS.Start();

	bool running = true;

	SDL_RenderSetLogicalSize(renderer, 1024, 768);

	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	
	while (running)
	{
		//Input
		while (SDL_PollEvent(global->input->event))
		{
			if (global->input->event->type == SDL_QUIT)
				running = false;
			if (global->input->keyboard->isKeyPressedOnce(SDLK_ESCAPE))
				running = false;

			global->input->keyboard->Update();
		}

		//Screenshot Creation
		if (global->input->keyboard->isKeyPressedOnce(SDLK_F2))
			CreateScreenshot(window, renderer);

		//Update



		//Draw
		SDL_RenderClear(renderer);
		


		SDL_RenderPresent(renderer);

		//FPS Stuff
		FPS.Update();

		FPSCounter(timer);
	}

	delete global;
	delete timer;
	delete logger;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	Quit();

	return 0;
}