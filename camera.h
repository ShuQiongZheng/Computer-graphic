#pragma once
#include "vector3f.h"

class Camera
{
public:
	Camera();

	// Camera Position: mPos
	// Camera ViewCenter: mViewCenter
	// Camera Up normal: mUp 
	Vector3f mPos,mViewCenter,mUp;
	bool mbMoveLeft, mbMoveRight,mbMoveForward,mbMoveBackward;
	void Update();
};
