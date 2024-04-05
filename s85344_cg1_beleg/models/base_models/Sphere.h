#pragma once

#include "BaseShape.h"

class Sphere : public BaseShape
{
protected:
	void createShape() final;
public:
	Sphere();
};

