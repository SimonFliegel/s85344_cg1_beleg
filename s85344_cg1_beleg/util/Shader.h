#pragma once

#include <glew.h>
#include <array>
#include <string>
#include <glm.hpp>

enum class ShaderType
{
	VERTEX,
	FRAGMENT,
	GEOMETRY,
	TESSCONTROL,
	TESSEVALUATION,
	COMPUTE,
	PROGRAM, // for linking
};

const std::array<GLenum, 6> glShaderTypes = 
{
	GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_COMPUTE_SHADER,
};

const std::array<const char*, 6> shaderTypeNames = 
{ 
	"VERTEX", "FRAGMENT", "GEOMETRY", "TESSCONTROL", "TESSEVALUATION", "COMPUTE" 
};

// see @https://github.com/JoeyDeVries/LearnOpenGL/blob/master/includes/learnopengl/shader.h
class Shader
{
public:
	unsigned int ID;

	/// <summary>
	/// wraps the shader compilation and linking process
	/// </summary>
	/// <param name="vertexPath"></param>
	/// <param name="fragmentPath"></param>
	/// <param name="geometryPath"></param>
	/// <param name="tesscontrolPath"></param>
	/// <param name="tessevaluationPath"></param>
	/// <param name="computePath"></param>
	Shader(const char* vertexPath, const char* fragmentPath, 
		const char* geometryPath = nullptr, const char* tesscontrolPath = nullptr, 
		const char* tessevaluationPath = nullptr, const char* computePath = nullptr);

	~Shader();

	/// <summary>
	/// binds the shader
	/// </summary>
	void use() const;

	/// <summary>
	/// sets a boolean uniform
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void setBool(const std::string &name, bool value) const;

	/// <summary>
	/// sets an integer uniform
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void setInt(const std::string &name, int value) const;

	/// <summary>
	/// sets a float uniform
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void setFloat(const std::string &name, float value) const;

	/// <summary>
	/// sets a vec2 uniform
	/// </summary>
	/// <param name="name"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void setVec2(const std::string &name, float x, float y) const;

	/// <summary>
	/// sets a vec2 uniform
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void setVec2(const std::string &name, const glm::vec2& value) const;

	/// <summary>
	/// sets a vec3 uniform
	/// </summary>
	/// <param name="name"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	void setVec3(const std::string &name, float x, float y, float z) const;

	/// <summary>
	/// sets a vec3 uniform
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void setVec3(const std::string &name, const glm::vec3& value) const;

	/// <summary>
	/// sets a vec4 uniform
	/// </summary>
	/// <param name="name"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	/// <param name="w"></param>
	void setVec4(const std::string &name, float x, float y, float z, float w) const;

	/// <summary>
	/// sets a vec4 uniform
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void setVec4(const std::string &name, const glm::vec4& value) const;

	/// <summary>
	/// stes a mat2 uniform
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void setMat2(const std::string &name, const glm::mat2& value) const;

	/// <summary>
	/// sets a mat3 uniform
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void setMat3(const std::string &name, const glm::mat3& value) const;

	/// <summary>
	/// sets a mat4 uniform
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void setMat4(const std::string &name, const glm::mat4& value) const;

	private:
		std::array<const char*, 6> shaderPaths;

		void checkCompileErrors(GLuint shader, ShaderType type) const;
};

