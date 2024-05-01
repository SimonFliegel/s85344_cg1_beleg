#pragma once

#include "../util/Shader.h"
#include "Room.h"
#include "Lamp.h"

const char* const OBJECT_ID_LOC = "objectId";

const char* const EXTERNAL_LIGHT_POS_LOC = "externalLightPos";
const char* const EXTERNAL_LIGHT_COLOR_LOC = "externalLightColor";

class RoomWithLamp : private AbstractShape
{
public:
	/// <summary>
	/// scene with a room and a lamp init using a given shader
	/// </summary>
	/// <param name="shader">shader for rendering</param>
	explicit RoomWithLamp(const Shader& shader);

	/// <summary>
	/// draws the romm with the lamp
	/// </summary>
	/// <param name="model">for transformation of the scene</param>
	void draw(const glm::mat4& model) override;

	/// <summary>
	/// toggles the light of the lamp
	/// </summary>
	void toggleLight();

	/// <returns>light position</returns>
	glm::vec3 getLightPosition() const;

	void setExternalLightSource(const glm::vec3& lightPos, const glm::vec3& lightColor);

private:
	const Shader& shader;
	glm::vec3 lightPosition;
	Lamp lamp = Lamp(shader, OBJECT_ID_LOC);
	Room room = Room(shader, OBJECT_ID_LOC);
};

