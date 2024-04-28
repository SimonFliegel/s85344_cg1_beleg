#include <gtx/transform.hpp>

#include "Room.h"

Room::Room(const Shader& shader, const char* const objectIdLoc) 
	: shader(shader), objectIdLoc(objectIdLoc)
{
	shader.use();

	// texture uniforms
	shader.setInt(wallTextureLoc, wallTexture.getTextureUnit());
	shader.setInt(floorTextureLoc, floorTexture.getTextureUnit());
}

void Room::draw(glm::mat4 model)
{
	shader.use();

	// ####################### walls ######################
	shader.setInt(objectIdLoc, WALL_ID);
	wallTexture.bind();
	walls.bind();

	glm::mat4 modelWalls = glm::scale(model, glm::vec3(3.0f, 1.5f, 3.0f));
	shader.setMat4("model", modelWalls);

	walls.draw();
	wallTexture.unbind();

	// ####################### floor ######################
	shader.setInt(objectIdLoc, FLOOR_ID);
	floorTexture.bind();
	floor.bind();

	glm::mat4 modelFloor = glm::translate(model, glm::vec3(0.0f, -0.49f, -0.0f)); // -0.49f to avoid z-fighting with walls
	modelFloor = glm::scale(modelFloor, glm::vec3(3.0f, 1.0f, 3.0f));
	modelFloor = glm::rotate(modelFloor, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", modelFloor);

	floor.draw();
	floorTexture.unbind();
}
	
	