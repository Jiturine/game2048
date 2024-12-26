#include "FileManager.h"

std::string FileManager::GetPersistentDataPath()
{
	std::filesystem::path path = std::format("{}\\game2048", std::getenv("APPDATA"));
	if (!std::filesystem::exists(path))
	{
		std::filesystem::create_directories(path);
	}
	return path.string();
}
