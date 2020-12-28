#pragma once
#include "vector3f.h"

class Camera
{
public:
	Camera();
public:
    int translateX = 50;
    int translateY = 50;
    int distance = 50;

	// Camera Position: mPos
	// Camera ViewCenter: mViewCenter
	// Camera Up normal: mUp 
	Vector3f mPos,mViewCenter,mUp;
	bool mbMoveLeft, mbMoveRight,mbMoveForward,mbMoveBackward;
	void Update(float deltaTime);
};
