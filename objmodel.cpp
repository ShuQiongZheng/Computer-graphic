#include <QtWidgets>
#include <QGLWidget>
#include "objmodel.h"
#include "vertexData.h"
#include "utils.h"
#include <cstring>
#include <sstream>
#include <vector>

// 点，线，法线，纹理贴图，模型
void ObjModel::Init(const char* objModel)
{
	struct FloatData
	{
		float v[3];
	};
	//使用vector存储坐标
	std::vector<FloatData> positions, texcoords, normals;


	struct VerticeDefine
	{
		int posIndex;
		int texcoordIndex;
		int normalIndex;
	};
	std::vector<VerticeDefine> vertexes; //唯一的点的信息，已经去重了！
	std::vector<int> indexes; //点的连接信息



	// 先将这个模型文件加载进来 --> 内存
	unsigned char* fileContent = LoadFileContent(objModel);
	// 一行的内容是多少？我们给一行256个字符
	char szOneLine[256];

	std::stringstream ssFileContent((char*)fileContent);
	std::string temp;

	while (!ssFileContent.eof())
	{
		// 读取一行，最多256个文件！
		memset(szOneLine, 0, 256);
		ssFileContent.getline(szOneLine, 256);

		if (strlen(szOneLine) > 0) // 过滤空行！
		{
			if (szOneLine[0] == 'v') 
			{
				// 当数据为v开头，那就说明我们需要这一个数据，我们就把它放入stringstream里面
				std::stringstream ssOneLine(szOneLine);

				if (szOneLine[1] == 't')
				{
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					// printf("texcoord : %f,%f\n", floatData.v[0], floatData.v[1]);
					texcoords.push_back(floatData);
				}
				else if (szOneLine[1] == 'n')
				{
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					normals.push_back(floatData);
					// printf("normal : %f,%f,%f\n", floatData.v[0], floatData.v[1], floatData.v[2]);

				}
				else
				{
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					positions.push_back(floatData);
					// printf("position : %f,%f,%f\n", floatData.v[0], floatData.v[1], floatData.v[2]);

				}
			}
			else if (szOneLine[0] == 'f')
			{
				//std::stringstream ssOneLine(); 需要初始化！
				std::stringstream ssOneLine(szOneLine);
				ssOneLine >> temp; 
				std::string vertexStr;// 1/1/1

				// 没一行有三个，对每一行解码：1/1/1
				for (int i = 0;i < 3;i++)
				{
					ssOneLine >> vertexStr;
					size_t pos = vertexStr.find_first_of('/'); // 找到斜杠

					std::string posIndexStr = vertexStr.substr(0, pos);
					// 1
					size_t pos2 = vertexStr.find_first_of('/', pos + 1);
					// 1
					std::string texcoordIndexStr = vertexStr.substr(pos + 1, pos2 - 1 - pos);
					// 1
					std::string normalIndexStr = vertexStr.substr(pos2 + 1, vertexStr.length() - 1 - pos2);

					// 转为整数
					VerticeDefine vd;
					vd.posIndex = atoi(posIndexStr.c_str());
					vd.texcoordIndex = atoi(texcoordIndexStr.c_str());
					vd.normalIndex = atoi(normalIndexStr.c_str());

					// printf("%d,%d,%d\n", vd.posIndex, vd.texcoordIndex, vd.normalIndex);

					int nCurrentVertexIndex = -1;
					int nCurrentVertexCount = (int)vertexes.size();

					// 去重！去掉重复的点！
					for (int j = 0;j < nCurrentVertexCount;++j)
					{
						if (vertexes[j].posIndex == vd.posIndex &&
							vertexes[j].normalIndex == vd.normalIndex &&
							vertexes[j].texcoordIndex == vd.texcoordIndex)
						{
							nCurrentVertexIndex = j;
							break;
						}
					}
					if (nCurrentVertexIndex == -1)
					{
						nCurrentVertexIndex = (int)vertexes.size();
						vertexes.push_back(vd);
					}
					indexes.push_back(nCurrentVertexIndex);
				}
				// printf("face : %s\n", szOneLine);
			}
		}
	}
	// printf("unique vertex count %u index count %u\n", vertexes.size(), indexes.size());
	
	// 头文件定义的内容
	mIndexCount = (int)indexes.size();
	mIndices = new int[mIndexCount];
	for (int i = 0;i < mIndexCount;++i)
	{
		mIndices[i] = indexes[i];
	}
	int vertexCount = (int)vertexes.size();
	mVertexes = new VertexData[vertexCount];

	for (int i = 0;i < vertexCount;++i)
	{
		// 把vertex的数据转为opengl能用的数据
		memcpy(mVertexes[i].position, positions[vertexes[i].posIndex - 1].v, sizeof(float) * 3);
		memcpy(mVertexes[i].texcoord, texcoords[vertexes[i].texcoordIndex - 1].v, sizeof(float) * 2);
		memcpy(mVertexes[i].normal, normals[vertexes[i].normalIndex - 1].v, sizeof(float) * 3);
	}
	delete fileContent;
}

void ObjModel::Draw()
{
	// glEnable(GL_CULL_FACE);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// glPolygonMode(GL_FRONT, GL_LINE);

	// rotate

	static float angle = 0.0f;
	angle += 1.0f;
	if (angle >= 360.0f)
	{
		angle = 0.0f;
	}

	glPushMatrix();
	
	glTranslatef(0.0f, 0.0f, -1.0f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glScalef(-0.5f, -0.5f, -0.5f);

	// 面都是由三角形构成的！
	glBegin(GL_TRIANGLES);
	for (int i = 0;i < mIndexCount;++i)
	{
		glTexCoord2fv(mVertexes[mIndices[i]].texcoord);
		glNormal3fv(mVertexes[mIndices[i]].normal);
		glVertex3fv(mVertexes[mIndices[i]].position);

	}
	glEnd();
	glPopMatrix();

}
