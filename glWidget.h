// glwidget.h

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "camera.h"

class glWidget : public QGLWidget
{
    Q_OBJECT
public:
	explicit glWidget(QWidget *parent = 0);
	~glWidget();

public slots:
	// called by the timer in the main window
	void updateAngle();
	void setMoveLeft();
	void setMoveRight();


protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);

private:
	void draw(); 
	double _angle;
	
	Camera camera;

};

#endif // GLWIDGET_H
