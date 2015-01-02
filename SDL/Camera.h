#ifndef CAMERA_H
#define CAMERA_H

#include "Rect.h"

class Camera
{
public:
	Camera();

	void TranslateView(int x, int y);

	void TranslateViewX(int x);
	void TranslateViewY(int y);

	void SetSize(int w, int h);

	void SetCenter(int x, int y);

	int& GetX();
	int& GetY();
	int& GetW();
	int& GetH();

	Rect& GetView();

	void SetView(Rect view);

private:
	Rect m_view;
};

#endif