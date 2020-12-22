#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "qtlogo.h"
#include "window.h"

class QtLogo;

class GLWidget : public QGLWidget
{
	Q_OBJECT

public:
	GLWidget(QWidget *parent = 0);
	~GLWidget();

	QSize minimumSizeHint() const;
	QSize sizeHint() const;

// The signals and slots are used to allow other objects to interact with the 3D scene.
public slots:
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);

	signals:
	void xRotationChanged(int angle);
	void yRotationChanged(int angle);
	void zRotationChanged(int angle);

// OpenGL initialization --> QGLWidget::initializeGL()
// viewport resizing --> QGLWidget::resizeGL()
// painting --> QGLWidget::paintGL()
protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	
	// To enable the user to interact directly with the scene using the mouse
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

// The rest of the class contains utility functions and variables that are used to construct and hold orientation information for the scene.
// The logo variable will be used to hold a pointer to the QtLogo object which contains all the geometry.
private:
	QtLogo *logo;
	int xRot;
	int yRot;
	int zRot;
	QPoint lastPos;
	QColor qtGreen;
	QColor qtPurple;
};

#endif











