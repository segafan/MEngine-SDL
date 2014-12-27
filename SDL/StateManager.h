//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <string>

class StateManager
{
public:
	StateManager()
	{
		state = "";
	}

	void SetState(std::string state)
	{
		this->state = state;
	}

	std::string GetState()
	{
		return state;
	}

	bool IsState(std::string state)
	{
		return (this->state == state);
	}
private:
	std::string state;
};

#endif