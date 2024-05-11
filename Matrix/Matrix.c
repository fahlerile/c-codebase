#include <math.h>
#include <assert.h>
#include <stddef.h>
#include "Matrix.h"
#include "Vector/Vector4.h"

static inline Vector4d Matrix4GetColumn(Matrix4* a, size_t i)
{
	assert(i <= 3);
	return (Vector4d) {
		a->data[0][i],
		a->data[1][i],
		a->data[2][i],
		a->data[3][i]
	};
}

static inline void Matrix4SetColumn(Matrix4* a, Vector4d column, size_t i)
{
	assert(i <= 3);
	a->data[0][i] = column.x;
	a->data[1][i] = column.y;
	a->data[2][i] = column.z;
	a->data[3][i] = column.w;
}

bool Matrix4Equal(Matrix4* a, Matrix4* b)
{
	return (a->data[0][0] == b->data[0][0] &&
			a->data[0][1] == b->data[0][1] &&
			a->data[0][2] == b->data[0][2] &&
			a->data[0][3] == b->data[0][3] &&
			a->data[1][0] == b->data[1][0] &&
			a->data[1][1] == b->data[1][1] &&
			a->data[1][2] == b->data[1][2] &&
			a->data[1][3] == b->data[1][3] &&
			a->data[2][0] == b->data[2][0] &&
			a->data[2][1] == b->data[2][1] &&
			a->data[2][2] == b->data[2][2] &&
			a->data[2][3] == b->data[2][3] &&
			a->data[3][0] == b->data[3][0] &&
			a->data[3][1] == b->data[3][1] &&
			a->data[3][2] == b->data[3][2] &&
			a->data[3][3] == b->data[3][3]);
}

Vector4d Matrix4MultiplyVector4d(Matrix4* a, Vector4d b)
{
	Vector4d res = {0};
	for (size_t i = 0; i < 4; i++)
	{
		res = Vector4dAdd(res, Vector4dMultiplyD(
			Matrix4GetColumn(a, i), Vector4dIndex(&b, i)
		));
	}
	return res;
}

Vector4d Matrix4MultiplyVector4dHomogeneous(Matrix4* a, Vector4d b)
{
	Vector4d homogenous = Matrix4MultiplyVector4d(a, b);
	Vector3d res = Vector4dHomogenousDivide(homogenous);
	return (Vector4d) {
		res.x, res.y, res.z, 1.
	};
}

Matrix4 Matrix4MultiplyMatrix4(Matrix4* a, Matrix4* b)
{
	Matrix4 res = {0};
	for (size_t i = 0; i < 4; i++)
	{
		Vector4d column = Matrix4MultiplyVector4d(a, Matrix4GetColumn(b, i));
		Matrix4SetColumn(&res, column, i);
	}
	return res;
}

Matrix4 Matrix4ConstructIdentity()
{
	Matrix4 res = {
		.data = {
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
		}
	};
	return res;
}

Matrix4 Matrix4ConstructScale(Vector3d scale)
{
	Matrix4 res = {
		.data = {
			{scale.x,		0,		 0, 0},
			{	   0, scale.y,		 0, 0},
			{	   0,		0, scale.z, 0},
			{	   0,		0,		 0, 1}
		}
	};
	return res;
}

Matrix4 Matrix4ConstructTranslate(Vector3d trans)
{
	Matrix4 res = {
		.data = {
			{1, 0, 0, trans.x},
			{0, 1, 0, trans.y},
			{0, 0, 1, trans.z},
			{0, 0, 0,		1}
		}
	};
	return res;
}

Matrix4 Matrix4ConstructRotate(Vector3d rot)
{
	Matrix4 res = {0};
	res.data[0][0] = cos(rot.y) * cos(rot.z);
	res.data[0][1] = sin(rot.x) * sin(rot.y) * cos(rot.z) - cos(rot.x) * sin(rot.z);
	res.data[0][2] = cos(rot.x) * sin(rot.y) * cos(rot.z) + sin(rot.x) * sin(rot.z);
	res.data[0][3] = 0;
	res.data[1][0] = cos(rot.y) * sin(rot.z);
	res.data[1][1] = sin(rot.x) * sin(rot.y) * sin(rot.z) + cos(rot.x) * cos(rot.z);
	res.data[1][2] = cos(rot.x) * sin(rot.y) * sin(rot.z) - sin(rot.x) * cos(rot.z);
	res.data[1][3] = 0;
	res.data[2][0] = -sin(rot.y);
	res.data[2][1] = sin(rot.x) * cos(rot.y);
	res.data[2][2] = cos(rot.x) * cos(rot.y);
	res.data[2][3] = 0;
	res.data[3][0] = 0;
	res.data[3][1] = 0;
	res.data[3][2] = 0;
	res.data[3][3] = 1;
	return res;
}

Matrix4 Matrix4ConstructTRS(Vector3d trans, Vector3d rot, Vector3d scale)
{
	Matrix4 T = Matrix4ConstructTranslate(trans);
	Matrix4 R = Matrix4ConstructRotate(rot);
	Matrix4 S = Matrix4ConstructScale(scale);
	Matrix4 RS = Matrix4MultiplyMatrix4(&R, &S);
	return Matrix4MultiplyMatrix4(&T, &RS);
}

Matrix4 Matrix4ConstructView(Vector3d trans, Vector3d rot, Vector3d scale)
{
	return Matrix4ConstructTRS(Vector3dNegate(trans), Vector3dNegate(rot), scale);
}

// Construct matrix that transforms everything inside specified rectangular parallelepiped to unit cube (min: (-1, -1, -1), max: (1, 1, 1))
Matrix4 Matrix4ConstructOrthogonalProjection(
	double x_min, double x_max,
	double y_min, double y_max,
	double z_min, double z_max
)
{
	Matrix4 res = {0};
	res.data[0][0] = 2 / (x_max - x_min);
	res.data[0][1] = 0;
	res.data[0][2] = 0;
	res.data[0][3] = -(x_max + x_min) / (x_max - x_min);
	res.data[1][0] = 0;
	res.data[1][1] = 2 / (y_max - y_min);
	res.data[1][2] = 0;
	res.data[1][3] = -(y_max + y_min) / (y_max - y_min);
	res.data[2][0] = 0;
	res.data[2][1] = 0;
	res.data[2][2] = 2 / (z_max - z_min);
	res.data[2][3] = -(z_max + z_min) / (z_max - z_min);
	res.data[3][0] = 0;
	res.data[3][1] = 0;
	res.data[3][2] = 0;
	res.data[3][3] = 1;
	return res;
}

Matrix4 Matrix4ConstructPerspectiveProjection(
	double x_min_near, double x_max_near,
	double y_min_near, double y_max_near,
	double z_near, double z_far
)
{
	Matrix4 perspective = {0};
	perspective.data[0][0] = z_near;
	perspective.data[0][1] = 0;
	perspective.data[0][2] = 0;
	perspective.data[0][3] = 0;
	perspective.data[1][0] = 0;
	perspective.data[1][1] = z_near;
	perspective.data[1][2] = 0;
	perspective.data[1][3] = 0;
	perspective.data[2][0] = 0;
	perspective.data[2][1] = 0;
	perspective.data[2][2] = z_near + z_far;
	perspective.data[2][3] = -z_near * z_far;
	perspective.data[3][0] = 0;
	perspective.data[3][1] = 0;
	perspective.data[3][2] = 1;
	perspective.data[3][3] = 0;

	Matrix4 orthogonal = Matrix4ConstructOrthogonalProjection(
		x_min_near, x_max_near,
		y_min_near, y_max_near,
		z_near, z_far
	);

	return Matrix4MultiplyMatrix4(&orthogonal, &perspective);
}

