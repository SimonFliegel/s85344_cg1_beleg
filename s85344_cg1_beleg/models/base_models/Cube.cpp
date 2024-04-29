#include "Cube.h"

#include <iostream>



void Cube::createShape()
{
	Vertex v;

	const glm::vec3 positions[24] = 
	{
		// Front face
		{-0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, 0.5f}, {0.5f, 0.5f, 0.5f}, {-0.5f, 0.5f, 0.5f},
		// Back face
		{0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f}, {0.5f, 0.5f, -0.5f},
		// Left face
		{-0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, 0.5f}, {-0.5f, 0.5f, 0.5f}, {-0.5f, 0.5f, -0.5f},
		// Right face
		{0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f, 0.5f, -0.5f}, {0.5f, 0.5f, 0.5f},
		// Bottom face
		{-0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, 0.5f}, {-0.5f, -0.5f, 0.5f},
		// Top face
		{-0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f}
	};

	const glm::vec3 normals[24] =
	{
		// Front face
	   {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f},
	   // Back face
	   {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f},
	   // Left face
	   {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f},
	   // Right face
	   {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f},
	   // Bottom face
	   {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f},
	   // Top face
	   {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}
	};

	const unsigned int repeat = 10;
	const glm::vec2 texCoords[24] = 
	{
		{0.0f, 0.0f}, {repeat * 1.0f, 0.0f}, {repeat * 1.0f, repeat * 1.0f}, {0.0f, repeat * 1.0f},
		{0.0f, 0.0f}, {repeat * 1.0f, 0.0f}, {repeat * 1.0f, repeat * 1.0f}, {0.0f, repeat * 1.0f},
		{0.0f, 0.0f}, {repeat * 1.0f, 0.0f}, {repeat * 1.0f, repeat * 1.0f}, {0.0f, repeat * 1.0f},
		{0.0f, 0.0f}, {repeat * 1.0f, 0.0f}, {repeat * 1.0f, repeat * 1.0f}, {0.0f, repeat * 1.0f},
		{0.0f, 0.0f}, {repeat * 1.0f, 0.0f}, {repeat * 1.0f, repeat * 1.0f}, {0.0f, repeat * 1.0f},
		{0.0f, 0.0f}, {repeat * 1.0f, 0.0f}, {repeat * 1.0f, repeat * 1.0f}, {0.0f, repeat * 1.0f}
	};

	indices = {
		0, 1, 2, 0, 2, 3, // Front face
		4, 5, 6, 4, 6, 7, // Back face
		8, 9, 10, 8, 10, 11, // Left face
		12, 13, 14, 12, 14, 15, // Right face
		16, 17, 18, 16, 18, 19, // Bottom face
		20, 21, 22, 20, 22, 23 // Top face
	};

	for (unsigned int i = 0; i < 24; i++)
	{
		v.position = positions[i];
		v.normal = normals[i];
		v.texCoord = texCoords[i];
		vertices.push_back(v);
	}


}

Cube::Cube()
{
	createShape();
}
