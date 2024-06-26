#include <math.h>
#include <stdlib.h>
#include "Vector3.h"
#include "log.h"

double Vector3dMagnitude(Vector3d a)
{
	return sqrt(a.x * a.x +
				a.y * a.y +
				a.z * a.z);
}

Vector3d Vector3dNormalize(Vector3d a)
{
	return Vector3dDivideD(a, Vector3dMagnitude(a));
}

Vector3d Vector3dAdd(Vector3d a, Vector3d b)
{
	return (Vector3d) {
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
	};
}

Vector3d Vector3dSubtract(Vector3d a, Vector3d b)
{
	return (Vector3d) {
		a.x - b.x,
		a.y - b.y,
		a.z - b.z
	};
}

Vector3d Vector3dMultiplyD(Vector3d a, double b)
{
	return (Vector3d) {
		a.x * b,
		a.y * b,
		a.z * b
	};
}

Vector3d Vector3dDivideD(Vector3d a, double b)
{
	return (Vector3d) {
		a.x / b,
		a.y / b,
		a.z / b
	};
}

Vector3d Vector3dNegate(Vector3d a)
{
	return (Vector3d) {
		-a.x,
		-a.y,
		-a.z
	};
}

double Vector3dDot(Vector3d a, Vector3d b)
{
	return a.x * b.x +
		   a.y * b.y +
		   a.z * b.z;
}

Vector3d Vector3dCross(Vector3d a, Vector3d b)
{
	return (Vector3d) {
		a.y * b.z - a.z * b.y,
		a.x * b.z - a.z * b.x,
		a.x * b.y - a.y * b.x
	};
}

bool Vector3dEqual(Vector3d a, Vector3d b)
{
	return (a.x == b.x &&
			a.y == b.y &&
			a.z == b.z);
}

Vector3d Vector3dZeroZ(Vector3d a)
{
	return (Vector3d) {
		a.x, a.y, 0
	};
}

Vector4d Vector3dToVector4dHomogenous(Vector3d a)
{
	return (Vector4d) {
		a.x, a.y, a.z, 1.
	};
}

