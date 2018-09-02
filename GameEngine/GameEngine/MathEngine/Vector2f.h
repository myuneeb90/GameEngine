#ifndef VECTOR2F_H
#define VECTOR2F_H

class Vector2f
{
	public:
			float X;
			float Y;
	public:
		    Vector2f() : X(0), Y(0) {}
			Vector2f(float x, float y) : X(x), Y(y) {}
			~Vector2f() {}

			Vector2f operator-(const Vector2f &v) const
			{
				return Vector2f(this->X - v.X, this->Y - v.Y);
			}
};

#endif