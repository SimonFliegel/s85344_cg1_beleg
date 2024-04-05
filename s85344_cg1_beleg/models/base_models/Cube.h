#pragma once

#include "BaseShape.h"

class Cube : public BaseShape
{
protected:
	void createShape() final;
public:
	Cube();
};

