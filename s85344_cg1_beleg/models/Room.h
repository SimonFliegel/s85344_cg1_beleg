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
	/// <summary>
	/// Room conataining walls and floor with textures
	/// </summary>
	/// <param name="shader">for rendering</param>
	/// <param name="objectIdLoc">for mappign the right texture to the objects</param>
	explicit Room(const Shader& shader, const char* const objectIdLoc);

	/// <summary>
	/// draws the room
	/// </summary>
	/// <param name="model">for transformation of the scene</param>
	void draw(const glm::mat4& model) override;
private:
	const Shader& shader;
	const char* const objectIdLoc;
	const int WALL_ID = 0;
	const int FLOOR_ID = 1;
	const Texture wallTexture = Texture(WALL_TEXTURE, 10);
	const Texture floorTexture = Texture(FLOOR_TEXTURE, 11);
	Cube walls;
	Plain floor;
};
