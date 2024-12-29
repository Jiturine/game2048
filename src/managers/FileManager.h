#pragma once
#include <iostream>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <format>

class FileManager
{
  public:
	static std::string GetPersistentDataPath();
};