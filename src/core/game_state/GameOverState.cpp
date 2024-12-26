#include "GameOverState.h"

void GameOverState::Render()
{
	Text::Render("Game over, Press to restart ...", 200.0f, 600.0f, 1.2f, glm::vec3(0.0f, 0.0f, 0.0f));
}