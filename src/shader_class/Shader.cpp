#pragma once
#include "Shader.h"

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
{
	const char *vertexSource = ParseShader(vertexPath);
	const char *fragmentSource = ParseShader(fragmentPath);
	rendererID = CreateShader(vertexSource, fragmentSource);
}
Shader::~Shader()
{
	glDeleteProgram(rendererID);
}
void Shader::Bind() const
{
	glUseProgram(rendererID);
}
void Shader::Unbind() const
{
	glUseProgram(0);
}
void Shader::SetUniform(const std::string &name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform(const std::string &name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}
void Shader::SetUniform(const std::string &name, glm::mat4 matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}
void Shader::SetUniform(const std::string &name, int count, int *array)
{
	glUniform1iv(GetUniformLocation(name), count, array);
}
int Shader::GetUniformLocation(const std::string &name)
{
	if (uniformLocationCache.find(name) != uniformLocationCache.end())
	{
		return uniformLocationCache[name];
	}
	int location = glGetUniformLocation(rendererID, name.c_str());
	if (location == -1)
	{
		std::cout << "WARNING: Uniform '" << name << "' doesn't exist!" << std::endl;
	}
	uniformLocationCache[name] = location;
	return location;
}
const char *Shader::ParseShader(const std::string &filePath)
{
	std::stringstream ss;
	std::ifstream ifs(std::string(PATH) + "/" + filePath);
	ss << ifs.rdbuf();
	ifs.close();

	std::string shaderContent = ss.str();
	char *cStyleString = new char[shaderContent.length() + 1];
	strcpy(cStyleString, shaderContent.c_str());

	return cStyleString;
}
unsigned int Shader::CreateShader(const char *vertexSource, const char *fragmentSource)
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	CompileShader(vertexShader, ShaderType::VERTEX);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	CompileShader(fragmentShader, ShaderType::FRAGMENT);
	unsigned int program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return program;
}
void Shader::CompileShader(unsigned int shader, ShaderType shaderType)
{
	int success;
	char infoLog[512];
	glCompileShader(shader);
	// 打印编译错误（如果有的话）
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		if (shaderType == ShaderType::VERTEX)
		{
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl;
		}
		else if (shaderType == ShaderType::FRAGMENT)
		{
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << std::endl;
		}
		std::cout << infoLog << std::endl;
	};
}