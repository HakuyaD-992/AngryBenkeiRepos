#include "Vector2.h"

Vector2::Vector2()
{
}


Vector2::~Vector2()
{
}

Vector2::Vector2(int x, int y)
{
	this->x = x;
	this->y = y;
}

Vector2 & Vector2::operator=(const Vector2 & vec)
{
	this->x = vec.x;
	this->y = vec.y;
	return (*this);
}

int & Vector2::operator[](int i)
{
	if (i == 0)
	{
		return x;
	}
	else if (i == 1)
	{
		return y;
	}
	else if (i == 2)
	{
		return x;
	}
}

bool Vector2::operator==(const Vector2 & vec) const
{
	return ((this->x == vec.x) && (this->y == vec.y));
}
bool operator==(const Vector2 & vec, int k)
{
	return ((k == vec.x) && (k == vec.y));
}

bool Vector2::operator!=(const Vector2 & vec) const
{
	return !((this->x == vec.x) && (this->y == vec.y));
}

Vector2 & Vector2::operator+=(const Vector2 & vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return (*this);
}

Vector2 & Vector2::operator-=(const Vector2 & vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return (*this);
}

Vector2 & Vector2::operator*=(const Vector2 & vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return (*this);
}

Vector2 & Vector2::operator/=(const Vector2 & vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return (*this);
}

Vector2 Vector2::operator+() const
{
	return (*this);
}

Vector2 Vector2::operator-() const
{
	return -(*this);
}

Vector2 operator+(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec.x = u.x + v.x;
	vec.y = u.y + v.y;

	return vec;
}

Vector2 operator+(const Vector2 & u, int k)
{
	Vector2 vec;
	vec.x = u.x + k;
	vec.y = u.y + k;
	return vec;
}

Vector2 operator+(int k, const Vector2 & v)
{
	Vector2 vec;
	vec.x = k + v.x;
	vec.y = k + v.y;
	return vec;
}

Vector2 operator-(const Vector2 & u, int k)
{
	Vector2 vec;
	vec.x = u.x - k;
	vec.y = u.y - k;
	return vec;
}

Vector2 operator-(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec.x = u.x - v.x;
	vec.y = u.y - v.y;

	return vec;
}

Vector2 operator%(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec.x = u.x % v.y;
	vec.y = u.y % v.y;

	return vec;
}

Vector2 operator%(const Vector2 & u, int k)
{
	Vector2 vec;
	vec.x = u.x % k;
	vec.y = u.y % k;
	return vec;
}


Vector2 operator*(int k, const Vector2 & v)
{
	Vector2 vec;
	vec.x = k * v.x;
	vec.y = k * v.y;

	return vec;
}



Vector2 operator*(const Vector2 & u, int k)
{
	Vector2 vec;
	vec.x = u.x * k;
	vec.y = u.y * k;

	return vec;
}

Vector2 operator/(const Vector2 & u, int k)
{
	Vector2 vec;
	vec.x = u.x / k;
	vec.y = u.y / k;

	return vec;
}

Vector2 operator/(const int k, Vector2 & v)
{
	Vector2 vec;
	vec.x = k / v.x;
	vec.y = k / v.y;

	return vec;
}

Vector2 & operator+=(const Vector2 & v, int k)
{
	Vector2 vec;
	vec.x += k;
	vec.y += k;

	return vec;
}

Vector2 operator/(const float fk, Vector2 & v)
{
	return Vector2();
}

Vector2 operator<(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec.x = u.x < v.x;
	vec.y = u.y < v.y;

	return vec;
}

Vector2 operator>(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec.x = u.x > v.x;
	vec.y = u.y > v.y;

	return vec;
}

Vector2 operator<(const Vector2 & u, const int k)
{
	Vector2 vec;
	vec.x = u.x < k;
	vec.y = u.y < k;

	return vec;
}

Vector2 operator>(const int k, const Vector2 & v)
{
	Vector2 vec;
	vec.x = k > vec.x;
	vec.y = k > vec.y;

	return vec;
}

bool operator>=(const Vector2 & u, const Vector2 & v)
{
	return (u.x >= v.x && u.y >= v.y);
}

bool operator<=(const Vector2 & u, const Vector2 & v)
{
	return (u.x <= v.x && u.y <= v.y);
}
