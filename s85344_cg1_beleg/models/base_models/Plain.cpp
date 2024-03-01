#include "Plain.h"

void Plain::createShape()
{
	vertex v;

	v.position = glm::vec3(-1.0f, -1.0f, 0.0f); v.normal = glm::vec3(0.0f, 0.0f, 1.0f); v.texture_coord = glm::vec2(0.0f, 0.0f); vertices.push_back(v); // bottom left
	v.position = glm::vec3(1.0f, -1.0f, 0.0f); v.normal = glm::vec3(0.0f, 0.0f, 1.0f); v.texture_coord = glm::vec2(1.0f, 0.0f); vertices.push_back(v); // bottom right
	v.position = glm::vec3(-1.0f, 1.0f, 0.0f); v.normal = glm::vec3(0.0f, 0.0f, 1.0f); v.texture_coord = glm::vec2(0.0f, 1.0f); vertices.push_back(v); // top left
	v.position = glm::vec3(1.0f, 1.0f, 0.0f); v.normal = glm::vec3(0.0f, 0.0f, 1.0f); v.texture_coord = glm::vec2(1.0f, 1.0f); vertices.push_back(v); // top right

	indices = {
		0, 1, 2, 1, 2, 3
	};
}


