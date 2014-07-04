#ifndef CAMERA_H
#define CAMERA_H

#include "Rect.h"

class Camera
{
public:
	Camera()
	{
		SetView(Rect(0, 0, 1024, 768));
	}


	void TranslateView(int x, int y)
	{
		m_view.Translate(x, y);
	}

	void TranslateViewX(int x)
	{
		m_view.TranslateX(x);
	}
	void TranslateViewY(int y)
	{
		m_view.TranslateY(y);
	}

	void SetSize(int w, int h)
	{
		m_view.SetSize(w, h);
	}

	void SetCenter(int x, int y)
	{
		m_view.SetX(x - (m_view.GetW() / 2));
		m_view.SetY(y - (m_view.GetH() / 2));
	}

	Rect& GetView() { return m_view; }

	void SetView(Rect view) { m_view = view; }

private:
	Rect m_view;
};

#endif