#pragma once

#include "BaseShape.h"

class Cylinder : public BaseShape
{
private:
	const int RESOLUTION = 50;
	const float RADIUS = 0.5f;
	const float HEIGHT = 1.0f;

	int baseCenterIndex;
	int topCenterIndex;

	std::vector<glm::vec3> getUnitCircleVertices();
	void createIndices(int topCenterIndex, int baseCenterIndex);
	void createVertices();
protected:
	void createShape() final;
public:
	Cylinder();
};

