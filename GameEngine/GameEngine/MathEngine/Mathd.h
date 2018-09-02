#ifndef MATHD_H
#define MATHD_H

class Vector3d;
class Matrix4x4d;

class Mathd
{
	public:
		   const static double PI;
		   const static double PIOVER180;
		   const static double PIUNDER180;
	public:
		   static double DegreeToRadian(double angle);
		   static double RadianToDegree(double angle);
		   static Vector3d CubeToSphereMapping(Vector3d v);
		   static double RandomRange(double min, double max);
		   static Vector3d CirclePoint(double radius, double angle);
};

#endif