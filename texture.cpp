#include "texture.h"
#include "utils.h"

// ����BMP�ļ�������һ���ļ�ָ�룬������һ��ָ�룬ָ��һ����������
unsigned char* DecodeBMP(unsigned char* bmpFileData, int& width, int& height)
{
	// �����ж��Ƿ���һ������ͼƬ
	if (0x4D42 == *((unsigned short*)bmpFileData))
	{
		// �����������Ƕ����������ݵ�ƫ�Ƶ�ַ
		int pixelDataOffset = *((int*)(bmpFileData + 10));

		// �����������ݵĸ߶ȺͿ��
		width = *((int*)(bmpFileData + 18));
		height = *((int*)(bmpFileData + 22));
		unsigned char* pixelData = bmpFileData + pixelDataOffset;
		
		// �ʼBGR���Ų���ʽ�������ĳ�RGB���Ų���ʽ
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

		// ��ͼƬ���ļ��ж��� --> �ڴ���ȥ��ʹ��untils����ķ�����æ���ļ�
		// LoadFileContent()��utilis����ķ���
		unsigned char* imageFileContent = LoadFileContent(imagePath);

		// ���ļ�����
		pixelData = DecodeBMP(imageFileContent, width, height);
		
		//generate an opengl texture
		// ����һ�������ID
		glGenTextures(1, &mTextureID);
        	delete imageFileContent;

	}
	else if(temp==2){

		// ���ļ�����
		DecodePPM(imagePath);

		// ����һ�������ID
		glGenTextures(2,&mTextureID);

	}

	
	// ����������ʱ�����ó�һ����ǰ������Ϊ��mTextureID
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	
	//operation on current texture��״̬�������ǶԵ�ǰ����Ĵ���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // ��ͼƬ�Ŵ������С��ʱ������������: GL_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	// ���������ȡֵ�����˷�ΧȡֵӦ����Σ����ǹ涨����0������1��0�����ɫ��1�����ظ���
	// ���Ե��������곬����ȡֵ�����ͻῴ���ظ���������ǲ�ƺ�Ǿ��޷���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	// ��������: ��������ڴ� >> �Դ�,����ȥ������������һ���������
	if(temp==1){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixelData);
	}
	else if(temp==2){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, N_X_IMAGE, N_Y_IMAGE, 0, GL_RGB, GL_UNSIGNED_BYTE, image);	
	}

	//�������֮����������IDΪ��0
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





























