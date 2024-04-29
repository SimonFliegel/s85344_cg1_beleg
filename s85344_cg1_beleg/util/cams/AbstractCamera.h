#include <glm.hpp>

#pragma once
class AbstractCamera
{
public:

	/// <returns>view matrix</returns>
	virtual glm::mat4 getViewMatrix() const = 0;

	/// <summary>
	/// calculates the projection matrix
	/// </summary>
	/// <param name="windowWidth"></param>
	/// <param name="windowHeight"></param>
	/// <returns></returns>
	virtual glm::mat4 getProjectionMatrix(int windowWidth, int windowHeight) const = 0;

	/// <param name="position"></param>
	virtual void setPosition(const glm::vec3& position) = 0;

	/// <returns>camera position</returns>
	virtual glm::vec3 getPosition() const = 0;

	/// <param name="front">direction the camera is pointing at</param>
	virtual void setFront(const glm::vec3& front) = 0;

	/// <returns>direction the camera is pointing at</returns>
	virtual glm::vec3 getFront() const = 0;
};

