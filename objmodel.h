#include "vertexData.h"

class ObjModel
{
public:
	// 我们需要从obj中解出 点和面的相关信息
	VertexData* mVertexes;
	int *mIndices;
	int mIndexCount;

	void Init(const char* objModel);  //初始化模型文件
	void Draw();
};
