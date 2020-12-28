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
	glClearColor(0.3, 0.3, 0.3, 0.0);

	sTimeSinceStartUp = timeGetTime() / 1000.0f;

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
	// printf("Here setMoveRight!");
}

void glWidget::paintGL()
{
	m_timer->start();

	//draw scene
	qDebug()<<"paintGL";
	glLoadIdentity();

	// clear the widget
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float currentTime = timeGetTime() / 1000.0f;
	float timeElapse = currentTime - sTimeSinceStartUp; //经历了多少时间
	sTimeSinceStartUp = currentTime;

	//需要在loadIdentity之后，紧接着就初始化camera
	//set up camera 每一帧都设置一个camera --> 更新摄像机
	printf("camera.Update: %d",camera.mbMoveLeft);
	camera.Update(timeElapse); // 0.01q6f


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 4000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera.mPos.x,camera.mPos.y,camera.mPos.z, camera.mViewCenter.x,camera.mViewCenter.y,camera.mViewCenter.z, camera.mUp.x,camera.mUp.y,camera.mUp.z);

	this->CenterTower();




   // gluLookAt(camera.mPos.x,camera.mPos.y,camera.mPos.z, camera.mViewCenter.x,camera.mViewCenter.y,camera.mViewCenter.z, camera.mUp.x,camera.mUp.y,camera.mUp.z);
    //glScalef(0.1f,0.1f,0.1f);
    //glTranslatef(0,21.,0.);

	static float angle = 0.0f;
//	angle += 1.0f;
//	if (angle >= 360.0f)
//	{
//		angle = 0.0f;
//	}
//	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	this->diamond();




    //glPopMatrix();


	// flush to screen
	glFlush();
    //swapBuffers();

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

void glWidget::drawAnimal(){
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
	

/*   Center Tower   */
void glWidget::CenterTower(){
/*Matrial of the tower*/
	materialStruct* p_front = &whiteShinyMaterials;
		
	glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
	glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

/*The base**/
	// right face
	glNormal3fv(normals[0]);
	glBegin(GL_POLYGON);
	glVertex3f( 1.0, -1.0,  1.0);
	glVertex3f( 1.0, -1.0, -1.0);
	glVertex3f( 1.0,  3.0, -1.0);
	glVertex3f( 1.0,  3.0,  1.0);
	glEnd();

	// back face
	glNormal3fv(normals[3]); 
	glBegin(GL_POLYGON);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f( 1.0, -1.0, -1.0);
	glVertex3f( 1.0,  3.0, -1.0);
	glVertex3f(-1.0,  3.0, -1.0);
	glEnd();

	// front face
	glNormal3fv(normals[2]); 
	glBegin(GL_POLYGON);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f( 1.0, -1.0, 1.0);
	glVertex3f( 1.0,  3.0, 1.0);
	glVertex3f(-1.0,  3.0, 1.0);
	glEnd();

	// left face
	glNormal3fv(normals[1]);
	glBegin(GL_POLYGON);
	glVertex3f( -1.0, -1.0,  1.0);
	glVertex3f( -1.0, -1.0, -1.0);
	glVertex3f( -1.0,  3.0, -1.0);
	glVertex3f( -1.0,  3.0,  1.0);
	glEnd();

	// top face
	glNormal3fv(normals[4]);
	glBegin(GL_POLYGON);
	glVertex3f(  1.0,  1.0,  1.0);
	glVertex3f(  1.0,  1.0, -1.0);
	glVertex3f( -1.0,  1.0, -1.0);
	glVertex3f( -1.0,  1.0,  1.0);
	glEnd();

	// bottom face
	glNormal3fv(normals[5]);
	glBegin(GL_POLYGON);
	glVertex3f(  1.0,  -1.0,  1.0);
	glVertex3f(  1.0,  -1.0, -1.0);
	glVertex3f( -1.0,  -1.0, -1.0);
	glVertex3f( -1.0,  -1.0,  1.0);
	glEnd();



/*The top**/
	top(3.0,0.2,0.2);
	top(3.4,0.2,0.2);
	top(3.8,0.2,0.2);

}

void glWidget::top(double base,double x,double y){

/*Matrial of the top*/
	materialStruct* p_front = &whiteShinyMaterials;
		
	glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
	glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);


	double height = base + x;
	double thick = base + x + y;
	// right face
	glNormal3fv(normals[0]);
	glBegin(GL_POLYGON);
	glVertex3f( 1.0, height,  1.0); 
	glVertex3f( 1.0, height, -1.0);
	glVertex3f( 1.0, thick, -1.0);
	glVertex3f( 1.0, thick,  1.0);
	glEnd();

	// back face
	glNormal3fv(normals[3]); 
	glBegin(GL_POLYGON);
	glVertex3f(-1.0, height, -1.0);
	glVertex3f( 1.0, height, -1.0);
	glVertex3f( 1.0, thick, -1.0);
	glVertex3f(-1.0, thick, -1.0);
	glEnd();

	// front face
	glNormal3fv(normals[1]); 
	glBegin(GL_POLYGON);
	glVertex3f(-1.0, height, 1.0);
	glVertex3f( 1.0, height, 1.0);
	glVertex3f( 1.0, thick, 1.0);
	glVertex3f(-1.0, thick, 1.0);
	glEnd();

	// left face
	glNormal3fv(normals[1]);
	glBegin(GL_POLYGON);
	glVertex3f( -1.0, height,  1.0);
	glVertex3f( -1.0, height, -1.0);
	glVertex3f( -1.0, thick, -1.0);
	glVertex3f( -1.0, thick,  1.0);
	glEnd();

	// top face
	glNormal3fv(normals[4]);
	glBegin(GL_POLYGON);
	glVertex3f(  1.0,  thick,  1.0);
	glVertex3f(  1.0,  thick, -1.0);
	glVertex3f( -1.0,  thick, -1.0);
	glVertex3f( -1.0,  thick,  1.0);
	glEnd();

	// bottom face
	glNormal3fv(normals[5]);
	glBegin(GL_POLYGON);
	glVertex3f(  1.0,  height,  1.0);
	glVertex3f(  1.0,  height, -1.0);
	glVertex3f( -1.0,  height, -1.0);
	glVertex3f( -1.0,  height,  1.0);
	glEnd();
}

void glWidget::diamond(){

/*Define the sun light*/
	GLfloat sun_light_position[] = {0.0f, 4.0f, 0.0f, 1.0f};
	GLfloat sun_light_ambient[]  = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_light_diffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position); // Specifies the location of the no. 0 light source
	glLightfv(GL_LIGHT0, GL_AMBIENT,  sun_light_ambient);  // refers to the intensity (color) of light rays that hit the material and are left behind in the environment after many reflections
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  sun_light_diffuse);  // Diffuse reflection
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular); // Specular reflection

/*Define the sun material*/
	GLfloat sun_mat_ambient[]  = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_mat_diffuse[]  = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_mat_emission[] = {0.5f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_mat_shininess  = 0.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT,   sun_mat_ambient); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   sun_mat_diffuse); 
	glMaterialfv(GL_FRONT, GL_SPECULAR,  sun_mat_specular); 
	glMaterialfv(GL_FRONT, GL_EMISSION,  sun_mat_emission); 
	glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess); 
 
	float Triangle[6][3] = {{0.0f,4.0f,0.0f},{0.0f,-4.0f,0.0f},{-2.0f,0.0f,0.0f},
	{2.0f,0.0f,0.0f},{0.0f,0.0f,2.0f},{0.0f,0.0f,-2.0f}};

	glBegin(GL_TRIANGLES);
	glVertex3f(Triangle[1][0],Triangle[1][1],Triangle[1][2]);
	glVertex3f(Triangle[2][0],Triangle[2][1],Triangle[2][2]);
	glVertex3f(Triangle[5][0],Triangle[5][1],Triangle[5][2]);
	glEnd(); //End

	glBegin(GL_TRIANGLES);
	glVertex3f(Triangle[1][0],Triangle[1][1],Triangle[1][2]);
	glVertex3f(Triangle[2][0],Triangle[2][1],Triangle[2][2]);
	glVertex3f(Triangle[4][0],Triangle[4][1],Triangle[4][2]);
	glEnd(); //End

	glBegin(GL_TRIANGLES);
	glVertex3f(Triangle[1][0],Triangle[1][1],Triangle[1][2]);
	glVertex3f(Triangle[3][0],Triangle[3][1],Triangle[3][2]);
	glVertex3f(Triangle[4][0],Triangle[4][1],Triangle[4][2]);
	glEnd(); //End

	glBegin(GL_TRIANGLES);
	glVertex3f(Triangle[1][0],Triangle[1][1],Triangle[1][2]);
	glVertex3f(Triangle[3][0],Triangle[3][1],Triangle[3][2]);
	glVertex3f(Triangle[5][0],Triangle[5][1],Triangle[5][2]);
	glEnd(); //End

	glBegin(GL_TRIANGLES);
	glVertex3f(Triangle[0][0],Triangle[0][1],Triangle[0][2]);
	glVertex3f(Triangle[2][0],Triangle[2][1],Triangle[2][2]);
	glVertex3f(Triangle[5][0],Triangle[5][1],Triangle[5][2]);
	glEnd(); //End

	glBegin(GL_TRIANGLES);
	glVertex3f(Triangle[0][0],Triangle[0][1],Triangle[0][2]);
	glVertex3f(Triangle[2][0],Triangle[2][1],Triangle[2][2]);
	glVertex3f(Triangle[4][0],Triangle[4][1],Triangle[4][2]);
	glEnd(); //End

	glBegin(GL_TRIANGLES);
	glVertex3f(Triangle[0][0],Triangle[0][1],Triangle[0][2]);
	glVertex3f(Triangle[3][0],Triangle[3][1],Triangle[3][2]);
	glVertex3f(Triangle[4][0],Triangle[4][1],Triangle[4][2]);
	glEnd(); //End

	glBegin(GL_TRIANGLES);
	glVertex3f(Triangle[0][0],Triangle[0][1],Triangle[0][2]);
	glVertex3f(Triangle[3][0],Triangle[3][1],Triangle[3][2]);
	glVertex3f(Triangle[5][0],Triangle[5][1],Triangle[5][2]);
	glEnd(); //End

        glEnable(GL_LIGHTING);
}









































