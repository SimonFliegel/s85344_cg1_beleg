#include <gtx/transform.hpp>

#include "Lamp.h"

Lamp::Lamp(const Shader& shader, const char* const objectIdLoc)
	: shader(shader), objectIdLoc(objectIdLoc)
{
	shader.use();
	shader.setInt(METAL_TEXTURE_LOC, standTexture.getTextureUnit());
	shader.setInt(LIGHT_TEXTURE_LOC, lightTexture.getTextureUnit());
	setLight(true);
}

void Lamp::draw(const glm::mat4& model) {
	shader.use();

	shader.setInt(objectIdLoc, STAND_AND_ARM_ID);
	standTexture.bind();
	cylinder.bind();

	// ########################### stand ############################
	glm::mat4 modelStand = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
	modelStand = glm::rotate(modelStand, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	modelStand = glm::scale(modelStand, glm::vec3(0.25f, 0.25f, 0.075f));
	shader.setMat4("model", modelStand);

	cylinder.draw();

	// ############################ arm #############################
	glm::mat4 modelArm = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	modelArm = glm::scale(modelArm, glm::vec3(0.05f, 0.05f, 1.0f)); // make it thin
	shader.setMat4("model", modelArm);

	cylinder.draw();
	standTexture.unbind();

	// ########################## light bulb #########################
	shader.setInt(objectIdLoc, LIGHT_BULB_ID);
	lightTexture.bind();
	lightBulb.bind();

	lightPos = glm::vec3(0.0f, 0.5f, 0.0f);
	glm::mat4 modelLightBulb = glm::translate(model, lightPos);
	modelLightBulb = glm::scale(modelLightBulb, glm::vec3(0.4f, 0.15f, 0.4f));
	shader.setMat4("model", modelLightBulb);

	lightPos = glm::vec3(modelLightBulb * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	lightBulb.draw();
	lightTexture.unbind();
}

void Lamp::setLight(bool state) {
	const std::string LIGHT_COLOR_LOC = "lightColor";
	const glm::vec3 LIGHT_COLOR_OFF = glm::vec3(0.0f, 0.0f, 0.0f);

	if (state) {
		shader.setVec3(LIGHT_COLOR_LOC, lightColor);
	} else {
		shader.setVec3(LIGHT_COLOR_LOC, LIGHT_COLOR_OFF);
	}
}

glm::vec3 Lamp::getLightPosition() const {
	return lightPos;
}