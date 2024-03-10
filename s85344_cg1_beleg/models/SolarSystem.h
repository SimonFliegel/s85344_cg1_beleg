#pragma once

#include <array>
#include <memory>

#include "base_models/Sphere.h";
#include "../util/Texture.h";
#include "../util/Shader.h"

struct Sun {
	float size;
	glm::vec3 position;
	const char* texturePath;
	const char* textureLoc;
};

// textures: https://www.solarsystemscope.com/textures/
struct Planet {
	float radius; // distance to sun
	float speed;
	float size;
	const char* texturePath;
	const char* textureLoc;
};

const Sun SUN { 0.3f, glm::vec3(0.0f, 0.0f, 0.0f), "textures/sun.jpg", "texSun"};

const Planet MERCURY { 0.2f, 0.9f, 0.1f, "textures/mercury.jpg", "texMercury"};
const Planet VENUS = { 0.27f, 0.85f, 0.1f, "textures/venus.jpg", "texVenus"};
const Planet EARTH = { 0.37f, 0.8f, 0.15f, "textures/earth.jpg", "texEarth"};
const Planet MARS{ 0.47f, 0.7f, 0.1f, "textures/mars.jpg", "texMars"};
const Planet JUPITER{ 0.6f, 0.6f, 0.3f, "textures/jupiter.jpg", "texJupiter"};
const Planet SATURN{ 0.75f, 0.5f, 0.25f, "textures/saturn.jpg", "texSaturn"};
const Planet URANUS{ 0.9f, 0.4f, 0.15f, "textures/uranus.jpg", "texUranus"};
const Planet NEPTUNE{ 1.0f, 0.3f, 0.15f, "textures/neptune.jpg", "texNeptune"};

class SolarSystem
{
public:
	explicit SolarSystem(const Shader& shader); // need to do uniforms with shaders
	void draw();
	glm::vec3 getSunPosition() const;

private:
	Shader shader;
	int modelLoc;
	int sphereIdLoc;
	const float SPEED = 0.0001f; // used as a multiplier for the orbiting motion
	float theta = 0.0f;; // orbiting motion incremented and later mutliplied by speed
	Sphere sphere = Sphere();

	const Sun sun{ SUN };
	std::unique_ptr<Texture> sunTexture;

	const std::array<Planet, 8> planets = { MERCURY, VENUS, EARTH, MARS, JUPITER, SATURN, URANUS, NEPTUNE };
	std::array<std::unique_ptr<Texture>, 8> textures;

	void drawSolarSystem(bool firstDraw, float angle);
	void drawSaturn(bool firstDraw, float angle);
	void constraintAngle(float& angle) const;
	void applyLighting();
};


