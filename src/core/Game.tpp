#pragma once
#include "Game.h"

template <class T>
void Game::SwitchState()
{
	if (currentState != nullptr)
	{
		currentState->OnExit();
	}
	currentState = std::make_unique<T>();
	currentState->OnEnter();
}
