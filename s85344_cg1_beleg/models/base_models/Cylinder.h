#pragma once

#include "BaseShape.h"

class Cylinder : public BaseShape
{
protected:
	void createShape() final;
public:
	Cylinder();
};

