#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>
#include <memory>

#include "SolarSystem.h"

SolarSystem::SolarSystem(GLuint program) : program(program)
{
	modelLoc = glGetUniformLocation(program, "model");
	sphereIdLoc = glGetUniformLocation(program, "sphereId");
	sphere.createShape();
	sphere.bind();

	sunTexture = std::make_unique<Texture>(sun.texturePath, 0);
	glUniform1i(glGetUniformLocation(program, sun.textureLoc), sunTexture->getTextureUnit());
	for (int i = 0; i < sizeof(planets) / sizeof(Planet); i++)
	{
		textures[i] = std::make_unique<Texture>(planets[i].texturePath, i+1); // sun is 0
		glUniform1i(glGetUniformLocation(program, planets[i].textureLoc), textures[i]->getTextureUnit());
	}


	drawSolarSystem(true, 0.0f);
}

void SolarSystem::draw()
{
	drawSolarSystem(false, theta);
	theta += SPEED;
	constraintAngle(theta);
}

void SolarSystem::drawSolarSystem(bool firstDraw, float angle) {
	// sun
	if (firstDraw) {
		sunTexture->bind();
	}
	auto model = glm::mat4(1.0f);
	model = glm::translate(model, sun.position);
	model = glm::scale(model, glm::vec3(sun.size, sun.size, sun.size));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniform1i(sphereIdLoc, 0);
	sphere.draw();

	for (int i = 0; i < sizeof(planets) / sizeof(Planet); i++)
	{
		if (firstDraw) {
			textures[i]->bind();
		}
		model = glm::mat4(1.0f);
		Planet planet = planets[i];
		float planetAngle = planet.speed * angle;
		constraintAngle(planetAngle);
		model = glm::translate(model, glm::vec3(planet.radius * cos(planetAngle), planet.radius * sin(planetAngle), 0.0f));
		model = glm::scale(model, glm::vec3(planet.size, planet.size, planet.size));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(sphereIdLoc, i+1);
		sphere.draw();
	}
}

void SolarSystem::constraintAngle(float &angle) const {
	if (angle > 4 * PI)
	{
		angle = 0.0f;
	}
}