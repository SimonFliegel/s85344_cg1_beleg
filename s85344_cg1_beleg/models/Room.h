#pragma once

#include "../util/Shader.h"
#include "../util/Texture.h"
#include "base_models/Cube.h"
#include "base_models/Plain.h"

const char* const WALL_TEXTURE = "textures/wall.jpg";
const char* const FLOOR_TEXTURE = "textures/wood.jpg";

const char* const wallTextureLoc = "texWall";
const char* const floorTextureLoc = "texFloor";

class Room : AbstractShape
{
public:
	explicit Room(const Shader&, const char* const objectIdLoc);
	void draw(glm::mat4 model);
private:
	const Shader& shader;
	const char* const objectIdLoc;
	const int WALL_ID = 0;
	const int FLOOR_ID = 1;
	const Texture wallTexture = Texture(WALL_TEXTURE, 10);
	const Texture floorTexture = Texture(FLOOR_TEXTURE, 11);
	const glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	Cube walls;
	Plain floor;
	glm::vec3 lightPos;
};
