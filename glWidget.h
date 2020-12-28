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
    void setMoveLeft( int value);
    void setMoveRight(int value);


protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);



private:
    void drawAnimal();
    void CenterTower();
    void top(double base,double x,double y);
    void diamond();
    double _angle;

    Camera camera;
    QTimer * m_timer;

};

#endif // GLWIDGET_H
