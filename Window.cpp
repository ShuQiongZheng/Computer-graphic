#include "Window.h"
#include <QVBoxLayout>
#include <QtWidgets>
#include "glWidget.h"
#include "objmodel.h"
#include "texture.h"
#include "utils.h"
#include "vertexData.h"
#include "camera.h"

// constructor / destructor
Window::Window(QWidget *parent)
	: QWidget(parent)
	{ // constructor

	// create menu bar
	menuBar = new QMenuBar(this);
	
	// create file menu
	fileMenu = menuBar->addMenu("&File");

	// create the action
	actionQuit = new QAction("&Quit", this);

	// leave signals & slots to the controller
	
	// add the item to the menu
	fileMenu->addAction(actionQuit);
	
	// create the Window layout
	windowLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

	// create main widget
	cubeWidget = new glWidget(this);

	// create slider
	xSlider = createSlider();
	ySlider = createSlider();

	// If the slider's value changed, then we execute the function -> in SLOT
	connect(xSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(setMoveLeft()));

	connect(ySlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(setMoveRight()));

	windowLayout->addWidget(cubeWidget);
	windowLayout->addWidget(xSlider);
	windowLayout->addWidget(ySlider);

	xSlider->setValue(15 * 16);
	ySlider->setValue(345 * 16);

	} // constructor

// The createSlider() utility function constructs a QSlider, and ensures that it is set up with a suitable range, 
// step value, tick interval, and page step value before returning it to the calling function.
QSlider *Window::createSlider()
{
	QSlider *slider = new QSlider(Qt::Horizontal);
	slider->setRange(0, 360 * 16);
	slider->setSingleStep(16);
	slider->setPageStep(15 * 16);
	slider->setTickInterval(15 * 16);
	slider->setTickPosition(QSlider::TicksRight);  //Define the number position rather than the slider position
	return slider;
}

Window::~Window()
	{ // destructor
	delete ptimer;
	delete nVerticesSlider;
	delete cubeWidget;
	delete windowLayout;
	delete actionQuit;
	delete fileMenu;
	delete menuBar;
	} // destructor

// resets all the interface elements
void Window::ResetInterface()
	{ // ResetInterface()
	nVerticesSlider->setMinimum(3);
	nVerticesSlider->setMaximum(30);

	//don't use the slider for now

	//	nVerticesSlider->setValue(thePolygon->nVertices);
	
	// now force refresh
	cubeWidget->update();
	update();
	} // ResetInterface()

void Window::keyPressEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_Escape)
	close();
	else
	QWidget::keyPressEvent(e);
}













