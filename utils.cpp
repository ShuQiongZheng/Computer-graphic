#include "utils.h"
unsigned char* LoadFileContent(const char* filePath)
{
	// 首先假设我们有一个文件指针
	unsigned char* fileContent = nullptr;

	// 二进制读取文件方法
	FILE* pFile = fopen(filePath, "rb");

	if (pFile) // 如果我们文件打开成功了，那么我们就读！
	{
		// 将文件指针移到文件尾部，并获取指针长度
		fseek(pFile, 0, SEEK_END);
		int nLen = ftell(pFile);

		// 如果指针长度大于零，那么我们就读！否则就返回一个空指针
		if (nLen > 0)
		{
			// 再次移到文件头
			rewind(pFile);

			// 多加了一位是用来存放‘\0’的
			fileContent = new unsigned char[nLen + 1];

			fread(fileContent, sizeof(unsigned char), nLen, pFile);
			fileContent[nLen] = '\0';
		}
		fclose(pFile);
	}
	return fileContent;
}
