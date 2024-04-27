#pragma once

class AbstractShape
{
public:
	AbstractShape() = default;
	virtual ~AbstractShape() = default;
	virtual void draw(glm::mat4 model) = 0;
};

