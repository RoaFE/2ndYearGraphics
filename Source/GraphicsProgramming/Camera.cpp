#include "Camera.h"



Camera::Camera()
{
	//Rotations
	Yaw = 0;
	Pitch = 0;
	Roll = 0;
}


Camera::~Camera()
{
}


void Camera::update()
{
	float cosR, cosP, cosY; //temp values for sin/cos from
	float sinR, sinP, sinY;
	// Roll, Pitch and Yall are variables stored by the camera
	// handle rotation
	// Only want to calculate these values once, when rotation changes, not every frame.
	cosY = cosf(Yaw*3.1415 / 180);
	cosP = cosf(Pitch*3.1415 / 180);
	cosR = cosf(Roll*3.1415 / 180);
	sinY = sinf(Yaw*3.1415 / 180);
	sinP = sinf(Pitch*3.1415 / 180);
	sinR = sinf(Roll*3.1415 / 180);

	//This using the parametric equation of a sphere
	// Calculate the three vectors to put into glu Lookat
	// Look direction, position and the up vector
	// This function could also calculate the right vector
	forward.x = sinY * cosP;
	forward.y = sinP;
	forward.z = cosP * -cosY;

	lookat = position + forward;
	// Look At Point

	// To calculate add Forward Vector to Camera position.
	// Up Vector
	up.x = -cosY * sinR - sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR - sinP * cosR * -cosY;
	// Side Vector (right)
	// this is a cross product between the forward and up vector.
	right = forward.cross(up);

}

void Camera::handleInput(float dt, float x, float y, float z)
{
		//moving up in the y
		if (input->isKeyDown('q'))
		{
			moveUp(dt, y);
			//input->SetKeyUp('q');
			update();
		}
		//down in y
		if (input->isKeyDown('e'))
		{
			moveDown(dt, y);
			//input->SetKeyUp('e');
			update();
		}
		//forward
		if (input->isKeyDown('w'))
		{
			moveForward(dt,x,y,z);
			//input->SetKeyUp('w');
			update();
		}
		//back
		if (input->isKeyDown('s'))
		{
			moveBack(dt, x, y, z);
			//input->SetKeyUp('s');
			update();
		}
		//left
		if (input->isKeyDown('a'))
		{
			moveLeft(dt, x, y, z);
			//input->SetKeyUp('a');
			update();
		}
		//right
		if (input->isKeyDown('d'))
		{
			moveRight(dt, x, y, z);
			//input->SetKeyUp('d');
			update();
		}
	//the dx and dy of the mouse's position
	mousex = input->getMouseX() - 400;
	mousey = input->getMouseY() - 300;

	//if mouse has moved calculate by how much and rotate camera that much
	if (mousex != 0)
	{
		setYaw(getYaw() + 0.1*mousex);
		glutWarpPointer(400, 300);
		update();
	}

	if (mousey != 0)
	{
		setPitch(getPitch() - 0.1*mousey);
		glutWarpPointer(400, 300);
		update();
	}

	//stop the camera moving out of it's defined space
	if (position.x < start.x)
	{
		position.x = start.x;
	}
	if (position.x > end.x)
	{
		position.x = end.x;
	}

	if (position.z < start.z)
	{
		position.z = start.z;
	}
	if (position.z > end.z)
	{
		position.z = end.z;
	}
}


void Camera::moveUp(float dt, float y)
{
	position.y += y * dt;
}

void Camera::moveDown(float dt, float y)
{
	position.y -= y * dt;
}

void Camera::moveLeft(float dt, float x, float y, float z)
{
	Vector3 go(right.x * x, right.y * y, right.z * z);
	position.add(go, -dt);
}

void Camera::moveRight(float dt, float x, float y, float z)
{
	Vector3 go(right.x * x, right.y * y, right.z * z);
	position.add(go, dt);
}

void Camera::moveBack(float dt, float x, float y, float z)
{
	Vector3 go(forward.x * x, forward.y * y, forward.z * z);
	position.add(go, -dt);
}

void Camera::moveForward(float dt, float x, float y, float z)
{
	Vector3 go(forward.x * x, forward.y * y, forward.z * z);
	position.add(go, dt);
}
