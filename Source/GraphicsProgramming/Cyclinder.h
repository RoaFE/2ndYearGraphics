#pragma once
#include "Shape.h"
class Cyclinder :
	public Shape
{
public:
	Cyclinder();
	~Cyclinder();

	void generateCylinder(float radius, int vertices, int height, int divisions);
};

