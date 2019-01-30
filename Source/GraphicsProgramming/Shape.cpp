#include "shape.h"

							
//Render quad function
void Shape::renderQuads()
{
	//convert vector into a readable form for the pointer
	float* v = vertex.data();
	float* n = normals.data();
	float* t = texCoords.data();

	int size = texCoords.size();
	//since there is 2 texture cordinates for every vertex the size should be half the amount
	size = size / 2;
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v);
	glNormalPointer(GL_FLOAT, 0, n);
	glTexCoordPointer(2, GL_FLOAT, 0, t);

	glDrawArrays(GL_QUADS, 0, size);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}

//render triangle function
void Shape::renderTris()
{
	//convert vector into a readable form for the pointer
	float* v = vertex.data();
	float* n = normals.data();
	float* t = texCoords.data();
	//since there is 2 texture cordinates for every vertex the size should be half the amount
	int size = texCoords.size();
	size = size / 2;
	// add code to render the cube (above) using method 2
	//glBindTexture(GL_TEXTURE_2D, texture);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v);
	glNormalPointer(GL_FLOAT, 0, n);
	glTexCoordPointer(2, GL_FLOAT, 0, t);

	glDrawArrays(GL_TRIANGLES, 0, size);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}




void Shape::loadTexture(char* filename)
{
	texture = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT  // Depending on texture file type some need inverted others don't.
	);

	//check for an error during the load process
	if (texture == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

}

