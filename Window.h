#ifndef __GL_POLYGON_Window_H__
#define __GL_POLYGON_Window_H__ 1

#include <QGLWidget>
#include <QMenuBar>
#include <QSlider>
#include <QTimer>
#include <QBoxLayout>
#include "glWidget.h"
#include "camera.h"

// The Window class is used as a container for the GLWidget used to display the scene.
class QSlider;

class Window: public QWidget
{ 
public:
	// constructor / destructor
	Window(QWidget *parent);
	~Window();

	// visual hierarchy
	// menu bar
	QMenuBar *menuBar;
	// file menu
	QMenu *fileMenu;
	// quit action
	QAction *actionQuit;

	// Window layout
	QBoxLayout *windowLayout;

	// beneath that, the main widget
	glWidget *cubeWidget;
	// and a slider for the number of vertices
	QSlider *nVerticesSlider;

	// a timer
	QTimer *ptimer;

	// resets all the interface elements
	void ResetInterface();

protected:
	void keyPressEvent(QKeyEvent *event);

private:
	QSlider *createSlider();

	QSlider *xSlider;
	QSlider *ySlider;
	QSlider *zSlider;
}; 
	
#endif

















