#pragma once

#include <format>
#include <iostream>
#include <fstream>
#include <iostream>
#include <filesystem>

class FileManager
{
  public:
	static std::string GetPersistentDataPath();
};