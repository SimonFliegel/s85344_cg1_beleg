#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>
#include <memory>

#include "SolarSystem.h"

SolarSystem::SolarSystem(const Shader& shader) : shader(shader)
{
	sphere.bind();

	sunTexture = std::make_unique<Texture>(sun.texturePath, 0);
	shader.setInt(sun.textureLoc, sunTexture->getTextureUnit());
	for (int i = 0; i < sizeof(planets) / sizeof(Planet); i++)
	{
		textures[i] = std::make_unique<Texture>(planets[i].texturePath, i+1); // sun is 0
		shader.setInt(planets[i].textureLoc, textures[i]->getTextureUnit());
	}

	applyLighting();
	drawSolarSystem(true, 0.0f);
}

void SolarSystem::draw()
{
	drawSolarSystem(false, theta);
	theta += SPEED;
	constraintAngle(theta);
}

void SolarSystem::drawSolarSystem(bool firstDraw, float angle) {
	const std::string SPHERE_ID = "sphereId";

	// sun
	if (firstDraw) {
		sunTexture->bind();
	}
	auto model = glm::mat4(1.0f);
	model = glm::translate(model, sun.position);
	model = glm::scale(model, glm::vec3(sun.size, sun.size, sun.size));
	shader.setInt(SPHERE_ID, 0);
	shader.setMat4("model", model);
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
		shader.setInt(SPHERE_ID, i+1);
		shader.setMat4("model", model);
		sphere.draw();
	}
}

void SolarSystem::constraintAngle(float &angle) const {
	if (angle > 4 * PI)
	{
		angle = 0.0f;
	}
}

glm::vec3 SolarSystem::getSunPosition() const
{
	return sun.position;
}

void SolarSystem::drawSaturn(bool firstDraw, float angle)
{
	// TODO
}

void SolarSystem::applyLighting()
{
	shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f)); // white light
	// TODO
}