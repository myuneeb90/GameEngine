#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2d
{
	public:
			double X;
			double Y;
	public:
		    Vector2d() : X(0), Y(0) {}
			Vector2d(double x, double y) : X(x), Y(y) {}
			~Vector2d() {}

			Vector2d operator-(const Vector2d &v) const
			{
				return Vector2d(this->X - v.X, this->Y - v.Y);
			}
};

#endif