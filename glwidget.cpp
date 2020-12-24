#include <GL/glu.h>
#include <QtWidgets>
#include <QGLWidget>
#include "glWidget.h"
#include "Window.h"
#include "objmodel.h"
#include "texture.h"
#include "utils.h"
#include "vertexData.h"
#include "math.h"
#include "camera.h"
#include <time.h> 

const static GLfloat normals[][3] = { {1., 0. ,0.}, {-1., 0., 0.}, {0., 0., 1.}, {0., 0., -1.}, {0, 1, 0}, {0, -1, 0} };

// Setting up material properties
typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;

static materialStruct whiteShinyMaterials = {
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  100.0 
};

static materialStruct brassMaterials = {
  { 0.33, 0.22, 0.03, 1.0},
  { 0.78, 0.57, 0.11, 1.0},
  { 0.99, 0.91, 0.81, 1.0},
  27.8 
};

glWidget::glWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent),  _angle(0.0)
{

}

glWidget::~glWidget()
{

}

void glWidget::initializeGL()
{
	// set the widget background colour
	glClearColor(0.3, 0.3, 0.3, 0.0);
}

void glWidget::setMoveLeft()
{
	camera.mbMoveLeft = true;
	// printf("Here setMoveLeft!");
}

void glWidget::setMoveRight()
{
	camera.mbMoveRight = true;
	// printf("Here setMoveRight!");
}

void glWidget::paintGL()
{

	//draw scene
	glLoadIdentity();

	// clear the widget
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//需要在loadIdentity之后，紧接着就初始化camera
	//set up camera 每一帧都设置一个camera --> 更新摄像机
	printf("camera.Update: %d",camera.mbMoveLeft);
	camera.Update(); // 0.016f

	//set model view matrix
	gluLookAt(camera.mPos.x, camera.mPos.y, camera.mPos.z,
		camera.mViewCenter.x, camera.mViewCenter.y, camera.mViewCenter.z,
		camera.mUp.x, camera.mUp.y, camera.mUp.z);

	// Position light
	glPushMatrix();

	// You must set the matrix mode to model view directly before enabling the depth test
	glMatrixMode(GL_MODELVIEW); 

	// Draw the Center tower
	// glScalef(0.1f,0.1f,0.1f);
	// glTranslatef(0,-1.,0.);

	this->draw();
	glPopMatrix();

	// flush to screen
	glFlush();

}



// called every time the widget is resized
void glWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);

	glEnable(GL_LIGHTING); // enable lighting in general
	glEnable(GL_LIGHT0);   // each light source must also be enabled

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	// glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4.0, 4.0, -4.0, 4.0, -4.0, 4.0);

}

void glWidget::draw(){
	// 类的构建
	Texture texture;
	//texture.InitBMP("extra/earth.bmp");//初始化成为一个opengl的文件
        texture.Init("extra/Mercator-projection.ppm",2);//初始化成为一个opengl的文件

	ObjModel model;
	model.Init("extra/Sphere.obj"); // 解码出来

   	//init light
	float blackColor[] = { 0.0f,0.0f,0.0f,1.0f };
	float whiteColor[] = { 1.0f,1.0f,1.0f,1.0f };
	float lightPos[] = { 0.0f,1.0f,0.0f,0.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, whiteColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);//direction light,point,spot

	float blackMat[] = { 0.0f,0.0f,0.0f,1.0f };
	float ambientMat[] = { 0.1f,0.1f,0.1f,1.0f };
	float diffuseMat[] = { 0.4f,0.4f,0.4f,1.0f };
	float specularMat[] = { 0.9f,0.9f,0.9f,1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, blackMat);

	glMaterialf(GL_FRONT, GL_SHININESS,128.0f); // 镜面光

        //draw scene
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.mTextureID);
	model.Draw(); // 实现画模型
}


void glWidget::updateAngle(){
  _angle += 1.0;
  this->repaint();
}
	








































