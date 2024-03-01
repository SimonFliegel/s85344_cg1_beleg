#pragma once

#include <vector>

#include <glew.h>
#include <glm.hpp>
#include <freeglut.h>

#define PI 3.14150

struct vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texture_coord;
};

class Shape {
private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

public:
	Shape() = default;
	~Shape() = default;
	
	std::vector<vertex> vertices;
	std::vector<GLuint> indices;
	GLuint texture;

	virtual void createShape() = 0;
	void bind();
	void draw() const;
};