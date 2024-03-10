#pragma once

#include "Shape.h"

class Plain : public Shape
{
protected:
	void createShape() final;
public:
	Plain();
};

