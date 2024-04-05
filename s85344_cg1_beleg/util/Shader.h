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

const std::array<GLenum, 6> glShaderTypes = {
	GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_COMPUTE_SHADER,
};

const std::array<const char*, 6> shaderTypeNames = { 
	"VERTEX", "FRAGMENT", "GEOMETRY", "TESSCONTROL", "TESSEVALUATION", "COMPUTE" 
};

// see @https://github.com/JoeyDeVries/LearnOpenGL/blob/master/includes/learnopengl/shader.h
class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath, 
		const char* geometryPath = nullptr, const char* tesscontrolPath = nullptr, 
		const char* tessevaluationPath = nullptr, const char* computePath = nullptr);
	~Shader();

	void use() const;
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec2(const std::string &name, float x, float y) const;
	void setVec2(const std::string &name, const glm::vec2& value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec3(const std::string &name, const glm::vec3& value) const;
	void setVec4(const std::string &name, float x, float y, float z, float w) const;
	void setVec4(const std::string &name, const glm::vec4& value) const;
	void setMat2(const std::string &name, const glm::mat2& value) const;
	void setMat3(const std::string &name, const glm::mat3& value) const;
	void setMat4(const std::string &name, const glm::mat4& value) const;

	private:
		std::array<const char*, 6> shaderPaths;

		void checkCompileErrors(unsigned int shader, ShaderType type) const;
};

