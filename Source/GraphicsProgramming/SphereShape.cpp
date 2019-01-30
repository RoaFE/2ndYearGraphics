#include "SphereShape.h"



SphereShape::SphereShape()
{
}


SphereShape::~SphereShape()
{
}

void SphereShape::generateSphere(int r, int lon, int lat)
{
	normals.clear();
	texCoords.clear();
	vertex.clear();
	//calculating increment of angle in long and latitude
	float theta = (2 * 3.14159) / lat;
	float delta = 3.14159 / lon;
	for (float i = 0; i < lon; i++)
	{
		for (float o = 0; o < lat; o++)
		{

			
			//Tex cordinates are calcualted since the circle is 
			//like a rectangle curved into a sphere
			texCoords.push_back(theta*o / (2 * 3.14151));
			texCoords.push_back(delta*i / 3.14151);
			//normals are the exact same as the vector from the centre to that vertice
			normals.push_back(cos(theta*o) * sin(delta*i));
			normals.push_back(cos(delta * i));
			normals.push_back(sin(theta*o) * sin(delta*i));
			//vertex cordinates 
			vertex.push_back(r*cos(theta*o) * sin(delta*i));
			vertex.push_back(r*cos(delta * i));
			vertex.push_back(r*sin(theta*o) * sin(delta*i));


			texCoords.push_back(theta*o / (2 * 3.14151));
			texCoords.push_back(delta*((i + 1)) / 3.14151);
			normals.push_back(cos(theta*o) * sin(delta*((i + 1))));
			normals.push_back(cos(delta * ((i + 1))));
			normals.push_back(sin(theta*o) * sin(delta*((i + 1))));
			vertex.push_back(r*cos(theta*o) * sin(delta*((i + 1))));
			vertex.push_back(r*cos(delta * ((i + 1))));
			vertex.push_back(r*sin(theta*o) * sin(delta*((i + 1))));



			texCoords.push_back(theta*((o + 1)) / (2 * 3.14151));
			texCoords.push_back(delta*(i + 1) / 3.14151);
			normals.push_back(cos(theta*((o + 1))) * sin(delta*(i + 1)));
			normals.push_back(cos(delta * (i + 1)));
			normals.push_back(sin(theta*((o + 1))) * sin(delta*(i + 1)));
			vertex.push_back(r*cos(theta*((o + 1))) * sin(delta*(i + 1)));
			vertex.push_back(r*cos(delta * (i + 1)));
			vertex.push_back(r*sin(theta*((o + 1))) * sin(delta*(i + 1)));



			texCoords.push_back(theta*(o + 1) / (2 * 3.14151));
			texCoords.push_back(delta*i / 3.14151);
			normals.push_back(cos(theta*(o + 1)) * sin(delta*i));
			normals.push_back(cos(delta * i));
			normals.push_back(sin(theta*(o + 1)) * sin(delta*i));
			vertex.push_back(r*cos(theta*(o + 1)) * sin(delta*i));
			vertex.push_back(r*cos(delta * i));
			vertex.push_back(r*sin(theta*(o + 1)) * sin(delta*i));


			
		}
	}
}

//void SphereShape::renderSphere()
//{
//	float* v = vertex.data();
//	float* n = normals.data();
//	float* t = texCoords.data();
//
//	int size = texCoords.size();
//	size = size / 2;
//
//	glEnableClientState(GL_VERTEX_ARRAY);
//	glEnableClientState(GL_NORMAL_ARRAY);
//	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//	glVertexPointer(3, GL_FLOAT, 0, v);
//	glNormalPointer(GL_FLOAT, 0, n);
//	glTexCoordPointer(2, GL_FLOAT, 0, t);
//
//
//	glDrawArrays(GL_QUADS, 0, size);
//
//	glDisableClientState(GL_VERTEX_ARRAY);
//	glDisableClientState(GL_NORMAL_ARRAY);
//	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//}
