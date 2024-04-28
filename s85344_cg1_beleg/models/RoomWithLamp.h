#pragma once

#include "../util/Shader.h"
#include "Room.h"
#include "Lamp.h"

const char* const OBJECT_ID_LOC = "objectId";

class RoomWithLamp : private AbstractShape
{
public:
	explicit RoomWithLamp(const Shader& shader);
	void draw(glm::mat4 model) override;
	void toggleLight();
	glm::vec3 getLightPosition() const;

private:
	const Shader& shader;
	glm::vec3 lightPosition;
	Lamp lamp = Lamp(shader, OBJECT_ID_LOC);
	Room room = Room(shader, OBJECT_ID_LOC);
	bool lightOn = true;
};

