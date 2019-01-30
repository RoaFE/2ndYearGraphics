#include "Scene.h"

Scene::Scene(Input *in)
{
	
	// Store pointer for input class
	input = in;
		
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Darkness of the soul
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glEnable(GL_LIGHTING);								// Enables Lighting
	glEnable(GL_TEXTURE_2D);							// Enables Texturing
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// What type of blending to do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	//glPolygonMode(GL_BACK, GL_LINE);					// Wire Frame 
	//glPolygonMode(GL_FRONT, GL_LINE);					// Wire Frame 
	// Other OpenGL / render setting should be applied here.
	camera1.setPosition(Vector3(0.0f, 1.5f, -0.3f));	//Initialise the roam camera and it's zone
	camera1.setEnd(Vector3(10.8f, 0.0f, -0.3f));
	camera1.setStart(Vector3(-10.8f, 3.0f, -29.7f));

	camera2.setPosition(Vector3(0.0f, 18.0f, -1.1f));	//Initialise the arieal view camera and it's starting 
	camera2.setPitch(-65);								//view
	camera2.setStart(Vector3(-0.1f, 18.1f, -1.2f));
	camera2.setEnd(Vector3(0.1f, 17.9f, -1.0f));

	camera3.setPosition(Vector3(0.0f, 9.0f, -15.f));	//Initialise the free roam camera
	camera3.setStart(Vector3(-30.f, 40.f, -50.f));
	camera3.setEnd(Vector3(30.f, -20.f, 20.f));


	camera0.setPosition(Vector3(0.0f, 1.5f, 60.f));		//Initialise the starting camera that walks you into the screen
	camera0.setStart(Vector3(-0.1f, 1.6f, -1.4f));
	camera0.setEnd(Vector3(0.1f, 1.4f, 60.1f));

	camera1.input = in;									//Set the cameras
	camera1.update();
	camera2.input = in;
	camera2.update();
	camera3.input = in;
	camera3.update();
	camera0.input = in;
	camera0.update();

	//set the cursor up
	glutWarpPointer(400, 300);
	glutSetCursor(GLUT_CURSOR_NONE);


	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	
	// Initialise variables
	
	palm.load("models/palm_tree.obj", "gfx/VHS-overlay.png");	//Load in the palm tree model

	//Ground
	floor.generateXZPlane(30,10);				//Generate the floor
	floor.loadTexture("gfx/grid.png");

	river.generateXZPlane(30, 8);						//Generate the river

	//Mirror
	mirrorBorder.generateXYPlane(100, 100);

	//Shadow Stencil
	shadowSten.generateXZPlane(30, 24);			//Stop the shadows rendering outside the screen

	//window boxes
	window.generateXYPlane(16,8);
	window.loadTexture("gfx/vaporwindows.png");

	window2.generateXYPlane(18, 6);
	window2.loadTexture("gfx/window2.png");

	window3.generateXYPlane(16, 8);
	window3.loadTexture("gfx/window3.png");

	//Skybox
	vaporbox.loadTexture("gfx/vaporskybox.png");

	//The computer screen
	back.generateXYPlane(24, 18);
	compSten.generateXYPlane(24, 18);
	back.loadTexture("gfx/screen.png");
	borderTop.generateCuboid(1, 13, 1);
	borderSide.generateCuboid(1, 1, 9);

	vhs = SOIL_load_OGL_texture
		(
			"gfx/VHS-overlay.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);


	//The statue which is meant to be an aesthetic staute of alexander as helios
	//but all online models wouldn't load so we have an eagle now
	helios.load("models/EagleBoi.obj", "gfx/Concrete.png");
	heliosR.load("models/EagleBoi.obj", "gfx/Concrete.png");
	//Sphere and diamond that orbit the reflection of the Eagle
	sphere1.generateSphere(1, 80, 80);
	//Lower the poly's on the sphere so it forms a diamond 
	sphere2.generateSphere(2, 2, 4);

	//The border around the scene
	frontWall.generateXYPlane(22, 12);
	frontWall.loadTexture("gfx/border.png");
	leftWall.generateYZPlane(12, 29);
	leftWall.loadTexture("gfx/border.png");
	rightWall.generateYZPlane(12, 29);
	rightWall.loadTexture("gfx/border.png");

	//The sun lighting
	glEnable(GL_LIGHT7);
}

void Scene::update(float dt)
{
	//update rotation
	rotation += speed * dt;

	//Start camera, Locked so you can't change camera till you've enetered the scene
	if (camera0.getPosition().z > -0.1)
	{
		start = false;
		currentcam = &camera0;
		currentcam->handleInput(dt, 0, 0, 0.7);
		camera1.setYaw(camera0.getYaw());		//Match the direction of camera
		camera1.setPitch(camera0.getPitch());	//So it's seemless when you switch cameras entering the scene
	}
	else
	{
		start = true;
		//Controls which camera you are looking through
		switch (cameraController) {
		case 1:
			currentcam = &camera1;					//Floor camera
			currentcam->handleInput(dt, 0.7, 0, 0.7);
			break;
		case 2:
			currentcam = &camera2;					// Bird Eye camera
			currentcam->handleInput(dt, 0, 0, 0);
			break;
		case 3:
			currentcam = &camera3;					//No Clip
			currentcam->handleInput(dt, 1, 1, 1);
			break;
		}
	}

	//Change camera
	if (input->isKeyDown('c'))
	{
		cameraController ++;
		input->SetKeyUp('c');
	}
	//Change texture filtering on the plane
	if (input->isKeyDown('i'))
	{
		textControl++;
		input->SetKeyUp('i');
	}
	//reset
	if (textControl > 4)
	{
		textControl = 0;
	}

	if (cameraController >= 4)
	{
		cameraController = 1;
	}
	//Decrease the sunset
	if (input->isKeyDown('p'))
	{
		if (green > 0)
		{
			green -= 0.01;
		}
		else if (blue < 0.1)
		{
			blue += 0.01;
		}
		else if (red > 0.1)
		{
			blue += 0.01;
			red -= 0.01;
		}
		input->SetKeyUp('p');
	}
	//Increase the sunset
	if (input->isKeyDown('o'))
	{
		if (red < 1.0)
		{
			blue -= 0.01;
			red += 0.01;
		}
		else if (blue > 0.0)
		{
			blue -= 0.01;
		}
		else if (green < 0.05)
		{
			green += 0.01;
		}
		input->SetKeyUp('o');
	}

	//Testing for specular lighting 
	if (input->isKeyDown('v'))
	{
		shin += 1.f;
		input->SetKeyUp('v');
	}
	else if (input->isKeyDown('b'))
	{
		shin -= 1.f;
		input->SetKeyUp('b');
	}

	// WireFrame Mode
	if (input->isKeyDown('r') && poly == false)
	{
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
		poly = true;
		input->SetKeyUp('r');
	}
	else if(input->isKeyDown('r') && poly == true)
	{
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
		poly = false;
		input->SetKeyUp('r');
	}
	//FlashLight
	if (input->isKeyDown('f') && light == false)
	{
		light = true;
		renderText = false;
		glEnable(GL_LIGHT0);
		input->SetKeyUp('f');

	}
	else if (input->isKeyDown('f') && light == true)
	{
		light = false;
		glDisable(GL_LIGHT0);
		input->SetKeyUp('f');
	}
	//Change lighting
	if (input->isKeyDown('l') && sun == false)
	{
		//Sun and no tree lights
		sun = true;
		glEnable(GL_LIGHT7);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glDisable(GL_LIGHT4);
		input->SetKeyUp('l');

	}
	else if (input->isKeyDown('l') && sun == true)
	{
		//tree lights and no sun
		sun = false;
		glDisable(GL_LIGHT7);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT3);
		glEnable(GL_LIGHT4);
		input->SetKeyUp('l');
	}
	//Toggle menu
	if (input->isKeyDown('m') && menu == false)
	{
		menu = true;
		input->SetKeyUp('m');

	}
	else if (input->isKeyDown('m') && menu == true)
	{
		menu = false;
		input->SetKeyUp('m');
	}

	// Calculate FPS for output
	//calculateFPS();
}

void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


	// Reset transformations
	glLoadIdentity();
	// Set the camera

	//Look at the current cameras position and lookat
	gluLookAt(currentcam->getPosition().x, currentcam->getPosition().y, currentcam->getPosition().z, currentcam->getLookat().x, currentcam->getLookat().y, currentcam->getLookat().z, currentcam->getUp().x, currentcam->getUp().y, currentcam->getUp().z);
	//skybox
	//If not within the scene activate a stencil buffer so the sky box
	//and everything else only stays within the screen in the scene
	if (!start) {
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, NULL);
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_ALWAYS, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glDisable(GL_DEPTH_TEST);

		glTranslatef(-12, -1.2, 0);
		compSten.renderQuads();

		glEnable(GL_DEPTH_TEST);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glStencilFunc(GL_EQUAL, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glPopMatrix();
	}
	//Render Skybox
		glPushMatrix();
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_LIGHTING);
			glBindTexture(GL_TEXTURE_2D, vaporbox.texture);
			glTranslatef(currentcam->getPosition().x, currentcam->getPosition().y + 0.6, currentcam->getPosition().z - 0.5);
			vaporbox.render2();
			glEnable(GL_LIGHTING);
			glEnable(GL_DEPTH_TEST);
		glPopMatrix();
	//Lighting values

	//Spotlight 
	GLfloat Light_Ambient0[] = { 0.0f, 0.0f, 0.0f, 1.0 };	//Don't want to create any ambient lighting with the spotlight
	GLfloat Light_Diffuse0[] = { 1.0f, 0.44f, 0.8f, 1.0 };	//Sweet vaporwave pink
	GLfloat Light_specular[] = { 0.1f, 0.1f, 0.1f, 1 };	//Low specular value
	GLfloat Light_Position0[] = { camera1.getPosition().x, camera1.getPosition().y, camera1.getPosition().z, 1.0 };	//Keep the flashlight with the camera
	GLfloat spot_Direction[] = { camera1.getForward().x, camera1.getForward().y, camera1.getForward().z };			//Make the flashpoint point with the camera
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light_Ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Diffuse0);
	glLightfv(GL_LIGHT0, GL_POSITION, Light_Position0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light_specular);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0f);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_Direction);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 100.0);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.05);

	//Tree lights
	GLfloat Light_Ambient1[] = { 0.05, 0.05, 0.05, 1.0 };
	GLfloat Light_Diffuse1[] = { 0.15f, 0.42f, 0.46f, 1.0 };
	GLfloat Light_Position1[] = { 7.8, 0.75 + 0.5*sin(0.2 * rotation), -10.0, 1.0 };			//To get the light to bob up and down
	//glLightfv(GL_LIGHT1, GL_SPECULAR, Light_specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, Light_Ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Diffuse1);
	glLightfv(GL_LIGHT1, GL_POSITION, Light_Position1);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.3);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

	GLfloat Light_Diffuse2[] = { 0.51, 0.6, 0.2, 1.0 };
	GLfloat Light_Position2[] = { 7.8, 0.75 + 0.5*cos(0.2 * rotation), -20.0, 1.0 };			//To get the light to bob up and down off by 90 degrees
	//glLightfv(GL_LIGHT2, GL_SPECULAR, Light_specular);
	glLightfv(GL_LIGHT2, GL_AMBIENT, Light_Ambient1);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Light_Diffuse2);
	glLightfv(GL_LIGHT2, GL_POSITION, Light_Position2);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.3);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.1);

	GLfloat Light_Position3[] = { -7.8, 0.75 + 0.5*sin((0.2 * rotation) + 45), -10.0, 1.0 };	//To get the light to bob up and down off by 45 degrees
	//glLightfv(GL_LIGHT3, GL_SPECULAR, Light_specular);
	glLightfv(GL_LIGHT3, GL_AMBIENT, Light_Ambient1);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, Light_Diffuse1);
	glLightfv(GL_LIGHT3, GL_POSITION, Light_Position3);
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 1);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.3);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.2);

;
	GLfloat Light_Position4[] = { -7.8, 0.75 + 0.5*cos((0.2 * rotation) + 45), -20.0, 1.0 };	//To get the light to bob up and down off by 135 degrees
	//glLightfv(GL_LIGHT4, GL_SPECULAR, Light_specular);
	glLightfv(GL_LIGHT4, GL_AMBIENT, Light_Ambient1);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, Light_Diffuse2);
	glLightfv(GL_LIGHT4, GL_POSITION, Light_Position4);
	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 1);
	glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 0.3);
	glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0.1);

	//Global/ sunset lighting
	GLfloat Light_Ambient7[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat Light_Diffuse7[] = { red, green, blue, 0.0 };
	GLfloat Light_Position7[] = { 0.0, 20.0 - (blue*3), -32.0, 0.0 };
	glLightfv(GL_LIGHT7, GL_SPECULAR, Light_specular);
	glLightfv(GL_LIGHT7, GL_AMBIENT, Light_Ambient7);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, Light_Diffuse7);
	glLightfv(GL_LIGHT7, GL_POSITION, Light_Position7);

	//Palm tree material. Shininess breaks when lower than 1024 and doesn't really appear above it
	GLfloat mat_Diffuse1[] = { 0.8,0.8,0.8,1 };
	GLfloat mat_Ambient[] = { 0.6, 0.6, 0.6, 1 };
	GLfloat mat_specular1[] = { 0.2, 0.2, 0.2, 1 };
	GLfloat shininess1[] = { shin };

	//Eagle material, I know it says lion it's because before the eagle I was using a lion 
	//Because Helios still wouldn't work
	GLfloat mat_DiffuseLion[] = { 0.9,0.9,0.9,1 };
	GLfloat mat_specularLion[] = { 0.1, 0.1, 0.1, 1 };
	GLfloat shininessLion[] = { 5500 };

	//Wanted to make the floating orb shine 
	GLfloat mat_DiffuseOrb[] = { 0.9,0.9,0.9,1 };
	GLfloat mat_specularOrb[] = { 0.2, 0.2, 0.2, 1 };
	GLfloat shininessOrb[] = { 300 };

	GLfloat mat_AmbientW[] = { 0.6, 0.6, 0.6, 1 };

	//Generic value for the rest of the world
	GLfloat mat_DiffuseWorld[] = { 1.0,1.0,1.0,1 };
	GLfloat mat_specularWorld[] = { 0.1,0.1, 0.1, 1 };
	GLfloat shininessWorld[] = { 0 };

	// Render geometry/scene here -------------------------------------

	// Shadow stuff ------------------------------------------------
	GLfloat floorVerts[] = { -12.f, 0.f, -30.f,		//top left
							-12.f, 0.f, 0.f,		// bottom left
							12.f, 0.f, 0.f,		//bottom right
							12.f, 0.f, -30.f };	// top right
	shadow.generateShadowMatrix(shadowMatrix, Light_Position7, floorVerts);


	//The ground --------------------------------------------------------------------------------------------

	//Render 2 planes with a gap between them for the river
	for (int i = -1; i < 2; i += 2)
	{
		glPushMatrix();
			glScalef(i * 1, 1, 1);
			glTranslatef(1, 0, -30.0f);
			glBindTexture(GL_TEXTURE_2D, floor.texture);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specularWorld);
			glMaterialfv(GL_FRONT, GL_SHININESS, shininessWorld);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_DiffuseWorld);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_Ambient);
			floor.renderQuads();
		//different texture filters to switch between
		switch (textControl)
		{
		case 0:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;
		case 1:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		case 2:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			break;
		case 4:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			break;
		}
		glPopMatrix();
	}
	//river plane to go underneath the world slightly
	glPushMatrix();
		glEnable(GL_COLOR_MATERIAL);
		glTranslatef(-4, -0.2, -30.0f);
		glBindTexture(GL_TEXTURE_2D, NULL);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specularWorld);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininessWorld);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_DiffuseWorld);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_Ambient);
		glColor3f(0.92, 0.8, 0.41);
		river.renderQuads();
		glColor3f(1.0, 1.0, 1.0);
		glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//a loop to generate the bank of the river
	for (int j = -1; j < 2; j += 2)
	{
		glPushMatrix();
			glScalef(0.5 * j, 1, 1);
			glTranslatef(-2, 0, -30);
			glBindTexture(GL_TEXTURE_2D, floor.texture);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specularWorld);
			glMaterialfv(GL_FRONT, GL_SHININESS, shininessWorld);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_DiffuseWorld);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_AmbientW);
		for (int i = 0; i < 30; i++)
		{
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glNormal3f(1.0f, 1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, i + 1);

			glTexCoord2f(0.0f, 1.0f);
			glNormal3f(1.0f, 1.0f, 0.0f);
			glVertex3f(1.0f, -0.2f, i + 1);

			glTexCoord2f(1.0f, 1.0f);
			glNormal3f(1.0f, 1.0f, 0.0f);
			glVertex3f(1.0f, -0.2f, i);

			glTexCoord2f(1.0f, 0.0f);
			glNormal3f(1.0f, 1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, i);
			glEnd();
		}
		glPopMatrix();
	}


	//Palm tress --------------------------------------------------
	//Don't want shadows being rendered when it's in the alternative light mode
	if (sun)
	{
		//A stencil buffer for the shadows so it doesn't render off the floor
		glBindTexture(GL_TEXTURE_2D, NULL);
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_ALWAYS, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glDisable(GL_DEPTH_TEST);

		glPushMatrix();
			glTranslatef(-12, 0, -30);
			shadowSten.renderQuads();
		glPopMatrix();

		glEnable(GL_DEPTH_TEST);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glStencilFunc(GL_EQUAL, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		//Rendering the shadows

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glColor3f(0.1f, 0.23f, 0.21f); // Shadow's colour
		glPushMatrix();
			glMultMatrixf((GLfloat *)shadowMatrix);
			glTranslatef(3, 0, -26.9);
			glScalef(2, 2, 2);
			helios.render();
		glPopMatrix();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		for (int j = -1; j < 2; j += 2)
		{
			glPushMatrix();
			for (int i = 4; i > -1; i--)
			{
				glDisable(GL_DEPTH_TEST);
				glDisable(GL_LIGHTING);
				glDisable(GL_TEXTURE_2D);
				glPushMatrix();
					glMultMatrixf((GLfloat *)shadowMatrix);
					//translate to floor and draw shadow
					glTranslatef(8 * j, 0.2f, (-i * 5) - 5);
					glScalef(0.1f, 0.1f, 0.1f);
					palm.render();
				glPopMatrix();
				
				glEnable(GL_DEPTH_TEST);
				glEnable(GL_LIGHTING);
				glEnable(GL_TEXTURE_2D);
			}
			glPopMatrix();
		}
		glDisable(GL_STENCIL_TEST);
	}
	glColor3f(1.0f, 1.0f, 1.0f); // S
	//rendering the trees
	for (int j = -1; j < 2; j += 2)
	{
		glPushMatrix();

		glTranslatef(8 * j, 0, 0);
		for (int i = 4; i > -1; i--)
		{
			glPushMatrix();
				glPolygonMode(GL_FRONT, GL_LINE);		//Make the trees Poly always
				glPolygonMode(GL_BACK, GL_LINE);
				glBindTexture(GL_TEXTURE_2D, NULL);
				glEnable(GL_COLOR_MATERIAL);
				glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
				glMaterialfv(GL_FRONT, GL_SHININESS, shininess1);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_Diffuse1);
				glMaterialfv(GL_FRONT, GL_AMBIENT, mat_Ambient);	
				glTranslatef(0.0f, 0.0f, (-i * 5) - 5);
				glScalef(0.1f, 0.1f, 0.1f);
				palm.render();
			glDisable(GL_COLOR_MATERIAL);
			//To stop it disabling wire frame when we want wire frame active
			if (!poly)
			{
				glPolygonMode(GL_FRONT, GL_FILL);
				glPolygonMode(GL_BACK, GL_FILL);
			}
			glPopMatrix();

		}
		glPopMatrix();
	}
	
	//Mirror stencil buffer -------------------------------------------------------
	glBindTexture(GL_TEXTURE_2D, NULL);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glDisable(GL_DEPTH_TEST);
	glPushMatrix();
		glBegin(GL_QUADS);
		glVertex3f(1, 4, -29.98);
		glVertex3f(1, 0, -29.98);
		glVertex3f(5, 0, -29.98);
		glVertex3f(5, 4, -29.98);
		glEnd();
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	// Draw the reflected Eagle
	glPushMatrix();
		glTranslatef(3, 0, -32.9);
		glScalef(2, 2, -2);
		glBindTexture(GL_TEXTURE_2D, heliosR.texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specularLion);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininessLion);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_DiffuseLion);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_Ambient);
		heliosR.render();
		//Push to have an orb Rotate around the reflection only for atmosphere effects
		glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, helios.texture);
			glTranslatef(0, 0.5, 0);
			glRotatef(rotation, 0, 1, 1);
			glTranslatef(-0.6, -0.2, 0);
			glScalef(0.08, 0.08, 0.08);
			sphere1.renderQuads();
			//Render 2 Diamonds with opposite rotation so they are
			//Stationary around the poles
			glPushMatrix();
				glRotatef(-rotation, 0, 1, 1);
				glTranslatef(0, 1.5, 0);
				glScalef(0.2, 0.2, 0.2);
				sphere2.renderQuads();
			glPopMatrix();
			glPushMatrix();
				glRotatef(-rotation, 0, 1, 1);
				glTranslatef(0, -1.5, 0);
				glScalef(0.2, 0.2, 0.2);
				sphere2.renderQuads();
			glPopMatrix();
		glPopMatrix();
		//Push to have a diamond rotate while sitting above the Eagle
		glPushMatrix();
			glScalef(0.05, 0.05, 0.05);
			glTranslatef(0, 20, 0);
			glRotatef(rotation / 3, 0, 1, 0);
			sphere2.renderQuads();
		glPopMatrix();
	glPopMatrix();
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	//Draw the actual mirror
	glPushMatrix();
		glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
		glBegin(GL_QUADS);
		glVertex3f(1, 4, -29.98);
		glVertex3f(1, 0, -29.98);
		glVertex3f(5, 0, -29.98);
		glVertex3f(5, 4, -29.98);
		glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	//Draw the Real Eagle
	glPushMatrix();
		glTranslatef(3, 0, - 26.9);
		glScalef(2, 2, 2);
		glBindTexture(GL_TEXTURE_2D, helios.texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specularLion);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininessLion);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_DiffuseLion);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_Ambient);
		helios.render();
	glPopMatrix();
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, NULL);
		glTranslatef(0.8, -0.2, -29.99);
		glScalef(0.044, 0.044, 1.0);
		mirrorBorder.renderQuads();
	glPopMatrix();

	
	//Windows boxes ------------------------------------------------------------------

	//We only want the front faces showing
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPushMatrix();
		glScalef(0.25, 0.25, 0.25);
		glPushMatrix();
			glTranslatef(4, 2.0f, -60.0f);
			glBindTexture(GL_TEXTURE_2D, window2.texture);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specularWorld);
			glMaterialfv(GL_FRONT, GL_SHININESS, shininessWorld);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_DiffuseWorld);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_AmbientW);
			window2.renderQuads();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-16, 0.0f, -20.0f);
			glBindTexture(GL_TEXTURE_2D, window.texture);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specularWorld);
			glMaterialfv(GL_FRONT, GL_SHININESS, shininessWorld);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_DiffuseWorld);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_AmbientW);
			window.renderQuads();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-28 , -0.5f, -72.0f);
			glBindTexture(GL_TEXTURE_2D, window3.texture);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specularWorld);
			glMaterialfv(GL_FRONT, GL_SHININESS, shininessWorld);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_DiffuseWorld);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_AmbientW);
			window3.renderQuads();
		glPopMatrix();
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_Ambient);

	//The screen ------------------------------------------
	glPushMatrix();
		glTranslatef(12, -1.2, 0);
		glRotatef(180, 0.f, 1.f, 0.f);
		glBindTexture(GL_TEXTURE_2D, back.texture);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specularWorld);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininessWorld);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_DiffuseWorld);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_AmbientW);
		back.renderQuads();
		glBindTexture(GL_TEXTURE_2D, NULL);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specularWorld);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininessWorld);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_DiffuseWorld);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_AmbientW);
		glDisable(GL_CULL_FACE);
		glEnable(GL_COLOR_MATERIAL);
		//using matrices to help build the border around the screen easier
		glPushMatrix();
			glColor3f(0.8, 0.8, 0.8);
			glTranslatef(12, 18.8, 0);
			borderTop.renderQuads();
		glPopMatrix();
		glPushMatrix();
			glColor3f(0.8, 0.8, 0.8);
			glTranslatef(12, 0.21, 0);
			borderTop.renderQuads();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(24, 9.8, 0);
			borderSide.renderQuads();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 9.8, 0);
			borderSide.renderQuads();
			glColor3f(1.0, 1.0, 1.0);
		glPopMatrix();
		glDisable(GL_COLOR_MATERIAL);
		glColor4f(1.0, 1.0, 1.0, 1.0);
	glPopMatrix();

	//The border around the world --------------------------------------------------------------------------
	glPushMatrix();
		glEnable(GL_BLEND);
		glPushMatrix();
			glTranslatef(-11, -1.2, -30);
			glBindTexture(GL_TEXTURE_2D, frontWall.texture);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specularWorld);
			glMaterialfv(GL_FRONT, GL_SHININESS, shininessWorld);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_DiffuseWorld);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_AmbientW);
			frontWall.renderQuads();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-11, -0.2, -30);
			glBindTexture(GL_TEXTURE_2D, leftWall.texture);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specularWorld);
			glMaterialfv(GL_FRONT, GL_SHININESS, shininessWorld);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_DiffuseWorld);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_AmbientW);
			leftWall.renderQuads();
		glPopMatrix();
		glPushMatrix();
			glRotatef(180, 0, 1, 0);
			glTranslatef(-11, -0.2, 1);
			glBindTexture(GL_TEXTURE_2D, rightWall.texture);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specularWorld);
			glMaterialfv(GL_FRONT, GL_SHININESS, shininessWorld);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_DiffuseWorld);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_AmbientW);
			rightWall.renderQuads();
		glPopMatrix();
		glDisable(GL_BLEND);
	glPopMatrix();

	//vhs overlay needs to be rendered last for transparency 
	glPushMatrix();
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D, vhs);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specularWorld);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininessWorld);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_DiffuseWorld);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_AmbientW);
		glTranslatef(-12, -1.2, 0);
		back.renderQuads();

		glDisable(GL_BLEND);
		glDisable(GL_CULL_FACE);
	glPopMatrix();
	// End render geometry --------------------------------------
	//for the stencil at the start so nothing can be seen on the outer edges of the scene
	if (!start)
	{
		glDisable(GL_STENCIL_TEST);
		glEnable(GL_DEPTH_TEST);
	}
	// Render text, should be last object rendered. -------------------------------------------------
	
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	renderTextOutput();
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the tPotview
	glMatrixMode(GL_MODELVIEW);

	
}

// Calculates FPS
void Scene::calculateFPS()
{

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	if (!start)
	{
		displayText(-0.45f, -0.3f, 0.92, 0.8, 0.41, "Look at the computer and press W to move forward WASD to move");
	}
	else if (renderText)
	{
		displayText(-0.17f, -0.3f, 0.92, 0.8, 0.41, "Press F to toggle flashlight");
		displayText(-0.17f, -0.4f, 0.92, 0.8, 0.41, "Press M to toggle Menu");
	}
	if (menu)
	{
		displayText(-1.f, 0.9f, 0.92, 0.8, 0.41, "Press M to toggle Menu");
		displayText(-1.f, 0.8f, 0.92, 0.8, 0.41, "Press C to switch between Cameras");
		displayText(-1.f, 0.7f, 0.92, 0.8, 0.41, "Press R to toggle wire Frame");
		displayText(-1.f, 0.6f, 0.92, 0.8, 0.41, "Press F to toggle flashlight");
		displayText(-1.f, 0.5f, 0.92, 0.8, 0.41, "Press O and P to change the colour of the sunset");
		displayText(-1.f, 0.4f, 0.92, 0.8, 0.41, "Press L to swap lighting effect");
		displayText(-1.f, 0.3f, 0.92, 0.8, 0.41, "Press I to change filtering mode / to compare filtering techniques");
	}
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}

