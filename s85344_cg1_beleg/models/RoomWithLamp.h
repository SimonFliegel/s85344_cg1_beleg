#pragma once

#include "../util/Shader.h"
#include "base_models/Cube.h"
#include "Lamp.h"

const char* const ROOM_TEXTURE = "textures/wood.jpg";
const char* const ROOM_TEXTURE_LOC = "texWood";

class RoomWithLamp : private AbstractShape
{
public:
	explicit RoomWithLamp(const Shader& shader);
	void draw(glm::mat4 model) override;
	void toggleLight();
	glm::vec3 getLightPosition() const;

private:
	const Shader& shader;
	const Texture roomTexture = Texture(ROOM_TEXTURE, 10);
	glm::vec3 lightPosition;
	Lamp lamp = Lamp(shader);
	Cube room;
	bool lightOn = true;
};

