#pragma once
#include "Shape.h"
class CuboidShape :
	public Shape
{
public:
	CuboidShape();
	~CuboidShape();

	void generateCuboid(int l, int b, int h);
};

