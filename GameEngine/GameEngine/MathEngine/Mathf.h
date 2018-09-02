#ifndef MATHLIB_H
#define MATHLIB_H

class Vector3f;
class Matrix4x4f;
class Quaternion;

class Mathf
{
	public:
		   const static float PI;
		   const static float PIOVER180;
		   const static float PIUNDER180;
	public:
		   static float DegreeToRadian(float angle);
		   static float RadianToDegree(float angle);
		   static Vector3f CubeToSphereMapping(Vector3f v);
		   static int RandomRange(int min, int max);
		   static float RandomRange(float min, float max);
		   static Vector3f CirclePoint(float radius, float angle);
		   static float Lerp(float a, float b, float t);
		   
};

#endif