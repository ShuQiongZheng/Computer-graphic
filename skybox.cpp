#include "skybox.h"
#include <GL/glu.h>
#include <cstring>
#include <iostream>

// Initializing is just loading our image.
void SkyBox::Init(const char* path)
{

	// Copy the path into temp
	strcpy(frontPath, path);
	strcpy(backPath, path);
	strcpy(topPath, path);
	strcpy(bottomPath, path);
	strcpy(leftPath, path);
	strcpy(rightPath, path);

	//connect the path
	strcat(frontPath, "/front.bmp");
	strcat(backPath, "/back.bmp");
	strcat(topPath, "/top.bmp");
	strcat(bottomPath, "/bottom.bmp");
	strcat(leftPath, "/left.bmp");
	strcat(rightPath, "/right.bmp");

}
	
// Give the position of the camera
void SkyBox::Draw(float x, float y, float z)
{
	// Turn off the lights when you paint the skybox!
	glDisable(GL_LIGHTING);

	// There is no need to open the GL_Depth_TEST
	glDisable(GL_DEPTH_TEST);

	glPushMatrix();

	// Let the sky box follow the camera's coordinates,then we cannot escape the skybox
	glTranslatef(x, y, z);

	// What texture does the sky Box use:
	//glBindTexture(GL_TEXTURE_2D, front->mTextureID);
	
	front->Init(frontPath,1);
	// Define the current color as white
	glColor4ub(255, 255, 255, 255);
	glBegin(GL_QUADS);

	// Now map the texture coordinates£¡
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);  //left corner

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);  //right corner

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);   //right top

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);  //left top

	glEnd();

	//left
	//glBindTexture(GL_TEXTURE_2D, left->mTextureID);
	left->Init(leftPath,1);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	glEnd();

	//right
	//glBindTexture(GL_TEXTURE_2D, right->mTextureID);
	right->Init(rightPath,1);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);

	glEnd();

	//top
	//glBindTexture(GL_TEXTURE_2D, top->mTextureID);
	top->Init(topPath,1);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	glEnd();

	//bottom
	//glBindTexture(GL_TEXTURE_2D, bottom->mTextureID);
	bottom->Init(bottomPath,1);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	glEnd();

	//back
	//glBindTexture(GL_TEXTURE_2D, back->mTextureID);
	back->Init(backPath,1);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);

	glEnd();

	glPopMatrix();

}
