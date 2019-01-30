#include "Cyclinder.h"



Cyclinder::Cyclinder()
{
}


Cyclinder::~Cyclinder()
{
}

void Cyclinder::generateCylinder(float r, int v, int h, int d)
{
	float theta = 2 * 3.14159 / v;
	float a = h / d;
	for (int j = 0; j < d; j++)
	{
		for (int i = 0; i < v; i++)
		{
			float x = r * cos(theta*i);
			float z = r * sin(theta*i);
			float x1 = r * cos(theta*(1 + i));
			float z1 = r * sin(theta*(1 + i));
			float u = x / theta;
			float v = 1 - (j / d);
			float u1 = x1 / theta;
			float v1 = 1 - ((j + 1) / d);

			//tri 1
			//Lower left
			texCoords.push_back(u);
			texCoords.push_back(v);
			normals.push_back(0.0);
			normals.push_back(0.0);
			normals.push_back(1.0);
			vertex.push_back(x);
			vertex.push_back(j*a);
			vertex.push_back(z);
			//lower right
			texCoords.push_back(u1);
			texCoords.push_back(v);
			normals.push_back(0.0);
			normals.push_back(0.0);
			normals.push_back(1.0);
			vertex.push_back(x1);
			vertex.push_back(j*a);
			vertex.push_back(z1);
			//upper right
			texCoords.push_back(u1);
			texCoords.push_back(v1);
			normals.push_back(0.0);
			normals.push_back(0.0);
			normals.push_back(1.0);
			vertex.push_back(x1);
			vertex.push_back((j+1)*a);
			vertex.push_back(z1);
			//tri2
			//upper right
			texCoords.push_back(u1);
			texCoords.push_back(v1);
			normals.push_back(0.0);
			normals.push_back(0.0);
			normals.push_back(1.0);
			vertex.push_back(x1);
			vertex.push_back((j + 1)*a);
			vertex.push_back(z1);
			//upper left
			texCoords.push_back(u);
			texCoords.push_back(v1);
			normals.push_back(0.0);
			normals.push_back(0.0);
			normals.push_back(1.0);
			vertex.push_back(x);
			vertex.push_back((j + 1)*a);
			vertex.push_back(z);
			//lower left
			texCoords.push_back(u);
			texCoords.push_back(v);
			normals.push_back(0.0);
			normals.push_back(0.0);
			normals.push_back(1.0);
			vertex.push_back(x);
			vertex.push_back(j*a);
			vertex.push_back(z);
		}
	}
}
