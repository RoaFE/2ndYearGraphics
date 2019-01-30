#ifndef _SHAPE_H
#define _SHAPE_H

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

class Shape
{

	public:
		void renderQuads();
		void renderTris();
		void loadTexture(char*);
		GLuint texture;
protected:
		//vectors storing vertex normal and texture positions
		std::vector<float> vertex, normals, texCoords;
		

};
#endif 
