#include <glm.hpp>
#include <gtx/transform.hpp>

#include "RoomWithLamp.h"

RoomWithLamp::RoomWithLamp(const Shader& shader)
	: shader(shader)
{
	shader.use();
}

void RoomWithLamp::draw(glm::mat4 model)
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

	lightPosition = modelLamp * glm::vec4(lamp.getLightPosition(), 1.0f);
}

void RoomWithLamp::toggleLight()
{
	if (lightOn)
	{
		lamp.setLight(false);
		lightOn = false;
	}
	else
	{
		lamp.setLight(true);
		lightOn = true;
	}
}

glm::vec3 RoomWithLamp::getLightPosition() const
{
	return lightPosition;
}