#include "vertexData.h"

class ObjModel
{
public:
	// ������Ҫ��obj�н�� �����������Ϣ
	VertexData* mVertexes;
	int *mIndices;
	int mIndexCount;

	void Init(const char* objModel);  //��ʼ��ģ���ļ�
	void Draw();
};
