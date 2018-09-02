#include "CoreEngine/AppMain.h"

const double Mathd::PI = 3.1415926535897932384626433832795f;
const double Mathd::PIOVER180 = 0.0174532925199432957692369076848861f;
const double Mathd::PIUNDER180 = 57.2957795130823208767981548141052f;

double Mathd::DegreeToRadian(double angle)
{
	return (angle * PIOVER180);
}

double Mathd::RadianToDegree(double angle)
{
	return (angle * PIUNDER180);
}

Vector3d Mathd::CubeToSphereMapping(Vector3d v)
{
	Vector3d finalVertex = Vector3d(v.X * sqrt(1 - ((v.Y * v.Y) / 2) - ((v.Z * v.Z) / 2) + (((v.Y * v.Y) * (v.Z * v.Z)) / 3)),
								    v.Y * sqrt(1 - ((v.Z * v.Z) / 2) - ((v.X * v.X) / 2) + (((v.Z * v.Z) * (v.X * v.X)) / 3)),
									v.Z * sqrt(1 - ((v.X * v.X) / 2) - ((v.Y * v.Y) / 2) + (((v.X * v.X) * (v.Y * v.Y)) / 3)));
	return finalVertex;
}

double Mathd::RandomRange(double min, double max)
{
	return rand() % (int)max + min;
}

Vector3d Mathd::CirclePoint(double radius, double angle)
{
	return Vector3d(radius * cos(Mathf::DegreeToRadian(angle)),
					0,
					radius * sin(Mathf::DegreeToRadian(angle)));
}