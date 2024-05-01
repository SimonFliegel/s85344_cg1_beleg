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

class BaseShape : private AbstractShape {
private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

protected:
	/// <summary>
	/// creates the shape by generating the vertices and indices
	/// </summary>
	virtual void createShape() = 0;

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

public:
	BaseShape() = default;
	virtual ~BaseShape() = default;
	
	/// <summary>
	/// generates buffers and binds the vertices to them so the shape can be drawn
	/// </summary>
	void bind();

	/// <summary>
	/// draws the shape
	/// </summary>
	/// <param name="model">not needed for basic shapes</param>
	void draw(const glm::mat4& model = glm::mat4(1.0f)) override; // inherited from AbstractShape

	/// <summary>
	/// draws the shape in wireframe mode (only for base shapes available)
	/// </summary>
	/// <param name="model"></param>
	void drawPolygonMode(const glm::mat4& model = glm::mat4(1.0f)); // draw in wireframe mode (only for base shapes available)

	/*************************** debug ******************************/
	void printVerticesInIndexedOrder() const;
	void printPositionVerticesInIndexedOrder() const;
	void printVertices() const;
	void printPositionVertices() const;
};