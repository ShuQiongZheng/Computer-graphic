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

	qDebug()<<"Update";

	//update everything
	float moveSpeed = 1.0f;

	printf("Here setMoveLeft!");
	qDebug()<<"left tranlation";

	//left direction vector
	Vector3f leftDirection(1.0f,0.0f,0.0f);
	leftDirection.Normalize();
	//mPos.x= (translateX-50);


	printf("Here setMoveRight!");

	//right direction vector
	Vector3f rightDirection(0.0f, 1.0f, 0.0f);
	rightDirection.Normalize();

	mPos = Vector3f(10.0f, 10.0f, 10.0f) + leftDirection*moveSpeed*(translateX-50) + rightDirection*moveSpeed*(translateY-50);
	mViewCenter = Vector3f(0.0f, 0.0f, 0.0f)  + leftDirection*moveSpeed*(translateX-50) + 	rightDirection*moveSpeed*(translateY-50);

	qDebug()<<"mPos"<<mPos.x<<mPos.y<<mPos.z <<"mViewCenter"<< mViewCenter.x<<mViewCenter.y<<mViewCenter.z;

	//set model view matrix
	gluLookAt(mPos.x, mPos.y, mPos.z,mViewCenter.x, mViewCenter.y, mViewCenter.z,mUp.x, mUp.y, mUp.z);
}






















