#pragma once

#include "Shape.h"

class Cylinder : public Shape
{
protected:
	void createShape() final;
public:
	Cylinder();
};

