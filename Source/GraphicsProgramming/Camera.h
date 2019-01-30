#pragma once
// Include GLUT, openGL, input.
#include "Input.h"
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>
#include "Vector3.h"
#include "Camera.h"
class Camera
{
public:
	Camera();

	~Camera();
	Input* input;
	void update();

	//gets and sets

	void setPosition(Vector3 pos) { position = pos; }
	void setPosx(float pos) { position.x = pos; }
	void setPosy(float pos) { position.y = pos; }
	void setPosz(float pos) { position.z = pos; }

	Vector3 getPosition(){ return position; }
	float getPosx() { return position.x; }
	float getPosy() { return position.y; }
	float getPosz() { return position.z; }

	float getRx() { return right.x; }
	float getRy() { return right.y; }
	float getRz() { return right.z; }

	Vector3 getLookat(){ return lookat; }


	void setForward(float x, float y, float z) 
	{ 
		Vector3 view(x, y, z);
		forward = view;
	}
	Vector3 getForward(){ return forward; }

	Vector3 getUp(){ return up; }

	void setStart(Vector3 in) { start = in; }
	void setEnd(Vector3 in) { end = in; }


	void setYaw(float y) { Yaw = y; }
	float getYaw() { return Yaw; }

	void setPitch(float p) { Pitch = p; }
	float getPitch() { return Pitch; }


	//movement functions

	void handleInput(float dt, float x, float y, float z);
	void moveUp(float dt, float y);
	void moveDown(float dt, float y);
	void moveLeft(float dt, float x, float y, float z);
	void moveRight(float dt, float x, float y, float z);
	void moveBack(float dt, float x, float y, float z);
	void moveForward(float dt, float x, float y, float z);
	float mousex;
	float mousey;
protected:
	//variables
	Vector3 start;
	Vector3 end;
	Vector3 position;
	Vector3 lookat;
	Vector3 forward;
	Vector3 up;
	Vector3 right;
	float Yaw;
	float Pitch;
	float Roll;
	
};

