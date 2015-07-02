#include "Input.h"

bool Input::PollEvent()
{
	if (clearSinglePressData)
	{
		keyboard.Clear();
		mouse.Clear();
		clearSinglePressData = false;
	}

	if (SDL_PollEvent(&event) > 0)
	{
		mouse.Update();
		keyboard.Update();
		text.Update();

		return true;
	}
	else
	{
		clearSinglePressData = true;
		return false;
	}
}
