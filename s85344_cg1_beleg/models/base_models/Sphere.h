#pragma once

#include "Shape.h"

class Sphere : public Shape
{
protected:
	void createShape() final;
public:
	Sphere();
};

