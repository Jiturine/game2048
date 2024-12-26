#pragma once
#include "Log.h"

class GameState
{
  public:
	virtual ~GameState() = default;
	enum class Type
	{
		Start,
		Playing,
		Pause,
		GameOver
	};
	virtual Type GetType() = 0;
	virtual void OnEnter() {}
	virtual void Update() {}
	virtual void Render() {}
	virtual void OnExit() {}
};