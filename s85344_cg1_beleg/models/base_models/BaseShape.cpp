#include <iostream>

#include "BaseShape.h"

void BaseShape::bind() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) nullptr);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) (3 * sizeof(float))); // vec3 position offset

	// texture
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) (6 * sizeof(float))); // vec3 position and vec3 normal offset

	glBindVertexArray(0);
}


void BaseShape::draw(glm::mat4 model) {
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

void BaseShape::drawPolygonMode(glm::mat4 model) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
/*************************** debug ******************************/

void BaseShape::printVerticesInIndexedOrder() const {
	for (const auto& index : indices) {
		std::cout << "Position: " << vertices[index].position.x << ", " << vertices[index].position.y << ", " << vertices[index].position.z << std::endl;
		std::cout << "Normal: " << vertices[index].normal.x << ", " << vertices[index].normal.y << ", " << vertices[index].normal.z << std::endl;
		std::cout << "TexCoord: " << vertices[index].texCoord.x << ", " << vertices[index].texCoord.y << std::endl;
	}
}

void BaseShape::printPositionVerticesInIndexedOrder() const {
	for (const auto& index : indices) {
		std::cout << vertices[index].position.x << " " << vertices[index].position.y << " " << vertices[index].position.z << std::endl;
	}
}

void BaseShape::printVertices() const {
	for (const auto& vertex : vertices) {
		std::cout << "Position: " << vertex.position.x << ", " << vertex.position.y << ", " << vertex.position.z << std::endl;
		std::cout << "Normal: " << vertex.normal.x << ", " << vertex.normal.y << ", " << vertex.normal.z << std::endl;
		std::cout << "TexCoord: " << vertex.texCoord.x << ", " << vertex.texCoord.y << std::endl;
	}
}

void BaseShape::printPositionVertices() const {
	for (const auto& vertex : vertices) {
		std::cout << vertex.position.x << " " << vertex.position.y << " " << vertex.position.z << std::endl;
	}
}

