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
	explicit Lamp(const Shader&);
	void draw(glm::mat4 model);
	void toggleLight();
	glm::vec3 getLightPosition() const;
private:
	const Shader& shader;
	const Texture standTexture = Texture(METAL_TEXTURE, 11);
	const Texture lightTexture = Texture(LIGHT_TEXTURE, 12);
	Cylinder cylinder;
	Sphere lightBulb;
	glm::vec3 lightPos;
	bool lightOn = true;
};

