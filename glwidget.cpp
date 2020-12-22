#include <QtOpenGL>

#include <math.h>

#include "qtlogo.h"
#include "glwidget.h"
#include "window.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
/*The constructor provides default rotation angles for the scene, sets the pointer to the QtLogo object to null, and sets up some colors for later use.*/
     logo = 0;

     xRot = 0;
     yRot = 0;
     zRot = 0;

     qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
     qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
}

// We also implement a destructor to release OpenGL-related resources when the widget is deleted.
GLWidget::~GLWidget()
{
}

// We provide size hint functions to ensure that the widget is shown at a reasonable size.
QSize GLWidget::minimumSizeHint() const
{
     return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
     return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
     while (angle < 0)
         angle += 360 * 16;
     while (angle > 360 * 16)
         angle -= 360 * 16;
}

// The widget provides three slots that enable other components in the example to change the orientation of the scene.
void GLWidget::setXRotation(int angle)
{
     qNormalizeAngle(angle);

     // In the above slot, the xRot variable is updated only if the new angle is different to the old one.
     if (angle != xRot) {
         xRot = angle;
	  
         // xRotationChanged() signal is emitted to allow other components to be updated.
         emit xRotationChanged(angle);
	
	 // Then the widget's updateGL() handler function is called
         updateGL();
     }
}

void GLWidget::setYRotation(int angle)
{
     qNormalizeAngle(angle);
     if (angle != yRot) {
         yRot = angle;
         emit yRotationChanged(angle);
         updateGL();
     }
}

void GLWidget::setZRotation(int angle)
{
     qNormalizeAngle(angle);
     if (angle != zRot) {
         zRot = angle;
         emit zRotationChanged(angle);
         updateGL();
     }
}

// The initializeGL() function is used to perform useful initialization tasks that are needed to render the 3D scene.
void GLWidget::initializeGL()
{
     // Clear the color with xxx.
     qglClearColor(qtPurple.dark());

     logo = new QtLogo(this, 64);
     logo->setColor(qtGreen.dark());

     glEnable(GL_DEPTH_TEST);
     glEnable(GL_CULL_FACE);
     glShadeModel(GL_SMOOTH);
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_MULTISAMPLE);
     
     static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
     glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

// The paintGL() function is used to paint the contents of the scene onto the widget.
// In this example, we clear the widget using the background color that we defined in the initializeGL() function
// set up the frame of reference for the geometry we want to display, 
// and call the draw method of the QtLogo object to render the scene.
void GLWidget::paintGL()
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glLoadIdentity();
     glTranslatef(0.0, 0.0, -10.0);
     glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
     glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
     glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
     logo->draw();
}

// The resizeGL() function is used to ensure that the OpenGL implementation renders the scene onto a viewport that matches the size of the widget, 
// using the correct transformation from 3D coordinates to 2D viewport coordinates.
void GLWidget::resizeGL(int width, int height)
{
     int side = qMin(width, height);
     glViewport((width - side) / 2, (height - side) / 2, side, side);

     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();

 #ifdef QT_OPENGL_ES_1
     glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
 #else
     glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
 #endif
     glMatrixMode(GL_MODELVIEW);
}

// The mousePressEvent() function simply records the position of the mouse when a button is initially pressed.
void GLWidget::mousePressEvent(QMouseEvent *event)
{
     lastPos = event->pos();
}

// The mouseMoveEvent() function uses the previous location of the mouse cursor to determine how much the object in the scene should be rotated, 
// and in which direction.
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
     int dx = event->x() - lastPos.x();
     int dy = event->y() - lastPos.y();

     if (event->buttons() & Qt::LeftButton) {
         setXRotation(xRot + 8 * dy);
         setYRotation(yRot + 8 * dx);
     } else if (event->buttons() & Qt::RightButton) {
         setXRotation(xRot + 8 * dy);
         setZRotation(zRot + 8 * dx);
     }
     lastPos = event->pos();
}



