#pragma once
#include "GameState.h"
#include "Text.h"

class StartState : public GameState
{
  public:
	Type GetType() override
	{
		return Type::Start;
	}
	void Render() override;
	void OnExit() override;
};