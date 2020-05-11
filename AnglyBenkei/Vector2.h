#pragma once
class Vector2
{
public:
	Vector2();
	~Vector2();

	int x;
	int y;

	Vector2(int x, int y);

	Vector2& operator = (const Vector2& vec);
	int& operator[](int i);

	bool operator==(const Vector2& vec) const;

	bool operator!=(const Vector2& vec) const;

	Vector2& operator+=(const Vector2& vec);


	Vector2& operator-=(const Vector2& vec);
	Vector2& operator*=(const Vector2& vec);
	Vector2& operator/=(const Vector2& vec);
	Vector2 operator+()const;						//const = éQè∆ìnÇµÇÃç€Ç…égóp
	Vector2 operator-()const;

};
Vector2 operator+(const Vector2& u, const Vector2& v);
Vector2 operator+(const Vector2& u, int k);

Vector2 operator+(int k, const Vector2& v);
Vector2 operator-(const Vector2& u, int k);

//Vector3D-Vector3D
Vector2 operator-(const Vector2& u, const Vector2& v);
Vector2 operator%(const Vector2& u, const Vector2& v);
Vector2 operator%(const Vector2& u, int k);

Vector2 operator*(int k, const  Vector2& v);

bool operator==(const Vector2& vec, int k);

//Vector3D*int
Vector2 operator*(const Vector2& u, int k);

Vector2 operator/(const Vector2& u, int k);
Vector2 operator/(const int k, Vector2& v);
Vector2& operator+=(const Vector2& v, int k);

Vector2 operator<(const Vector2& u, const Vector2& v);
Vector2 operator>(const Vector2& u, const Vector2& v);

Vector2 operator<(const Vector2& u, const int k);
Vector2 operator>(const int k, const Vector2& v);

bool operator>=(const Vector2& u, const Vector2& v);
bool operator<=(const Vector2& u, const Vector2& v);


