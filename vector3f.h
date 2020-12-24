#pragma once

// ʵ����������ƶ�����Ҫ����ѧ����ļ���

class Vector3f
{
public:
	union // �ȿ���ͨ��xyz����ȡֵ���ֿ���ͨ��v[3],����ȡֵ
	{
		struct
		{
			float x, y, z;
		};
		float v[3];
	};

	Vector3f();
	Vector3f(float x, float y, float z);

	void operator=(const Vector3f& r);
	Vector3f operator*(const float scaler);
	float operator*(Vector3f& r);
	Vector3f operator+(const Vector3f& r);
	Vector3f operator-(const Vector3f& r);

	void Normalize();
	float Magnitude();
};
