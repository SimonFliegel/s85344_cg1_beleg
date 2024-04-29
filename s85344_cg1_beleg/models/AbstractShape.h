#pragma once

class AbstractShape
{
public:
	AbstractShape() = default;
	virtual ~AbstractShape() = default;
	virtual void draw(const glm::mat4& model) = 0;
};

