#include "vector3f.h"
#include "math.h"

// initial the vector
Vector3f::Vector3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3f::Vector3f()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

void Vector3f::operator=(const Vector3f& r)
{
	x = r.x;
	y = r.y;
	z = r.z;
}

void Vector3f::Normalize()
{
	// 求出向量的长度，求总长度，然后再分别除以长度！
	float len = Magnitude();
	x /= len;
	y /= len;
	z /= len;
}

float Vector3f::Magnitude()
{
	return sqrtf(x * x + y * y + z * z);
}

Vector3f Vector3f::operator*(const float scaler)
{
	return Vector3f(x * scaler, y * scaler, z * scaler);
}

float Vector3f::operator*(Vector3f& r)
{
	return x * r.x + y * r.y + z * r.z;
}


Vector3f Vector3f::operator+(const Vector3f& r)
{
	return Vector3f(x + r.x, y + r.y, z + r.z);
}

Vector3f Vector3f::operator-(const Vector3f& r)
{
	return Vector3f(x - r.x, y - r.y, z - r.z);
}



