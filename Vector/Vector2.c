#include <math.h>
#include <stdlib.h>
#include "Vector2.h"
#include "log.h"

double Vector2dMagnitude(Vector2d a)
{
	return sqrt(a.x * a.x +
				a.y * a.y);
}

Vector2d Vector2dNormalize(Vector2d a)
{
	return Vector2dDivideD(a, Vector2dMagnitude(a));
}

Vector2d Vector2dAdd(Vector2d a, Vector2d b)
{
	return (Vector2d) {
		a.x + b.x,
		a.y + b.y
	};
}

Vector2d Vector2dSubtract(Vector2d a, Vector2d b)
{
	return (Vector2d) {
		a.x - b.x,
		a.y - b.y
	};
}

Vector2d Vector2dMultiplyD(Vector2d a, double b)
{
	return (Vector2d) {
		a.x * b,
		a.y * b
	};
}

Vector2d Vector2dDivideD  (Vector2d a, double b)
{
	return (Vector2d) {
		a.x / b,
		a.y / b
	};
}

Vector2d Vector2dNegate(Vector2d a)
{
	return (Vector2d) {-a.x, -a.y};
}

double Vector2dDot(Vector2d a, Vector2d b)
{
	return a.x * b.x +
		   a.y * b.y;
}

bool Vector2dEqual(Vector2d a, Vector2d b)
{
	return (a.x == b.x &&
			a.y == b.y);
}

Vector2i Vector2dRound(Vector2d a)
{
	return (Vector2i) {
		round(a.x),
		round(a.y)
	};
}

Vector2i Vector2dFloor(Vector2d a)
{
	return (Vector2i) {
		floor(a.x),
		floor(a.y)
	};
}

Vector2i Vector2iAdd(Vector2i a, Vector2i b)
{
	return (Vector2i) {
		a.x + b.x,
		a.y + b.y
	};
}

