#include <glm.hpp>
#include <gtx/transform.hpp>

#include "RoomWithLamp.h"

RoomWithLamp::RoomWithLamp(const Shader& shader)
	: shader(shader)
{
	shader.use();
}

void RoomWithLamp::draw(const glm::mat4& model)
{
	shader.use();
	
	// ########################## room ###########################
	glm::mat4 modelRoom = model;
	shader.setMat4("model", modelRoom);
	room.draw(modelRoom);

	// ######################### lamp ###########################
	glm::mat4 modelLamp = glm::translate(model, glm::vec3(-1.2f, 0.0f, -1.2f)); // back left corner of room
	shader.setMat4("model", modelLamp);
	lamp.draw(modelLamp);

	lightPosition = glm::vec4(lamp.getLightPosition(), 1.0f) * modelLamp;
}

void RoomWithLamp::toggleLight()
{
	lamp.setLightState(!lamp.getLightState());
}

glm::vec3 RoomWithLamp::getLightPosition() const
{
	return lightPosition;
}

void RoomWithLamp::setExternalLightSource(const glm::vec3& lightPos, const glm::vec3& lightColor)
{
	shader.setVec3(EXTERNAL_LIGHT_POS_LOC, lightPos);
	shader.setVec3(EXTERNAL_LIGHT_COLOR_LOC, lightColor);
}