#pragma once
#include "Utils.h"

enum VectorType
{
	scaled,
	fixed,
	constrained
};

class Vector
{
private:
	Utils::Vector2 calculateArrow(float arrowAngle, float arrowLength);

public:
	Vector( Utils::Vector2 tail,
			Utils::Vector2 head,
			float length = 1, // Depending on the Vector type, will either control the scale, the exact length or the maximum length of the Vector
			VectorType type = VectorType::scaled,
			float arrowAngle = M_PI / 5.6f, 
			float arrowLength = 1.8f );

	Utils::Vector2 tail;
	Utils::Vector2 head;
	Utils::Vector2 arrowPoint1;
	Utils::Vector2 arrowPoint2;
};
