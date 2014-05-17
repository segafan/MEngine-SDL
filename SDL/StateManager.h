#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <map>
#include <iostream>

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
		if (this->state == state)
			return true;
		else
			return false;
	}
private:
	std::string state;
};

#endif