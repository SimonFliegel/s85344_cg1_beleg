#pragma once

class AnimatedAbstractShape
{
public:
	AnimatedAbstractShape() = default;
	virtual ~AnimatedAbstractShape() = default;

	/// <summary>
	/// draws the shape
	/// </summary>
	/// <param name="model"></param>
	/// <param name="deltaTime">for constant animation speed independent from fps</param>
	virtual void draw(const glm::mat4& model, float deltaTime) = 0;
};

