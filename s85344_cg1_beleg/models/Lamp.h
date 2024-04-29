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
	/// <summary>
	/// Lamp containing stand and light bulb as light source with textures
	/// </summary>
	/// <param name="shader">for rendering</param>
	/// <param name="objectIdLoc">for mapping the right texture to the objects</param>
	explicit Lamp(const Shader& shader, const char* const objectIdLoc);

	/// <summary>
	/// draws the lamp
	/// </summary>
	/// <param name="model">for transformation of the scene</param>
	void draw(const glm::mat4& model) override;

	/// <summary>
	/// sets the light on or off
	/// </summary>
	/// <param name="state"></param>
	void setLight(bool state);

	/// <returns>light position</returns>
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

