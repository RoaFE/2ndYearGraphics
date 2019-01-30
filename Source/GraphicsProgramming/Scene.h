// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>
#include "Shape.h"
#include "Model.h"
#include "Camera.h"
#include "PlaneShape.h"
#include "SphereShape.h"
#include "Cyclinder.h"
#include "Shadow.h"
#include "CuboidShape.h"
#include "SkyBox.h"
class Scene{

public:
	Scene(Input *in);
	// Main render function
	void render();
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);
	

	

	float speed = 2.0;
	float rotation;

protected:
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
	void calculateFPS();
	//
	Camera camera0;		//Camera for entering the screen
	Camera camera1;		//Camera for moving about the scene
	Camera camera2;		//Birds eye
	Camera camera3;		//No clip

	Camera* currentcam;	//pointer to the current camera

	// For access to user input.
	Input* input;
		
	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	//other variables
	Model palm;					//Palm trees
	Model helios;				//Eagle 
	Model heliosR;				//Eagle reflection
	PlaneShape floor;			//Floor
	PlaneShape mirrorBorder;	//Border around the mirror
	PlaneShape river;			//river on the ground
	PlaneShape window;			//window box 1
	PlaneShape window2;			//window box 2
	PlaneShape window3;			//window box 3
	PlaneShape back;			//Back of the monitor
	PlaneShape frontWall;		//Wall at the back of the scene
	PlaneShape leftWall;		//wall to the left
	PlaneShape rightWall;		//wall to the right
	PlaneShape compSten;		//Comptuer screen stencil buffer
	PlaneShape shadowSten;		//floor stencil buffer to stop shadows appearing off the plane
	SphereShape sphere1;		//Speher that rotates around the eagle
	SphereShape sphere2;		//Diamond
	CuboidShape borderTop;		//Top of the monitor
	CuboidShape borderSide;		//Side of the monitor
	SkyBox vaporbox;			//Sky box
	Shadow shadow;				//Shadow class
	GLuint vhs;				//Texture for vhs overlay

	//sun colour
	float red = 1.0;
	float blue = 0.05;
	float green = 0.0f;

	//camera controller
	int cameraController = 1;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];
	float shadowMatrix[16];

	//control variables
	bool poly = false;
	bool light = false;
	bool renderText = true;
	bool start = false;
	bool menu = false;
	bool sun = true;
	int textControl = 0;
	float shin = 1025;
};

#endif