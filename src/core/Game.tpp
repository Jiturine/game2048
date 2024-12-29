#pragma once
#include "Game.h"

template <class T>
	requires std::is_base_of_v<GameState, T>
void Game::SwitchState()
{
	if (currentState != nullptr)
	{
		currentState->OnExit();
	}
	currentState = std::make_unique<T>();
	currentState->OnEnter();
}
