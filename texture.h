#ifndef __GL_POLYGON_texture_H__
#define __GL_POLYGON_texture_H__ 1
#include <GL/glu.h>
#include <QImage>

const unsigned int N_COLOR   = 3;
const unsigned int N_X_IMAGE = 128;
const unsigned int N_Y_IMAGE = 128;

class Texture
{
public:
	GLuint mTextureID;// What is the name of the texture to be processed --> TextureID 
	void Init(const char* imagePath,int temp);
	void DecodePPM(const char* imagePath);

private:
	void fillimage();

	GLubyte image[N_X_IMAGE][N_Y_IMAGE][N_COLOR];
	GLubyte check[512];
	QImage* p_qimage;

};

#endif
