#include "texture.h"
#include "utils.h"

// 解码BMP文件，传入一个文件指针，并返回一个指针，指向一个像素数据
unsigned char* DecodeBMP(unsigned char* bmpFileData, int& width, int& height)
{
	// 首先判断是否是一个像素图片
	if (0x4D42 == *((unsigned short*)bmpFileData))
	{
		// 像素数据在那儿？像素数据的偏移地址
		int pixelDataOffset = *((int*)(bmpFileData + 10));

		// 读出像素数据的高度和宽度
		width = *((int*)(bmpFileData + 18));
		height = *((int*)(bmpFileData + 22));
		unsigned char* pixelData = bmpFileData + pixelDataOffset;
		
		// 最开始BGR的排布方式，后来改成RGB的排布方式
		// bgr bgr bgr  --> rgb rgb rgb
		for (int i = 0; i < width * height * 3; i += 3)
		{
			unsigned char temp = pixelData[i];
			pixelData[i] = pixelData[i + 2];
			pixelData[i + 2] = temp;
		}
		return pixelData;
	}
	else
	{
		return nullptr;
	}
}

/*
*  if temp == 1, Decode BMP;
*  if temp == 2, Decode PPM;
*/

void Texture::Init(const char* imagePath,int temp)
{
	unsigned char* pixelData;
	int width = 0, height = 0;

	if(temp==1){

		// 将图片从文件中读出 --> 内存中去，使用untils里面的方法帮忙读文件
		// LoadFileContent()是utilis里面的方法
		unsigned char* imageFileContent = LoadFileContent(imagePath);

		// 将文件解码
		pixelData = DecodeBMP(imageFileContent, width, height);
		
		//generate an opengl texture
		// 申请一个纹理的ID
		glGenTextures(1, &mTextureID);
        	delete imageFileContent;

	}
	else if(temp==2){

		// 将文件解码
		DecodePPM(imagePath);

		// 申请一个纹理的ID
		glGenTextures(2,&mTextureID);

	}

	
	// 即将操作的时候，设置成一个当前的纹理为：mTextureID
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	
	//operation on current texture；状态机：就是对当前纹理的处理
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 当图片放大或者缩小的时候，做线性缩放: GL_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	// 纹理坐标的取值超过了范围取值应该如何？我们规定等于0或者是1，0代表黑色，1代表重复！
	// 所以当纹理坐标超过了取值，您就会看到重复现象。如果是草坪那就无妨！
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	// 生成纹理: 将纹理从内存 >> 显存,上面去，并且生成了一个纹理对象
	if(temp==1){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixelData);
	}
	else if(temp==2){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, N_X_IMAGE, N_Y_IMAGE, 0, GL_RGB, GL_UNSIGNED_BYTE, image);	
	}

	//操作完成之后，设置纹理ID为：0
	glBindTexture(GL_TEXTURE_2D, 0);

}

void Texture::DecodePPM(const char* imagePath)
{
	p_qimage = new QImage(imagePath);

	for(unsigned int i_x_pix = 0; i_x_pix < N_X_IMAGE; i_x_pix++){
		for(unsigned int i_y_pix = 0; i_y_pix < N_Y_IMAGE; i_y_pix++){
			QRgb colval = p_qimage->pixel(i_x_pix,i_y_pix);
			image[N_Y_IMAGE - 1 - i_y_pix][i_x_pix][0] = qRed(colval);
			image[N_Y_IMAGE - 1 - i_y_pix][i_x_pix][1] = qGreen(colval);
			image[N_Y_IMAGE - 1 - i_y_pix][i_x_pix][2] = qBlue(colval);
		}
	}


	GLubyte  wb[2] = {0x00, 0xff};

	for(int i = 0; i < 64; i++){
		for(int j = 0; j < 8; j++){
			check[i*8+j]=wb[(i/8+j)%2];
		}
	}
}





























