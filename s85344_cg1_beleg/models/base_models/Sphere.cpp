#include "Sphere.h"

// @see: http://www.songho.ca/opengl/gl_sphere.html
void Sphere::createShape() {
	const float radius = 0.5f;
	const int resolution = 10;

	float x, y, z, xy;
	float normalX, normalY, normalZ, lengthInv = 1.0f / radius;
	float textureX, textureY;

	float sectorStep = 2 * PI / resolution;
	float stackStep = PI / resolution;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= resolution; ++i) { // iterate over longitude lines
		stackAngle = PI / 2 - i * stackStep;
		xy = radius * cosf(stackAngle);
		z = radius * sinf(stackAngle);

		for (int j = 0; j <= resolution; ++j) { // iterate over latitude lines
			sectorAngle = j * sectorStep;

			x = xy * cosf(sectorAngle);
			y = xy * sinf(sectorAngle);

			normalX = x * lengthInv;
			normalY = y * lengthInv;
			normalZ = z * lengthInv;

			textureX = (float) j / resolution;
			textureY = (float) i / resolution;

			vertex v;
			v.position = glm::vec3(x, y, z);
			v.normal = glm::vec3(normalX, normalY, normalZ);
			v.texture_coord = glm::vec2(textureX, textureY);
			vertices.push_back(v);
		}
	}

	int k1, k2;
	for (int i = 0; i < resolution; ++i) {
		k1 = i * (resolution + 1);
		k2 = k1 + resolution + 1;

		for (int j = 0; j < resolution; ++j, ++k1, ++k2) {
			if (i != 0) {
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			if (i != (resolution - 1)) {
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}
}
