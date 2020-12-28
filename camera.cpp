#include "camera.h"
#include "math.h"
#include "vector3f.h"
#include <GL/glu.h>
#include <cstdio>
#include <QDebug>

Camera::Camera() :mPos(10.0f, 10.0f, 10.0f),
    mViewCenter(0.0f, 0.0f, 0.0f),
    mUp(-1.0f, 1.0f, -1.0f),
    mbMoveLeft(false),
    mbMoveRight(false),
    mbMoveForward(false),
    mbMoveBackward(false)
{

}

// Update the Camera position 
void Camera::Update(float deltaTime)
{

    float moveSpeed = 1.0f;

    //qDebug()<<"left tranlation";
    //left direction vector
    Vector3f leftDirection(1.0f,0.0f,0.0f);
    leftDirection.Normalize();

    Vector3f rightDirection(0.0f, 1.0f, 0.0f);
    rightDirection.Normalize();
    mPos = Vector3f(10.0f, 10.0f, 10.0f) + leftDirection*moveSpeed*(translateX-50) + rightDirection*moveSpeed*(translateY-50) + Vector3f(1,1,1)*distance;
    mViewCenter = Vector3f(0.0f, 0.0f, 0.0f)  + leftDirection*moveSpeed*(translateX-50) + rightDirection*moveSpeed*(translateY-50);
    //qDebug()<<"mPos"<<mPos.x<<mPos.y<<mPos.z <<"mViewCenter"<< mViewCenter.x<<mViewCenter.y<<mViewCenter.z;

}






















