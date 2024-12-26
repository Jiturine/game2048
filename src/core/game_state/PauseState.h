#pragma once
#include "GameState.h"
#include "ScoreManager.h"
#include "Text.h"

class PauseState : public GameState
{
  public:
	Type GetType() override
	{
		return Type::Pause;
	}
	void Render() override;
};