//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef VERTEX_H
#define VERTEX_H

#include "Vector3.h"
#include "Vector2.h"

class Vertex
{
public:
	static const int SIZE = 3;
	Vector3 pos;
    Vector2 texCoord;
    Vector3 normal;

	Vertex(Vector3 pos, Vector2 texCoord = Vector2(0, 0), Vector3 normal = Vector3(0, 0, 0))
	{
		 this->pos = pos;
		this->texCoord = texCoord;
	}
};

#endif