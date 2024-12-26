#include "PauseState.h"

void PauseState::Render()
{
	Text::Render("Rank List", 600.0f, 900.0f, 1.5f, glm::vec3(0.0f, 0.0f, 0.0f));
	int count = 0;
	for (auto info : ScoreManager::rankList)
	{
		count++;
		Text::Render(std::format("Rank:{:02}", count),
					 200.0f, 840.0f - 60.0f * count, 1.2f, glm::vec3(0.0f, 0.0f, 0.0f));
		Text::Render(std::format("Score:{:<10}", info.score),
					 450.0f, 840.0f - 60.0f * count, 1.2f, glm::vec3(0.0f, 0.0f, 0.0f));
		Text::Render(std::format("Time:{:04}/{:02}/{:02} {:02}:{:02}",
								 info.dateTime.tm_year + 1900,
								 info.dateTime.tm_mon + 1,
								 info.dateTime.tm_mday,
								 info.dateTime.tm_hour,
								 info.dateTime.tm_min),
					 800.0f, 840.0f - 60.0f * count, 1.2f, glm::vec3(0.0f, 0.0f, 0.0f));
		if (count == 10)
			break;
	}
}