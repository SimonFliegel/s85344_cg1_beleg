#include "Cube.h"

void Cube::createShape() {
	vertex v;

	const glm::vec3 positions[8] = {
		{-0.5f, -0.5f, 0.5f}, // Front bottom left
		{0.5f, -0.5f, 0.5f}, // Front bottom right
		{0.5f, 0.5f, 0.5f}, // Front top right
		{-0.5f, 0.5f, 0.5f}, // Front top left
		{-0.5f, -0.5f, -0.5f}, // Back bottom left
		{0.5f, -0.5f, -0.5f}, // Back bottom right
		{0.5f, 0.5f, -0.5f}, // Back top right
		{-0.5f, 0.5f, -0.5f} // Back top left
	};

	const glm::vec3 normals[6] = {
		{0.0f, 0.0f, 1.0f}, // Front face
		{0.0f, 0.0f, -1.0f}, // Back face
		{-1.0f, 0.0f, 0.0f}, // Left face
		{1.0f, 0.0f, 0.0f}, // Right face
		{0.0f, 1.0f, 0.0f}, // Up face
		{0.0f, -1.0f, 0.0f} // Down face
	};

	const glm::vec2 texture_coords[4] = {
		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f}
	};

	indices = {
		0, 1, 2, 0, 2, 3, // Front face
		4, 5, 6, 4, 6, 7, // Back face
		3, 2, 6, 3, 6, 7, // Top face
		0, 1, 5, 0, 5, 4, // Bottom face
		0, 3, 7, 0, 7, 4, // Left face
		1, 2, 6, 1, 6, 5 // Right face
	};

	for (int i = 0; i < 36; i++) {
		v.position = positions[indices[i]];
		v.normal = normals[i / 6];
		v.texture_coord = texture_coords[i % 4];
		vertices.push_back(v);
	}

	/*vertices.push_back({ positions[0], normals[0], texture_coords[0] });
	vertices.push_back({ positions[1], normals[0], texture_coords[1] });
	vertices.push_back({ positions[2], normals[0], texture_coords[2] });
	vertices.push_back({ positions[3], normals[0], texture_coords[3] });*/

	//// Front face
	//v.position = glm::vec3(-0.5f, -0.5f, 0.5f); v.normal = glm::vec3(0.0f, 0.0f, 1.0f); v.texture_coord = glm::vec2(0.0f, 0.0f); vertices.push_back(v);
	//v.position = glm::vec3(0.5f, -0.5f, 0.5f); v.normal = glm::vec3(0.0f, 0.0f, 1.0f); v.texture_coord = glm::vec2(1.0f, 0.0f); vertices.push_back(v);
	//v.position = glm::vec3(0.5f, 0.5f, 0.5f); v.normal = glm::vec3(0.0f, 0.0f, 1.0f); v.texture_coord = glm::vec2(1.0f, 1.0f); vertices.push_back(v);
	//v.position = glm::vec3(-0.5f, 0.5f, 0.5f); v.normal = glm::vec3(0.0f, 0.0f, 1.0f); v.texture_coord = glm::vec2(0.0f, 1.0f); vertices.push_back(v);

	//// Back face
	//v.position = glm::vec3(-0.5f, -0.5f, -0.5f); v.normal = glm::vec3(0.0f, 0.0f, -1.0f); v.texture_coord = glm::vec2(0.0f, 0.0f); vertices.push_back(v);
	//v.position = glm::vec3(0.5f, -0.5f, -0.5f); v.normal = glm::vec3(0.0f, 0.0f, -1.0f); v.texture_coord = glm::vec2(1.0f, 0.0f); vertices.push_back(v);
	//v.position = glm::vec3(0.5f, 0.5f, -0.5f); v.normal = glm::vec3(0.0f, 0.0f, -1.0f); v.texture_coord = glm::vec2(1.0f, 1.0f); vertices.push_back(v);
	//v.position = glm::vec3(-0.5f, 0.5f, -0.5f); v.normal = glm::vec3(0.0f, 0.0f, -1.0f); v.texture_coord = glm::vec2(0.0f, 1.0f); vertices.push_back(v);

	//// Left face
	//v.position = glm::vec3(-0.5f, -0.5f, -0.5f); v.normal = glm::vec3(-1.0f, 0.0f, 0.0f); v.texture_coord = glm::vec2(0.0f, 0.0f); vertices.push_back(v);
	//v.position = glm::vec3(-0.5f, -0.5f, 0.5f); v.normal = glm::vec3(-1.0f, 0.0f, 0.0f); v.texture_coord = glm::vec2(1.0f, 0.0f); vertices.push_back(v);
	//v.position = glm::vec3(-0.5f, 0.5f, 0.5f); v.normal = glm::vec3(-1.0f, 0.0f, 0.0f); v.texture_coord = glm::vec2(1.0f, 1.0f); vertices.push_back(v);
	//v.position = glm::vec3(-0.5f, 0.5f, -0.5f); v.normal = glm::vec3(-1.0f, 0.0f, 0.0f); v.texture_coord = glm::vec2(0.0f, 1.0f); vertices.push_back(v);

	//// Right face
	//v.position = glm::vec3(0.5f, -0.5f, -0.5f); v.normal = glm::vec3(1.0f, 0.0f, 0.0f); v.texture_coord = glm::vec2(0.0f, 0.0f); vertices.push_back(v);
	//v.position = glm::vec3(0.5f, -0.5f, 0.5f); v.normal = glm::vec3(1.0f, 0.0f, 0.0f); v.texture_coord = glm::vec2(1.0f, 0.0f); vertices.push_back(v);
	//v.position = glm::vec3(0.5f, 0.5f, 0.5f); v.normal = glm::vec3(1.0f, 0.0f, 0.0f); v.texture_coord = glm::vec2(1.0f, 1.0f); vertices.push_back(v);
	//v.position = glm::vec3(0.5f, 0.5f, -0.5f); v.normal = glm::vec3(1.0f, 0.0f, 0.0f); v.texture_coord = glm::vec2(0.0f, 1.0f); vertices.push_back(v);

	//// Up face
	//v.position = glm::vec3(-0.5f, -0.5f, -0.5f); v.normal = glm::vec3(0.0f, 1.0f, 0.0f); v.texture_coord = glm::vec2(0.0f, 0.0f); vertices.push_back(v);
	//v.position = glm::vec3(0.5f, -0.5f, -0.5f); v.normal = glm::vec3(0.0f, 1.0f, 0.0f); v.texture_coord = glm::vec2(1.0f, 0.0f); vertices.push_back(v);
	//v.position = glm::vec3(0.5f, -0.5f, 0.5f); v.normal = glm::vec3(0.0f, 1.0f, 0.0f); v.texture_coord = glm::vec2(1.0f, 1.0f); vertices.push_back(v);
	//v.position = glm::vec3(-0.5f, -0.5f, 0.5f); v.normal = glm::vec3(0.0f, 1.0f, 0.0f); v.texture_coord = glm::vec2(0.0f, 1.0f); vertices.push_back(v);

	//// Down face
	//v.position = glm::vec3(-0.5f, 0.5f, -0.5f); v.normal = glm::vec3(0.0f, -1.0f, 0.0f); v.texture_coord = glm::vec2(0.0f, 0.0f); vertices.push_back(v);
	//v.position = glm::vec3(0.5f, 0.5f, -0.5f); v.normal = glm::vec3(0.0f, -1.0f, 0.0f); v.texture_coord = glm::vec2(1.0f, 0.0f); vertices.push_back(v);
	//v.position = glm::vec3(0.5f, 0.5f, 0.5f); v.normal = glm::vec3(0.0f, -1.0f, 0.0f); v.texture_coord = glm::vec2(1.0f, 1.0f); vertices.push_back(v);
	//v.position = glm::vec3(-0.5f, 0.5f, 0.5f); v.normal = glm::vec3(0.0f, -1.0f, 0.0f); v.texture_coord = glm::vec2(0.0f, 1.0f); vertices.push_back(v);

}
