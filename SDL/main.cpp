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

	TextureManager* textures = new TextureManager(window, renderer);
	AudioManager* audio = new AudioManager();

	Input *input = new Input();

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
		while (SDL_PollEvent(input->event))
		{
			if (input->event->type == SDL_QUIT)
				running = false;
			if (input->keyboard->isKeyPressedOnce(SDLK_ESCAPE))
				running = false;

			input->keyboard->Update();
		}

		//Screenshot Creation
		if (input->keyboard->isKeyPressedOnce(SDLK_F2))
			CreateScreenshot(window, renderer);

		//Update



		//Draw
		SDL_RenderClear(renderer);
		


		SDL_RenderPresent(renderer);

		//FPS Stuff
		FPS.Update();

		FPSCounter(timer);
	}

	delete audio;
	delete textures;
	delete timer;
	delete logger;
	delete input;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	Quit();

	return 0;
}