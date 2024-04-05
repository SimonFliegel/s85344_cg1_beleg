#pragma once

#include "BaseShape.h"

class Plain : public BaseShape
{
protected:
	void createShape() final;
public:
	Plain();
};

