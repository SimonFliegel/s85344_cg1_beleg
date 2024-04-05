#pragma once

#include "../util/Shader.h"
#include "base_models/Cube.h"

class RoomWithLamp
{
public:
	explicit RoomWithLamp(const Shader& shader);
	void draw();
	glm::vec3 getLightPosition() const;

private:
	Shader shader;
	glm::vec3 lightPosition;
	Cube room;
	
};

