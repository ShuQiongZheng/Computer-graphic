// glwidget.h

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "camera.h"
#include "planet.h"
#include "skybox.h"


class glWidget : public QGLWidget
{
	Q_OBJECT
public:
	explicit glWidget(QWidget *parent = 0);
	~glWidget();

public slots:
	// called by the timer in the main window
	void setMoveLeft( int value);
	void setMoveRight(int value);


protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void wheelEvent(QWheelEvent *event);



private:
	double _angle;

	Camera camera;
	SkyBox skybox;

	QTimer * m_timer;
	planet * m_earth;
	planet * m_sun;
	planet * moon;

};

#endif // GLWIDGET_H
