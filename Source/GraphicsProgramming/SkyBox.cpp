#include "SkyBox.h"



SkyBox::SkyBox()
{
}


SkyBox::~SkyBox()
{
}

extern float verts[] = {	//front
							-1.0, 1.0, -1.0,		// Vertex #0
							-1.0, -1.0, -1.0,		// Vertex #1
							1.0,  -1.0, -1.0,		// Vertex #2
							1.0,  1.0, -1.0,		// Vertex #3
							//right
							1.0, 1.0, -1.0,			//V4
							1.0, -1.0, -1.0,		//V5
							1.0, -1.0, 1.0,			//V6
							1.0, 1.0, 1.0,			//V7
							//back
							1.0,  1.0, 1.0,			// Vertex #8
							1.0,  -1.0, 1.0,		// Vertex #9
							-1.0, -1.0, 1.0,		// Vertex #10
							-1.0, 1.0, 1.0,			// Vertex #11
							//left
							-1.0, 1.0, 1.0,			//V12
							-1.0, -1.0, 1.0,		//V13
							-1.0, -1.0, -1.0,		//V14
							-1.0, 1.0, -1.0,		//V15
							//top
							-1.0, 1.0, 1.0,			//V16
							-1.0, 1.0, -1.0,		//V17
							1.0,  1.0, -1.0,		//V18
							1.0, 1.0, 1.0,			//V19
							//bottom
							-1.0, -1.0, -1.0,		//V20
							-1.0, -1.0, 1.0,		//V21
							1.0, -1.0, 1.0,			//V22
							1.0, -1.0, -1.0,		//V23

						};

extern float norms[] = {//Front 
						0.0, 0.0, 1.0,		//0
						0.0, 0.0, 1.0,		//1
 						0.0, 0.0, 1.0,		//2
						0.0, 0.0, 1.0,		//3
						//right
						1.0, 0.0, 0.0,		//4
						1.0, 0.0, 0.0,		//5
						1.0, 0.0, 0.0,		//6
						1.0, 0.0, 0.0,		//7
						//back
						0.0, 0.0, -1.0,		//8
						0.0, 0.0, -1.0,		//9
						0.0, 0.0, -1.0,		//10
						0.0, 0.0, -1.0,		//11
						//left
						-1.0, 0.0, 0.0,		//12
						-1.0, 0.0, 0.0,		//13
						-1.0, 0.0, 0.0,		//14
						-1.0, 0.0, 0.0,		//15
						//top
						0.0, 1.0, 0.0,		//16
						0.0, 1.0, 0.0,		//17
						0.0, 1.0, 0.0,		//18
						0.0, 1.0, 0.0,		//19
						//Bottom
						0.0, -1.0, 0.0,		//16
						0.0, -1.0, 0.0,		//17
						0.0, -1.0, 0.0,		//18
						0.0, -1.0, 0.0,		//19
						};		


extern float texcoords[]= {	//front
							0.25, 0.33, 	//0
							0.25, 0.66, 	//1
 							0.5, 0.66, 		//2
							0.5, 0.33, 		//3
							//right
							0.5, 0.33, 		//4
							0.5, 0.66, 		//5
							0.75, 0.66, 		//6
							0.75, 0.33, 		//7
							//back
							0.75, 0.33, 		//8
							0.75, 0.66, 		//9
							1.0, 0.66, 		//10
							1.0, 0.33, 		//11
							//left
							0.0, 0.33, 		//12
							0.0, 0.66, 		//13
							0.25, 0.66, 		//14
							0.25, 0.33, 		//15
							//top
							0.25, 0.0, 		//16
							0.25, 0.33, 	//17
							0.5, 0.33, 		//18
							0.5, 0.0, 		//19
							//bottom
							0.25, 0.66, 	//20
							0.25, 1.0, 		//21
							0.5, 1.0, 		//22
							0.5, 0.66,  	//23
							};


void SkyBox::render2()
{
	// code to render the sky box
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

	glDrawArrays(GL_QUADS, 0, 24);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}

void SkyBox::loadTexture(char* filename)
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