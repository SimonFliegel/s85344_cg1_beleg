#pragma once

#include "Shape.h"

class Sphere : public Shape
{
    public:
	Sphere() = default;
	void createShape() override;
};

