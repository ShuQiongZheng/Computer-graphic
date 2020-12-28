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

//在未进入循环的时候，开始记录时间
static float sTimeSinceStartUp;

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

     m_timer = new QTimer();

     connect(m_timer,SIGNAL(timeout()),this, SLOT(update()));


}

glWidget::~glWidget()
{

}

unsigned int timeGetTime()
{
	unsigned int uptime = 0;
	struct timespec on;
	if(clock_gettime(CLOCK_MONOTONIC, &on) == 0)
	uptime = on.tv_sec*1000 + on.tv_nsec/1000000;
	return uptime;
}

void glWidget::initializeGL()
{
	// set the widget background colour
	glClearColor(0.0, 0.0, 0.0, 0.0);

	sTimeSinceStartUp = timeGetTime() / 1000.0f;

	string texturePath= "extra/earthmap2k.jpg";
	string sunTexturePath = "extra/sun.bmp";
	m_earth = new planet ( point(0.0,0.0,15.0),  point(0.0,1.0,0.0), 3.0, 30.0, 30.0, true, texturePath.c_str());
	m_sun = new planet ( point(0.0,0.0,0.0),  point(1.0,0.0,0.0), 5.0, 30.0, 0.0, true, sunTexturePath.c_str());
	m_sun->add_secondary(m_earth);


}

void glWidget::setMoveLeft(int value)
{

	camera.mbMoveLeft = true;
	camera.translateX = value;

}

void glWidget::setMoveRight(int value)
{
	camera.mbMoveRight = true;
	camera.translateY = value;
}

void glWidget::paintGL()
{
	m_timer->start();

	//qDebug()<<"paintGL";
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float currentTime = timeGetTime() / 1000.0f;
	float timeElapse = currentTime - sTimeSinceStartUp; //经历了多少时间
	sTimeSinceStartUp = currentTime;

	camera.Update(timeElapse); // 0.01q6f


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 4000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera.mPos.x,camera.mPos.y,camera.mPos.z, camera.mViewCenter.x,camera.mViewCenter.y,camera.mViewCenter.z, camera.mUp.x,camera.mUp.y,camera.mUp.z);

	m_sun->draw();
	m_sun->update(timeElapse);

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

void glWidget::wheelEvent(QWheelEvent *event)
{
    //qDebug()<<"dealt"<<event->delta();
    if (event->delta()>0)
    {
      camera.distance ++;

    }
    if (event->delta()<0)
    {

        camera.distance--;
    }

}




















