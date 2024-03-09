#include <glew.h>
#include <glm.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath,
	const char* geometryPath, const char* tesscontrolPath,
	const char* tessevaluationPath, const char* computePath)

	: shaderPaths({ vertexPath, fragmentPath, geometryPath, tesscontrolPath, tessevaluationPath, computePath })
{
	ID = glCreateProgram();

	// fields for looping
	std::array<std::string, 6> shaderCodes; // opengl expects const char* type
	std::array<GLuint, 6> shaderIDs;

	for (int i = 0; i < shaderPaths.size(); i++) // loop over all shaders
	{
		if (shaderPaths[i] != nullptr)
		{
			std::ifstream shaderFile;
			shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			try
			{
				shaderFile.open(shaderPaths[i]);
				std::stringstream shaderStream;
				shaderStream << shaderFile.rdbuf();
				shaderFile.close();
				shaderCodes[i] = shaderStream.str();
			}
			catch (std::ifstream::failure e)
			{
				std::cout << shaderTypeNames[i] << ": ERROR::FILE_NOT_SUCCESFULLY_READ" << std::endl;
			}

			const char* shaderCode = shaderCodes[i].c_str();

			shaderIDs[i] = glCreateShader(glShaderTypes[i]);
			glShaderSource(shaderIDs[i], 1, &shaderCode, nullptr);
			glCompileShader(shaderIDs[i]);
			checkCompileErrors(shaderIDs[i], static_cast<ShaderType>(i));
			glAttachShader(ID, shaderIDs[i]);
		}
	}

	glLinkProgram(ID);
	checkCompileErrors(ID, ShaderType::PROGRAM);

	for (int i = 0; i < shaderPaths.size(); i++) // loop over all shaders
	{
		if (shaderPaths[i] != nullptr)
		{
			glDeleteShader(shaderIDs[i]);
		}
	}
}

Shader::~Shader()
{
	glDeleteProgram(ID);
}

void Shader::use() const
{
	glUseProgram(ID);
}

// uniforms
void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setMat2(const std::string& name, const glm::mat2& value) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& value) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::checkCompileErrors(GLuint shaderID, ShaderType type) const
{
	GLint result = GL_FALSE;
	int infoLogLength;

	if (type == ShaderType::PROGRAM) // for linking
	{
		glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
		glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			std::vector<char> programErrorMessage(infoLogLength);
			glGetProgramInfoLog(shaderID, infoLogLength, nullptr, &programErrorMessage[0]);
			std::cout << "PROGRAM::ERROR::" << &programErrorMessage[0] << std::endl;
		}
	}
	else
	{
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			std::vector<char> shaderErrorMessage(infoLogLength);
			glGetShaderInfoLog(shaderID, infoLogLength, nullptr, &shaderErrorMessage[0]);
			std::cout << shaderTypeNames[static_cast<int>(type)] << "::ERROR::" << &shaderErrorMessage[0] << std::endl;
		}
	}
}

