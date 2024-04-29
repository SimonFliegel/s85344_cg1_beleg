#pragma once

class AbstractShape
{
public:
	AbstractShape() = default;
	virtual ~AbstractShape() = default;

	/// <summary>
	/// draws the shape
	/// </summary>
	/// <param name="model"></param>
	virtual void draw(const glm::mat4& model) = 0;
};

