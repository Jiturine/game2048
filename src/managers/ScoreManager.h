#pragma once
#include <string>
#include "List.h"
#include "FileManager.h"
#include <ctime>
#include <iomanip>

class ScoreManager
{
  public:
	ScoreManager() = delete;
	class ScoreInfo
	{
	  public:
		int score;
		std::tm dateTime;
		ScoreInfo(std::tm dateTime, int score)
			: dateTime(dateTime), score(score) {}
		ScoreInfo() {}
		bool operator<(const ScoreInfo &other)
		{
			return this->score < other.score;
		}
	};
	static void Init();
	static void AddScore(int score);
	static int GetHighestScore();
	static List<ScoreInfo> rankList;
};