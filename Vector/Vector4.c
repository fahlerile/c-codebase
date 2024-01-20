#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "Vector4.h"
#include "log.h"

double Vector4dMagnitude(Vector4d a)
{
    return sqrt(a.x * a.x +
                a.y * a.y +
                a.z * a.z +
                a.w * a.w);
}

Vector4d Vector4dNormalize(Vector4d a)
{
    return Vector4dDivideD(a, Vector4dMagnitude(a));
}

Vector4d Vector4dAdd(Vector4d a, Vector4d b)
{
    return (Vector4d) {
        a.x + b.x,
        a.y + b.y,
        a.z + b.z,
        a.w + b.w
    };
}

Vector4d Vector4dSubtract(Vector4d a, Vector4d b)
{
    return (Vector4d) {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z,
        a.w - b.w
    };
}

Vector4d Vector4dMultiplyD(Vector4d a, double b)
{
    return (Vector4d) {
        a.x * b,
        a.y * b,
        a.z * b,
        a.w * b
    };
}

Vector4d Vector4dDivideD(Vector4d a, double b)
{
    return (Vector4d) {
        a.x / b,
        a.y / b,
        a.z / b,
        a.w / b
    };
}

Vector4d Vector4dNegate(Vector4d a)
{
    return (Vector4d) {
        -a.x,
        -a.y,
        -a.z,
        -a.w
    };
}

double Vector4dDot(Vector4d a, Vector4d b)
{
    return a.x * b.x +
           a.y * b.y +
           a.z * b.z +
           a.w * b.w;
}

Vector3d Vector4dHomogenousDivide(Vector4d a)
{
    Vector4d res = Vector4dDivideD(a, a.w);
    return (Vector3d) {
        res.x, res.y, res.z
    };
}

Color Vector4dToColor(Vector4d a)
{
    assert(a.x >= 0 && a.y >= 0 && a.z >= 0 && a.w >= 0);
    Vector4d temp = Vector4dMultiplyD(a, 255.);
    return (Color) {
        round(temp.x),
        round(temp.y),
        round(temp.z),
        round(temp.w)
    };
}

double Vector4dIndex(Vector4d a, size_t i)
{
    switch (i)
    {
        case 0:
            return a.x;
        case 1:
            return a.y;
        case 2:
            return a.z;
        case 3:
            return a.w;
        default:
            LOGE("Vector4d invalid index %zu", i);
            abort();
    }
}

bool Vector4dEqual(Vector4d a, Vector4d b)
{
    return (a.x == b.x &&
            a.y == b.y &&
            a.z == b.z &&
            a.w == b.w);
}
