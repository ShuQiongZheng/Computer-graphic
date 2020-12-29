#pragma once
#include "texture.h"

class SkyBox
{
public:
	// The whole is six picture
	Texture* front, * back, * right, * left, * top, * bottom;

	// Init the method
	void Init(const char* path);

	// The method of drawing, the position of the camera, is to keep the camera inside the sky box at all times
	void Draw(float x, float y, float z);

private:
	char frontPath[128];
	char backPath[128];
	char topPath[128];
	char bottomPath[128];
	char leftPath[128];
	char rightPath[128];
};
