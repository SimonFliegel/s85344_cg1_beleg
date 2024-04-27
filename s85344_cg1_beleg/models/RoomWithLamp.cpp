#include <glm.hpp>
#include <gtx/transform.hpp>

#include "RoomWithLamp.h"

RoomWithLamp::RoomWithLamp(const Shader& shader)
	: shader(shader)
{
	shader.use();
	shader.setInt(ROOM_TEXTURE_LOC, roomTexture.getTextureUnit());
}

void RoomWithLamp::draw(glm::mat4 model)
{
	const std::string OBJECT_ID = "objectId";

	shader.use();
	
	// room
	shader.setInt(OBJECT_ID, 0);
	roomTexture.bind();
	glm::mat4 modelCube = glm::scale(model, glm::vec3(2.0f, 1.0f, 2.0f));
	shader.setMat4("model", modelCube);
	room.bind();
	room.draw();

	// lamp
	glm::mat4 modelLamp = glm::translate(model, glm::vec3(-0.7f, -0.1f, -0.7f));
	modelLamp = glm::scale(modelLamp, glm::vec3(0.8f, 0.8f, 0.8f));
	shader.setMat4("model", modelLamp);
	lamp.draw(modelLamp);

	lightPosition = glm::vec3(modelLamp * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	//shader.setVec3("lightPos", lamp.getLightPosition());
	//shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));


}

glm::vec3 RoomWithLamp::getLightPosition() const
{
	return lightPosition;
}