#ifndef _SKYBOX_H
#define _SKYBOX_H

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

class SkyBox
{
public:
	SkyBox();
	~SkyBox();

	void render2();		//Render function
	void loadTexture(char* filename);		//Load in texture
	GLuint texture;		//Texture variable
};

#endif