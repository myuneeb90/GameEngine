#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3d
{
	public:
			double X;
			double Y;
			double Z;
	public:
			Vector3d() : X(0), Y(0), Z(0) {}
			Vector3d(double x, double y, double z) : X(x), Y(y), Z(z) {}
			~Vector3d() {}

			// Operators
			Vector3d operator+(const Vector3d &v) const
			{
				return Vector3d(this->X + v.X, this->Y + v.Y, this->Z + v.Z);
			}

			Vector3d operator-(const Vector3d &v) const
			{
				return Vector3d(this->X - v.X, this->Y - v.Y, this->Z - v.Z);
			}

			Vector3d operator*(double scalar) const
			{
				return Vector3d(this->X * scalar, this->Y * scalar, this->Z * scalar);
			}

			void operator=(const Vector3d &v)
			{
				this->X = v.X;
				this->Y = v.Y;
				this->Z = v.Z;
			}

			Vector3d operator+=(const Vector3d &v)
			{
				this->X = X + v.X;
				this->Y = Y + v.Y;
				this->Z = Z + v.Z;

				return Vector3d(X, Y, Z);
			}

			Vector3d operator-=(const Vector3d &v)
			{
				this->X = X - v.X;
				this->Y = Y - v.Y;
				this->Z = Z - v.Z;

				return Vector3d(X, Y, Z);
			}

			bool operator==(const Vector3d &v) const
			{
				return (this->X == v.X && this->Y == v.Y && this->Z == v.Z);
			}

			// Functions
			double Length()
			{
				return sqrtf((this->X * this->X) + (this->Y * this->Y) + (this->Z * this->Z));
			}

			Vector3d Normalize()
			{
				double length = this->Length();

				X /= length;
				Y /= length;
				Z /= length;

				return *this;
			}

			double Dot(const Vector3d &v) const
			{
				return (this->X * v.X + this->Y * v.Y + this->Z + v.Z);
			}

			static double Dot(const Vector3d &v1, const Vector3d &v2)
			{
				return (v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z);
			}

			Vector3d Cross(const Vector3d &v) const
			{
				return Vector3d(this->Y * v.Z - this->Z * v.Y,
								this->Z * v.X - this->X * v.Z,
								this->X * v.Y - this->Y * v.X);
			}

			static Vector3d Cross(const Vector3d &v1, const Vector3d &v2)
			{
				return Vector3d(v1.Y * v2.Z - v1.Z * v2.Y,
								v1.Z * v2.X - v1.X * v2.Z,
								v1.X * v2.Y - v1.Y * v2.X);
			}		

			static double Distance(const Vector3d &v1, const Vector3d &v2)
			{
				return sqrt((v1.X - v2.X) * (v1.X - v2.X) + 
							(v1.Y - v2.Y) * (v1.Y - v2.Y) + 
							(v1.Z - v2.Z) * (v1.Z - v2.Z));
			}

			static Vector3d Lerp(Vector3d start, Vector3d end, float percent)
			{
				return (start + (end - start) * percent);
			}
};

#endif