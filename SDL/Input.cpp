#include "Input.h"

bool PollEvent(Input* input)
{
	//TODO: Do something so this is not static (probably move this into the Input class)
	static bool clearSinglePressData = true;

	if (clearSinglePressData)
	{
		input->keyboard.Clear();
		input->mouse.Clear();
		clearSinglePressData = false;
	}

	if (SDL_PollEvent(&input->event) > 0)
	{
		input->mouse.Update();
		input->keyboard.Update();
		input->text.Update();

		return true;
	}
	else
	{
		clearSinglePressData = true;
		return false;
	}
}
