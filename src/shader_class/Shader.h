#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <glm/glm.hpp>
#include "SysConfig.h"
#include <iostream>
#include <string.h>

class Shader
{
public:
	unsigned int rendererID;
	enum class ShaderType
	{
		VERTEX,
		FRAGMENT
	};
	Shader(const std::string &vertexPath, const std::string &fragmentPath);
	~Shader();
	void Bind() const;
	void Unbind() const;
	void SetUniform(const std::string &name, float v0, float v1, float v2, float v3);
	void SetUniform(const std::string &name, int value);
	void SetUniform(const std::string &name, glm::mat4 matrix);
	void SetUniform(const std::string &name, int count, int *array);
	int GetUniformLocation(const std::string &name);

private:
	unsigned int vertexShader;
	unsigned int fragmentShader;
	std::unordered_map<std::string, int> uniformLocationCache;
	const char *ParseShader(const std::string &filePath);
	unsigned int CreateShader(const char *vertexSource, const char *fragmentSource);
	void CompileShader(unsigned int shader, ShaderType shaderType);
};