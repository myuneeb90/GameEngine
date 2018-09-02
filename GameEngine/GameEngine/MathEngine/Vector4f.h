#ifndef VECTOR4F_H
#define VECTOR4F_H

class Vector4f
{
	public:
			float X;
			float Y;
			float Z;
			float W;
	public:
		    Vector4f() : X(0), Y(0), Z(0), W(0) {}
			Vector4f(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}
			~Vector4f() {}
			
			static Vector4f Cross(Vector4f v1, Vector4f v2, Vector4f v3)
			{
				Vector4f res;

				res.X =   v1.Y * (v2.Z * v3.W - v3.Z * v2.W) - v1.Z * (v2.Y * v3.W - v3.Y * v2.W) + v1.W * (v2.Y * v3.Z - v2.Z * v3.Y);
				res.Y = -(v1.X * (v2.Z * v3.W - v3.Z * v2.W) - v1.Z * (v2.X * v3.W - v3.X * v2.W) + v1.W * (v2.X * v3.Z - v3.X * v2.Z));
				res.Z =   v1.X * (v2.Y * v3.W - v3.Y * v2.W) - v1.Y * (v2.X * v3.W - v3.X * v2.W) + v1.W * (v2.X * v3.Y - v3.X * v2.Y);
				res.W = -(v1.X * (v2.Y * v3.Z - v3.Y * v2.Z) - v1.Y * (v2.X * v3.Z - v3.X * v2.Z) + v1.Z * (v2.X * v3.Y - v3.X * v2.Y));
			
				return res;
			}
};

#endif