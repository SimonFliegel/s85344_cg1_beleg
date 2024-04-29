#pragma once

#include "AbstractCamera.h";

class FixedCamera : public AbstractCamera
{
public:
	/// <summary>
	/// camera with fixed position and front
	/// </summary>
	FixedCamera() = default;

	/// <param name="fov">field of view in degrees</param>
	void setFov(float fov);

	// interface methods

	glm::mat4 getViewMatrix() const override;

	glm::mat4 getProjectionMatrix(int windowWidth, int windowHeight) const override;

	void setPosition(const glm::vec3& pos) override;

	glm::vec3 getPosition() const override;
	
	void setFront(const glm::vec3& front) override;

	glm::vec3 getFront() const override;

private:
	float fov = 45.0f;
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
};

