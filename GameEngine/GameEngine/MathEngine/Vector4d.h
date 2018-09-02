#ifndef VECTOR4D_H
#define VECTOR4D_H

class Vector4d
{
	public:
			double X;
			double Y;
			double Z;
			double W;
	public:
		    Vector4d() : X(0), Y(0), Z(0), W(0) {}
			Vector4d(double x, double y, double z, double w) : X(x), Y(y), Z(z), W(w) {}
			~Vector4d() {}
};

#endif