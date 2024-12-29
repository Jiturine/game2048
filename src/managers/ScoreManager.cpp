#include "ScoreManager.h"

List<ScoreManager::ScoreInfo> ScoreManager::rankList;

void ScoreManager::Init()
{
	std::ifstream ifs(FileManager::GetPersistentDataPath() + "/historyScore.txt");
	if (ifs.is_open())
	{
		std::tm dateTime;
		int score;
		while (ifs >> std::get_time(&dateTime, "%Y-%m-%d %H:%M:%S") >> score)
		{
			rankList.Add(ScoreInfo(dateTime, score));
		}
		ifs.close();
	}
}

void ScoreManager::AddScore(int score)
{
	std::time_t currentTime = std::time(nullptr);
	std::tm *localTime = std::localtime(&currentTime);
	ScoreManager::rankList.Add(ScoreManager::ScoreInfo(*localTime, score));
	ScoreManager::rankList.Sort();
	ScoreManager::rankList.RemoveToTen();
	std::ofstream ofs(FileManager::GetPersistentDataPath() + "/historyScore.txt");
	for (auto data : rankList)
	{
		ofs << std::put_time(&data.dateTime, "%Y-%m-%d %H:%M:%S") << " " << data.score << std::endl;
	}
	ofs.close();
}
int ScoreManager::GetHighestScore()
{
	if (rankList.size == 0)
	{
		return 0;
	}
	return rankList.head->next->data.score;
}