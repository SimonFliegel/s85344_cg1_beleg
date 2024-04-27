#pragma once

class AnimatedAbstractShape
{
public:
	AnimatedAbstractShape() = default;
	virtual ~AnimatedAbstractShape() = default;
	virtual void draw(glm::mat4 model, float deltaTime) = 0;
};

