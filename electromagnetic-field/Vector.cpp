#include "Vector.h"
#include <cmath>

Vector::Vector(Utils::Vector2 _tail, Utils::Vector2 _head, float _length, VectorType _type, float _scale, float _arrowAngle, float _arrowProportion) : 
	head(_head), tail(_tail), length(_length), type(_type), scale(_scale), arrowAngle(_arrowAngle), arrowProportion(_arrowProportion)
{	
	generate();
}

void Vector::generate()
{

	if (head == tail)
		isValid = false;
	else
		isValid = true;

	if (length != lastLength)
	{
		switch (type)
		{
		case VectorType::normal:
			calculatedHead = (head - tail) * scale + tail;
			break;
		case VectorType::fixed:
			calculatedHead = (head - tail).normalised() * length + tail;
			break;
		case VectorType::constrained:
			calculatedHead = (head - tail) * scale + tail;
			if ((head - tail).length() > length)
				calculatedHead = (calculatedHead - tail).normalised() * length + tail;
			break;
		}
	}

	lastLength = length;

	calculateArrow();
}

void Vector::calculateArrow()
{
	Utils::Vector2 tempVar = (tail - head).normalised();
	arrowPoint1 = {
		std::cos(arrowAngle) * tempVar.x - std::sin(arrowAngle) * tempVar.y,
		std::sin(arrowAngle) * tempVar.x + std::cos(arrowAngle) * tempVar.y
	};
	arrowPoint2 = {
		std::cos(-arrowAngle) * tempVar.x - std::sin(-arrowAngle) * tempVar.y,
		std::sin(-arrowAngle) * tempVar.x + std::cos(-arrowAngle) * tempVar.y
	};

	arrowPoint1.normalise();
	arrowPoint1 *= (calculatedHead - tail).length() * arrowProportion;
	arrowPoint2.normalise();
	arrowPoint2 *= (calculatedHead - tail).length() * arrowProportion;
}
