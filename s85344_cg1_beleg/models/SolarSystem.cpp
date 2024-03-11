#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>
#include <memory>

#include "SolarSystem.h"

SolarSystem::SolarSystem(const Shader& shader) : shader(shader)
{
	sphere.bind();

	// texture uniforms
	shader.setInt(sun.textureLoc, sun.texture.getTextureUnit());
	for (int i = 0; i < NUM_PLANETS; i++)
	{
		Planet planet = planets[i];
		shader.setInt(planet.textureLoc, planet.texture.getTextureUnit());
	}

	applyLighting();
	drawSolarSystem(0.0f, true); // initial draw to bind textures
}

void SolarSystem::draw(float deltaTime)
{
	drawSolarSystem(deltaTime, false);
}

void SolarSystem::drawSolarSystem(float deltaTime, bool isFirstDraw) {
	const std::string SPHERE_ID = "sphereId";

	// sun
	if (isFirstDraw) {
		sun.texture.bind();
	}
	auto model = glm::mat4(1.0f);
	model = glm::translate(model, sun.position);
	model = glm::scale(model, glm::vec3(sun.size, sun.size, sun.size));
	shader.setInt(SPHERE_ID, 0);
	shader.setMat4("model", model);
	sphere.draw();

	for (int i = 0; i < NUM_PLANETS; i++)
	{
		if (isFirstDraw) {
			planets[i].texture.bind();
		}
		model = glm::mat4(1.0f);

		Planet planet = planets[i];
		float planetOrbitAngle = planet.orbitAngle + planet.orbitalSpeed * SPEED * deltaTime;
		float planetRotationAngle = planet.rotationAngle + planet.rotationSpeed * SPEED * deltaTime;
		constraintAngle(planetOrbitAngle);
		constraintAngle(planetRotationAngle);

		model = glm::translate(model, glm::vec3(planet.radius * cos(planetOrbitAngle), planet.radius * sin(planetOrbitAngle), 0.0f));
		model = glm::rotate(model, planetRotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(planet.size, planet.size, planet.size));
		
		shader.setInt(SPHERE_ID, i+1);
		shader.setMat4("model", model);
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
	// TODO
}