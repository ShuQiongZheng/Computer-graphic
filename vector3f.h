#pragma once

// 实现摄像机的移动，主要是数学方面的计算

class Vector3f
{
public:
	union // 既可以通过xyz，来取值，又可以通过v[3],进行取值
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
