#pragma once
#include "GameState.h"
#include "Text.h"

class GameOverState : public GameState
{
  public:
	Type GetType() override
	{
		return Type::GameOver;
	}
	void Render() override;
};