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
class SphereShape :
	public Shape
{
public:
	SphereShape();
	~SphereShape();
	void generateSphere(int radius, int longitude, int latitude);
	/*void renderSphere();*/
};

