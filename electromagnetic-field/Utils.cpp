#include "Utils.h"
#include <cmath>

namespace Utils
{
	SDL_Renderer* createWindow(int width, int height, const char* title)
	{
		SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
		return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	}

	void Clock::tick()
	{
		Uint32 tick_time = SDL_GetTicks();
		delta = (tick_time - last_tick_time) / 1000.0f;
		last_tick_time = tick_time;
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
}