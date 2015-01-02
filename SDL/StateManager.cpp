#include "StateManager.h"

StateManager::StateManager()
{
	states.push_back(0);
}

void StateManager::SetState(int state)
{
	states[states.size() - 1] = state;
}

int StateManager::GetState()
{
	return states[states.size() - 1];
}

bool StateManager::IsState(int state)
{
	return (this->states[states.size() - 1] == state);
}

void StateManager::PushState(int state)
{
	states.push_back(state);
}

void StateManager::PopState()
{
	states.pop_back();
}
