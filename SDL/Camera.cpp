#include "Camera.h"

Camera::Camera()
{
	SetView(Rect(0, 0, 1024, 768));
}

void Camera::TranslateView(int x, int y)
{
	m_view.Translate(x, y);
}

void Camera::TranslateViewX(int x)
{
	m_view.TranslateX(x);
}

void Camera::TranslateViewY(int y)
{
	m_view.TranslateY(y);
}

void Camera::SetSize(int w, int h)
{
	m_view.SetSize(w, h);
}

void Camera::SetCenter(Point& center)
{
	m_view.SetX(center.getX() - (m_view.GetW() / 2));
	m_view.SetY(center.getY() - (m_view.GetH() / 2));
}

void Camera::SetCenter(int x, int y)
{
	m_view.SetX(x - (m_view.GetW() / 2));
	m_view.SetY(y - (m_view.GetH() / 2));
}

int& Camera::GetX()
{
	return m_view.GetX();
}
int& Camera::GetY()
{
	return m_view.GetY();
}
int& Camera::GetW()
{
	return m_view.GetW();
}
int& Camera::GetH()
{
	return m_view.GetH();
}

Rect& Camera::GetView()
{
	return m_view;
}

void Camera::SetView(Rect view)
{
	m_view = view;
}
