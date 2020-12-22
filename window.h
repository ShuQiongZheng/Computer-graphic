#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "qtlogo.h"
#include "glwidget.h"

// The Window class is used as a container for the GLWidget used to display the scene.
class QSlider;

class GLWidget;

class Window : public QWidget
{
	Q_OBJECT

public:
	Window();

protected:
	void keyPressEvent(QKeyEvent *event);

// In addition, it contains sliders that are used to change the orientation of the object in the scene.
private:
	QSlider *createSlider();

	GLWidget *glWidget;
	QSlider *xSlider;
	QSlider *ySlider;
	QSlider *zSlider;
};

#endif
