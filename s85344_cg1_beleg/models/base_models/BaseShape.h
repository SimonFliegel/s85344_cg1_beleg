#pragma once

#include <vector>

#include <glew.h>
#include <glm.hpp>
#include <freeglut.h>

#include "../AbstractShape.h"

#define PI 3.14150

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

class BaseShape : AbstractShape {
private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

protected:
	virtual void createShape() = 0;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

public:
	BaseShape() = default;
	virtual ~BaseShape() = default;
	
	void bind();
	void draw() override;
};