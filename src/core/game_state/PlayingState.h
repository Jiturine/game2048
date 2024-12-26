#pragma once
#include "GameState.h"
#include "Game.h"
class PlayingState : public GameState
{
  public:
	Type GetType() override
	{
		return Type::Playing;
	}
	void Update() override;
	void Render() override;
};