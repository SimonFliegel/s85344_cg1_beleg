#pragma once

#include "Shape.h"

class Cube : public Shape
{
protected:
	void createShape() final;
public:
	Cube();
};

