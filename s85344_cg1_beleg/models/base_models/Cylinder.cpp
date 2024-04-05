#include "Cylinder.h"

void Cylinder::createShape() {
	const float RADIUS = 0.5f;
	const float RESOLUTION = 50;
    const float HEIGHT = 1.0f; // Height of the cylinder


    for (int i = 0; i < RESOLUTION; ++i) {
        Vertex v1, v2;
        float angle = (2.0f * PI * i) / RESOLUTION;

        // Position
        glm::vec3 position(RADIUS * glm::cos(angle), 0.0f, RADIUS * glm::sin(angle));
        v1.position = position;
        v2.position = glm::vec3(position.x, HEIGHT, position.z);

        // Normal
        glm::vec3 normal(glm::cos(angle), 0.0f, glm::sin(angle));
        v1.normal = normal;
        v2.normal = normal;

        // Texture coordinates
        glm::vec2 texCoord((float)i / (RESOLUTION - 1), 0.0f);
        v1.texCoord = texCoord;
        v2.texCoord = glm::vec2(texCoord.x, 1.0f);

        vertices.push_back(v1);
        vertices.push_back(v2);
    }
}

Cylinder::Cylinder() {
	createShape();
}
