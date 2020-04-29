#pragma once
#include "Utils.h"

enum VectorType
{
	scaled,
	fixed,
	constrained
};

struct Vector
{
	Vector( Utils::Vector2 tail,
			Utils::Vector2 head,
			float length = 1,
			VectorType type = VectorType::scaled,
			float arrowAngle = M_PI / 5.6f, 
			float arrowLength = 1.0f );

	void generate();
	void calculateArrow();

	Vector operator - (const Utils::Vector2& vec)
	{
		Vector temp = *this;
		temp.tail -= vec;
		temp.head -= vec;
		temp.calculatedHead -= vec;
		return temp;
	}

	Utils::Vector2 tail;
	Utils::Vector2 head;
	Utils::Vector2 calculatedHead;
	float length; // Depending on the vector type, will either control the scale, the exact length or the maximum length of the vector
	VectorType type;
	Utils::Vector2 arrowPoint1;
	Utils::Vector2 arrowPoint2;
	float arrowAngle;
	float arrowLength;

	bool isValid = true;

private:
	float lastLength;
};
