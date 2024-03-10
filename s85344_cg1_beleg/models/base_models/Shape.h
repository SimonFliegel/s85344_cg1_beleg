#pragma once

#include <vector>

#include <glew.h>
#include <glm.hpp>
#include <freeglut.h>

#define PI 3.14150

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

class Shape {
private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

protected:
	virtual void createShape() = 0;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

public:
	Shape() = default;
	virtual ~Shape() = default;
	
	void bind();
	void draw() const;
};