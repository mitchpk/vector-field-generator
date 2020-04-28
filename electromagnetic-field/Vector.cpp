#include "Vector.h"
#include <cmath>

Vector::Vector(Utils::Vector2 _tail, Utils::Vector2 _head, float length, VectorType type, float arrowAngle, float arrowLength) : head(_head), tail(_tail)
{	
	if (head == tail)
		isValid = false;

	switch (type)
	{
	case VectorType::scaled:
		head = (head - tail) * length + tail;
		break;
	case VectorType::fixed:
		head = (head - tail).normalised() * length + tail;
		break;
	case VectorType::constrained:
		if (head.length() > length)
		{
			head = (head - tail).normalised() * length + tail;
		}
		break;
	}

	arrowPoint1 = calculateArrow(arrowAngle, arrowLength);
	arrowPoint2 = calculateArrow(-arrowAngle, arrowLength);
}

Utils::Vector2 Vector::calculateArrow(float arrowAngle, float arrowLength)
{
	Utils::Vector2 tempVar = (tail - head).normalised();
	Utils::Vector2 arrowPoint = {
		std::cos(arrowAngle) * tempVar.x - std::sin(arrowAngle) * tempVar.y,
		std::sin(arrowAngle) * tempVar.x + std::cos(arrowAngle) * tempVar.y
	};

	arrowPoint.normalise();
	arrowPoint *= arrowLength;

	return arrowPoint;
}
