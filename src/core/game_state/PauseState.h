#pragma once
#include "GameState.h"

class PauseState : public GameState
{
  public:
	void OnEnter() override;
};