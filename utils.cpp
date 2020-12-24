#include "utils.h"
unsigned char* LoadFileContent(const char* filePath)
{
	// ���ȼ���������һ���ļ�ָ��
	unsigned char* fileContent = nullptr;

	// �����ƶ�ȡ�ļ�����
	FILE* pFile = fopen(filePath, "rb");

	if (pFile) // ��������ļ��򿪳ɹ��ˣ���ô���ǾͶ���
	{
		// ���ļ�ָ���Ƶ��ļ�β��������ȡָ�볤��
		fseek(pFile, 0, SEEK_END);
		int nLen = ftell(pFile);

		// ���ָ�볤�ȴ����㣬��ô���ǾͶ�������ͷ���һ����ָ��
		if (nLen > 0)
		{
			// �ٴ��Ƶ��ļ�ͷ
			rewind(pFile);

			// �����һλ��������š�\0����
			fileContent = new unsigned char[nLen + 1];

			fread(fileContent, sizeof(unsigned char), nLen, pFile);
			fileContent[nLen] = '\0';
		}
		fclose(pFile);
	}
	return fileContent;
}
