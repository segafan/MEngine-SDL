//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <vector>

class StateManager
{
public:
	StateManager();

	void SetState(int state);

	int GetState();

	bool IsState(int state);

	void PushState(int state);

	void PopState();
private:
	std::vector<int> states;
};

#endif