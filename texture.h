#pragma once
#include <Window.h>

const unsigned int N_COLOR   = 3;
const unsigned int N_X_IMAGE = 128;
const unsigned int N_Y_IMAGE = 128;

class Texture
{
public:
	GLuint mTextureID;// 告诉显卡要处理的纹理的名字叫什么 --> TextureID 
	void Init(const char* imagePath,int temp);
	void DecodePPM(const char* imagePath);

private:
	void fillimage();

	GLubyte image[N_X_IMAGE][N_Y_IMAGE][N_COLOR];
	GLubyte check[512];
	QImage* p_qimage;

};

