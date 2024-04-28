#pragma once

#include "../util/Shader.h"
#include "../util/Texture.h"
#include "base_models/Cylinder.h"
#include "base_models/Sphere.h"

const char* const METAL_TEXTURE = "textures/metal.jpg";
const char* const LIGHT_TEXTURE = "textures/light.jpg";
const char* const METAL_TEXTURE_LOC = "texMetal";
const char* const LIGHT_TEXTURE_LOC = "texLight";

class Lamp : AbstractShape
{
public:
	explicit Lamp(const Shader&, const char* const objectIdLoc);
	void draw(glm::mat4 model);
	void setLight(bool state);
	glm::vec3 getLightPosition() const;
private:
	const Shader& shader;
	const char* const objectIdLoc;
	const int STAND_AND_ARM_ID = 2;
	const int LIGHT_BULB_ID = 3;
	const Texture standTexture = Texture(METAL_TEXTURE, 20);
	const Texture lightTexture = Texture(LIGHT_TEXTURE, 21);
	const glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	Cylinder cylinder;
	Sphere lightBulb;
	glm::vec3 lightPos;
};

