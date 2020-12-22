#include <QtWidgets>
#include "qtlogo.h"
#include "glwidget.h"
#include "window.h"

// The constructor constructs an instance of the GLWidget class and some sliders to manipulate its contents.
Window::Window()
{
	glWidget = new GLWidget;

	xSlider = createSlider();
	ySlider = createSlider();
	zSlider = createSlider();

	// We connect the valueChanged() signal from each of the sliders 滑块 to the appropriate slots槽 in glWidget. 
	// This allows the user to change the orientation of the object by dragging the sliders.
	// We also connect the xRotationChanged(), yRotationChanged(), and zRotationChanged() signals from glWidget to the setValue() slots in the corresponding sliders.
	connect(xSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setXRotation(int)));
	connect(glWidget, SIGNAL(xRotationChanged(int)), xSlider, SLOT(setValue(int)));

	connect(ySlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setYRotation(int)));
	connect(glWidget, SIGNAL(yRotationChanged(int)), ySlider, SLOT(setValue(int)));

	connect(zSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setZRotation(int)));
	connect(glWidget, SIGNAL(zRotationChanged(int)), zSlider, SLOT(setValue(int)));

	// The sliders are placed horizontally in a layout alongside the GLWidget, and initialized with suitable default values.
	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addWidget(glWidget);
	mainLayout->addWidget(xSlider);
	mainLayout->addWidget(ySlider);
	mainLayout->addWidget(zSlider);
	setLayout(mainLayout);

	xSlider->setValue(15 * 16);
	ySlider->setValue(345 * 16);
	zSlider->setValue(0 * 16);
	setWindowTitle(tr("Hello GL"));
}

// The createSlider() utility function constructs a QSlider, and ensures that it is set up with a suitable range, 
// step value, tick interval, and page step value before returning it to the calling function.
QSlider *Window::createSlider()
{
	QSlider *slider = new QSlider(Qt::Vertical);
	slider->setRange(0, 360 * 16);
	slider->setSingleStep(16);
	slider->setPageStep(15 * 16);
	slider->setTickInterval(15 * 16);
	slider->setTickPosition(QSlider::TicksRight);
	return slider;
}

void Window::keyPressEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_Escape)
	close();
	else
	QWidget::keyPressEvent(e);
}
