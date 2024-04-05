#pragma once

class AbstractShape
{
public:
	AbstractShape() = default;
	virtual ~AbstractShape() = default;
	virtual void draw() = 0;
};

