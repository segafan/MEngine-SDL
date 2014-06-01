#include "MEngine.h"

#include "GUITextBox.h"
#include "GUIButton.h"

int main(int argc, char *argv[])
{
	if (Init() != 0)
		return 1;

	SDL_StartTextInput();

	Logger *logger = new Logger;

	//Create Window
	SDL_Window *window = CreateAndLogWindow("SDL", 1024, 768, SDL_WINDOW_SHOWN, logger);

	if (window == NULL)
		return 1;

	//Create Renederer
	SDL_Renderer *renderer = NULL;
	renderer = CreateAndLogRenderer(window, logger, true, false, 60);

	if (renderer == NULL)
		return 1;

	Global *global = new Global(window, renderer, logger);
	
	global->gfx.AddFont("resources/fonts/Arial.ttf", "FONT", 12);

	Timer *timer = new Timer();
	timer->Start();
	
	FPSTimer FPS(60.0f);
	FPS.Start();

	bool running = true;

	SDL_RenderSetLogicalSize(renderer, 1024, 768);

	global->screen.SetRenderColor(255, 255, 0);
	
	GUITextBox textBox(global, "1");

	while (running)
	{
		if (FPS.Tick())
		{
			//Input
			while (SDL_PollEvent(&global->input.event))
			{
				if (global->input.event.type == SDL_QUIT)
					running = false;
				if (global->input.keyboard.IsKeyPressed(SDLK_ESCAPE))
					running = false;

				global->input.mouse.Update();
				global->input.keyboard.Update();
				global->input.text.Update();
			}

			//Screenshot Creation
			if (global->input.keyboard.IsKeyPressedOnce(SDLK_F2))
				CreateScreenshot(window, renderer);

			//Update			

			global->input.text.SetTextInputActive("RANDOM", true);

			textBox.Update();

			//Draw

			global->screen.RenderClear();
			
			textBox.Draw();

			global->screen.RenderPresent();

			//FPS StufF

			FPSCounter(timer);
		}
	}

	delete global;
	delete timer;
	delete logger;

	Quit();

	return 0;
}