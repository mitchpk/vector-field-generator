#pragma once
#include "Utils.h"

enum VectorType
{
	normal,
	fixed,
	constrained
};

struct Vector
{
	Vector( Utils::Vector2 tail,
			Utils::Vector2 head,
			float length = 1,
			VectorType type = VectorType::normal,
			float scale = 1,
			float arrowAngle = M_PI / 5.6f, 
			float arrowProportion = 0.2f );

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

	Vector operator * (const float& f)
	{
		Vector temp = *this;
		temp.tail *= f;
		temp.head *= f;
		temp.calculatedHead *= f;
		temp.arrowPoint1 *= f;
		temp.arrowPoint2 *= f;
		return temp;
	}

	Vector operator / (const float& f)
	{
		Vector temp = *this;
		temp.tail /= f;
		temp.head /= f;
		temp.calculatedHead /= f;
		temp.arrowPoint1 /= f;
		temp.arrowPoint2 /= f;
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
	float arrowProportion;
	float scale;
	float unscaledLength=(head-tail).length();

	bool isValid = true;

private:
	float lastLength = 0;
};
