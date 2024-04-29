#include <glm.hpp>

#pragma once
class AbstractCamera
{
public:
	virtual glm::mat4 getViewMatrix() const = 0;
	virtual glm::mat4 getProjectionMatrix(int windowWidth, int windowHeight) const = 0;
	virtual void setPosition(const glm::vec3& position) = 0;
	virtual glm::vec3 getPosition() const = 0;
	virtual void setFront(const glm::vec3& front) = 0;
	virtual glm::vec3 getFront() const = 0;
};

