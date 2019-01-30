#pragma once
#include "Shape.h"
// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>
#include "Vector3.h"
class PlaneShape :
	public Shape
{
public:
	PlaneShape();
	~PlaneShape();

	void generateXZPlane(int len, int breadth);
	void generateXYPlane(int breadth, int height);
	void generateYZPlane(int len, int breadth);

};

