#include "Display.h"

Display::Display()
{
	window = NULL;
	renderer = NULL;
	glContext = NULL;

	ScreenWidth = 0;
	ScreenHeight = 0;
}

Display::~Display()
{
	if (glContext != NULL)
		SDL_GL_DeleteContext(glContext);

	glContext = NULL;

	if (renderer != NULL)
		SDL_DestroyRenderer(renderer);

	renderer = NULL;

	if (window != NULL)
		SDL_DestroyWindow(window);

	window = NULL;
}

bool Display::Create2D(std::string title, int w, int h, int flags, bool TargetTexture, bool VSYNC, float FPS)
{
	is3D = false;

	window = NULL;
	window = CreateAndLogWindow(title.c_str(), w, h, flags);

	if (window == NULL)
	{
		LOG_ERROR("Couldn't create Window! Error: " << SDL_GetError());
		return false;
	}

	renderer = NULL;
	renderer = CreateAndLogRenderer(window, TargetTexture, VSYNC, FPS);

	if (renderer == NULL)
	{
		LOG_ERROR("Couldn't create Renderer! Error: " << SDL_GetError());
		return false;
	}

	LOG_PURE("Using 2D");
	Logger::Instance()->NewLine();

	camera.SetSize(GetW(), GetH());

	return true;
}

bool Display::Create3D(std::string title, int w, int h, int flags)
{
	is3D = true;

	if (!ContainsFlag(flags, SDL_WINDOW_OPENGL))
	{
		LOG_ERROR("Flag must contain SDL_WINDOW_OPENGL if using 3D!");
		SDL_ShowSimpleMessageBox(0, "Error!", "Flag must contain SDL_WINDOW_OPENGL if using 3D!", NULL);
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = NULL;
	window = CreateAndLogWindow(title.c_str(), w, h, flags);

	if (window == NULL)
	{
		LOG_ERROR("Couldn't create Window! Error: " << SDL_GetError());
		return false;
	}

	glContext = NULL;
	glContext = SDL_GL_CreateContext(window);

	if (glContext == NULL)
	{
		LOG_ERROR("Couldn't create glContext! Error: " << SDL_GetError());
		return false;
	}

	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		LOG_ERROR("GLEW failed to initalize!");
	}

	LOG_PURE("Vendor: " << glGetString(GL_VENDOR));
	LOG_PURE("Renderer: " << glGetString(GL_RENDERER));
	LOG_PURE("OpenGL Version: " << glGetString(GL_VERSION));
	LOG_PURE("GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION));

	Logger::Instance()->NewLine();

	glEnable(GL_DEPTH_TEST);

	LOG_PURE("Using 3D");
	Logger::Instance()->NewLine();

	return true;
}

Rect& Display::GetSize()
{
	SDL_GetWindowSize(window, &ScreenWidth, &ScreenHeight);

	ScreenPos.SetPosition(0, 0, ScreenWidth, ScreenHeight);

	return ScreenPos;
}

int& Display::GetW()
{
	SDL_GetWindowSize(window, &ScreenWidth, NULL);
	return ScreenWidth;
}

int& Display::GetH()
{
	SDL_GetWindowSize(window, NULL, &ScreenHeight);
	return ScreenHeight;
}

SDL_Window* Display::GetWindow()
{
	return window;
}

SDL_Renderer* Display::GetRenderer()
{
	return renderer;
}

void Display::Clear()
{
	if (is3D)
	{
		glClearColor((float)(color.r / 255), (float)(color.g / 255), (float)(color.b / 255), (float)(color.a / 255));
		//TODO: Add Other buffers to clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	else
	{
		if (renderer != NULL)
			SDL_RenderClear(renderer);
	}
}

void Display::Present()
{
	if (is3D)
	{
		SDL_GL_SwapWindow(window);
	}
	else
	{
		if (renderer != NULL)
			SDL_RenderPresent(renderer);
	}
}

void Display::SetRenderColor(Color color)
{
	this->color = color;

	if (renderer != NULL)
	{
		if (SDL_SetRenderDrawColor(renderer, (Uint8)color.r, (Uint8)color.g, (Uint8)color.b, (Uint8)color.a) != 0)
		{
			LOG_ERROR("Couldn't set Render Draw Color! Error: " << SDL_GetError());
		}
	}
}

void Display::SetRenderColor(SDL_Color color)
{
	this->color = color;

	if (renderer != NULL)
	{
		if (SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) != 0)
		{
			LOG_ERROR("Couldn't set Render Draw Color! Error: " << SDL_GetError());
		}
	}
}

void Display::SetRenderColor(unsigned short r, unsigned short g, unsigned short b)
{
	color.SetColor(r, g, b, 255);

	if (renderer != NULL)
	{
		if (SDL_SetRenderDrawColor(renderer, (Uint8)r, (Uint8)g, (Uint8)b, 255) != 0)
		{
			LOG_ERROR("Couldn't set Render Draw Color! Error: " << SDL_GetError());
		}
	}
}

void Display::SetRenderColor(unsigned short r, unsigned short g, unsigned short b, unsigned short a)
{
	color.SetColor(r, g, b, a);

	if (renderer != NULL)
	{
		if (SDL_SetRenderDrawColor(renderer, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a) != 0)
		{
			LOG_ERROR("Couldn't set Render Draw Color! Error: " << SDL_GetError());
		}
	}
}

void Display::PushRenderColor()
{
	renderColorStack.push_back(color);
}

void Display::PopRenderColor()
{
	if (renderColorStack.size() > 0)
	{
		SetRenderColor(renderColorStack[renderColorStack.size() - 1]);
		renderColorStack.pop_back();
	}
	else
		LOG_DEBUG("Can't pop back render color because no render color is pushed to stack");
}

Color& Display::GetRenderColor()
{
	return color;
}

bool Display::Is3D()
{
	return is3D;
}

void Display::SetCamera(Camera& camera)
{
	this->camera = camera;
}

Camera& Display::GetCamera()
{
	return camera;
}