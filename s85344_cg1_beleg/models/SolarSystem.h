#pragma once

#include <array>
#include <memory>

#include "base_models/Sphere.h";
#include "../util/Texture.h";
#include "../util/Shader.h"

struct Sun {
	const float size;
	const glm::vec3 position;
	const float rotationSpeed;
	Texture texture;
	const char* textureLoc;
};

// textures: https://www.solarsystemscope.com/textures/
struct Planet {
	const float radius; // distance to sun
	float orbitAngle;
	const float orbitalSpeed;
	float rotationAngle;
	const float rotationSpeed;
	const float size;
	Texture texture;
	const char* textureLoc;
};

class SolarSystem
{
public:
	explicit SolarSystem(const Shader& shader);
	void draw(float deltaTime);

private:
	Shader shader;
	int modelLoc;
	int sphereIdLoc;
	const float SPEED = 1.0f; // used as a multiplier for the orbiting motion (dependent on FPS)
	Sphere sphere = Sphere();

	Sun sun { 0.3f, glm::vec3(0.0f, 0.0f, 0.0f), 8.0f, Texture("textures/sun.jpg", 0), "texSun" };
	
	const int NUM_PLANETS = 8;
	std::array<Planet, 8> planets = { 
		//		radius,	orbitAngle	orbitalSpeed	rotationAngle	rotationSpeed	size	texture								textureLoc
		Planet{	0.2f,	0.0f,		0.9f,			0.0f,			6.0f,			0.1f,	Texture("textures/mercury.jpg", 1), "texMercury"},
		Planet{	0.27f,	0.0f,		0.85f,			0.0f,			4.5f,			0.1f,	Texture("textures/venus.jpg", 2),   "texVenus"},
		Planet{	0.37f,	0.0f,		0.8f,			0.0f,			4.0f,			0.15f,	Texture("textures/earth.jpg", 3),   "texEarth"},
		Planet{	0.47f,	0.0f,		0.7f,			0.0f,			3.5f,			0.1f,	Texture("textures/mars.jpg", 4),    "texMars"},
		Planet{	0.6f,	0.0f,		0.6f,			0.0f,			3.0f,			0.3f,	Texture("textures/jupiter.jpg", 5), "texJupiter"},
		Planet{	0.75f,	0.0f,		0.5f,			0.0f,			2.5f,			0.25f,	Texture("textures/saturn.jpg", 6),  "texSaturn"},
		Planet{	0.9f,	0.0f,		0.4f,			0.0f,			2.0f,			0.15f,	Texture("textures/uranus.jpg", 7),  "texUranus"},
		Planet{	1.0f,	0.0f,		0.3f,			0.0f,			1.5f,			0.15f,	Texture("textures/neptune.jpg", 8), "texNeptune"}
	};

	void drawSolarSystem(float deltaTime, bool firstDraw);
	void drawSaturn(float deltaTime, bool firstDraw);
	void constraintAngle(float& angle) const;
	void applyLighting();
};


