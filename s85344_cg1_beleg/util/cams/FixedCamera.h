#pragma once

#include "AbstractCamera.h";

class FixedCamera : public AbstractCamera
{
public:
	FixedCamera() = default;
	void setPositon(glm::vec3 pos);
	void setFront(glm::vec3 target);
	void setFov(float fov);
	glm::mat4 getViewMatrix() const override;
	glm::mat4 getProjectionMatrix(int windowWidth, int windowHeight) const override;
	glm::vec3 getPosition() const override;

private:
	float fov = 45.0f;
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
};

