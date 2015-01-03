//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef RANDOM_H
#define RANDOM_H

#include "Config.h"

namespace Random
{
	bool IsSafe();

	void Init();

	int Number(int min, int max);

	int Number(int max);

	bool Bool();
}
#endif