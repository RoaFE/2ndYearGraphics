#include "PlaneShape.h"



PlaneShape::PlaneShape()
{
}


PlaneShape::~PlaneShape()
{
}

void PlaneShape::generateXZPlane(int len, int breadth)
{
	//loops to generate a plane
	for (int z = 0; z < len; z++)
	{
		for (int x = 0; x < breadth; x++)
		{
			texCoords.push_back(1);
			texCoords.push_back(0);
			normals.push_back(0.0);
			normals.push_back(1.0);
			normals.push_back(0.0);
			vertex.push_back((x + 1));
			vertex.push_back(0.0);
			vertex.push_back(z);

			texCoords.push_back(0);
			texCoords.push_back(0);
			normals.push_back(0.0);
			normals.push_back(1.0);
			normals.push_back(0.0);
			vertex.push_back(x);
			vertex.push_back(0.0);
			vertex.push_back(z);

			texCoords.push_back(0);
			texCoords.push_back(1);
			normals.push_back(0.0);
			normals.push_back(1.0);
			normals.push_back(0.0);
			vertex.push_back(x);
			vertex.push_back(0.0);
			vertex.push_back((z + 1));

			texCoords.push_back(1);
			texCoords.push_back(1);
			normals.push_back(0.0);
			normals.push_back(1.0);
			normals.push_back(0.0);
			vertex.push_back((x + 1));
			vertex.push_back(0.0);
			vertex.push_back((z + 1));

		}
	}
}

void PlaneShape::generateXYPlane(int b, int h)
{

	float u1, u2, v1, v2;
	//loops to generate a plane
	for (float y = h; y > 0; y--)
	{
		for (float x = 0; x < b; x++)
		{
			//calculate the tex coordinates
			u1 = (x / b);
			u2 = ((x + 1) / b);
			v1 = 1 - (y / h);
			v2 = 1 - ((y - 1) / h);
			texCoords.push_back(u1);
			texCoords.push_back(v1);
			normals.push_back(0.0);
			normals.push_back(0.0);
			normals.push_back(1.0);
			vertex.push_back((x));
			vertex.push_back(y + 1);
			vertex.push_back(0.0);


			texCoords.push_back(u1);
			texCoords.push_back(v2);
			normals.push_back(0.0);
			normals.push_back(0.0);
			normals.push_back(1.0);
			vertex.push_back(x);
			vertex.push_back(y);
			vertex.push_back(0.0);


			texCoords.push_back(u2);
			texCoords.push_back(v2);
			normals.push_back(0.0);
			normals.push_back(0.0);
			normals.push_back(1.0);
			vertex.push_back(x + 1);
			vertex.push_back((y));
			vertex.push_back(0.0);


			texCoords.push_back(u2);
			texCoords.push_back(v1);
			normals.push_back(0.0);
			normals.push_back(0.0);
			normals.push_back(1.0);
			vertex.push_back((x + 1));
			vertex.push_back((y + 1));
			vertex.push_back(0.0);
		}
	}
}

void PlaneShape::generateYZPlane(int l, int b)
{
	//loops to generate a plane
	float u1, u2, v1, v2;
	for (float y = l; y > 0; y--)
	{
		for (float z = 0; z < b; z++)
		{
			//calculate the tex coordinates
			 u1 = (z / b);
			 u2 = ((z + 1) / b);
			 v1 = 1- (y / l);
			 v2 = 1 - ((y - 1) / l);


			texCoords.push_back(u1);
			texCoords.push_back(v1);
			normals.push_back(1.0);
			normals.push_back(0.0);
			normals.push_back(0.0);
			vertex.push_back(0.0);
			vertex.push_back((y));
			vertex.push_back(z);

			texCoords.push_back(u1);
			texCoords.push_back(v2);
			normals.push_back(1.0);
			normals.push_back(0.0);
			normals.push_back(0.0);
			vertex.push_back(0.0);
			vertex.push_back(y-1);
			vertex.push_back(z);

			texCoords.push_back(u2);
			texCoords.push_back(v2);
			normals.push_back(1.0);
			normals.push_back(0.0);
			normals.push_back(0.0);
			vertex.push_back(0.0);
			vertex.push_back(y-1);
			vertex.push_back((z + 1));

			texCoords.push_back(u2);
			texCoords.push_back(v1);
			normals.push_back(1.0);
			normals.push_back(0.0);
			normals.push_back(0.0);
			vertex.push_back(0.0);
			vertex.push_back((y));
			vertex.push_back((z + 1));

		}
	}
}


//irrelivent code I may wish to try and re implement later

//u1 = (x / b);
//u2 = ((x + 1) / b);
//v1 = (y / b);
//v2 = ((y + 1) / b);
//texCoords.push_back(u1);
//texCoords.push_back(v1);
//normals.push_back(0.0);
//normals.push_back(0.0);
//normals.push_back(1.0);
//vertex.push_back((x));
//vertex.push_back(y + 1);
//vertex.push_back(0.0);
//
//
//texCoords.push_back(u1);
//texCoords.push_back(v2);
//normals.push_back(0.0);
//normals.push_back(0.0);
//normals.push_back(1.0);
//vertex.push_back(x);
//vertex.push_back(y);
//vertex.push_back(0.0);
//
//
//texCoords.push_back(u2);
//texCoords.push_back(v2);
//normals.push_back(0.0);
//normals.push_back(0.0);
//normals.push_back(1.0);
//vertex.push_back(x + 1);
//vertex.push_back((y));
//vertex.push_back(0.0);
//
//
//texCoords.push_back(u2);
//texCoords.push_back(v2);
//normals.push_back(0.0);
//normals.push_back(0.0);
//normals.push_back(1.0);
//vertex.push_back((x + 1));
//vertex.push_back((y + 1));
//vertex.push_back(0.0);


//texCoords.push_back(0);
//texCoords.push_back(0);
//normals.push_back(0);
//normals.push_back(0);
//normals.push_back(1);
//vertex.push_back(0 - b);
//vertex.push_back(0 + h);
//vertex.push_back(0);
//
//texCoords.push_back(0);
//texCoords.push_back(1);
//normals.push_back(0);
//normals.push_back(0);
//normals.push_back(1);
//vertex.push_back(0 - b);
//vertex.push_back(0 - h);
//vertex.push_back(0);
//
//texCoords.push_back(1);
//texCoords.push_back(1);
//normals.push_back(0);
//normals.push_back(0);
//normals.push_back(1);
//vertex.push_back(0 + b);
//vertex.push_back(0 - h);
//vertex.push_back(0);
//
//texCoords.push_back(1);
//texCoords.push_back(0);
//normals.push_back(0);
//normals.push_back(0);
//normals.push_back(1);
//vertex.push_back(0 + b);
//vertex.push_back(0 + h);
//vertex.push_back(0);