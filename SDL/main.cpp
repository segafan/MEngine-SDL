#include "MEngine.h"

int main(int argc, char *argv[])
{
	if (Init() != 0)
		return 1;

	//TODO: Move this to a better place & do it so it shows keyboard only when needed
	SDL_StartTextInput();

	Logger *logger = new Logger;

	//Create Display
	Display* display = new Display();

	if (!display->Create2D("SDL", 1024, 768, SDL_WINDOW_SHOWN, true, false, 60.0f, logger))
		return 1;

	Global *global = new Global(display, logger);

	FPSTimer FPS(60.0f);
	FPS.Start();

	bool running = true;

	global->display.SetRenderColor(255, 255, 0);

	while (running)
	{
		if (FPS.Tick())
		{
			//FPS Counter
			FPSCounter();

			//Input
			global->input.keyboard.Clear();
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
			if (global->input.keyboard.OnKeyPress(SDLK_F2))
				CreateScreenshot(display->GetWindow(), display->GetRenderer());

			//Update

			

			//Draw

			global->display.Clear();
			
			

			global->display.Present();
		}
	}

	delete display;
	delete global;
	delete logger;

	SDL_StopTextInput();

	Quit();

	return 0;
}