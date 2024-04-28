#include <glm.hpp>

#pragma once
class AbstractCamera
{
public:
	virtual glm::mat4 getViewMatrix() const = 0;
	virtual glm::mat4 getProjectionMatrix(int windowWidth, int windowHeight) const = 0;
	virtual glm::vec3 getPosition() const = 0;
};

