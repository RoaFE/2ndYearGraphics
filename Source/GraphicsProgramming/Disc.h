#pragma once
#include "Shape.h"
class Disc :
	public Shape
{
public:
	Disc();
	~Disc();

	void generateDisc(int radius, int vertices);
};

