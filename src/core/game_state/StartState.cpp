#include "StartState.h"

void StartState::Render()
{
	Text::Render("Press any key to start game ...", 200.0f, 600.0f, 1.2f, glm::vec3(0.0f, 0.0f, 0.0f));
}

void StartState::OnExit()
{
	Game::Init();
}