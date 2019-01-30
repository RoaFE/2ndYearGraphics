#include "Disc.h"



Disc::Disc()
{
}


Disc::~Disc()
{
}


void Disc::generateDisc(int r, int v)
{
	float theta = 2 * 3.14159 / v;
	for (int i = 0; i < v; i++)
	{
		float x = r * cos(theta*i);
		float y = r * sin(theta*i);
		float x1 = r * cos(theta*(1 + i));
		float y1 = r * sin(theta*(1 + i));
		float u = ((cos(theta * i)) / 2 * r) + 0.5f;
		float v = ((sin(theta * i)) / 2 * r) + 0.5f;
		float u1 = ((cos(theta * (i + 1))) / 2 * r) + 0.5f;
		float v1 = ((sin(theta * (i + 1))) / 2 * r) + 0.5f;

		texCoords.push_back(0.5);
		texCoords.push_back(0.5);
		normals.push_back(0.0); 
		normals.push_back(0.0);
		normals.push_back(1.0);
		
		vertex.push_back(0.0);
		vertex.push_back(0.0);
		vertex.push_back(0.0);

		texCoords.push_back(u);
		texCoords.push_back(v);
		normals.push_back(0.0);
		normals.push_back(0.0);
		normals.push_back(1.0);
		vertex.push_back(x);
		vertex.push_back(y);
		vertex.push_back(0.0);

		texCoords.push_back(u1);
		texCoords.push_back(v1);
		normals.push_back(0.0);
		normals.push_back(0.0);
		normals.push_back(1.0);
		vertex.push_back(x1);
		vertex.push_back(y1);
		vertex.push_back(0.0);

	}
}