#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>
#include <memory>

#include "SolarSystem.h"

SolarSystem::SolarSystem(const Shader& shader) : shader(shader)
{
	shader.use();
	sphere.bind();

	// texture uniforms
	shader.setInt(sun.textureLoc, sun.texture.getTextureUnit());
	for (int i = 0; i < NUM_PLANETS; i++)
	{
		Planet planet = planets[i];
		shader.setInt(planet.textureLoc, planet.texture.getTextureUnit());
	}

	applyLighting();
	drawSolarSystem(glm::mat4(1.0f), 0.0f, true); // initial draw to bind textures
}

void SolarSystem::draw(glm::mat4 model, float deltaTime)
{
	drawSolarSystem(model, deltaTime, false);
}

void SolarSystem::drawSolarSystem(glm::mat4 model, float deltaTime, bool isFirstDraw) {
	const std::string SPHERE_ID = "sphereId";

	// sun
	if (isFirstDraw) {
		sun.texture.bind();
	}

	float sunRotationAngle = sun.rotationAngle + sun.rotationSpeed * SPEED * deltaTime;
	
	glm::mat4 modelSun = model;
	modelSun = glm::translate(modelSun, sun.position);
	modelSun = glm::rotate(modelSun, sunRotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));
	modelSun = glm::scale(modelSun, glm::vec3(sun.size, sun.size, sun.size));

	shader.setInt(SPHERE_ID, 0);
	shader.setMat4("model", modelSun);
	sphere.draw();

	// update angle
	sun.rotationAngle = sunRotationAngle;

	for (int i = 0; i < NUM_PLANETS; i++)
	{
		if (isFirstDraw) {
			planets[i].texture.bind();
		}
		glm::mat4 modelPlanet = model;

		Planet planet = planets[i];
		float planetOrbitAngle = planet.orbitAngle + planet.orbitalSpeed * SPEED * deltaTime;
		float planetRotationAngle = planet.rotationAngle + planet.rotationSpeed * SPEED * deltaTime;
		constraintAngle(planetOrbitAngle);
		constraintAngle(planetRotationAngle);

		modelPlanet = glm::translate(modelPlanet, glm::vec3(planet.radius * cos(planetOrbitAngle), planet.radius * sin(planetOrbitAngle), 0.0f));
		modelPlanet = glm::rotate(modelPlanet, planetRotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));
		modelPlanet = glm::scale(modelPlanet, glm::vec3(planet.size, planet.size, planet.size));
		
		shader.setInt(SPHERE_ID, i+1);
		shader.setMat4("model", modelPlanet);
		sphere.draw();
		
		// update angles
		planets[i].orbitAngle = planetOrbitAngle;
		planets[i].rotationAngle = planetRotationAngle;
	}
}

void SolarSystem::constraintAngle(float &angle) const {
	if (angle > 2 * PI)
	{
		angle = 0.0f;
	}
}

void SolarSystem::drawSaturn(float deltaTime, bool firstDraw)
{
	// TODO
}

void SolarSystem::applyLighting()
{
	shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f)); // white light
}

glm::vec3 SolarSystem::getLightPosition() const
{
	return sun.position;
}