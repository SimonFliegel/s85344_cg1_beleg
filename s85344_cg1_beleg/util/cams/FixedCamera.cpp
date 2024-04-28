#include "FixedCamera.h"

#include<gtx/transform.hpp>


void FixedCamera::setPositon(glm::vec3 pos)
{
	position = pos;
}

void FixedCamera::setFront(glm::vec3 front)
{
	this->front = front;
}

void FixedCamera::setFov(float fov)
{
	this->fov = fov;
}

glm::mat4 FixedCamera::getViewMatrix() const
{
	return glm::lookAt(position, front, up);
}

glm::mat4 FixedCamera::getProjectionMatrix(int windowWidth, int windowHeight) const
{
	return glm::perspective(glm::radians(fov), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
}

glm::vec3 FixedCamera::getPosition() const
{
	return position;
}


