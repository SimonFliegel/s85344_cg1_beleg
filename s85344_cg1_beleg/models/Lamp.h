#pragma once

#include "base_models/Cylinder.h"

class Lamp
{
public:
	explicit Lamp();
	void draw();
	void toggleLight();
	glm::vec3 getLightPosition() const;
};

