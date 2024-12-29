#pragma once
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string.h>
#include "Log.h"
#include "SysConfig.h"

class Shader
{
  public:
	unsigned int rendererID;
	enum class ShaderType
	{
		VERTEX,
		FRAGMENT
	};
	Shader() = default;
	Shader(const std::string &vertexPath, const std::string &fragmentPath);
	Shader(const Shader &shader);
	Shader(Shader &&shader) noexcept;
	Shader &operator=(Shader shader);
	~Shader();
	friend void swap(Shader &shader_1, Shader &shader_2);
	void Bind() const;
	void Unbind() const;
	void SetUniform(const std::string &name, float v0, float v1, float v2, float v3);
	void SetUniform(const std::string &name, int value);
	void SetUniform(const std::string &name, glm::vec3 vector);
	void SetUniform(const std::string &name, glm::vec4 vector);
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