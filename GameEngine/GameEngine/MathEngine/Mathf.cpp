#include "CoreEngine/AppMain.h"

const float Mathf::PI = 3.1415926535897932384626433832795f;
const float Mathf::PIOVER180 = 0.0174532925199432957692369076848861f;
const float Mathf::PIUNDER180 = 57.2957795130823208767981548141052f;

float Mathf::DegreeToRadian(float angle)
{
	return (angle * PIOVER180);
}

float Mathf::RadianToDegree(float angle)
{
	return (angle * PIUNDER180);
}

Vector3f Mathf::CubeToSphereMapping(Vector3f v)
{
	Vector3f finalVertex = Vector3f(v.X * sqrt(1 - ((v.Y * v.Y) / 2) - ((v.Z * v.Z) / 2) + (((v.Y * v.Y) * (v.Z * v.Z)) / 3)),
								    v.Y * sqrt(1 - ((v.Z * v.Z) / 2) - ((v.X * v.X) / 2) + (((v.Z * v.Z) * (v.X * v.X)) / 3)),
									v.Z * sqrt(1 - ((v.X * v.X) / 2) - ((v.Y * v.Y) / 2) + (((v.X * v.X) * (v.Y * v.Y)) / 3)));
	return finalVertex;
}

int Mathf::RandomRange(int min, int max)
{
	return rand() % max + min;
}

float Mathf::RandomRange(float min, float max)
{
	return min + static_cast<float> (rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

Vector3f Mathf::CirclePoint(float radius, float angle)
{
	return Vector3f(radius * cos(Mathf::DegreeToRadian(angle)),
					0,
					radius * sin(Mathf::DegreeToRadian(angle)));
}

float Mathf::Lerp(float a, float b, float t)
{
	return (a + t * (b - a));
}

