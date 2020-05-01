#include "Utils.h"
#include <cmath>

namespace Utils
{
	void Clock::tick()
	{
		Uint64 tick = SDL_GetPerformanceCounter();
		delta = (tick - lastTick) / (float)SDL_GetPerformanceFrequency();
		lastTick = tick;
	}

	// Vector3

	Vector3 Vector3::operator+(const Vector3& v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 Vector3::operator-(const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 Vector3::operator*(const float s) const
	{
		return Vector3(x * s, y * s, z * s);
	}

	Vector3 Vector3::operator/(const float s) const
	{
		return Vector3(x / s, y / s, z / s);
	}

	Vector3& Vector3::operator+=(const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vector3& Vector3::operator*=(const float s)
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	Vector3& Vector3::operator/=(const float s)
	{
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

	bool Vector3::operator==(const Vector3& v) const
	{
		return (x == v.x && y == v.y && z == v.z);
	}

	bool Vector3::operator!=(const Vector3& v) const
	{
		return !(*this == v);
	}

	float Vector3::dot(const Vector3& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	Vector3 Vector3::cross(const Vector3& v) const
	{
		return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	float Vector3::length() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	// Vector2

	Vector2 Vector2::operator+(const Vector2& v) const
	{
		return Vector2(x + v.x, y + v.y);
	}

	Vector2 Vector2::operator-(const Vector2& v) const
	{
		return Vector2(x - v.x, y - v.y);
	}

	Vector2 Vector2::operator*(const float s) const
	{
		return Vector2(x * s, y * s);
	}

	Vector2 Vector2::operator/(const float s) const
	{
		return Vector2(x / s, y / s);
	}

	Vector2& Vector2::operator+=(const Vector2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vector2& Vector2::operator*=(const float s)
	{
		x *= s;
		y *= s;
		return *this;
	}

	Vector2& Vector2::operator/=(const float s)
	{
		x /= s;
		y /= s;
		return *this;
	}

	bool Vector2::operator==(const Vector2& v) const
	{
		return (x == v.x && y == v.y);
	}

	bool Vector2::operator!=(const Vector2& v) const
	{
		return !(*this == v);
	}

	float Vector2::dot(const Vector2& v) const
	{
		return x * v.x + y * v.y;
	}

	float Vector2::length() const
	{
		return std::sqrt(x * x + y * y);
	}

	Vector2 getMousePos()
	{
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		return { (float)mouseX, (float)mouseY };
	}

	Vector2 toCoords(Vector2 pixels) { return { pixels.x / 20, -pixels.y / 20 }; }
	Vector2 toPixels(Vector2 coords) { return { coords.x * 20, -coords.y * 20 }; }
}

/*
Vector2 Window::conversionToCoordinates(Vector2 pixelCoordinates, DomainAndRange domainAndRange)
{
	return { ((domainAndRange.x.y - domainAndRange.x.x) * (2 * pixelCoordinates.x - _width)) / (2 * _width), ((domainAndRange.y.y - domainAndRange.y.x) * (2 * pixelCoordinates.y + _height)) / (2 * _height)};
}

Vector2 Window::conversionToPixels(Vector2 cartesianCoordinates, DomainAndRange domainAndRange)
{
	return { ((2*_width*cartesianCoordinates.x /(domainAndRange.x.y - domainAndRange.x.x) + _width)/2) ,  ((2*_height*cartesianCoordinates.y /(domainAndRange.y.y - domainAndRange.y.x) - _height)/2)  };
}


//Window size is X,Y
//User will input the domain and range along with camera offset and vector density
//We need to make a function that converts coordinates to pixels and pixels to coordinates.

//Convert coordinates to pixel coordinates.



// F_x(x,y)=2x+2y
// F_y(x,y)=xy

//Example (1,1) The vector will start at (1,1) and end at (5,2)
//Let input be V, and the resulting vector is R, |R-V|<=c */