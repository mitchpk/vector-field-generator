#pragma once
#include <SDL.h>
#include <string>

namespace Utils
{
	class Vector3
	{
	public:
		float x, y, z;
		Vector3() : x(0), y(0), z(0) {};
		Vector3(float dx, float dy, float dz) : x(dx), y(dy), z(dz) {};

		Vector3 operator+(const Vector3& v) const;
		Vector3 operator-(const Vector3& v) const;
		Vector3 operator*(const float s) const;
		Vector3 operator/(const float s) const;

		Vector3& operator+=(const Vector3& v);
		Vector3& operator-=(const Vector3& v);
		Vector3& operator*=(const float s);
		Vector3& operator/=(const float s);

		bool operator==(const Vector3& v) const;
		bool operator!=(const Vector3& v) const;

		float dot(const Vector3& v) const;
		Vector3 cross(const Vector3& v) const;

		float length() const;
		void normalise() { *this /= length(); }
		Vector3& normalised() { return *this /= length(); }
	};

	class Vector2
	{
	public:
		float x, y;
		Vector2() : x(0), y(0) {};
		Vector2(float dx, float dy) : x(dx), y(dy) {};

		Vector2 operator+(const Vector2& v) const;
		Vector2 operator-(const Vector2& v) const;
		Vector2 operator*(const float s) const;
		Vector2 operator/(const float s) const;

		Vector2& operator+=(const Vector2& v);
		Vector2& operator-=(const Vector2& v);
		Vector2& operator*=(const float s);
		Vector2& operator/=(const float s);

		bool operator==(const Vector2& v) const;
		bool operator!=(const Vector2& v) const;

		float dot(const Vector2& v) const;

		float length() const;
		void normalise() { *this /= length(); }
		Vector2& normalised() { return *this /= length(); }

		std::string toString() { return "(" + std::to_string(x) + ", " + std::to_string(y) + ")"; }
	};

    struct DomainAndRange
    {
        Vector2 x, y;
    };

    struct Clock
    {
        Uint32 last_tick_time = 0;
        float delta = 0;

        void tick();
    };

	SDL_Renderer* createWindow(int width = 1024, int height = 720, const char* title = "title");
}
