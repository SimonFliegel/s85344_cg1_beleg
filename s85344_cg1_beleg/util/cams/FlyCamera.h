// @see https://github.com/JoeyDeVries/LearnOpenGL/blob/master/includes/learnopengl/camera.h
#pragma once

#include "AbstractCamera.h"

enum class ECameraMovementDirection
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float MOVEMENT_SPEED = 1.0f;
const float SENSITIVITY = 0.1f;
const float FOV = 45.0f; // min zoom
const float MAX_ZOOM = 5.0f;

class FlyCamera : public AbstractCamera
{
public: 
	/// <summary>
	/// 
	/// </summary>
	/// <param name="yaw">angle in degrees</param>
	/// <param name="pitch">angle in degrees</param>
	/// <param name="zoom">max fov when not zoomed</param>
	/// <param name="movementSpeed">speed when steering with WASD</param>
	/// <param name="sensitivity">mouse sensitivity for looking around</param>
	FlyCamera(float yaw = YAW, float pitch = PITCH, float zoom = FOV, float movementSpeed = MOVEMENT_SPEED, float sensitivity = SENSITIVITY);

	/// <summary>
	/// handles keyboard input (WASD) for moving the camera
	/// </summary>
	/// <param name="direction">{FORWARD, BACKWARD, LEFT, RIGHT}</param>
	/// <param name="deltaTime">for constant movement speed independent of fps</param>
	void processKeyboardInput(ECameraMovementDirection direction, float deltaTime);

	/// <summary>
	/// handles mouse input for looking around
	/// </summary>
	/// <param name="xPos">current x-pos of the mouse</param>
	/// <param name="yPos">current y-pos of the mouse</param>
	void processMouseInput(int xPos, int yPos);

	/// <summary>
	/// handles scroll input for zooming in and out
	/// </summary>
	/// <param name="dir">+1: zoom in, -1: zoom out</param>
	void processScrollInput(int dir);

	/// <returns>current fov depending on zoom</returns>
	float getZoom() const;

	// interface methods

	glm::mat4 getViewMatrix() const override;

	glm::mat4 getProjectionMatrix(int windowWidth, int windowHeight) const override;

	void setPosition(const glm::vec3& position) override;

	glm::vec3 getPosition() const override;	

	void setFront(const glm::vec3& front) override;

	glm::vec3 getFront() const override;


private:
	float zoom;
	float movementSpeed;
	float mouseSensitivity;
	// euler angles
	float yaw;
	float pitch;

	// initial default values
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 worldUp = up;

	bool firstMouse = true;
	int lastX = 0;
	int lastY = 0;

	void updateCameraVectors();
};

