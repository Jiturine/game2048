#pragma once
#include <string>
#include "List.h"

class ScoreManager
{
  public:
	class ScoreInfo
	{
	  public:
		int score;
		std::string userName;
		ScoreInfo(int score, std::string userName)
			: score(score), userName(userName) {}
		ScoreInfo() {}
		bool operator<(const ScoreInfo &other)
		{
			return this->score < other.score;
		}
	};
	static void Init() {}
	static List<ScoreInfo> rankList;

  private:
	ScoreManager() = delete;
};